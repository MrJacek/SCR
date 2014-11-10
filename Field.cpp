#include "Field.h"


Field::Field()
{
// Ustawia pole na wlasciwej pozycji na osi X.
    position.x=0;
// Ustawia pole na wlasciwej pozycji na osi Y.
    position.y=0;
// Poczatkowo na polu nie stoi zadna figura.
    figureOnField=NULL;
    fieldImage=NULL;

}
//***********************************************************************************
Field::Field(int pOnBoardY,int pOnBoardX,const char* pathToImageFile)
{
    positionOnBoardX=pOnBoardX;
    positionOnBoardY=pOnBoardY;
// Ustawia pole na wlasciwej pozycji na osi X.
    position.x=(positionOnBoardX*fieldSizeX)+fieldOffset;
// Ustawia pole na wlasciwej pozycji na osi Y.
    position.y=(positionOnBoardY*fieldSizeY)+fieldOffset;

// Poczatkowo na polu nie stoi zadna figura.
    figureOnField=NULL;
    if(SetGraphics(pathToImageFile)==-1)
        exit(-1);
}
//***********************************************************************************
Field::~Field()
{
    SDL_FreeSurface(fieldImage);
}
//***********************************************************************************
int Field::SetGraphics(const char* pathToImageFile)
{
// Laduje obraz pol do pomocniczej powierzchni.
    SDL_Surface* help00=IMG_Load(pathToImageFile);
// Sprawdza czy udalo sie zaladowanie obraz.
    if(help00==NULL)
// Gdy w powierzchnie nie ma obrazu konczy funkcje i zwraca -1.
        return -1;
// Konwertuje obraz na typ formatu glownej powierzchni graficznej.
    fieldImage=SDL_DisplayFormat(help00);
    SDL_SetColorKey(fieldImage,SDL_SRCCOLORKEY, SDL_MapRGB( fieldImage->format, 255, 0 , 255 ));
// Zwalnia pamieci nie potrzebna powierzchnie graficzna.
    SDL_FreeSurface(help00);
return 1;
}
//***********************************************************************************
void Field::ShowField(SDL_Surface* screen)
{

    SDL_BlitSurface(fieldImage,NULL,screen,&position);
    SDL_Flip(screen);

}


