#include <stdio.h>
#include "GLCD.h"
#include "Board_Joystick.h"
#include "picture1.c"
#include "picture2.c"
#include "picture3.c"
#include "picture4.c"

extern void Main_Menu(void);
void Photo_Gallery(void);
void Scroll_Through_Gallery(int picNum);

void Photo_Gallery(void){
	int selection = 0;
	int prevSelection = 0;
	uint32_t state = 0;
	uint32_t prevState = 0;
	int i, j;
	char line[40];
	
	GLCD_Clear(Black);
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(Yellow);
	GLCD_DisplayString(1, 4, 1, (unsigned char*)"Photo Gallery");
	GLCD_SetBackColor(Green);
	GLCD_SetTextColor(Black);
	GLCD_DisplayString(4, 0, 1, (unsigned char*)"> Sunset Lake");
	GLCD_SetBackColor(Black);
	GLCD_SetTextColor(White);
	GLCD_DisplayString(5, 0, 1, (unsigned char*)"Winter Mountains");
	GLCD_DisplayString(6, 0, 1, (unsigned char*)"Summer Cowboy");
	GLCD_DisplayString(7, 0, 1, (unsigned char*)"Springtime Flowers");
	GLCD_DisplayString(8, 0, 1, (unsigned char*)"Back to Main Menu");
	
	while(1){
		state = Joystick_GetState();
		
		if(state != prevState){
			if(state == JOYSTICK_DOWN){
				selection++;
				if(selection > 4){
					selection = 0;
				}
			}
			else if(state == JOYSTICK_UP){
				selection--;
				if(selection < 0){
					selection = 4;
				}
			}
			else if(state == JOYSTICK_CENTER){
				switch(selection){
					case 0: 
						Scroll_Through_Gallery(selection); 
						break;
					case 1: 
						Scroll_Through_Gallery(selection);
						break;
					case 2:
						Scroll_Through_Gallery(selection);
						break;
					case 3:
						Scroll_Through_Gallery(selection);
						break;
					case 4:
						Main_Menu();
						break;
				}
			}
			if(selection != prevSelection){
				for(i = 0; i < 5; i++){
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
							sprintf(line, "%sSunset Lake", (i == selection) ? "> " : "");
							GLCD_DisplayString(4, 0, 1, (unsigned char*)line);
							break;
						case 1:
							GLCD_ClearLn(5, 1);
							sprintf(line, "%sWinter Mountains", (i == selection) ? "> " : "");
							GLCD_DisplayString(5, 0, 1, (unsigned char*)line);
							break;
						case 2:
							GLCD_ClearLn(6, 1);
							sprintf(line, "%sSummer Cowboy", (i == selection) ? "> " : "");
							GLCD_DisplayString(6, 0, 1, (unsigned char*)line);
							break;
						case 3:
							GLCD_ClearLn(7, 1);
							sprintf(line, "%sSpringtime Flowers", (i == selection) ? "> " : "");
							GLCD_DisplayString(7, 0, 1, (unsigned char*)line);
							break;
						case 4:
							GLCD_ClearLn(8, 1);
							sprintf(line, "%sBack to Main Menu", (i == selection) ? "> " : "");
							GLCD_DisplayString(8, 0, 1, (unsigned char*)line);
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

void Scroll_Through_Gallery(int picNum){
	int picture = picNum;
	int lastPicture = 0;
	uint32_t state = 0;
	uint32_t prevState = 0;
	GLCD_Clear(White);
	GLCD_SetBackColor(DarkCyan);
	GLCD_DisplayString(0, 2, 1, (unsigned char*)"Scroll w/ < or >");
	
	//Showing picture selected from previous menu
	switch(picture){
		case 0:
			GLCD_Bitmap(0, 30, PIC1_WIDTH, PIC1_HEIGHT, PIC1_PIXEL_DATA);
			break;
		case 1:
			GLCD_Bitmap(0, 30, PIC2_WIDTH, PIC2_HEIGHT, PIC2_PIXEL_DATA);
			break;
		case 2:
			GLCD_Bitmap(0, 30, PIC3_WIDTH, PIC3_HEIGHT, PIC3_PIXEL_DATA);
			break;
		case 3:
			GLCD_Bitmap(0, 30, PIC4_WIDTH, PIC4_HEIGHT, PIC4_PIXEL_DATA);
			break;
	}
	
	//Scrolling functionality	
	while(1){
		state = Joystick_GetState();
		
		if(state != prevState){
			if(state == JOYSTICK_CENTER){
				Photo_Gallery();
			}
			else if(state == JOYSTICK_RIGHT){
				picture++;
				if(picture > 3){
					picture = 0;
				}
			}
			else if(state == JOYSTICK_LEFT){
				picture--;
				if(picture < 0){
					picture = 3;
				}
			}
			if(picture != lastPicture){
				GLCD_Clear(White);
				GLCD_SetBackColor(DarkCyan);
				GLCD_DisplayString(0, 0, 1, (unsigned char*)"Centre for Main Menu");
				
				switch(picture){
					case 0:
						GLCD_Bitmap(0, 30, PIC1_WIDTH, PIC1_HEIGHT, PIC1_PIXEL_DATA);
						break;
					case 1:
						GLCD_Bitmap(0, 30, PIC2_WIDTH, PIC2_HEIGHT, PIC2_PIXEL_DATA);
						break;
					case 2:
						GLCD_Bitmap(0, 30, PIC3_WIDTH, PIC3_HEIGHT, PIC3_PIXEL_DATA);
						break;
					case 3:
						GLCD_Bitmap(0, 30, PIC4_WIDTH, PIC4_HEIGHT, PIC4_PIXEL_DATA);
						break;
				}
				lastPicture = picture;
			}
			prevState = state;
		}
	}
}
