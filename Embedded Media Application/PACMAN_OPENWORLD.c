#include "GLCD.h"
#include "Board_LED.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "PACMAN.h"

extern void Game_Select(void);

char scoreText_OP[20], livesText_OP[20];
int numOfDots_OP;

Pacman pac_op;
Ghost ghost_op;

void delay_OP(void){
	int i;
	for(i = 0; i < 2500000; i++);
}

int mazeOP[MAZE_H][MAZE_W] = {
		
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
};

int mazeOriginalOP[MAZE_H][MAZE_W] = {
		
	{2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
};

void DrawBlock_OP(int x, int y, int size, int color) {
	int i, j;
	GLCD_SetTextColor(color);
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			GLCD_PutPixel(x + i, y + j);
		}
	}
}

void DrawDot_OP(int x, int y, int color) {
	GLCD_SetTextColor(color);
	GLCD_PutPixel(x, y);
	GLCD_PutPixel(x+1, y);
	GLCD_PutPixel(x, y+1);
	GLCD_PutPixel(x+1, y+1);
}

void Reset_Pacman_OpenWorld(void){
	int x, y;  
	for (y = 0; y < MAZE_H; y++) {
		for (x = 0; x < MAZE_W; x++) {
        if (mazeOriginalOP[y][x] == 1)
					mazeOP[y][x] = 1;   // Wall
        else if (mazeOriginalOP[y][x] == 0)
          mazeOP[y][x] = 0;  // Dot
        else
          mazeOP[y][x] = 2;  // Empty space
			}
   }
	Run_Pacman_OpenWorld();
}

void DrawPacman_OP(void) {
	int px = pac_op.x * TILE_SIZE;
	int py = (pac_op.y+1) * TILE_SIZE;
	DrawBlock_OP(px, py, TILE_SIZE, Yellow);
}

void DrawGhost_OP(void) {
	int px = ghost_op.x * TILE_SIZE;
	int py = (ghost_op.y+1) * TILE_SIZE;
	DrawBlock_OP(px, py, TILE_SIZE, Red);
}

void Pacman_Init_OP(void) {
  GLCD_Clear(Black);
  Pacman_DrawMaze_OP();
	LED_Initialize();

	pac_op.x = 15; 
	pac_op.y = 18; 
	pac_op.lives = 3; 
	pac_op.score = 0;
  LED_SetOut(7);
	
	ghost_op.x = 15; 
	ghost_op.y = 10; 
	ghost_op.dir = LEFT;

  GLCD_SetBackColor(Black);
  GLCD_SetTextColor(White);
  DrawPacman_OP();
  DrawGhost_OP();
}

void Pacman_DrawMaze_OP(void) {
  int x, y;  
	for (y = 0; y < MAZE_H; y++) {
		for (x = 0; x < MAZE_W; x++) {
        int px = x * TILE_SIZE;
        int py = y * TILE_SIZE + TILE_SIZE;

        if (mazeOP[y][x] == 1)
					DrawBlock_OP(px, py, TILE_SIZE, Blue);   // Wall
        else if (mazeOP[y][x] == 0){
          DrawDot_OP(px + TILE_SIZE/2, py + TILE_SIZE/2, Yellow);  // Dot
					numOfDots_OP++;
				}
        else
          DrawBlock_OP(px, py, TILE_SIZE, Black);  // Empty space
			}
   }
}

void Pacman_MovePlayer_OP(int dir) {
    int newX = pac_op.x;
    int newY = pac_op.y;

    if (dir == UP) 
			newY--;
    else if (dir == DOWN) 
			newY++;
    else if (dir == LEFT) 
			newX--;
    else if (dir == RIGHT) 
			newX++;

    // Check if wall
    if (mazeOP[newY][newX] != 1) {
        // Erase old position
        DrawBlock_OP(pac_op.x*TILE_SIZE, (pac_op.y+1)*TILE_SIZE, TILE_SIZE, Black);
        // Update position
        pac_op.x = newX;
        pac_op.y = newY;
        // Eat dot
        if (mazeOP[newY][newX] == 0) {
            mazeOP[newY][newX] = 2;
            pac_op.score++;
						numOfDots_OP--;
        }

        // Redraw Pac-Man
        DrawPacman_OP();
    }
}

void Ghost_Move_OP(void) {
    int oldX = ghost_op.x;
    int oldY = ghost_op.y;
    int newX = oldX;
    int newY = oldY;
		int i, j;

    // ----- 1. Small chance to chase Pac-Man -----
    // 40% chance to try to move toward pac-man
    int chase = (rand() % 100);

    int tryDir[4];
    int tryCount = 0;

    if (chase <= 65) {
        // Prioritize the direction that minimizes distance
        if (pac_op.x < ghost_op.x) 
					tryDir[tryCount++] = LEFT;
        if (pac_op.x > ghost_op.x) 
					tryDir[tryCount++] = RIGHT;
        if (pac_op.y < ghost_op.y) 
					tryDir[tryCount++] = UP;
        if (pac_op.y > ghost_op.y) 
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

        if (mazeOP[newY][newX] != 1) {
            // found valid direction
            ghost_op.dir = dir;
            break;
        }
    }

    // ----- 4. Move using the chosen direction -----
    newX = ghost_op.x;
    newY = ghost_op.y;

    if (ghost_op.dir == UP) 
			newY--;
    else if (ghost_op.dir == DOWN) 
			newY++;
    else if (ghost_op.dir == LEFT) 
			newX--;
    else if (ghost_op.dir == RIGHT) 
			newX++;

    // If selected move is invalid, do nothing
    if (mazeOP[newY][newX] == 1) 
			return;

    // ----- 5. Restore old tile -----
    redrawTile_OP(oldX, oldY);

    // ----- 6. Update position -----
    ghost_op.x = newX;
    ghost_op.y = newY;

    // ----- 7. Draw ghost_op -----
    DrawGhost_OP();
}

void redrawTile_OP(int gx, int gy) {
	int px = gx * TILE_SIZE;
  int py = (gy+1) * TILE_SIZE;
  
	if (gx < 0 || gx >= MAZE_W || gy < 0 || gy >= MAZE_H)
        return;

    DrawBlock_OP(px, py, TILE_SIZE, Black);

    if (mazeOP[gy][gx] == 1) {
       DrawBlock_OP(px, py, TILE_SIZE, Blue);
    }
    else if (mazeOP[gy][gx] == 0) {
       DrawDot_OP(px + TILE_SIZE/2, py + TILE_SIZE/2, Yellow);
    }
    else {
			DrawBlock_OP(px, py, TILE_SIZE, Black);
    }
}

void Run_Pacman_OpenWorld(void) {
	bool won = false;
	numOfDots_OP = 0;
  Pacman_Init_OP();
	Joystick_Initialize();
	
  while (pac_op.lives > 0) {
		int dir = Joystick_GetState();

		if (dir != -1){
			Pacman_MovePlayer_OP(dir);
		}
		
		Ghost_Move_OP();

		if (pac_op.x == ghost_op.x && pac_op.y == ghost_op.y) {
				pac_op.lives--;
				LED_Off(pac_op.lives);
				pac_op.x = 15;
				pac_op.y = 18;
				DrawPacman_OP();
		}
		
		if (pac_op.lives == 0){
				won = false;
				Game_End_Screen_OP(won);
		}
		
		if(numOfDots_OP == 0){
			won = true;
			Game_End_Screen_OP(won);
		}
		
		GLCD_SetBackColor(Black);	
		GLCD_SetTextColor(White);
		sprintf(scoreText_OP, "Pts:%d", pac_op.score);
		sprintf(livesText_OP, "Lvs:%d", pac_op.lives);
		GLCD_DisplayString(0, 0, 1, (unsigned char*)scoreText_OP);
		GLCD_DisplayString(0, 15, 1, (unsigned char*)livesText_OP);
		
		delay_OP();
    }
}

void Game_End_Screen_OP(bool win){
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
						Reset_Pacman_OpenWorld(); 
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
