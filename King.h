#ifndef KING_H
#define KING_H

#include "Chessman.h"
#include <vector>

using namespace std;

class King : public Chessman
{
    public:
        King();
        /// Nadaje wspulrzedne polozenia figury na planszy gry i wiele innych.
        King(int positionOnBoardX,
                int positionOnBoardY,
                const char* pathToImageFile,
                int teamPlayer,
                Field* baseField
                );
        virtual ~King();

        void virtual GeneratePossiblyMoves(Field*** baseField);
        void GeneratePossiblyMoves(Field*** baseField,vector<Chessman*>* chessmanCollection);
    protected:
        bool MoveCorrectness(Field* src);
        bool MoveNoThreat(Field* src,vector<Chessman*>* Collection);
    private:
};

#endif // KING_H
