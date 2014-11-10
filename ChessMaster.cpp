#include "ChessMaster.h"

ChessMaster::ChessMaster(int nrStyle): nrFieldStyle(nrStyle)
{
// Zeruje wskaznik na powierzchnie graficzna
    screen=NULL;
// Zeruje wskaznik na powierzchnie graficzna
    chessBoard=NULL;
// Nadaje poczatkowa wartosc zmienej odpowiedzialnej za przebieg petli glownej programu.
    quit=false;
// Zeruje wskaznik do tablicy dwuwymiarowej obiektow Field.
    pBoard=NULL;

// Tworzenie dwu wymiarowej tablicy stringow, wykorzystywanej do przechowywania sciezek do plikow zgrafika.
// po dwa pliki dla kazdego stylu, odpowiadaja. Odpwiednio 0 dla pola czarnego i 1 dla pola bialego.
    fieldStyle=new string*[nrFieldStyle];
    fieldStyle[0]=new string[nrFieldStyle*2];
    for(int i=1;i<nrFieldStyle;++i)
        fieldStyle[i]=&fieldStyle[0][i*2];

// Wpypelnieni tablicy sciezkami do plikow.
    fieldStyle[0][0]="grafika/marble00.bmp";
    fieldStyle[0][1]="grafika/marble01.bmp";
    fieldStyle[1][0]="grafika/marble02.bmp";
    fieldStyle[1][1]="grafika/marble03.bmp";
    fieldStyle[2][0]="grafika/metal00.bmp";
    fieldStyle[2][1]="grafika/metal01.bmp";
    fieldStyle[3][0]="grafika/wood00.bmp";
    fieldStyle[3][1]="grafika/wood01.bmp";
    fieldStyle[4][0]="grafika/wood02.bmp";
    fieldStyle[4][1]="grafika/wood03.bmp";
    chessmanCollection.reserve(nrChassman);
    activeMoves=false;
    activeChessman.x=100;
    activeChessman.y=100;
    pActiveChessman=NULL;
    blackKing=NULL;
    whiteKing=NULL;
    activeTeam=white;
    activeTeamKing=whiteKing;


}
//***********************************************************************************
ChessMaster::~ChessMaster()
{
// Zwalnie pamieci ktore zjamowaly sciezki do stylow graficznych planszy.
    delete [] fieldStyle[0];
    delete [] fieldStyle;
// Zwalnia pamiec ktora zajmowaly figury.
    vector<Chessman*>::iterator iterEnd;
    iterEnd = chessmanCollection.end();
    //for (vector<Chessman*>::iterator iterBegin= chessmanCollection.begin(); iterBegin != iterEnd; ++iterBegin){
        while (!chessmanCollection.empty()) {
            if(chessmanCollection.back()!=NULL)
                delete chessmanCollection.back();
            chessmanCollection.pop_back();
        }
   // }
// Zwalnie pamieci ktora zajmowaly pola
    delete [] pBoard[0];
    delete [] pBoard;




// Zwalnia pamiec w ktorej byla przechowywana szachownica.
    SDL_FreeSurface(chessBoard);
// Konczy dzialanie biblioteki SDL.
    SDL_Quit();

}
//***********************************************************************************
int ChessMaster::InitSDL(
                bool fullScreen,
                int screenResolutionX,
                int screenResolutionY,
                int screenDeepColor
            )
{
// Towrze glowna powierzchnie graficzna na ktorej bedzie wyswietlana cala gra/
    if(SDL_Init(SDL_INIT_EVERYTHING)) // Aktywuje SDL-a z wszystkimi podsystemami.
// Jak aktywacja sie nie udala konczy funkcjie i zwraca -1
        return -1;

// Towrzy glowna powierzchnie graficzna na ktorej bedzie wyswietlana cala gra
    if(fullScreen)
        screen=SDL_SetVideoMode(screenResolutionX,screenResolutionY,screenDeepColor,SDL_DOUBLEBUF|SDL_HWSURFACE|SDL_FULLSCREEN);
    else
        screen=SDL_SetVideoMode(screenResolutionX,screenResolutionY,screenDeepColor,SDL_DOUBLEBUF|SDL_HWSURFACE);
// Sprawdza czy udalo sie stworzyc powierzchnie graficzna o zadanych parametrach.
    if(screen==NULL)
// Gdy sie nie udalo stworzyc powierzchni graficznej konczy funkcjie i zwraca 0.
        return 0;
// Ustawiamy tytul okienka w ktorym dziala program
    SDL_WM_SetCaption( "ChessGame by Jacek Hojczak", NULL );


return 1;
}
//***********************************************************************************
int ChessMaster::ConfigureBoard(int typeStyle,
                                const char* patchToBoardGrafic,
                                int sizeBoardX,
                                int sizeBoardY
                                )
{
//Tworzy tablice dwu wymiarow� typu wskaznik do Field.
int noFieldInGame=sizeBoardX*sizeBoardY;
    pBoard=new Field**[sizeBoardY];
    pBoard[0]=new Field*[noFieldInGame];
    for(int i=1;i<sizeBoardY;++i){
        pBoard[i]=&pBoard[0][i*sizeBoardX];
    }
// Tworzy obiekty w tablicy ktora repreznetuje pole gry.
    for(int y=0;y<sizeBoardY;++y){
        for(int x=0;x<sizeBoardX;++x){
            if((x+y)%2)
                pBoard[y][x]=new Field(y,x,fieldStyle[typeStyle][0].c_str());
            else
                pBoard[y][x]=new Field(y,x,fieldStyle[typeStyle][1].c_str());

        }
    }

// Laduje obraz szachownicy do pomocniczej powierzchni.
    SDL_Surface* help00=IMG_Load(patchToBoardGrafic);
// Sprawdza czy udalo sie zaladowanie obrazu
    if(help00==NULL)
// Gdy w powierzchnie nie ma obrazu konczy funkcje i zwraca -1.
        return -1;
// Konwertuje obraz na typ formatu glownej powierzchni graficznej.
    chessBoard=SDL_DisplayFormat(help00);
    SDL_SetColorKey(chessBoard,SDL_SRCCOLORKEY, SDL_MapRGB( chessBoard->format, 255, 0 , 255 ));
// Rysuje szachownice na glownej powierzchni graficznej.
    SDL_BlitSurface(chessBoard,NULL,screen,NULL);
// Wyswietla glowna powierzchnie graficzna.
    SDL_Flip(screen);
// Zwalnia pamieci nie potrzebna powierzchnie graficzna.
    SDL_FreeSurface(help00);

// Wyswietla pokolej kazde pole planszy. Specjalnie wyswietlanie pojedynicze.
    for(int i=0;i<sizeBoardX*sizeBoardY;++i){
        pBoard[0][i]->ShowField(screen);
        SDL_Flip(screen);
    }


// Utworzenie figur w tablicy wskaznikow
    chessmanCollection.push_back(new Man(6,7,"grafika/Figure/Marine.bmp",black,pBoard[6][7]));
    chessmanCollection.push_back(new Man(6,6,"grafika/Figure/Marine.bmp",black,pBoard[6][6]));
    chessmanCollection.push_back(new Man(6,5,"grafika/Figure/Marine.bmp",black,pBoard[6][5]));
    chessmanCollection.push_back(new Man(6,4,"grafika/Figure/Marine.bmp",black,pBoard[6][4]));
    chessmanCollection.push_back(new Man(6,3,"grafika/Figure/Marine.bmp",black,pBoard[6][3]));
    chessmanCollection.push_back(new Man(6,2,"grafika/Figure/Marine.bmp",black,pBoard[6][2]));
    chessmanCollection.push_back(new Man(6,1,"grafika/Figure/Marine.bmp",black,pBoard[6][1]));
    chessmanCollection.push_back(new Man(6,0,"grafika/Figure/Marine.bmp",black,pBoard[6][0]));
    chessmanCollection.push_back(new Tower(7,0,"grafika/Figure/SiegeTank.bmp",black,pBoard[7][0]));
    chessmanCollection.push_back(new Tower(7,7,"grafika/Figure/SiegeTank.bmp",black,pBoard[7][7]));
    chessmanCollection.push_back(new Knight(7,1,"grafika/Figure/Hellion.bmp",black,pBoard[7][1]));
    chessmanCollection.push_back(new Knight(7,6,"grafika/Figure/Hellion.bmp",black,pBoard[7][6]));
    chessmanCollection.push_back(new Bishop(7,2,"grafika/Figure/Marauder.bmp",black,pBoard[7][2]));
    chessmanCollection.push_back(new Bishop(7,5,"grafika/Figure/Marauder.bmp",black,pBoard[7][5]));
    chessmanCollection.push_back(new Queen(7,4,"grafika/Figure/Battlecruiser.bmp",black,pBoard[7][4]));
    blackKing=(new King(7,3,"grafika/Figure/Ghost.bmp",black,pBoard[7][3]));


    chessmanCollection.push_back(new Man(1,7,"grafika/Figure/Zealot.bmp",white,pBoard[1][7]));
    chessmanCollection.push_back(new Man(1,6,"grafika/Figure/Zealot.bmp",white,pBoard[1][6]));
    chessmanCollection.push_back(new Man(1,5,"grafika/Figure/Zealot.bmp",white,pBoard[1][5]));
    chessmanCollection.push_back(new Man(1,4,"grafika/Figure/Zealot.bmp",white,pBoard[1][4]));
    chessmanCollection.push_back(new Man(1,3,"grafika/Figure/Zealot.bmp",white,pBoard[1][3]));
    chessmanCollection.push_back(new Man(1,2,"grafika/Figure/Zealot.bmp",white,pBoard[1][2]));
    chessmanCollection.push_back(new Man(1,1,"grafika/Figure/Zealot.bmp",white,pBoard[1][1]));
    chessmanCollection.push_back(new Man(1,0,"grafika/Figure/Zealot.bmp",white,pBoard[1][0]));
    chessmanCollection.push_back(new Tower(0,0,"grafika/Figure/Immortal.bmp",white,pBoard[0][0]));
    chessmanCollection.push_back(new Tower(0,7,"grafika/Figure/Immortal.bmp",white,pBoard[0][7]));
    chessmanCollection.push_back(new Knight(0,1,"grafika/Figure/Colossus.bmp",white,pBoard[0][1]));
    chessmanCollection.push_back(new Knight(0,6,"grafika/Figure/Colossus.bmp",white,pBoard[0][6]));
    chessmanCollection.push_back(new Bishop(0,2,"grafika/Figure/PhasePrismPhasing.bmp",white,pBoard[0][2]));
    chessmanCollection.push_back(new Bishop(0,5,"grafika/Figure/PhasePrismPhasing.bmp",white,pBoard[0][5]));
    chessmanCollection.push_back(new Queen(0,3,"grafika/Figure/Archon.bmp",white,pBoard[0][3]));
    whiteKing=(new King(0,4,"grafika/Figure/HighTemplar.bmp",white,pBoard[0][4]));




return 1;
}
//***********************************************************************************
int ChessMaster::Menu()
{
    if(event.key.keysym.sym==SDLK_ESCAPE){
        quit=true;
        return 0;
    }

return 1;
}
//***********************************************************************************
int ChessMaster::MouseHandling()
{
// Wylapanie kliknieca myszy
    if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
            if(event.button.x >= Field::fieldOffset && event.button.x < Field::fieldSizeX*sizeChessBoard+Field::fieldOffset){
                if(event.button.y >= Field::fieldOffset && event.button.y < Field::fieldSizeY*sizeChessBoard+Field::fieldOffset){
                    // zapis do zmienej.
                    mousePosition.x=(event.button.x-Field::fieldOffset)/Field::fieldSizeX;
                    mousePosition.y=(event.button.y-Field::fieldOffset)/Field::fieldSizeY;
                    mousePosition.h=Field::fieldSizeY;
                    mousePosition.w=Field::fieldSizeX;
                    return 1;
                }
            }
        }
    }

return 0;
}

//***********************************************************************************
void ChessMaster::Start()
{
// Aktywuje biblioteki SDL-a.
   int error=InitSDL(0);
// Konfiguruje ustawaienie planszy.
    ConfigureBoard(1);
// pokazuje figure na ekranie.

    ShowAllChessman();
    GenerateMovesList();
    GameRuning();
}
int ChessMaster::GameRuning(int flag){

    while(!quit){
        if(SDL_PollEvent(&event)){
            if(Menu()){
                if(MouseHandling()){
// Wyswietla na ekranie mozliwe ruchy aktywenej figury.
                    if(ShowActiveMoves()){
                        GenerateMovesList();
                        if(CheckMate()){
                            if(IsMate()){
                            quit=true;
                            }
                        }
                    }
                }
            }
        }
        SDL_Delay(20);
    }
return 1;
}
//*******************************************************************************
int ChessMaster::ShowActiveMoves(){
// Lokalna do ktorej przepisze sie polozenie figury po przeliczeniu pozycji na pixele.
SDL_Rect PosInPx;
// Lokalny wskaznik do figury uzywany do operacji na wskazanej figurze.

    if(activeMoves){
// Sprawdza czy klikniece nastapilo na aktywnej figurzee, jesli tak deaktywuje j�.
        if(activeChessman.x == mousePosition.x && activeChessman.y == mousePosition.y){
// Deaktywacja aktywnosci.
            activeMoves=false;
// Rysuje pole na ktorym stoi figura.
            pBoard[activeChessman.y][activeChessman.x]->ShowField(screen);
// Dla wygody przepisanie wskaznika do wskaznika lokanego i jednoczesnie konwersja wskaznikan a typ umozliwajacy prace z figura.
            pActiveChessman=dynamic_cast<Chessman*>(pBoard[activeChessman.y][activeChessman.x]->figureOnField);
// Odrysowanie figury na ekranie.
            pActiveChessman->ShowField(screen);
// Odrysowanie pol na ktore byly zaznaczane jako mozliwe ruchy figury.
            for(std::list<Field*>::iterator iter=pActiveChessman->Moves.begin();iter!=pActiveChessman->Moves.end();iter++){
                (*iter)->ShowField(screen);
// Odrysowanie figur na polach ktore byly zaznaczano, o ile jakas figura stala na danym polu.
                if((*iter)->figureOnField!=NULL)
                    dynamic_cast<Chessman*>((*iter)->figureOnField)->ShowField(screen);
            }
        }
        else{
// Jak klikniecie nie bylo na aktywnej figurze to sprawdza czy nastapilo ono na ktores z mozliwych ruchow figury.
            if(pActiveChessman!=NULL){
                if(pActiveChessman->Move(pBoard[mousePosition.y][mousePosition.x],screen)){
// Odrysowanie pol na ktore byly zaznaczane jako mozliwe ruchy figury.
                    for(std::list<Field*>::iterator iter=pActiveChessman->Moves.begin();iter!=pActiveChessman->Moves.end();iter++){
                        (*iter)->ShowField(screen);
// Odryowanie figur na polach ktore byly zaznaczano, o ile jakas figura stala na danym polu.
                        if((*iter)->figureOnField!=NULL)
                            dynamic_cast<Chessman*>((*iter)->figureOnField)->ShowField(screen);
                    }
// Deaktywuje wyswietlanie mozliwych ruchow figury.
                    activeMoves=false;
                    if(activeTeam==white){
                        activeTeam= black;
                        activeTeamKing=blackKing;
                    }
                    else{
                        activeTeam=white;
                        activeTeamKing=whiteKing;
                    }
                    return 1;
                }
            }
        }
    }
// Jak zadna figura jest nie aktywna..
    else{
// Sprawdza czy na kliknietym polu stoi jakas figura..
        if(pBoard[mousePosition.y][mousePosition.x]->figureOnField!=NULL){
            activeChessman=mousePosition;
            pActiveChessman=dynamic_cast<Chessman*>(pBoard[activeChessman.y][activeChessman.x]->figureOnField);
            if(pActiveChessman->team==activeTeam){
    // Przepisuje polozenie do zmienej ktora przechowuje wspolrzedne aktualnej aktywnej figury
    // Przelicza polozenie w tablicy dwowymiarowej na polozenie na ekranie w pixelach.
                PosInPx=ConvToPX(activeChessman);
    // Zaznacza figure z u�yciem funkcji z SDL_gfx. Rysuje prostoka w wskazanym miejscu i okreslonym kolorze.
                boxRGBA(screen,PosInPx.x,PosInPx.y,PosInPx.x+PosInPx.w-1,PosInPx.y+PosInPx.h-1,0,255,0,100);
    // Dla wygody przepisanie wskaznika do wskaznika lokanego i jednoczesnie konwersja wskaznikan a typ umozliwajacy prace z figura.
                pActiveChessman=dynamic_cast<Chessman*>(pBoard[activeChessman.y][activeChessman.x]->figureOnField);
    // Spradza czy lista mozliwych ruchow figury jest pusta..

    // Jak tak generuje mozliwe ruchy fgiury.

    // Przegladanie listy mozliwych ruchow figury. W kazdym odrysowywane jest zaznaczenie pod postacia prostokatu o okreslonym kolorze.
                for(std::list<Field*>::iterator iter=pActiveChessman->Moves.begin();iter!=pActiveChessman->Moves.end();iter++){
                    boxRGBA(screen,(*iter)->position.x,(*iter)->position.y,(*iter)->position.x+(*iter)->position.w-1,(*iter)->position.y+(*iter)->position.h-1,255,255,255,100);
                }

                activeMoves=true;
                SDL_Flip(screen);
            }
            else
                pActiveChessman=NULL;
        }
    }
return 0;
}
//*******************************************************************************
SDL_Rect ChessMaster::ConvToPX(const SDL_Rect src){
// Struktura pomocnicza.
    SDL_Rect support;
// Przeliczamy indeksy tablicy na pixele i zapisujemy do zmienej pomocniczej.
    support.x = (src.x*Field::fieldSizeX)+Field::fieldOffset;
    support.y = (src.y*Field::fieldSizeY)+Field::fieldOffset;
    support.w = src.w;
    support.h = src.h;

return support;
}
//*******************************************************************************
void ChessMaster::ShowAllChessman(){
// Przygotowanie iteratorow do dzialania na vectorze w ktorym przechowane sa wszystkie figury.
    vector<Chessman*>::iterator iterBegin;
    vector<Chessman*>::iterator iterEnd;
    iterEnd = chessmanCollection.end();
// Przejscie przez caly vector wywolujac dla kazdego elemnetu funkcje wyswietlenia figury na ekranie.
    for (iterBegin= chessmanCollection.begin(); iterBegin != iterEnd; ++iterBegin)
        (*iterBegin)->ShowField(screen);

    whiteKing->ShowField(screen);
    blackKing->ShowField(screen);

}
//*******************************************************************************
void ChessMaster::CreateChessManTeam(enumTeam flag){



}
//********************************************************************************
void ChessMaster::GenerateMovesList(){

    vector<Chessman*>::iterator iterBegin;
    vector<Chessman*>::iterator iterEnd;
    iterEnd = chessmanCollection.end();

// Przejscie przez caly vector wywolujac dla kazdego elemnetu funkcje tworzaca mozliwe dozwolone ruchy.
    for (iterBegin= chessmanCollection.begin(); iterBegin != iterEnd; ++iterBegin){
        if((*iterBegin)->inGame){
            (*iterBegin)->Moves.clear();
            (*iterBegin)->GeneratePossiblyMoves(pBoard);
        }
    }
    whiteKing->Moves.clear();
    whiteKing->GeneratePossiblyMoves(pBoard,&chessmanCollection);

    blackKing->Moves.clear();
    blackKing->GeneratePossiblyMoves(pBoard,&chessmanCollection);
}
//**********************************************************************************
 bool ChessMaster::CheckMate(){

    vector<Chessman*>::iterator iterBegin;
    vector<Chessman*>::iterator iterEnd;
    iterEnd = chessmanCollection.end();

// Przejscie przez caly vector wywolujac dla kazdego elemnetu funkcje tworzaca mozliwe dozwolone ruchy.
    for (iterBegin= chessmanCollection.begin(); iterBegin != iterEnd; ++iterBegin){

        for(std::list<Field*>::iterator iterMoves=(*iterBegin)->Moves.begin();iterMoves!=(*iterBegin)->Moves.end();iterMoves++){
            if( (*iterMoves)==whiteKing->figureOnField)
                return true;
            if( (*iterMoves)==blackKing->figureOnField)
                return true;
        }
    }
return false;
}
bool ChessMaster::CheckMateSituation(){
bool quit=false;

    while(!quit){
        if(SDL_PollEvent(&event)){
            if(Menu()){
                if(MouseHandling())

                if(ShowActiveMoves()){
                    GenerateMovesList();
                    if(CheckMate()){

                    }
                    else
                    quit=true;
                }
            }
        }
        SDL_Delay(20);
    }
return true;
}
//****************************************************************************
bool ChessMaster::IsMate(){
    if(activeTeamKing->Moves.empty()){



    return true;
    }
return false;
}
//************************
bool ChessMaster::SearchPossibleKingHide(){
    vector<Chessman*>::iterator iterBegin;
    vector<Chessman*>::iterator iterEnd;
    iterEnd = chessmanCollection.end();

// Przejscie przez caly zbi�r figur, poza kr�lami.
    for (iterBegin= chessmanCollection.begin(); iterBegin != iterEnd; ++iterBegin){
        if(activeTeamKing->team!=(*iterBegin)->team){
            for(std::list<Field*>::iterator iterMoves=(*iterBegin)->Moves.begin();iterMoves!=(*iterBegin)->Moves.end();iterMoves++){
                Chessman* victim=NULL;
                Field* buffor=NULL;
                (*iterBegin)->Move((*iterMoves),victim,buffor);
                GenerateMovesList();
                if(!CheckMate()){
                    return true;
                }
                else{
                    victim->BackToGame();
                    (*iterBegin)->Move(buffor,NULL,NULL);

                }
            }
        }
    }
    return false;
}
