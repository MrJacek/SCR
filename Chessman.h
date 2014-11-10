#ifndef CHESSMAN_H
#define CHESSMAN_H

#include "Field.h"
#include <list>


class Chessman : public Field
{
    public:
        bool king;
///Konstruktor bez argumentowy.
        Chessman();
/// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        Chessman(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );

        virtual ~Chessman();
        int Move(Field* src,Chessman* vitcim,Field* postionBefor);
        int virtual Move(Field* src,SDL_Surface* screen);
/// Okresla do ktrorej druzyny nalezy figura -1 czarne, 1 biale, 0 neutralne.
        const int team;

        bool inGame;

/// Wyswietla figure na podanej w parametrze powierzchni graficznej.
        void virtual ShowField(SDL_Surface* screen);
/// Generuje mozliwe ruchy figury i zapisuje je do listy. Rozpoznaje czy jest to bice, szach czy zwykle przesuniecie.
        void virtual GeneratePossiblyMoves(Field*** baseField)=0;
/// Lista w ktorej przeochowuje sie wskazniki do mozliwych ruchow figury.
        std::list<Field*> Moves;
        void ChessmanOut();
        void BackToGame();

    protected:
/// Okresla predkosc z jaka przesuwa sie figura.
        int velocityChessmanX;
        int velocityChessmanY;
/// Okresla miejsce celu ruchu w pixelach.
        SDL_Rect moveTarget;
        void ChangePosition(int posBoardX,int posBoardY);

        bool virtual MoveCorrectness(Field* src);

    private:
};

#endif // CHESSMAN_H
