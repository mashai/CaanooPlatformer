#include "CGameManager.h"
#include "CUtils.h"

//Main

int main(int argc, char* argv[]){

    CGameManager game;
    return game.onExecute();
}

//Class CGameManager

CGameManager::CGameManager(): m_frameRate(0), m_joy(NULL), m_screen(NULL){

    m_running = true;
    m_debugging = false;
}

int CGameManager::onExecute(){

    if(onInit() == false) return -1;

    int frameNumber = 0;
    float currentTicks = 0;
    float lastFrameTicks = 0;
    float lastUpdateTicks = 0;

    SDL_Event event;
    while(m_running)
    {

        while(SDL_PollEvent(&event))
        {
            onEvent(event);
            m_sceneManager->onEvent(event);
        }

        currentTicks = SDL_GetTicks();
        if(currentTicks - lastUpdateTicks >= 20)
        {
            onUpdate();
            onRender();
            lastUpdateTicks = currentTicks;
        }

        //CalculateFrameRate
        frameNumber++;
        currentTicks = SDL_GetTicks();
        if(currentTicks - lastFrameTicks >= 1000)
        {
            lastFrameTicks = currentTicks;
            m_frameRate = frameNumber;
            frameNumber = 0;
        }

        SDL_Delay(10);
    }

    onCleanUp();

    return 0;
}

bool CGameManager::onInit(){

    // Initialize SDL
	if (SDL_Init (SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_JOYSTICK) < 0)
	{
		fprintf (stderr, "Couldn't initialize SDL: %s\n", SDL_GetError ());
		return false;
	}

    //Initialize screen
	m_screen = SDL_SetVideoMode (SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	if (m_screen == NULL)
	{
		fprintf (stderr, "Couldn't set 320x240x16 video mode: %s\n", SDL_GetError ());
		return false;
	}

    //Initialize text
	if(TTF_Init() < 0)
	{
	    fprintf(stderr, "Couldn't initialize TTF:%s\n", SDL_GetError());
	    return false;
	}

	// Check and open joystick device
	if (SDL_NumJoysticks() > 0)
	{
		m_joy = SDL_JoystickOpen(0);
		if(!m_joy)
		{
			fprintf (stderr, "Couldn't open joystick 0: %s\n", SDL_GetError ());
			return false;
		}
	}

    //Hide cursor
    SDL_ShowCursor(SDL_DISABLE);

	//Initialize graphics
	GRAPHICS->init(m_screen);

	//Initialize collisions
	COLLISIONS->init();

    //Create and initialize scene manager
    m_sceneManager = new CSceneManager();
    m_sceneManager->onInit();

    //load debug screen image
    m_debugScreenSprite = GRAPHICS->createSprite("debug.bmp");

    return true;
}

void CGameManager::onEvent(SDL_Event event){

    switch (event.type)
    {
        //KEYBOARD
        case SDL_KEYDOWN:
            //if d pressed, show or remove debugging data
            if (event.key.keysym.sym == SDLK_d) m_debugging = !m_debugging;
            //if escape pressed, terminate program
            if (event.key.keysym.sym == SDLK_ESCAPE) onExit();
            //if Ctrl + C pressed, terminate program
            if (event.key.keysym.sym == SDLK_c && event.key.keysym.mod & (KMOD_LCTRL | KMOD_RCTRL)) onExit();
            break;

        //JOYSTICK
        case SDL_JOYBUTTONDOWN:
            // if help1 button pressed, terminate program
            if ( event.jbutton.button == CAANOO_HELP_1 ) onExit();
            //if y button pressed, show or remove debugging data
            if (event.jbutton.button == CAANOO_BUTTON_Y) m_debugging = !m_debugging;
            break;

        case SDL_QUIT:
            onExit();
            break;

        default:
            break;
    }
}

void CGameManager::onUpdate(){

    m_sceneManager->onUpdate();
}

void CGameManager::onRender(){

    m_sceneManager->onRender();

    if(m_debugging)
    {
        GRAPHICS->drawSprite(m_debugScreenSprite, 0, 0);

        //create stream to store frame rate
        std::stringstream stream;
        stream << "FPS : " << m_frameRate;
        GRAPHICS->drawText(10, 10, stream.str(), 255, 255, 255);
    }

    if(m_sceneManager->playerWin()) GRAPHICS->drawText(100, 100, "YOU WIN =]", 0, 0, 0);

    SDL_Flip(m_screen);
    GRAPHICS->clearScreen();

}

void CGameManager::onCleanUp(){

    //cleanup scene manager
    if(m_sceneManager != NULL)delete m_sceneManager;

    //cleanup graphics
    GRAPHICS->destroy();

    //cleanup collisions
    COLLISIONS->destroy();

    //close TTF
    if(TTF_WasInit()) TTF_Quit();

    //close joystick
    if(m_joy) SDL_JoystickClose(m_joy);

    //quit
    SDL_Quit();

    #ifdef GP2X
	chdir("/usr/gp2x");
	execl("/usr/gp2x/gp2xmenu", "/usr/gp2x/gp2xmenu", NULL);
    #endif
}

void CGameManager::onExit(){

    m_running = false;
}


