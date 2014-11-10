#ifndef BISHOP_H
#define BISHOP_H

#include "Chessman.h"


class Bishop : public Chessman
{
    public:
        Bishop();
/// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        Bishop(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );
        virtual ~Bishop();
        void virtual GeneratePossiblyMoves(Field*** baseField);
    protected:
        bool MoveCorrectness(Field* src);
    private:
};

#endif // BISHOP_H
