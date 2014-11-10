#include "King.h"

King::King()
{
    //ctor
}
//*************************************************************************
King::King(int positionOnBoardX,
        int positionOnBoardY,
        const char* pathToImageFile,
        int teamPlayer,
        Field* baseField
        ): Chessman(positionOnBoardX,positionOnBoardY,pathToImageFile,teamPlayer,baseField)
{
Chessman::king=true;
}
//*************************************************************************
King::~King()
{
    //dtor
}
//*************************************************************************
void King::GeneratePossiblyMoves(Field*** baseField){


    for( int y=positionOnBoardY-1; y <= positionOnBoardY+1; ++y){
        if( y >= 0 && y < sizeChessBoard){
            for(int x=positionOnBoardX-1;x <= positionOnBoardX+1; ++x){
                if(x >= 0 && x < sizeChessBoard)
                    if(MoveCorrectness(baseField[y][x]))
                        Moves.push_back(baseField[y][x]);
            }
        }
    }
}
//*************************************************************************
void King::GeneratePossiblyMoves(Field*** baseField,vector<Chessman*>* Collection){

    for( int y=positionOnBoardY-1; y <= positionOnBoardY+1; ++y){
        if( y >= 0 && y < sizeChessBoard){
            for(int x=positionOnBoardX-1;x <= positionOnBoardX+1; ++x){
                if(x >= 0 && x < sizeChessBoard){
                    if(MoveCorrectness(baseField[y][x])){
                        if(MoveNoThreat(baseField[y][x],Collection))
                            Moves.push_back(baseField[y][x]);
                    }
                }
            }
        }
    }
}
//*************************************************************************
bool King::MoveNoThreat(Field* src,vector<Chessman*>* Collection){
    vector<Chessman*> chessmanCollection=*Collection;
    vector<Chessman*>::iterator iterBegin;
    vector<Chessman*>::iterator iterEnd;
    iterEnd = chessmanCollection.end();
    bool find=true;

     for ( iterBegin= chessmanCollection.begin(); iterBegin != iterEnd; ++iterBegin){
        if((*iterBegin)->inGame){
            if((*iterBegin)->team!=team){
                Chessman* pom=(*iterBegin);
                for(list<Field*>::iterator iter=pom->Moves.begin();iter!=pom->Moves.end();++iter){
                // Gdy w lisce znajduje sie ruch o takich samych wspulrzednych jakie zostaly podane do funkcji..
                    if(src==(*iter)){
                        find=false;
                    }
                }
            }
        }
    }
    return find;
}


bool King::MoveCorrectness(Field* src){
    if(src->figureOnField!=NULL){
        if( (dynamic_cast<Chessman*>(src->figureOnField))->team!=team)
            return true;
        else
            return false;
    }
return true;
}
