#include <dos.h>;
#include "video.h";
#include "mouse.h";

int mouseX = 0;
int mouseY = 0;
int leftClicked;
int rightClicked;
int middleClicked;

int mouseInit(void) {
	union REGS regs;
	regs.x.ax = 0x00;
	int86(0x33, &regs, &regs);
	if (regs.x.ax == 0xFFFF) {
		return 0;
	} else {
		return 99;
	}
}

void pollMouse(void) {
	union REGS regs;
	regs.x.ax = 0x03;
	int86(0x33, &regs, &regs);
	mouseX = (regs.x.cx / 2);
	mouseY = regs.x.dx;
	if (regs.x.bx & 1) { leftClicked = 1; } else { leftClicked = 0; }
	if (regs.x.bx & 2) { rightClicked = 1; } else { rightClicked = 0; }
	if (regs.x.bx & 4) { middleClicked = 1; } else { middleClicked = 0; }
	if (mouseX > 320) { mouseX = 320; }
	if (mouseY > 200) { mouseY = 200; }
}

void drawMouse(unsigned char color) {
	static int prevMouseX = -1;
	static int prevMouseY = -1;
	static int prevPixelColor = 0;

	if (prevMouseX == mouseX && prevMouseY == mouseY) { return; }

	if (prevMouseX != -1 && prevMouseY != -1) {
		plotPixel(prevMouseX, prevMouseY, prevPixelColor);
	}

	prevPixelColor = fetchPixelColor(mouseX, mouseY);

	plotPixel(mouseX, mouseY, color);

	prevMouseX = mouseX;
	prevMouseY = mouseY;
}
