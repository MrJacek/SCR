#ifndef CHESSMASTER_H
#define CHESSMASTER_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "Field.h"
#include "Chessman.h"
#include <string>
#include "Man.h"
#include "Tower.h"
#include "Bishop.h"
#include "Queen.h"
#include "Knight.h"
#include "King.h"
#include <string>
#include "SDL_gfxPrimitives.h"
#include <vector>
#include <list>


using namespace std;

class ChessMaster
{
    public:
        ChessMaster(int nrStyle);
        virtual ~ChessMaster();
///Uruchamia dzialanie calego programu.
        void Start();
        static string fileSeparator;
        
    protected:
    enum enumTeam{
    black=-1,
    neutral=0,
    white=1
        };
    enumTeam activeTeam;
/// Wskaznik do tablicy dwuwymiarowej w ktorej przeochywane sa sciezki do plikow graficznych dla pol.
    string** fieldStyle;
/// Liczba stylow graficznych pol.
    const int nrFieldStyle;
/// Rozmiar tablicy dwuwymiarowej reprezentujacy szachownice.
    const static int sizeChessBoard=8;
    
    Field*** pBoard;
///Aktywuje biblioteke graficzn� SDL wraz z bibliotekami dodatkowymi: image, gfx, mixer.
    int InitSDL(
                    bool fullScreen=false,
                    int screenResolutionX=1280,
                    int screenResolutionY=1024,
                    int screenDeepColor=32
                );
/// Ustawia wszystkie wstepne bitmapy, konfiguruje poczatkowe ustawienia planszy.
        int ConfigureBoard(int typeStyle=4,
                            const char* patchToBoardGrafic="grafika/woodchess.png",
                            int sizeBoardX=sizeChessBoard,
                            int sizeBoardY=sizeChessBoard
                          );
/// Wskaznik na glowna powierzchnie graficzna.
        SDL_Surface* screen;
/// Wskaznik pod ktorym przechowywana jest szachownice.
        SDL_Surface* chessBoard;
/// Unia SDL-a w ktorej przechowywane sa wylapywane zdarzenia.
        SDL_Event event;
/// Odpowiada za interakcje z menu.
        int Menu();
/// Kontroluje przebieg glownej petli programu.
        bool quit;
/// Oblsuguje zdarzenie zwiazane z myszka.
        int MouseHandling();
/// Aktywna figura na planszy.
        SDL_Rect activeChessman;

        SDL_Rect mousePosition;
/// Wlaczone/wylaczone pokazywanie ruchow.
        bool activeMoves;
/// Pokazauje mozliwe ruchu aktywnej figury.
        int ShowActiveMoves();
/// Tablica w ktorej przechowywane sa wszystkie figury w grze.
        vector<Chessman*> chessmanCollection;
        void ShowAllChessman();

        Chessman* pActiveChessman;

        King* blackKing;
        King* whiteKing;
        King* activeTeamKing;
        static const int nrChassman=32;

        SDL_Rect ConvToPX(const SDL_Rect src);

        void CreateChessManTeam(enumTeam flag);

        void GenerateMovesList();

        bool CheckMate();

        bool CheckMateSituation();

        int GameRuning(int flag=0);

        bool IsMate();

        bool SearchPossibleKingHide();



    private:
};




#endif // CHESSMASTER_H
