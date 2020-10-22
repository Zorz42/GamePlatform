#include "swl.h"

void main();
void main_event(SDL_Event& event);
Swl::scene main_scene(&main, &main_event);

void controller_main();
Swl::scene no_controller_scene(&controller_main);

Swl::rect_c test_rect;
Swl::rect_c background_rect;

void preInit() {
    //swl.window_width = 640;
    //swl.window_height = 400;
    //swl.window_caption = "Untitled";
    //swl.load_font = false;
    //swl.font_size = 32;
    
    // this library already comes with arial.ttf
    //swl.font_path = "/path/to/font.ttf";
    swl.goFullscreen();
}

void postInit() {
    swl.switchScene(main_scene);
    test_rect.w = 100;
    test_rect.h = 100;
    test_rect.x = swl.window_width - test_rect.w;
    test_rect.y = swl.window_height - test_rect.h;
    test_rect.c = {255, 255, 255};
    
    background_rect.w = swl.window_width;
    background_rect.h = swl.window_height;
    background_rect.c = {100, 100, 100};
}

void main_event(SDL_Event& event) {
    if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
        swl.stop();
}

void main() {
    swl.draw(test_rect);
    if(SDL_NumJoysticks() == 0)
        swl.switchScene(no_controller_scene);
}

void controller_main() {
    swl.draw(background_rect);
    if(SDL_NumJoysticks() != 0)
        swl.switchScene(main_scene);
}

/*
//Using SDL, SDL_image, standard IO, math, and strings
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Analog joystick dead zone
const int JOYSTICK_DEAD_ZONE = 8000;

//Texture wrapper class

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures

//Game Controller 1 handler
SDL_Joystick* gGameController = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Check for joysticks
        if( SDL_NumJoysticks() < 1 ) {
            printf( "Warning: No joysticks connected!\n" );
            exit(0);
        }
        else
        {
            //Load joystick
            gGameController = SDL_JoystickOpen( 0 );
            if( gGameController == NULL )
            {
                printf( "Warning: Unable to open game controller! SDL Error: %s\n", SDL_GetError() );
            }
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
        }
    }

    return success;
}

void close()
{

    //Close game controller
    SDL_JoystickClose( gGameController );
    gGameController = NULL;

    //Destroy window
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;
    gRenderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Normalized direction
            int xDir = 0;
            int yDir = 0;

            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    else if( e.type == SDL_JOYAXISMOTION )
                    {
                        //Motion on controller 0
                        if( e.jaxis.which == 0 )
                        {
                            //X axis motion
                            if( e.jaxis.axis == 0 )
                            {
                                //Left of dead zone
                                if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
                                {
                                    xDir = -1;
                                }
                                //Right of dead zone
                                else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
                                {
                                    xDir =  1;
                                }
                                else
                                {
                                    xDir = 0;
                                }
                            }
                            //Y axis motion
                            else if( e.jaxis.axis == 1 )
                            {
                                //Below of dead zone
                                if( e.jaxis.value < -JOYSTICK_DEAD_ZONE )
                                {
                                    yDir = -1;
                                }
                                //Above of dead zone
                                else if( e.jaxis.value > JOYSTICK_DEAD_ZONE )
                                {
                                    yDir =  1;
                                }
                                else
                                {
                                    yDir = 0;
                                }
                            }
                        }
                    }
                }

                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );

                //Calculate angle
                double joystickAngle = atan2( (double)yDir, (double)xDir ) * ( 180.0 / M_PI );
                
                //Correct angle
                if( xDir == 0 && yDir == 0 )
                {
                    joystickAngle = 0;
                }
                
                std::cout << joystickAngle << std::endl;

                //Render joystick 8 way angle

                //Update screen
                SDL_RenderPresent( gRenderer );
            }
    }

    //Free resources and close SDL
    close();

    return 0;
}
*/
