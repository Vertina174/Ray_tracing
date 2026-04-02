#include<SDL3/SDL.h>
#include<random>
#define width 1200
#define height 600
#define glow  0xfabb18// light orange
static const int number=500;// Number of Rays
using namespace std;

// Ray class represents a ray with an endpoint
class Ray{
public:
int end_x, end_y;
};

// Circle class represents a circle with position, radius, and speed
class Circle{
public:
int x,y,radius;
float speed;
};

// Initialize rays with random endpoints at the edges of the screen
void setlines(Ray *line){
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<int>   choice(1,4);

for(int i=0; i<number; i++){
    switch(choice(gen)){
    case 1:{// width constant height vairable
    
        line[i].end_x=0; 
        uniform_int_distribution<int> random_y(0,height);
        line[i].end_y=random_y(gen);
    
    break;
    }
    case 2:{// width constant height vairable
    
        line[i].end_x=width;
        uniform_int_distribution<int> random_y(0,height);
        line[i].end_y=random_y(gen);
   
    break;
}
    case 3:{// height constant width variable
  
          line[i].end_y=0; 
        uniform_int_distribution<int> random_x(0,width);
        line[i].end_x=random_x(gen);
    
    break;
}
    case 4:{// height constant width variable

        line[i].end_y=height; 
        uniform_int_distribution<int> random_x(0,width);
        line[i].end_x=random_x(gen);
    
    break;}
}}
}

// Draw rays from the first circle to their endpoints, stopping at the second circle (obstacle)
void drawlines(SDL_Surface *surface, Ray *line, Circle *circle){
for(int i=0; i<number; i++){// Here, We used Bresenham Algorithm to generate smooth straight lines...
int x1=circle[0].x, y1=circle[0].y;
    int dx = abs(line[i].end_x - x1);
    int dy = abs(line[i].end_y - y1);

    int sx = (x1 < line[i].end_x) ? 1 : -1;
    int sy = (y1 < line[i].end_y) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        float dis=(x1-circle[1].x)*(x1-circle[1].x)+(y1-circle[1].y)*(y1-circle[1].y);
        if(dis<=circle[1].radius*circle[1].radius)// if line touches the second circle stop Drawing the line...
                break;
          SDL_Rect pixel=(SDL_Rect){x1,y1,2,2};
                Uint32 color=SDL_MapSurfaceRGB(surface, 225,225,225);
                SDL_FillSurfaceRect(surface, &pixel, glow);
                

        if (x1 == line[i].end_x && y1 == line[i].end_y) break;// will exit when the line is competetly drawn...

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

// Clear the screen by filling it with black
void clear_screen(SDL_Surface *surface){
Uint32 black=SDL_MapSurfaceRGB(surface,0,0,0);
    SDL_Rect screen=(SDL_Rect){0,0,width,height};
            SDL_FillSurfaceRect(surface, &screen, black);
}

// Initialize two circles: first is controllable, second moves vertically
void setcircles(Circle *circle){
circle[0].x=150;
circle[0].y=120;
circle[0].radius=40;

circle[1].x=500;
circle[1].y=300;
circle[1].radius=80;
circle[1].speed=3;// speed only for second circle w.r.t y-axis

}

// Draw the first circle (light source, controlled by mouse)
void drawcircle1(SDL_Surface *surface, Circle circle){
    int radius=circle.radius=30;
    int x=circle.x;
    int y=circle.y;

  for(int i=x-radius; i<=x+radius; i++) {
    for(int j=y-radius; j<=y+radius; j++){
        float dis=(i-x)*(i-x)+(j-y)*(j-y);
        if(dis>radius* radius)  continue;
          Uint32 color=SDL_MapSurfaceRGB(surface, 225, 225, 225);
        SDL_Rect pixel =(SDL_Rect){i,j,1,1};
        SDL_FillSurfaceRect(surface, &pixel, color);
    }

   }
}

// Draw the second circle (obstacle that blocks rays)
void drawcircle2(SDL_Surface *surface, Circle circle){
    int radius=circle.radius;
    int x=circle.x;
    int y=circle.y;
  for(int i=x-radius; i<=x+radius; i++) {
    for(int j=y-radius; j<=y+radius; j++){
        float dis=(i-x)*(i-x)+(j-y)*(j-y);
        if(dis>radius* radius)  continue; // Stops Drawing if outside the circle...
          Uint32 color=SDL_MapSurfaceRGB(surface, 225, 225, 225);
        SDL_Rect pixel =(SDL_Rect){i,j,1,1};
        SDL_FillSurfaceRect(surface, &pixel, color);
    }

   }
}

// Main program: renders ray tracing simulation with interactive light source
// Move mouse to control the light source, watch rays bounce off the obstacles
int main(){
    SDL_Window *window= SDL_CreateWindow("Ray Tracing Simulator", width, height, 0);
    SDL_Surface *surface= SDL_GetWindowSurface(window);
    Circle circle[2];// Create Two object for light source and obstacle
    setcircles(circle);
 
    Ray line[number];  // Array of rays
    setlines(line);     // Initialize ray endpoints

    // Main event loop - runs until window is closed
    bool status=true;
    while(status){
        // Handle input events
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            
            if(event.type==SDL_EVENT_QUIT)
                status=false;
            // Update light source (circle[0]) position based on mouse movement
            if(event.type==SDL_EVENT_MOUSE_MOTION && event.motion.state!=0){
                circle[0].x=event.motion.x;
                circle[0].y=event.motion.y;
        }
    }
        // Render Frame
        clear_screen(surface);        // Clear previous screen
        drawlines(surface, line, circle);  // Draw rays from First Circle
        drawcircle1(surface, circle[0]);  // Draw First Circle
        drawcircle2(surface, circle[1]);  // Draw Second Circle(Obstacle)
      
      // Move second circle and bounce at screen edges
      circle[1].y+=circle[1].speed;
      if(circle[1].y<circle[1].radius || circle[1].y>height-circle[1].radius)
            circle[1].speed*=-1;
        
        SDL_UpdateWindowSurface(window);
    }
    
    // Cleanup and exit
    SDL_DestroyWindow(window);
    SDL_Quit();
}