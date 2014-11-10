#include "Man.h"

Man::Man()
{
    //ctor
}
//***********************************************************************************
Man::Man(int positionOnBoardX,
        int positionOnBoardY,
        const char* pathToImageFile,
        int teamPlayer,
        Field* baseField
        ): Chessman(positionOnBoardX,positionOnBoardY,pathToImageFile,teamPlayer,baseField)
{
firstMove=true;
}
//***********************************************************************************
Man::~Man()
{
    //dtor
}
//***********************************************************************************
void Man::GeneratePossiblyMoves(Field*** baseField){

    if(positionOnBoardY+1*team >= 0 && positionOnBoardY+1*team < 8){
        if(MoveCorrectness(baseField[positionOnBoardY+1*team][positionOnBoardX])){
            Moves.push_back(baseField[positionOnBoardY+1*team][positionOnBoardX]);

            if(positionOnBoardY+2*team >= 0 && positionOnBoardY+2*team < 8 && firstMove){
                if(MoveCorrectness(baseField[positionOnBoardY+2*team][positionOnBoardX])){
                    Moves.push_back(baseField[positionOnBoardY+2*team][positionOnBoardX]);

                }
            }
        }

        if( positionOnBoardX+1 < 8){
            if(MoveCorrectness(baseField[positionOnBoardY+1*team][positionOnBoardX+1],0))
                Moves.push_back(baseField[positionOnBoardY+1*team][positionOnBoardX+1]);
        }

        if( positionOnBoardX-1 >= 0){
            if(MoveCorrectness(baseField[positionOnBoardY+1*team][positionOnBoardX-1],0))
                Moves.push_back(baseField[positionOnBoardY+1*team][positionOnBoardX-1]);
        }

    }
}

//************************************************************************
int Man::Move(Field* src,SDL_Surface* screen)
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
            firstMove=false;
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
//************************************************************************
bool Man::MoveCorrectness(Field* src){
    if(src->figureOnField!=NULL){
            return false;
    }
return true;
}
//***************************************************************************
bool Man::MoveCorrectness(Field* src,int flag){
    if(src->figureOnField!=NULL){
        if( (dynamic_cast<Chessman*>(src->figureOnField))->team==team*-1)
            return true;
    }
return false;
}
