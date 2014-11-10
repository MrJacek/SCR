#ifndef MAN_H
#define MAN_H

#include "Chessman.h"


class Man : public Chessman
{
    public:
        Man();
/// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        Man(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );
        virtual ~Man();
        void virtual GeneratePossiblyMoves(Field*** baseField);
        int virtual Move(Field* src,SDL_Surface* screen);
    protected:
        bool firstMove;
        bool MoveCorrectness(Field* src);
        bool MoveCorrectness(Field* src,int);
    private:
};

#endif // MAN_H
