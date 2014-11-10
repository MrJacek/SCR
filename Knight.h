#ifndef KNIGHT_H
#define KNIGHT_H

#include "Chessman.h"


class Knight : public Chessman
{
    public:
        Knight();
/// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        Knight(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );
        virtual ~Knight();
        void virtual GeneratePossiblyMoves(Field*** baseField);
    protected:
        bool MoveCorrectness(Field* src);
        void CheckMoveDirection(int yDirection,int xDirection,Field*** baseField);
    private:
};

#endif // KNIGHT_H
