#include <stdio.h>;
#include <stdlib.h>;
#include <ctype.h>;
#include "video.h";
#include "mouse.h";

int i, j;
int saveColour = 0;

void savePaint(void) {
	FILE *file = fopen("painting.dat", "w");
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 320; j++) {
			saveColour = fetchPixelColor(j, i);
			fprintf(file, "%d ", saveColour);
		}
		fprintf(file, "\n");
	}
	fclose(file);
}

void loadPaint(void) {
	FILE *file = fopen("painting.dat", "r");
	for (i = 0; i < 200; i++) {
		for (j = 0; j < 320; j++) {
			fscanf(file, "%d ", &saveColour);
			plotPixel(j, i, saveColour);
		}
	}
	fclose(file);
}

int main(void) {	
	int thickness = 1;	
	int color = 15;
	
	toggleVideoMode();
	mouseInit();
	
	while(1) {
		pollMouse();
		
		if (kbhit()) {
			char key = getch();

			if (key == 'q') {break;}
			if (key == 's') {savePaint();}
			if (key == 'l') {loadPaint();}
			if (key == '=' || key == '+') {thickness++;}
			if ((key == '-' || key == '_') && thickness > 1) {thickness--;}
			if (isdigit(key)) {color = key - '0'; if (color == 0) {color = 15;}}
			if (key == 'c') {
				for (i = 0; i < 200; i++) {
					for (j = 0; j < 320; j++) {
						plotPixel(j, i, 0);
					}
				}
			}
		}
		
		if (leftClicked) {
			for (i = 0; i < thickness; i++) {
				for (j = 0; j < thickness; j++) {
					plotPixel(mouseX + j, mouseY + i, color);
				}
			}
		}

		if (rightClicked) {
			for (i = 0; i < thickness; i++) {
				for (j = 0; j < thickness; j++) {
					plotPixel(mouseX + j, mouseY + i, 0);
				}
			}
		}

		drawMouse(color);
	}
	return 0;
}