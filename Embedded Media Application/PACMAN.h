#ifndef PACMAN_H
#define PACMAN_H

#include "GLCD.h"
#include <stdlib.h>
#include <stdbool.h>
#include "Board_Joystick.h"


#define MAZE_W 32
#define MAZE_H 24
#define TILE_SIZE 10
#define UP JOYSTICK_UP
#define DOWN JOYSTICK_DOWN
#define LEFT JOYSTICK_LEFT
#define RIGHT JOYSTICK_RIGHT

typedef struct{
	int x, y;
	int lives;
	int score;
} Pacman;

typedef struct{
	int x, y;
	int dir;
} Ghost;

void Pacman_Init(void);
void Pacman_Init_OP(void);
void Reset_Pacman(void);
void Reset_Pacman_OpenWorld(void);
void Run_Pacman(void);
void Run_Pacman_OpenWorld(void);
void Pacman_DrawMaze(void);
void Pacman_DrawMaze_OP(void);
void Pacman_MovePlayer(int dir);
void Pacman_MovePlayer_OP(int dir);
void Ghost_Move(void);
void Ghost_Move_OP(void);
void redrawTile(int gx, int gy);
void redrawTile_OP(int gx, int gy);
void Game_End_Screen(bool win);
void Game_End_Screen_OP(bool win);

#endif
