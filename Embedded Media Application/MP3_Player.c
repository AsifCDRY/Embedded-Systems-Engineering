#include <stdio.h>
#include "GLCD.h"
#include "Board_Joystick.h"
#include "usb.h"
#include "usbcfg.h"
#include "usbhw.h"
#include "usbcore.h"
#include "usbaudio.h"
#include "Board_ADC.h"

extern void Main_Menu(void);
extern void MP3_Init(void);
void MP3_Player(void);

void MP3_Player(void){
	uint32_t state = 0;
	GLCD_Clear(Red);
	GLCD_SetBackColor(Red);
	GLCD_DisplayString(2, 2, 1, (unsigned char*)"Press CENTER to");
	GLCD_DisplayString(3, 4, 1, (unsigned char*)"play audio");
	GLCD_DisplayString(8, 0, 1, (unsigned char*)"Press DOWN to go back");

	while(1){
		state = Joystick_GetState();
		if(state == JOYSTICK_CENTER){
			GLCD_ClearLn(2, 1);
			GLCD_ClearLn(3, 1);
			GLCD_DisplayString(2, 2, 1, (unsigned char*)"Playing Audio...");
			MP3_Init();
		}
	}
}
