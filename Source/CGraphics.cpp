#include "CGraphics.h"

//Singleton class CGraphics

CGraphics* CGraphics::m_instance = 0;

CGraphics::CGraphics(): m_init(0), m_width(0), m_height(0), m_font(NULL), m_screen(NULL){}

CGraphics* CGraphics::instance() {

    //if instance has never been called before
    if(m_instance == 0)
    {
        //call constructor
        m_instance = new CGraphics();
    }
    //always return pointer to the CGraphic instance
    return m_instance;
}

bool CGraphics::init(SDL_Surface* screen){

    //if CGraphics has already been initialized, return
    if(m_init != 0) return true;

    //else initialize CGraphics
    m_init = 1;
    m_screen = screen;
    m_width = m_screen->w;
    m_height = m_screen->h;
    loadFont("andyb.ttf", 18);

    return true;
}

void CGraphics::destroy() {

    //delete sprites
    for(uint i = 0; i < m_spriteVector.size(); i++)
    {
		SDL_FreeSurface(m_spriteVector[i].surface);
    }

    //free font
    if(m_font)TTF_CloseFont(m_font);

    //delete allocateed memory for CGraphics
    if(m_instance)
    {
        delete m_instance;
    }
    m_instance = 0;
}

void CGraphics::clearScreen(BYTE r, BYTE g, BYTE b) {

    //if CGraphics not initialized, return
    if(m_init == 0) return;

    SDL_FillRect(m_screen, 0, SDL_MapRGB(m_screen->format, r, g, b));
}

void CGraphics::loadFont(std::string filename, int size){

    //if CGraphics not initialized, return
    if(m_init == 0) return;

    //Load font
    TTF_Font* font = TTF_OpenFont(filename.c_str(), size);

    //if font valid, store it in m_font
    if(font != NULL) m_font = font;
}

uint CGraphics::createSprite(const std::string filename, int frameNumber) {

    //if CGraphics not initialized, return
    if(m_init == 0) return -1;

    //check if image already exists
    for(uint i = 0; i < m_spriteVector.size(); i++)
	{
		//if it exists
		if(filename == m_spriteVector[i].name)
		{
		    //return indice of the sprite at which the image is stored
			return i;
		}
	}

	//otherwise load a new image
    SDL_Surface* surface = loadSurface(filename);

    //and store it inside spriteVector
    m_spriteVector.push_back(Sprite(filename, surface));

    //return indice at which the sprite is stored (will never change since sprites cannot be deleted unless the whole vector is cleared)
    return m_spriteVector.size() - 1;
}

void CGraphics::drawSprite(uint id, int x, int y, int frame_id) {

    //if CGraphics not initialized, return
    if(m_init == 0) return;

    //if id out of bounds, return
    if(id >= m_spriteVector.size()) return;

    //else apply Sprite's surface to screen
    applySurface(x, y, m_spriteVector[id].surface);
}

void CGraphics::drawRectangle(int x, int y, int width, int height, BYTE r, BYTE g, BYTE b){

    //if CGraphics not initialized, return
    if(m_init == 0) return;

    //convert rgba values to Uint32
    Uint32 color = SDL_MapRGB(m_screen->format, r, g, b);

    //create rectangle and draw it
    SDL_Rect rectangle = {x, y, width, height};
    SDL_FillRect(m_screen, &rectangle, color);
}

void CGraphics::drawText(int x, int y, std::string text, BYTE r, BYTE g, BYTE b){

    //if CGraphics not initialized, return
    if(m_init == 0) return;

    //if font not loaded
    if(m_font == NULL) return;

    //convert rgba values to SDL_Color
    SDL_Color color = {r, g, b};

    //create text surface
    SDL_Surface* surface = TTF_RenderText_Solid(m_font, text.c_str(), color);

    //apply text to screen
    applySurface(x, y, surface);

    //free surface
    SDL_FreeSurface(surface);
}

uint CGraphics::getSpriteWidth(uint id){

     //if CGraphics not initialized, return 0
    if(m_init == 0) return 0;

    //if id out of bounds, return 0
    if(id >= m_spriteVector.size()) return 0;

    //if sprite's surface is null, return 0
    if(m_spriteVector[id].surface == NULL) return 0;

    //else return surface's width
    return (uint)m_spriteVector[id].surface->w;
}

uint CGraphics::getSpriteHeight(uint id){

     //if CGraphics not initialized, return 0
    if(m_init == 0) return 0;

    //if id out of bounds, return 0
    if(id >= m_spriteVector.size()) return 0;

    //if sprite's surface is null, return 0
    if(m_spriteVector[id].surface == NULL) return 0;

    //else return surface's width
    return (uint)m_spriteVector[id].surface->h;
}

SDL_Surface* CGraphics::loadSurface(const std::string filename){

    //create temp storage for the loaded image
    SDL_Surface* loadedImage = NULL;

    //create optimized image to return
    SDL_Surface* optimizedImage = NULL;


    loadedImage = SDL_LoadBMP(filename.c_str());
    if(loadedImage != NULL)
    {
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
    }
    else
    {
        fprintf(stderr, "Couldn't load image %s\n", SDL_GetError());
    }

    if(optimizedImage != NULL)
    {
        //map color key and set it to be transparent
        Uint32 colorKey = SDL_MapRGB(optimizedImage->format, 255, 0, 255);
        SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, colorKey);
    }
    return optimizedImage;
}

void CGraphics::applySurface(int x, int y, SDL_Surface* surface)
{
    //if surface and screen not valid, return
    if(surface == NULL || m_screen == NULL) return;

    //Temp rectangle to hold offset
    SDL_Rect offset;
    offset.x = x;
    offset.y = y;

    SDL_BlitSurface(surface, NULL, m_screen, &offset);
}
