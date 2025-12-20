#include <stdio.h>
#include "GLCD.h"
#include "Board_Joystick.h"
#include "PACMAN.h"

extern void Main_Menu(void);
void Game_Select(void);

void Game_Select(void){
	int selection = 0;
	int prevSelection = 0;
	uint32_t state = 0;
	uint32_t prevState = 0;
	int i, j;
	char line[40];
	
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(1, 4, 1, (unsigned char*)" Game Menu");
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, 1, (unsigned char*)"> PACMAN");
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(5, 0, 1, (unsigned char*)"PACMAN Open World");
	GLCD_DisplayString(6, 0, 1, (unsigned char*)"Back to Main Menu");
	
	while(1){
		state = Joystick_GetState();
		
		if(state != prevState){
			if(state == JOYSTICK_DOWN){
				selection++;
				if(selection > 2){
					selection = 0;
				}
			}
			else if(state == JOYSTICK_UP){
				selection--;
				if(selection < 0){
					selection = 2;
				}
			}
			else if(state == JOYSTICK_CENTER){
				switch(selection){
					case 0: 
						Reset_Pacman();
						break;
					case 1: 
						Reset_Pacman_OpenWorld();
						break;
					case 2:
						Main_Menu();
						break;
				}
			}
			if(selection != prevSelection){
				for(i = 0; i < 3; i++){
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
							sprintf(line, "%sPACMAN", (i == selection) ? "> " : "");
							GLCD_DisplayString(4, 0, 1, (unsigned char*)line);
							break;
						case 1:
							GLCD_ClearLn(5, 1);
							sprintf(line, "%sPACMAN Open World", (i == selection) ? "> " : "");
							GLCD_DisplayString(5, 0, 1, (unsigned char*)line);
							break;			
						case 2:
							GLCD_ClearLn(6, 1);
							sprintf(line, "%sBack to Main Menu", (i == selection) ? "> " : "");
							GLCD_DisplayString(6, 0, 1, (unsigned char*)line);
							break;
					}
				}
				prevSelection = selection;
			}
			prevState = state;
		}
		for(j = 0; j < 100000; j++);
	}	
}
