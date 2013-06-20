//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <SDL.h>
//#include <SDL_ttf.h>
//#include <sstream>
//
///* GP2X button mapping */
//enum MAP_KEY
//{
//	VK_UP         , // 0
//	VK_UP_LEFT    , // 1
//	VK_LEFT       , // 2
//	VK_DOWN_LEFT  , // 3
//	VK_DOWN       , // 4
//	VK_DOWN_RIGHT , // 5
//	VK_RIGHT      , // 6
//	VK_UP_RIGHT   , // 7
//	VK_START      , // 8
//	VK_SELECT     , // 9
//	VK_FL         , // 10
//	VK_FR         , // 11
//	VK_FA         , // 12
//	VK_FB         , // 13
//	VK_FX         , // 14
//	VK_FY         , // 15
//	VK_VOL_UP     , // 16
//	VK_VOL_DOWN   , // 17
//	VK_TAT          // 18
//};
//
//enum CaanooAxes {
//CAANOO_AXIS_X = 0,
//CAANOO_AXIS_Y = 1
//};
//
//enum CaanooButtons {
//CAANOO_BUTTON_A = 0,
//CAANOO_BUTTON_X = 1,
//CAANOO_BUTTON_B = 2,
//CAANOO_BUTTON_Y = 3,
//CAANOO_BUTTON_L = 4,
//CAANOO_BUTTON_R = 5,
//CAANOO_BUTTON_HOME = 6,
//CAANOO_BUTTON_HOLD = 7,
//CAANOO_HELP_1 = 8,
//CAANOO_HELP_2 = 9,
//CAANOO_BUTTON_JOY = 10
//};
//
///* The attributes of the screen*/
//const int SCREEN_WIDTH = 320;
//const int SCREEN_HEIGHT = 240;
//const int SCREEN_BPP = 16;
//
///* The attributes of the joystick*/
//static const int CAANOO_JOYSTICK_MIN = -32768;
//static const int CAANOO_JOYSTICK_MAX = 32767;
//
///* The screen surface, joystick device */
//SDL_Surface *screen = NULL;
//SDL_Joystick *joy = NULL;
//
//void Terminate(void)
//{
//	SDL_Quit();
//#ifdef GP2X
//	chdir("/usr/gp2x");
//	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
//#endif
//}
//
//SDL_Surface* LoadImage(std::string filename)
//{
//    //Temp storage for the loaded image
//    SDL_Surface* loadedImage = NULL;
//    //Optimized image that will be used
//    SDL_Surface* optimizedImage = NULL;
//
//    loadedImage = SDL_LoadBMP(filename.c_str());
//    if(loadedImage != NULL)
//    {
//        optimizedImage = SDL_DisplayFormat(loadedImage);
//        SDL_FreeSurface(loadedImage);
//    }
//    else
//    {
//        fprintf(stderr, "Couldn't load image %s\n", SDL_GetError());
//    }
//    return optimizedImage;
//}
//
//TTF_Font* LoadFont(std::string filename, int size)
//{
//    //Load font
//    TTF_Font *font = TTF_OpenFont(filename.c_str(), size);
//    if(font == NULL) {
//        fprintf(stderr, "Couldn't load font %s\n", SDL_GetError());
//    }
//
//    return font;
//}
//
//void ApplySurface(int x, int y, SDL_Surface* source, SDL_Surface* destination)
//{
//    //Check if source and destination are valid surfaces
//    if(source == NULL || destination == NULL) return;
//
//    //Temp rectangle to hold offset
//    SDL_Rect offset;
//    offset.x = x;
//    offset.y = y;
//
//    SDL_BlitSurface(source, NULL, destination, &offset);
//}
//
//void Init()
//{
//    // Initialize SDL
//	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0) {
//		fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
//		exit (1);
//	}
//	atexit (Terminate);
//
//	// Set 320x240 16-bits video mode
//	screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
//	if (screen == NULL) {
//		fprintf (stderr, "Couldn't set 320x240x16 video mode: %s\n", SDL_GetError ());
//		exit (2);
//	}
//
//		SDL_ShowCursor(SDL_DISABLE);
//		SDL_WM_SetCaption("TouchScreen Test", NULL);
//
//		// Check and open joystick device
//	if (SDL_NumJoysticks() > 0) {
//		joy = SDL_JoystickOpen(0);
//		if(!joy) {
//			fprintf (stderr, "Couldn't open joystick 0: %s\n", SDL_GetError ());
//		}
//	}
//
//	//Initialize text drawing
//	if(TTF_Init() < 0){
//	    fprintf(stderr, "Couldn't initialize TTF:%s\n", SDL_GetError());
//	}
//}
//
//int main (int argc, char *argv[])
//{
//
//    Init();
//
//
//#ifdef GP2X
//	/* Only use GP2X code here */
//#endif
//
//#ifdef WIN32
//	/* Only use Windows code here */
//#endif
//
//    int fps = 0;
//    int framesDrawn = 0;
//    Uint32 prevTicks = SDL_GetTicks();
//
//    //Load font
//    TTF_Font *font = LoadFont("andyb.ttf", 18);
//    SDL_Surface* red = LoadImage("red.bmp");
//    SDL_Surface* redBig = LoadImage("redBig.bmp");
//    SDL_Surface* green = LoadImage("green.bmp");
//    SDL_Surface* black = LoadImage("black.bmp");
//
//    int x = 0, y = 0;
//    int minMousePosX = SCREEN_WIDTH/2, minMousePosY = SCREEN_HEIGHT/2;
//    int maxMousePosX = SCREEN_WIDTH/2, maxMousePosY = SCREEN_HEIGHT/2;
//
//	int done = 0;
//	bool clearScreen = false;
//	while (!done)
//	{
//	    SDL_Event event;
//
//		//Check for events
//		while (SDL_PollEvent (&event))
//		{
//			switch (event.type)
//			{
//			    //MOUSE MOUVEMENT
//			    case SDL_MOUSEMOTION:
//                    x = event.motion.x;
//                    y = event.motion.y;
//
//                    if(x < minMousePosX) minMousePosX = x;
//                    if(x > maxMousePosX) maxMousePosX = x;
//                    if(y < minMousePosY) minMousePosY = y;
//                    if(y > maxMousePosY) maxMousePosY = y;
//
//                    ApplySurface(x, y, red, screen);
//                    break;
//
//                //MOUSE BUTTON
//                case SDL_MOUSEBUTTONDOWN:
//                    if(event.button.button == SDL_BUTTON_LEFT)
//                    {
//                        x = event.button.x;
//                        y = event.button.y;
//
//                        if(x < minMousePosX) minMousePosX = x;
//                        if(x > maxMousePosX) maxMousePosX = x;
//                        if(y < minMousePosY) minMousePosY = y;
//                        if(y > maxMousePosY) maxMousePosY = y;
//
//                        ApplySurface(x, y, green, screen);
//                    }
//                    break;
//
//			    //KEYBORAD
//				case SDL_KEYDOWN:
//
//					//if Ctrl + C, terminate program
//					if ( (event.key.keysym.sym == SDLK_c) && (event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) ){
//					    done = 1;
//					}
//					//if a clear screen
//					if (event.key.keysym.sym == SDLK_a)
//					{
//					    clearScreen = true;
//					}
//
//				//JOYSTICK
//				case SDL_JOYBUTTONDOWN:
//					/* if press Start button, terminate program */
//					if ( event.jbutton.button == CAANOO_HELP_1 )
//					{
//					    done = 1;
//					    break;
//					}
//
//                    if (event.jbutton.button == CAANOO_BUTTON_X )
//                    {
//                        //Clear screen
//                        clearScreen = true;
//                    }
//					break;
//
//				case SDL_JOYBUTTONUP:
//					break;
//
//				case SDL_QUIT:
//					done = 1;
//					break;
//				default:
//					break;
//			}
//		}
//
//        Uint32 ticks = SDL_GetTicks();
//	    framesDrawn++;
//
//	    if(ticks - prevTicks >= 1000)
//	    {
//	        fps = framesDrawn;
//	        prevTicks = ticks;
//	        framesDrawn = 0;
//	    }
//
//		//Draw FPS
//		//std::stringstream stream;
//		//stream << "FPS : " << fps;
//		//stream << "Min : " << minMousePosX << ", " << minMousePosY << "  Max: " << maxMousePosX << ", " << maxMousePosY;
//		//SDL_Color red = {255, 0, 0, 0};
//		//ApplySurface(50, SCREEN_HEIGHT/2, black, screen);
//		//SDL_Surface *textSurface = .
//		//ApplySurface(50, SCREEN_HEIGHT/2, textSurface, screen);
//        //SDL_FreeSurface(textSurface);
//
//        if(clearScreen)
//        {
//            SDL_FillRect(screen, 0, SDL_MapRGB(screen->format, 0, 0, 0));
//            clearScreen = false;
//        }
//
//		SDL_Flip(screen);
//		SDL_Delay(10);
//	}
//
//	//Free objects before quitting
//	SDL_FreeSurface(red);
//	SDL_FreeSurface(green);
//    SDL_FreeSurface(black);
//	SDL_FreeSurface(screen);
//	SDL_Quit();
//
//	return 0;
//}
