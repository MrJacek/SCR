#ifndef QUEEN_H
#define QUEEN_H

#include "Chessman.h"


class Queen : public Chessman
{
    public:
        Queen();
        /// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        Queen(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );
        virtual ~Queen();
        void virtual GeneratePossiblyMoves(Field*** baseField);
    protected:
        bool MoveCorrectness(Field* src);
    private:
};

#endif // QUEEN_H
