#include "Queen.h"

Queen::Queen()
{
    //ctor
}
//*************************************************************************
Queen::Queen(int positionOnBoardX,
        int positionOnBoardY,
        const char* pathToImageFile,
        int teamPlayer,
        Field* baseField
        ): Chessman(positionOnBoardX,positionOnBoardY,pathToImageFile,teamPlayer,baseField)
{

}
//*************************************************************************
Queen::~Queen()
{
    //dtor
}
//*************************************************************************
void Queen::GeneratePossiblyMoves(Field*** baseField)
{
//----------------------------------------------------
//------------------Po skosie-------------------------
//----------------------------------------------------
    int x=positionOnBoardX;
    int y=positionOnBoardY;
//----------------------------------------------------
// Sprawdza mozliwe ruchu w pionie w duł.
    y=positionOnBoardY+1;
    x=positionOnBoardX+1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( y < sizeChessBoard && x < sizeChessBoard && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        y++;
        x++;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(y < sizeChessBoard && x < sizeChessBoard){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }
//----------------------------------------------------
// Sprawdza mozliwe ruchu w pionie w gore.
    y=positionOnBoardY-1;
    x=positionOnBoardX-1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( y >= 0 && x >= 0  && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        y--;
        x--;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(y >= 0 && x >= 0){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }
//----------------------------------------------------
// Sprawdza mozliwe ruchu w poziomie w prawo.
    y=positionOnBoardY-1;
    x=positionOnBoardX+1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( x < sizeChessBoard && y >= 0 && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        x++;
        y--;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(x < sizeChessBoard && y >= 0){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }
//----------------------------------------------------
// Sprawdza mozliwe ruchu w poziomie w lewo.
    x=positionOnBoardX-1;
    y=positionOnBoardY+1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( x >= 0 && y < sizeChessBoard && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        x--;
        y++;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(x >= 0 && y < sizeChessBoard){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }
//----------------------------------------------------
//------------------Po prostej------------------------
//----------------------------------------------------
x=positionOnBoardX;
y=positionOnBoardY;
// Sprawdza mozliwe ruchu w pionie w duł.
    y=positionOnBoardY+1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( y < sizeChessBoard && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        y++;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(y< sizeChessBoard){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }

// Sprawdza mozliwe ruchu w pionie w gore.
    y=positionOnBoardY-1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( y >= 0 && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        y--;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(y >= 0){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }

// Sprawdza mozliwe ruchu w poziomie w prawo.
    y=positionOnBoardY;
    x=positionOnBoardX+1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( x < sizeChessBoard && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        x++;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(x < sizeChessBoard){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }
// Sprawdza mozliwe ruchu w poziomie w lewo.
    x=positionOnBoardX-1;
// Przeglada pola po lini prostej pola dodajac kazde do mozliwych ruchow figury,
// Konczy przegladanie w momencie konca planszy lub napotkania pola zajetego przez jakas figure.
    while( x >= 0 && baseField[y][x]->figureOnField==NULL){
        Moves.push_back(baseField[y][x]);
        x--;
    }
// Gdy przegladanie pol skonczylo sie na polu zajetym a nie na koncu planszy..
    if(x >= 0){
// Sprawdzamy czy na polu tym stala figura przeciwnika...
        if( MoveCorrectness(baseField[y][x]) )
// Gdy na polu stoi figura przeciwnika dodajemy te pole do mozliwych ruchow figury.
            Moves.push_back(baseField[y][x]);
    }
}
//*************************************************************************
bool Queen::MoveCorrectness(Field* src){
    if(src->figureOnField!=NULL){
        if( (dynamic_cast<Chessman*>(src->figureOnField))->team==team*-1)
            return true;
    }
return false;
}
