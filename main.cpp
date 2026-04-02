#include<SDL3/SDL.h>
#include<random>
#define width 800
#define height 600
static const int number=50;
using namespace std;
class Ray{
public:
int end_x, end_y;
};

void setlines(Ray *line){
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>   choice(1,4);

for(int i=0; i<number; i++){
    switch(choice(gen)){
    case 1:{
    
        line[i].end_x=0;
        uniform_int_distribution<int> random_y(0,height);
        line[i].end_y=random_y(gen);
    
    break;
    }
    case 2:{
    
        line[i].end_x=width;
        uniform_int_distribution<int> random_y(0,height);
        line[i].end_y=random_y(gen);
   
    break;
}
    case 3:{
  
          line[i].end_y=0;
        uniform_int_distribution<int> random_x(0,width);
        line[i].end_x=random_x(gen);
    
    break;
}
    case 4:{

        line[i].end_y=height;
        uniform_int_distribution<int> random_x(0,width);
        line[i].end_x=random_x(gen);
    
    break;}
}}
}

void drawlines(SDL_Surface *surface, Ray *line, int x, int y){
for(int i=0; i<number; i++){
int x1=x, y1=y;
    int dx = abs(line[i].end_x - x1);
    int dy = abs(line[i].end_y - y1);

    int sx = (x1 < line[i].end_x) ? 1 : -1;
    int sy = (y1 < line[i].end_y) ? 1 : -1;

    int err = dx - dy;

    while (true) {
          SDL_Rect pixel=(SDL_Rect){x1,y1,1,1};
                Uint32 color=SDL_MapSurfaceRGB(surface, 225,225,225);
                SDL_FillSurfaceRect(surface, &pixel, color);
                

        if (x1 == line[i].end_x && y1 == line[i].end_y) break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }}
  
}

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
    int x=150,y=120,radius=40;
    Ray line[number];
    setlines(line);
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
    
        clear_screen(surface);
        drawcircle(surface, x, y, radius);
        drawlines(surface, line, x, y);
        
        SDL_UpdateWindowSurface(window);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
}