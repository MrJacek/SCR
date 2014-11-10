#include "Knight.h"

Knight::Knight()
{
    //ctor
}
//***********************************************************************
Knight::Knight(int positionOnBoardX,
        int positionOnBoardY,
        const char* pathToImageFile,
        int teamPlayer,
        Field* baseField
        ): Chessman(positionOnBoardX,positionOnBoardY,pathToImageFile,teamPlayer,baseField)
{

}
//***********************************************************************
Knight::~Knight()
{
    //dtor
}
//***********************************************************************
void Knight::GeneratePossiblyMoves(Field*** baseField){

// Sprawdza mozliwe ruchy po nizej pozycji figury.
    CheckMoveDirection(2,1,baseField);
    CheckMoveDirection(1,2,baseField);
// Sprawdza mozliwe ruchy po wyzej pozycji figury.
    CheckMoveDirection(-2,1,baseField);
    CheckMoveDirection(-1,2,baseField);



}
//***********************************************************************
bool Knight::MoveCorrectness(Field* src){
    if(src->figureOnField!=NULL){
        if( (dynamic_cast<Chessman*>(src->figureOnField))->team==team*-1)
            return true;
        else
            return false;
    }
return true;
}
//***********************************************************************
void Knight::CheckMoveDirection(int yDirection,int xDirection,Field*** baseField){

    if(positionOnBoardY+yDirection < sizeChessBoard && positionOnBoardY+yDirection >= 0){
        if(positionOnBoardX+xDirection < sizeChessBoard){
            if(MoveCorrectness(baseField[positionOnBoardY+yDirection][positionOnBoardX+xDirection]))
                Moves.push_back(baseField[positionOnBoardY+yDirection][positionOnBoardX+xDirection]);
        }
        if(positionOnBoardX-xDirection >= 0){
            if(MoveCorrectness(baseField[positionOnBoardY+yDirection][positionOnBoardX-xDirection]))
                Moves.push_back(baseField[positionOnBoardY+yDirection][positionOnBoardX-xDirection]);
        }
    }
}
