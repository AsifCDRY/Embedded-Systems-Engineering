#include "GLCD.h"
#include "Board_LED.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PACMAN.h"

extern void Game_Select(void);

char scoreText[20], livesText[20];
int numOfDots;

Pacman pac;
Ghost ghost;

void delay(void){
	int i;
	for(i = 0; i < 2500000; i++);
}

int maze[MAZE_H][MAZE_W] = {
		
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,1,1,0,0,0,1,},
	{1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,},
	{1,0,1,0,1,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,0,0,1,0,0,0,1,},
	{1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,1,},
	{1,1,1,0,1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,1,0,0,1,},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,},
	{1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,0,1,},
	{1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,},
	{1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
};

int mazeOriginal[MAZE_H][MAZE_W] = {
		
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,1,0,0,1,0,1,0,1,1,1,0,0,0,1,},
	{1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,0,0,1,0,0,0,1,0,1,0,0,0,1,0,0,0,1,},
	{1,0,1,0,1,1,1,0,1,1,0,0,1,0,1,0,0,1,0,1,1,1,0,1,1,0,0,1,0,0,0,1,},
	{1,0,0,0,1,0,0,0,0,1,0,0,0,1,1,0,0,1,1,1,0,0,0,0,1,0,0,0,1,0,0,1,},
	{1,1,1,0,1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,0,1,0,0,1,},
	{1,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1,0,0,1,},
	{1,0,1,1,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1,0,1,1,1,0,1,1,0,0,1,},
	{1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,1,0,0,1,},
	{1,0,1,0,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,1,1,1,0,1,1,1,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,1,0,1,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,1,},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,1,1,1,0,0,0,0,1,1,1,0,0,0,0,0,0,1,1,1,0,0,0,0,1,1,1,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
};

void DrawBlock(int x, int y, int size, int color) {
	int i, j;
	GLCD_SetTextColor(color);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			GLCD_PutPixel(x + i, y + j);
		}
	}
}

void DrawDot(int x, int y, int color) {
	GLCD_SetTextColor(color);
	GLCD_PutPixel(x, y);
	GLCD_PutPixel(x+1, y);
	GLCD_PutPixel(x, y+1);
	GLCD_PutPixel(x+1, y+1);
}

void Reset_Pacman(void){
	int x, y;  
	for (y = 0; y < MAZE_H; y++) {
		for (x = 0; x < MAZE_W; x++) {
        if (mazeOriginal[y][x] == 1)
					maze[y][x] = 1;   // Wall
        else if (mazeOriginal[y][x] == 0)
          maze[y][x] = 0;  // Dot
        else
          maze[y][x] = 2;  // Empty space
			}
   }
	Run_Pacman();
}

void DrawPacman(void) {
	int px = pac.x * TILE_SIZE;
	int py = (pac.y+1) * TILE_SIZE;
	DrawBlock(px, py, TILE_SIZE, Yellow);
}

void DrawGhost(void) {
	int px = ghost.x * TILE_SIZE;
	int py = (ghost.y+1) * TILE_SIZE;
	DrawBlock(px, py, TILE_SIZE, Red);
}

void Pacman_Init(void) {
  GLCD_Clear(Black);
  Pacman_DrawMaze();
	LED_Initialize();

	pac.x = 15; 
	pac.y = 18; 
	pac.lives = 3; 
	pac.score = 0;
  LED_SetOut(7);
	
	ghost.x = 15; 
	ghost.y = 10; 
	ghost.dir = LEFT;

  GLCD_SetBackColor(Black);
  GLCD_SetTextColor(White);
  DrawPacman();
  DrawGhost();
}

void Pacman_DrawMaze(void) {
  int x, y;  
	for (y = 0; y < MAZE_H; y++) {
		for (x = 0; x < MAZE_W; x++) {
        int px = x * TILE_SIZE;
        int py = y * TILE_SIZE + TILE_SIZE;

        if (maze[y][x] == 1)
					DrawBlock(px, py, TILE_SIZE, Blue);   // Wall
        else if (maze[y][x] == 0){
          DrawDot(px + TILE_SIZE/2, py + TILE_SIZE/2, Yellow);  // Dot
					numOfDots++;
				}
        else
          DrawBlock(px, py, TILE_SIZE, Black);  // Empty space
			}
   }
}

void Pacman_MovePlayer(int dir) {
    int newX = pac.x;
    int newY = pac.y;

    if (dir == UP) 
			newY--;
    else if (dir == DOWN) 
			newY++;
    else if (dir == LEFT) 
			newX--;
    else if (dir == RIGHT) 
			newX++;

    // Check if wall
    if (maze[newY][newX] != 1) {
        // Erase old position
        DrawBlock(pac.x*TILE_SIZE, (pac.y+1)*TILE_SIZE, TILE_SIZE, Black);
        // Update position
        pac.x = newX;
        pac.y = newY;
        // Eat dot
        if (maze[newY][newX] == 0) {
            maze[newY][newX] = 2;
            pac.score++;
						numOfDots--;
        }

        // Redraw Pac-Man
        DrawPacman();
    }
}

void Ghost_Move(void) {
    int oldX = ghost.x;
    int oldY = ghost.y;
    int newX = oldX;
    int newY = oldY;
		int i, j;

    // ----- 1. Small chance to chase Pac-Man -----
    // 40% chance to try to move toward pac-man
    int chase = (rand() % 100);

    int tryDir[4];
    int tryCount = 0;

    if (chase <= 60) {
        // Prioritize the direction that minimizes distance
        if (pac.x < ghost.x) 
					tryDir[tryCount++] = LEFT;
        if (pac.x > ghost.x) 
					tryDir[tryCount++] = RIGHT;
        if (pac.y < ghost.y) 
					tryDir[tryCount++] = UP;
        if (pac.y > ghost.y)
					tryDir[tryCount++] = DOWN;
    }

    // ----- 2. Add random directions after chase attempts -----
    while (tryCount < 4) {
        int r = rand() % 4;
        bool exists = false;
        for (i = 0; i < tryCount; i++) {
            if (tryDir[i] == r){
							exists = true;
						}
        }
        if (!exists){
					tryDir[tryCount++] = r;
				}
    }

    // ----- 3. Try directions in prioritized order -----
    for (j = 0; j < 4; j++) {
        int dir = tryDir[j];

        newX = oldX;
        newY = oldY;

        if (dir == UP) 
					newY--;
        else if (dir == DOWN) 
					newY++;
        else if (dir == LEFT) 
					newX--;
        else if (dir == RIGHT) 
					newX++;

        // check boundaries & walls
        if (newX < 0 || newX >= MAZE_W || newY < 0 || newY >= MAZE_H)
            continue;

        if (maze[newY][newX] != 1) {
            // found valid direction
            ghost.dir = dir;
            break;
        }
    }

    // ----- 4. Move using the chosen direction -----
    newX = ghost.x;
    newY = ghost.y;

    if (ghost.dir == UP) 
			newY--;
    else if (ghost.dir == DOWN) 
			newY++;
    else if (ghost.dir == LEFT) 
			newX--;
    else if (ghost.dir == RIGHT) 
			newX++;

    // If selected move is invalid, do nothing
    if (maze[newY][newX] == 1) 
			return;

    // ----- 5. Restore old tile -----
    redrawTile(oldX, oldY);

    // ----- 6. Update position -----
    ghost.x = newX;
    ghost.y = newY;

    // ----- 7. Draw ghost -----
    DrawGhost();
}

void redrawTile(int gx, int gy) {
	int px = gx * TILE_SIZE;
  int py = (gy+1) * TILE_SIZE;
  
	if (gx < 0 || gx >= MAZE_W || gy < 0 || gy >= MAZE_H)
        return;

    DrawBlock(px, py, TILE_SIZE, Black);

    if (maze[gy][gx] == 1) {
       DrawBlock(px, py, TILE_SIZE, Blue);
    }
    else if (maze[gy][gx] == 0) {
       DrawDot(px + TILE_SIZE/2, py + TILE_SIZE/2, Yellow);
    }
    else {
			DrawBlock(px, py, TILE_SIZE, Black);
    }
}

void Run_Pacman(void) {
	bool won = false;
	numOfDots = 0;
  Pacman_Init();
	Joystick_Initialize();
	
  while (pac.lives > 0) {
		int dir = Joystick_GetState();

		if (dir != -1){
			Pacman_MovePlayer(dir);
		}
		
		Ghost_Move();

		if (pac.x == ghost.x && pac.y == ghost.y) {
				pac.lives--;
				LED_Off(pac.lives);
				pac.x = 15;
				pac.y = 18;
				DrawPacman();
		}
		
		if (pac.lives == 0){
				won = false;
				Game_End_Screen(won);
		}
		
		if(numOfDots == 0){
			won = true;
			Game_End_Screen(won);
		}
		
		GLCD_SetBackColor(Black);	
		GLCD_SetTextColor(White);
		sprintf(scoreText, "Pts:%d", pac.score);
		sprintf(livesText, "Lvs:%d", pac.lives);
		GLCD_DisplayString(0, 0, 1, (unsigned char*)scoreText);
		GLCD_DisplayString(0, 15, 1, (unsigned char*)livesText);
		
		delay();
    }
}

void Game_End_Screen(bool win){
	int selection = 0;
	int prevSelection = 0;
	int i, j;
	char line[40];
	uint32_t state = 0;
	uint32_t prevState = 0;
	
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	
	if(win == true){
		GLCD_SetTextColor(Green);
		GLCD_DisplayString(2, 4, 1, (unsigned char*)"YOU WON!");
		GLCD_SetBackColor(Green);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString(4, 0, 1, (unsigned char*)"> Play Again");
	}
	else{
		GLCD_SetTextColor(Red);
		GLCD_DisplayString(2, 4, 1, (unsigned char*)"GAME OVER");
		GLCD_SetBackColor(Green);
		GLCD_SetTextColor(Black);
		GLCD_DisplayString(4, 0, 1, (unsigned char*)"> Try Again");
	}

	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(5, 0, 1, (unsigned char*)"Exit");
	
	while(1){
		state = Joystick_GetState();
		
		if(state != prevState){
			if(state == JOYSTICK_DOWN){
				selection++;
				if(selection > 1){
					selection = 0;
				}
			}
			else if(state == JOYSTICK_UP){
				selection--;
				if(selection < 0){
					selection = 1;
				}
			}
			else if(state == JOYSTICK_CENTER){
				switch(selection){
					case 0:
						Reset_Pacman(); 
						break;
					case 1:
						Game_Select(); 
						break;
				}
			}
			if(selection != prevSelection){
				for(i = 0; i < 2; i++){
					if(i == selection){
						GLCD_SetBackColor(Green);
						GLCD_SetTextColor(Black);
					}
					else{
						GLCD_SetBackColor(Black);
						GLCD_SetTextColor(White);
					}
					switch(i){
						case 0:
							GLCD_ClearLn(4, 1);
							if(win == true){
								sprintf(line, "%sPlay Again", (i == selection) ? "> " : "");
							}
							else{
								sprintf(line, "%sTry Again", (i == selection) ? "> " : "");
							}
							GLCD_DisplayString(4, 0, 1, (unsigned char*)line);
							break;
						case 1:
							GLCD_ClearLn(5, 1);
							sprintf(line, "%sExit", (i == selection) ? "> " : "");
							GLCD_DisplayString(5, 0, 1, (unsigned char*)line);
							break;
					}
				}
				prevSelection = selection;
			}
			prevState = state;
		}
		for(j = 0; j < 200000; j++);
	}	
	
}
