#ifndef CGRAPHICS_H
#define CGRAPHICS_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
//#include <unistd.h>
#include <sstream>

#define uint unsigned int
#define BYTE unsigned char
#define GRAPHICS CGraphics::instance()

//Sprite Structure
struct Sprite{

    std::string name;
	SDL_Surface* surface;
	Sprite(std::string n, SDL_Surface* s) : name(n), surface(s) {}
};

//Singleton class CGraphics
class CGraphics {
    public:

        static CGraphics* instance();

        //init - initializes the values needed for CGraphics
		bool init(SDL_Surface* screen);

		//destroy - deletes the memory used in CGraphics
		void destroy();

		//clearScreen - clears the screen to an arbitrary colour
		void clearScreen(BYTE r = 0, BYTE g = 0, BYTE b = 0);

        //loadFont - loads a font and uses it for all text drawing
		void loadFont(std::string filename, int size);

		//createSprite - creates a sprite and stores it
		uint createSprite(const std::string filename, int frameNumber = 1);

		//drawSprite - draws a sprite into the screen at an arbitrary location
		void drawSprite(uint id, int x, int y, int frame_id = 0);

		//drawRectangle - draws a rectangle to the screen with given size, position and color
		void drawRectangle(int x, int y, int width, int height, BYTE r, BYTE g, BYTE b);

        //drawText - draws text at given position with given color
		void drawText(int x, int y, std::string text, BYTE r, BYTE g, BYTE b);

        //getSpriteWidth - returns sprite's width
        uint getSpriteWidth(uint id);

		//getSpriteHeight - returns sprite's height
		uint getSpriteHeight(uint id);

		//getWidth - returns screen width
		int getWidth(){return m_width;}

		//getHeight - returns screen height
		int getHeight() {return m_height;}

    private:

        //constructor - only gets called once
        CGraphics();

        //loadSurface - loads an SDL_Surface and optimizes it if possible
        SDL_Surface* loadSurface(const std::string filename);

        //applySurface - applies an SDL_Surface to screen
        void applySurface(int x, int y, SDL_Surface* surface);


        //Data members

        bool m_init;
        int m_width;
        int m_height;
        TTF_Font* m_font;
        SDL_Surface* m_screen;
        std::vector<Sprite> m_spriteVector;

        static CGraphics* m_instance;

};

#endif // CGRAPHICS_H

