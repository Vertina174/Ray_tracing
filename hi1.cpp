#include<SDL3/SDL.h>
#define width 800
#define height 600

using namespace std;

void drawcircle(SDL_Surface *surface, int x, int y, int radius){
    
    for(int i=x-radius; i<x+radius; i++ ){
        for(int j=y-radius; j<y+radius; j++){
            int dis=((i-x)*(i-x))+((j-y)*(j-y));
            if(dis>radius*radius)   continue;
            SDL_Rect pixel=(SDL_Rect){i,j,1,1};
                Uint32 color=SDL_MapSurfaceRGB(surface, 225,225,225);
                SDL_FillSurfaceRect(surface, &pixel, color);
        }
    }
}
void clear_screen(SDL_Surface *surface){
Uint32 black=SDL_MapSurfaceRGB(surface,0,0,0);
    SDL_Rect screen=(SDL_Rect){0,0,width,height};
            SDL_FillSurfaceRect(surface, &screen, black);
}
int main()
{
    SDL_Window *window= SDL_CreateWindow("Ray Tracing Simulator", width, height, 0);
    SDL_Surface *surface= SDL_GetWindowSurface(window);

    bool status=true;
    int x=150,y=120,radius=20;
    while(status){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            
            if(event.type==SDL_EVENT_QUIT)
                status=false;
            if(event.type==SDL_EVENT_MOUSE_MOTION && event.motion.state!=0){
                x=event.motion.x;
                y=event.motion.y;
        }
    }
    
        if(x<radius || x>width-radius || y<radius || y>height-radius)   continue;
        drawcircle(surface, x, y, radius);
        
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}