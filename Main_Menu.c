#include <stdio.h>
#include "GLCD.h"
#include "Board_Joystick.h"

extern void USB_Connect(uint32_t con);
extern void Photo_Gallery(void);
extern void MP3_Player(void);
extern void MP3_Init(void);
extern void Game_Select(void);
void Main_Menu(void);

int main (void){
	GLCD_Init();
	Joystick_Initialize();
	Main_Menu();
}

void Main_Menu(void){
	int selection = 0;
	int prevSelection = 0;
	uint32_t state = 0;
	uint32_t prevState = 0;
	int i, j;
	char line[40];
	
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(1, 4, 1, (unsigned char*)" Menu Select");
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, 1, (unsigned char*)"> 1. Photo Gallery");
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(5, 0, 1, (unsigned char*)"2. MP3 Player");
	GLCD_DisplayString(6, 0, 1, (unsigned char*)"3. Games");
	GLCD_DisplayString(8, 0, 1, (unsigned char*)"Use Joystick up/down");
	GLCD_DisplayString(9, 0, 1, (unsigned char*)"   Select w/ centre  ");

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
						Photo_Gallery(); 
						break;
					case 1:
						MP3_Player(); 
						break;
					case 2:
						Game_Select(); 
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
							sprintf(line, "%s1. Photo Gallery", (i == selection) ? "> " : "");
							GLCD_DisplayString(4, 0, 1, (unsigned char*)line);
							break;
						case 1:
							GLCD_ClearLn(5, 1);
							sprintf(line, "%s2. MP3 Player", (i == selection) ? "> " : "");
							GLCD_DisplayString(5, 0, 1, (unsigned char*)line);
							break;
						case 2:
							GLCD_ClearLn(6, 1);
							sprintf(line, "%s3. Games", (i == selection) ? "> " : "");
							GLCD_DisplayString(6, 0, 1, (unsigned char*)line);
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
