#ifndef FIELD_H
#define FIELD_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>


class Field
{
    public:
        Field();
/// Nadaje wspulrzedne polozenia pola na planszy gry.
        Field(int pOnBoardX,int pOnBoardY,const char* pathToImageFile);

        virtual ~Field();

/// Rozmiar tablicy dwuwymiarowej reprezentujacy szachownice.
    const static int sizeChessBoard=8;
/// Okresla obecnosc figury na polu.
        Field* figureOnField;
/// Wyswietla na podanej w parametrze powierzchni graficznej
        void virtual ShowField(SDL_Surface* screen);
/// Szerokosc pojedyniczego pola.
        static const int fieldSizeX=102;
/// Wysokosc pojedyniczego pola.
        static const int fieldSizeY=102;
/// Przesuniecie pola wzgledem poczatku ukladu wspulrzednych.
        static const int fieldOffset=102;
/// Wskaznik na powierzchnie graficzna reprezentujaca pole.
        SDL_Surface* fieldImage;
/// Przydzielenie grafiki polom.
        int SetGraphics(const char* pathToImageFile="grafika/wood00.bmp");
/// Struktura SDL-a do przechowywania polozenia obrazow na ekranie.
        SDL_Rect position;
/// Wspulrzedne w tablicy.
        int positionOnBoardX;
        int positionOnBoardY;
    protected:
    private:
        friend class ChessMaster;
};

#endif // FIELD_H
