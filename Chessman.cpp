#include "Chessman.h"

//********************************************************************************
Chessman::Chessman():Field(),team(0)
{
// Zeruje predkosc poruszania sie figury.
    velocityChessmanY=0;
    velocityChessmanX=0;
    inGame=true;
    king=false;
}
//********************************************************************************
Chessman::~Chessman()
{

    Moves.clear();

}
//********************************************************************************
Chessman:: Chessman(int positionOnBoardX,
                    int positionOnBoardY,
                    const char* pathToImageFile,
                    int teamPlayer,
                    Field* baseField
                   ): Field(positionOnBoardX,positionOnBoardY,pathToImageFile), team(teamPlayer)
{
// Zeruje predkosc poruszania sie figury.
    velocityChessmanY=0;
    velocityChessmanX=0;
// Zapisuje wskaznik do figury w polu na ktorym stoi figura.
    baseField->figureOnField=this;
    figureOnField=baseField;
    inGame=true;
    king=false;

}
//********************************************************************************
void Chessman::ShowField(SDL_Surface* screen)
{
// Wyswitla figure na powierzchni graficznej.
    SDL_BlitSurface(fieldImage,NULL,screen,&position);
// Odsiweza ekran.
    SDL_Flip(screen);

}
//********************************************************************************
void Chessman::ChangePosition(int posBoardX,int posBoardY){
    positionOnBoardX=posBoardX;
    positionOnBoardY=posBoardY;

    position.x = (posBoardX*Field::fieldSizeX)+Field::fieldOffset;
    position.y = (posBoardY*Field::fieldSizeY)+Field::fieldOffset;

}
//********************************************************************************
int Chessman::Move(Field* src,SDL_Surface* screen)
{
// Przegladanie listy mozliwych ruchow.
    for(std::list<Field*>::iterator iter=Moves.begin();iter!=Moves.end();iter++){
    // Gdy w lisce znajduje sie ruch o takich samych wspulrzednych jakie zostaly podane do funkcji..
        if(src == (*iter)){
        // Gdy na polu jest figura przeciwnika..
            if((*iter)->figureOnField!=NULL){
                // Wyklucza figure z gry.
                dynamic_cast<Chessman*>((*iter)->figureOnField)->ChessmanOut();
                ((*iter)->figureOnField)=NULL;
            }
    // Zmienia wspulrzedne polozenia figury na planszy i w tablicy na wskazane przez argumenty w funkcji.
            ChangePosition((*iter)->positionOnBoardX,(*iter)->positionOnBoardY);
    // Odrysowuje pole na ktorym figura stala.
            figureOnField->ShowField(screen);
    // Zeruje wskaznik w polu. Pole staje sie wolne.
            figureOnField->figureOnField=NULL;
    // Przypisuje jako pole bazowe pole na ktore figura sie ruszyla.
            figureOnField=(*iter);
    // Polu bazowym przypisuje wskaznik na figure.
            figureOnField->figureOnField=this;
    // Odrysowuje figure na nowym polu.
            ShowField(screen);

            return 1;
        }
    }
return 0;
}
//******************************************************************
int Chessman::Move(Field* src,Chessman* victim,Field* positionBefor)
{
    if(src->figureOnField != NULL){
    // Wyklucza figure z gry.
        dynamic_cast<Chessman*>(src->figureOnField)->ChessmanOut();
        victim=dynamic_cast<Chessman*>(src->figureOnField);

    }
        positionBefor=figureOnField;
    // Zmienia wspulrzedne polozenia figury na planszy i w tablicy na wskazane przez argumenty w funkcji.
        ChangePosition(src->positionOnBoardX,src->positionOnBoardY);
    // Zeruje wskaznik w polu. Pole staje sie wolne.
        figureOnField->figureOnField=NULL;
    // Przypisuje jako pole bazowe pole na ktore figura sie ruszyla.
        figureOnField=src;
    // Polu bazowym przypisuje wskaznik na figure.
        figureOnField->figureOnField=this;
    // Odrysowuje figure na nowym polu.
        return 1;
}



void Chessman::ChessmanOut(){

    inGame=false;

}

void Chessman::BackToGame(){
    inGame=true;
}

bool Chessman::MoveCorrectness(Field* src){
    if(src->figureOnField!=NULL){
        if( (dynamic_cast<Chessman*>(src->figureOnField))->team==team*-1)
            return true;
        else
            return false;
    }
return true;
}
