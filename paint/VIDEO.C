 #include <dos.h>
 #include <string.h>
 #include "video.h"

 int isToggled = 0;

 unsigned char far *video_memory = (unsigned char far*)0xA0000000L;

 void toggleVideoMode() {
	if (!isToggled) {
		union REGS regs;
		regs.x.ax = 0x13;
		int86(0x10, &regs, &regs);
	} else {
		union REGS regs;
		regs.h.ah = 0x00;
		regs.h.al = 0x03;
		int86(0x10, &regs, &regs);
	}
 }

 void plotPixel(int pixelX, int pixelY, unsigned char pixelColor) {
	if (pixelX < 320 && pixelY < 200) {
		video_memory[(pixelY * 320) + pixelX] = pixelColor;
	}
 }

 int fetchPixelColor(int pixelX, int pixelY) {
	int colour;
	colour = video_memory[(pixelY * 320) + pixelX];
	return colour;
 }
