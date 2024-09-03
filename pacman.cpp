#include <stdio.h> 
#include <graphics.h> 
#include <conio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <math.h> 
#define UP 72 
#define DOWN 80 
#define LEFT 75 
#define RIGHT 77 
#define NUM_PELLETS 45 // Increased number of pellets 
#define NUM_OBSTACLES 7 // Number of obstacles 
struct Point { 
int x, y; 
}; 
struct Ghost { 
struct Point pos; 
}; 
struct Obstacle { 
struct Point pos; 
int radius; 
}; 
int score = 0; 
int pacManSpeed = 10; // Initial speed of Pac-Man 
struct Point pacMan; 
struct Ghost ghosts[2]; 
struct Point pellets[NUM_PELLETS]; 
struct Obstacle obstacles[NUM_OBSTACLES]; 
void drawPacMan() { 
setcolor(BLUE); // Set player color to blue 
setfillstyle(SOLID_FILL, BLUE); // Set fill color to blue 
pieslice(pacMan.x, pacMan.y, 45, 315, 15); 
floodfill(pacMan.x, pacMan.y, BLUE); // Flood fill with blue color 
} 
void drawGhost(struct Ghost ghost) { 
setcolor(LIGHTRED); 
circle(ghost.pos.x, ghost.pos.y, 15); 
floodfill(ghost.pos.x, ghost.pos.y, LIGHTRED); 
} 
void drawPellets() { 
for (int i = 0; i < NUM_PELLETS; i++) { 
if (pellets[i].x != -1) { 
setcolor(LIGHTBLUE); // Change pellet color to blue 
circle(pellets[i].x, pellets[i].y, 2); 
} 
} 
} 
void drawObstacles() { 
for (int i = 0; i < NUM_OBSTACLES; i++) { 
setcolor(RED); // Set obstacle border color to red 

setfillstyle(SOLID_FILL, RED); // Set obstacle fill color to red 
circle(obstacles[i].pos.x, obstacles[i].pos.y, obstacles[i].radius); 
floodfill(obstacles[i].pos.x, obstacles[i].pos.y, RED); 
} 
} 
void initialize() { 
srand(time(NULL)); 
// Initialize Pac-Man position 
pacMan.x = 350; // Start Pac-Man in the middle horizontally 
pacMan.y = 250; // Start Pac-Man near the middle vertically 
// Initialize ghosts 
for (int i = 0; i < 2; i++) { 
ghosts[i].pos.x = rand() % 600 + 50; // Random position within the window 
ghosts[i].pos.y = rand() % 400 + 50; // Random position within the window 
} 
// Initialize pellets 
for (int i = 0; i < NUM_PELLETS; i++) { 
pellets[i].x = rand() % 600 + 50; // Random position within the window 
pellets[i].y = rand() % 400 + 50; // Random position within the window 
} 
// Initialize obstacles with new positions and sizes 
obstacles[0].pos.x = 100; 
obstacles[0].pos.y = 100; 
obstacles[0].radius = 20; 
obstacles[1].pos.x = 200; 
obstacles[1].pos.y = 300; 
obstacles[1].radius = 15; 
obstacles[2].pos.x = 400; 
obstacles[2].pos.y = 200; 
obstacles[2].radius = 25; 
obstacles[3].pos.x = 550; 
obstacles[3].pos.y = 400; 
obstacles[3].radius = 30; 
obstacles[4].pos.x = 650; 
obstacles[4].pos.y = 150; 
obstacles[4].radius = 20; 
obstacles[5].pos.x = 300; 
obstacles[5].pos.y = 450; 
obstacles[5].radius = 25; 
obstacles[6].pos.x = 150; 
obstacles[6].pos.y = 350; 
obstacles[6].radius = 15; 
} 
int checkCollision(struct Point p1, struct Point p2, int radius) { 
int distance = sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)); 
if (distance <= radius) 
return 1; // Collision detected 
else 
return 0; // No collision 
} 
void updateScore() { 
setcolor(WHITE); // Change score display color to white 
outtextxy(10, 10, "Score: "); 
char scoreStr[10]; 
sprintf(scoreStr, "%d", score); 
outtextxy(90, 10, scoreStr); // Adjust position 
} 
int main() { 
int gd = DETECT, gm; 
int ch; 
initwindow(700, 500, "Pac-Man Game"); // Initialize window with new size 
initialize(); 
while (1) { 
if (kbhit()) { 
ch = getch(); 
if (ch == 27) // ESC key 
break; 
if (ch == UP) 
pacMan.y -= pacManSpeed; 
if (ch == DOWN) 
pacMan.y += pacManSpeed; 
if (ch == LEFT) 
pacMan.x -= pacManSpeed; 

if (ch == RIGHT) 
pacMan.x += pacManSpeed; 
} 
cleardevice(); 
// Draw Pac-Man 
drawPacMan(); 
// Draw pellets 
drawPellets(); 
// Draw obstacles 
drawObstacles(); 
// Draw ghosts 
for (int i = 0; i < 2; i++) 
drawGhost(ghosts[i]); 
// Check collision with pellets 
for (int i = 0; i < NUM_PELLETS; i++) { 
if (pellets[i].x != -1 && checkCollision(pacMan, pellets[i], 15)) { 
pellets[i].x = -1; // Remove pellet 
score += 10; // Increase score 
} 
} 
// Check collision with ghosts 
for (int i = 0; i < 2; i++) { 
if (checkCollision(pacMan, ghosts[i].pos, 15)) { 
outtextxy(250, 200, "Game Over!"); // Adjust position 
delay(2000); 
closegraph(); 
exit(0); 
} 
} 
// Check collision with obstacles 
for (int i = 0; i < NUM_OBSTACLES; i++) { 
if (checkCollision(pacMan, obstacles[i].pos, obstacles[i].radius)) { 
outtextxy(250, 200, "Game Over!"); // Adjust position 
delay(2000); 
closegraph(); 
exit(0); 
} 
} 
updateScore(); 
delay(100); // Adjust the speed of Pac-Man 
} 
closegraph(); 
return 0; 
}
