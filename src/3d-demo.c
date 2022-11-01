#include "SDL.h"
#include "SDL_gpu.h"
#include "SDL_gpu_OpenGL_1.h"
#include "glew.h"
#include <stdlib.h>



GLuint VBO;
GLuint modelViewProjection_loc;
GLuint vertex_loc;
GLuint color_loc;
Uint32 v, f, p;

void begin_3d(GPU_Target* screen)
{
    GPU_FlushBlitBuffer();
    
    
    GPU_MatrixMode(screen, GPU_MODEL);
    GPU_PushMatrix();
    GPU_LoadIdentity();
    GPU_MatrixMode(screen, GPU_VIEW);
    GPU_PushMatrix();
    GPU_LoadIdentity();
    GPU_MatrixMode(screen, GPU_PROJECTION);
    GPU_PushMatrix();
    GPU_LoadIdentity();
}

void end_3d(GPU_Target* screen)
{
    GPU_ResetRendererState();
    
    GPU_MatrixMode(screen, GPU_MODEL);
    GPU_PopMatrix();
    GPU_MatrixMode(screen, GPU_VIEW);
    GPU_PopMatrix();
    GPU_MatrixMode(screen, GPU_PROJECTION);
    GPU_PopMatrix();
}

void draw_spinning_triangle(GPU_Target* screen)
{
    GLfloat gldata[21];
    float mvp[16];
    float t = SDL_GetTicks()/1000.0f;

    GPU_Rotate(100*t, 0, 0.707, 0.707);
    GPU_Rotate(20*t, 0.707, 0.707, 0);


    gldata[0] = 0;
    gldata[1] = 0.2f;
    gldata[2] = 0;
    
    gldata[3] = 1.0f;
    gldata[4] = 0.0f;
    gldata[5] = 0.0f;
    gldata[6] = 1.0f;
    
    
    gldata[7] = -0.2f;
    gldata[8] = -0.2f;
    gldata[9] = 0;
    
    gldata[10] = 0.0f;
    gldata[11] = 1.0f;
    gldata[12] = 0.0f;
    gldata[13] = 1.0f;
    
    gldata[14] = 0.2f;
    gldata[15] = -0.2f;
    gldata[16] = 0;
    gldata[17] = 0.0f;
    gldata[18] = 0.0f;
    gldata[19] = 1.0f;
    gldata[20] = 1.0f;
    
    
    glUseProgram(p);
    
    GPU_GetModelViewProjection(mvp);
    glUniformMatrix4fv(modelViewProjection_loc, 1, 0, mvp);
    
    
    glEnableVertexAttribArray(vertex_loc);
    glEnableVertexAttribArray(color_loc);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(gldata), gldata, GL_STREAM_DRAW);
    
    glVertexAttribPointer(
       vertex_loc,
       3,                  // size
       GL_FLOAT,           // type
       GL_FALSE,           // normalize
       sizeof(float)*7,    // stride
       (void*)0            // offset
    );
    
    glVertexAttribPointer(
       color_loc,
       4,                      // size
       GL_FLOAT,               // type
       GL_FALSE,               // normalize
       sizeof(float)*7,        // stride
       (void*)(sizeof(float)*3)  // offset
    );
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
     
    glDisableVertexAttribArray(color_loc);
    glDisableVertexAttribArray(vertex_loc);
}

void draw_3d_stuff(GPU_Target* screen)
{
    begin_3d(screen);
    
    draw_spinning_triangle(screen);
    
    end_3d(screen);
}

void draw_more_3d_stuff(GPU_Target* screen)
{
	float t;
    begin_3d(screen);
    
    t = SDL_GetTicks()/1000.0f;
    GPU_Rotate(t*60, 0, 0, 1);
    GPU_Translate(0.4f, 0.4f, 0);
    draw_spinning_triangle(screen);
    
    end_3d(screen);
}

int main(int argc, char* argv[])
{
	GPU_Target* screen;
	
	GPU_SetRequiredFeatures(GPU_FEATURE_BASIC_SHADERS);
	screen = GPU_InitRenderer(GPU_RENDERER_OPENGL_1, 800, 600, GPU_DEFAULT_INIT_FLAGS);
	if(screen == NULL)
    {
        GPU_LogError("Initialization Error: Could not create a renderer with proper feature support for this demo.\n");
		return 1;
    }
    
    glewExperimental = GL_TRUE;  // Force GLEW to get exported functions instead of checking via extension string
    if(glewInit() != GLEW_OK)
    {
        GPU_LogError("Initialization Error: Failed to initialize GLEW.\n");
        return 2;
    }

	{
		GPU_Image* image;
		float dt;
		Uint32 startTime;
		long frameCount;
		int maxSprites = 50;
		int numSprites;
		float x[50];
		float y[50];
		float velx[50];
		float vely[50];
		int i;
		Uint8 done;
		SDL_Event event;

		image = GPU_LoadImage("data/test.bmp");
		if (image == NULL)
			return 3;
        
        v = GPU_LoadShader(GPU_VERTEX_SHADER, "data/shaders/untextured.vert");
        f = GPU_LoadShader(GPU_FRAGMENT_SHADER, "data/shaders/untextured.frag");
        p = GPU_LinkShaders(v, f);
        
        glUseProgram(p);
        vertex_loc = GPU_GetAttributeLocation(p, "gpu_Vertex");
        color_loc = GPU_GetAttributeLocation(p, "gpu_Color");
        modelViewProjection_loc = GPU_GetUniformLocation(p, "gpu_ModelViewProjectionMatrix");
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

		dt = 0.010f;

		startTime = SDL_GetTicks();
		frameCount = 0;

		numSprites = 1;

		for (i = 0; i < maxSprites; i++)
		{
			x[i] = rand() % screen->w;
			y[i] = rand() % screen->h;
			velx[i] = 10 + rand() % screen->w / 10;
			vely[i] = 10 + rand() % screen->h / 10;
		}


		done = 0;
		while (!done)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					done = 1;
				else if (event.type == SDL_KEYDOWN)
				{
					if (event.key.keysym.sym == SDLK_ESCAPE)
						done = 1;
					else if (event.key.keysym.sym == SDLK_EQUALS || event.key.keysym.sym == SDLK_PLUS)
					{
						if (numSprites < maxSprites)
							numSprites++;
					}
					else if (event.key.keysym.sym == SDLK_MINUS)
					{
						if (numSprites > 0)
							numSprites--;
					}
				}
			}

			for (i = 0; i < numSprites; i++)
			{
				x[i] += velx[i] * dt;
				y[i] += vely[i] * dt;
				if (x[i] < 0)
				{
					x[i] = 0;
					velx[i] = -velx[i];
				}
				else if (x[i]> screen->w)
				{
					x[i] = screen->w;
					velx[i] = -velx[i];
				}

				if (y[i] < 0)
				{
					y[i] = 0;
					vely[i] = -vely[i];
				}
				else if (y[i]> screen->h)
				{
					y[i] = screen->h;
					vely[i] = -vely[i];
				}
			}

			GPU_Clear(screen);

			draw_3d_stuff(screen);

			for (i = 0; i < numSprites; i++)
			{
				GPU_Blit(image, NULL, screen, x[i], y[i]);
			}

			draw_more_3d_stuff(screen);

			GPU_Flip(screen);

			frameCount++;
			if (frameCount % 500 == 0)
				printf("Average FPS: %.2f\n", 1000.0f*frameCount / (SDL_GetTicks() - startTime));
		}

		printf("Average FPS: %.2f\n", 1000.0f*frameCount / (SDL_GetTicks() - startTime));

		GPU_FreeImage(image);
	}

	GPU_Quit();
	
	return 0;
}


/*ANOTHER EXAMPLE*/
/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, standard IO, and strings
#include <SDL.h>
#include <stdio.h>
#include <string>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces
{
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ KEY_PRESS_SURFACE_TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
            gScreenSurface = SDL_GetWindowSurface( gWindow );
        }
    }

    return success;
}

bool loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load default surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] = loadSurface( "04_key_presses/press.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ] == NULL )
    {
        printf( "Failed to load default image!\n" );
        success = false;
    }

    //Load up surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] = loadSurface( "04_key_presses/up.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ] == NULL )
    {
        printf( "Failed to load up image!\n" );
        success = false;
    }

    //Load down surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] = loadSurface( "04_key_presses/down.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ] == NULL )
    {
        printf( "Failed to load down image!\n" );
        success = false;
    }

    //Load left surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] = loadSurface( "04_key_presses/left.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ] == NULL )
    {
        printf( "Failed to load left image!\n" );
        success = false;
    }

    //Load right surface
    gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] = loadSurface( "04_key_presses/right.bmp" );
    if( gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ] == NULL )
    {
        printf( "Failed to load right image!\n" );
        success = false;
    }

    return success;
}

void close()
{
    //Deallocate surfaces
    for( int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i )
    {
        SDL_FreeSurface( gKeyPressSurfaces[ i ] );
        gKeyPressSurfaces[ i ] = NULL;
    }

    //Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path )
{
    //Load image at specified path
    SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
    if( loadedSurface == NULL )
    {
        printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
    }

    return loadedSurface;
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
        //Load media
        if( !loadMedia() )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;

            //Event handler
            SDL_Event e;

            //Set default current surface
            gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];

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
                        //User presses a key
                    else if( e.type == SDL_KEYDOWN )
                    {
                        //Select surfaces based on key press
                        switch( e.key.keysym.sym )
                        {
                            case SDLK_UP:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_UP ];
                                break;

                            case SDLK_DOWN:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DOWN ];
                                break;

                            case SDLK_LEFT:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_LEFT ];
                                break;

                            case SDLK_RIGHT:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_RIGHT ];
                                break;

                            default:
                                gCurrentSurface = gKeyPressSurfaces[ KEY_PRESS_SURFACE_DEFAULT ];
                                break;
                        }
                    }
                }

                //Apply the current image
                SDL_BlitSurface( gCurrentSurface, NULL, gScreenSurface, NULL );

                //Update the surface
                SDL_UpdateWindowSurface( gWindow );
            }
        }
    }

    //Free resources and close SDL
    close();

    return 0;
}