#ifndef TOWER_H
#define TOWER_H

#include "Chessman.h"


class Tower : public Chessman
{
    public:
        Tower();
/// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        Tower(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );
        virtual ~Tower();
        void virtual GeneratePossiblyMoves(Field*** baseField);
    protected:
        bool MoveCorrectness(Field* src);
    private:
};

#endif // TOWER_H
