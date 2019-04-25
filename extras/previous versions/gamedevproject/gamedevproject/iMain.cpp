/*
    Original Author: S. M. Shahriar Nirjon
    Last Modified by: Mohammad Saifur Rahman
    last modified: October 13, 2015
    Version: 2.0
*/




# include "iGraphics.h"
#include <iostream>
#include <Windows.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std; 

const int WIDTH = 1280;
const int HEIGHT = 720;
const int backgourndHeight = 720;
const int backgroundWidth = 200;
int movingBackgroundPositionCheck = 0;
int mposx;
int mposy;
int mouseCounter = 0;
int movingBackgroundSpeed = 5;
char movingBackgroundImage[] = "Image\\moving Background2 buring ground.bmp";
char buringCoalImage1[] = "Image\\buring coal2.bmp";
char buringCoalImage2[] = "Image\\buring coal3.bmp";
char buringCoalImageSet[10][100];
char buringCoalImagePathExample[] = "Image\\buring coal";
int const burningCoalBackgroundHeight = 100;
int burningCoal1_X = WIDTH;
int burningCoal1_Y = burningCoalBackgroundHeight ;
int const buringCoalMovementSpeed = 7;
int buringCoalChange = 1;
int buringCoalImageNumber = 9;
const int gameScoreBoardWidth = 200;
const int gameScoreBoardHeight = HEIGHT;

char castielDemo[] = "Image\\castiel\\castielFlying1.bmp";


enum {
	PLAY, INSTRUCTIONS, SCORES, ABOUT, EXIT
};

bool mainMenu = true;
bool insidePlay = false;
bool insideInstruction = false;
bool insideScore = false;
bool insideAbout = false;
bool insideExit = false;

void xstrcpy(char *str1, char *str2);
void xstrcat(char *str1, char *str2);
/*
Original Author		:	Dipta
Subject				:	Moving Background
Last modified by	:	Dipta
last modified		:	12/02/2016

	For moving background in file, one this is must,
	we need to set at least a rectangle on the left side as the background is moving towards the left.
	I (Dipta) made this function about 2 weeks ago or so, therefore at the moment I am finding it hard to figure out how it works,
	whatever, for this moving background to the left, things those are mendatory:

	strcut movingBackgroundGroup
	variables:
		int movingBackgroundPositionCheck = 0;
		char movingBackgroundImage[] = "Image\\moving Background1.bmp";
	functions:
		xstrcpy()
		setMovingBackgroundPath()
		move(int speed) // don't use speed more than 20

	in the draw() functions i need to write the code below:
		for (int i = 0; i < 10; i++) {
			iShowBMP(movingBackground[i].x, movingBackground[i].y, movingBackground[i].setPath);
		}
	in draw() i need to call move(int speed)
	
	and finally in main I need to call setMovingBackgroundPath();
	that's it.
		
*/


// buring coal attack START
struct burningCoal {
	
};

void moveBuringCoalFromRightToLeft() {

	iShowBMP2(burningCoal1_X, burningCoal1_Y, buringCoalImageSet[buringCoalChange], 0);

	burningCoal1_X -= buringCoalMovementSpeed;
	//burningCoal1_Y -= (buringCoalMovementSpeed/2);
	buringCoalChange++;
	if (buringCoalChange > buringCoalImageNumber) {
		buringCoalChange = 1;
	}
}

void setBurningCoalImageSetPath() {
	for (int i = 1; i <= buringCoalImageNumber; i++) {
		char temp[100];
		xstrcpy(temp, buringCoalImagePathExample);
		int tempLen = strlen(temp);
		temp[tempLen] = i + 48;
		temp[tempLen + 1] = '\0';
		xstrcat(temp, ".bmp");
//		buringCoalImageSet[i] = temp;
		xstrcpy(buringCoalImageSet[i], temp);
	}
}


// buring coal attack END
struct movingBackgroundGroup {

	char setPath[200];
	int x, y;
	bool shiftPositionToTheRight = false;

	void movingBackgroundGroupToRight() {
		if (x - movingBackgroundPositionCheck <= 0) {
			shiftPositionToTheRight = true;
			x = WIDTH;
			printf("done %d \n", x - movingBackgroundPositionCheck);
		}
		if (shiftPositionToTheRight == true) {
//			x = WIDTH;
			shiftPositionToTheRight = false;
		}
	}
	
} movingBackground[10];

void setMovingBackgroundPath() {
	for (int i = 0; i < 10; i++) {
		xstrcpy(movingBackground[i].setPath, movingBackgroundImage);
		movingBackground[i].x = WIDTH - (i + 1) * backgroundWidth ;
		movingBackground[i].movingBackgroundGroupToRight();
	}
}

void move(int speed) {
	for (int i = 0; i < 10; i++) {
		movingBackground[i].x -= speed;
		movingBackground[i].movingBackgroundGroupToRight();
	}
}

int radius = 30;
int r1 = 100, g1 = 200, b1 = 255;
int r2 = 100, g2 = 200, b2 = 255;
int r3 = 100, g3 = 200, b3 = 255;

void changeColor() {
	r1 = rand() % 255;
	b1 = rand() % 255;
	g1 = 0;
	r2 = rand() % 255;
	b2 = rand() % 255;
	g2 = 0;
	r3 = rand() % 255;
	b3 = rand() % 255;
	g3 = 0;
}

void iDraw()
{
	iClear();

	Arc(1, 2, 3, 4, 5, 6, 7, 8, 9);


	iSetColor(r1, g1, b1);
	iFilledCircle(100, 100, radius);
	iSetColor(r2, g2, b2);

	iFilledCircle(200, 100, radius);
	iSetColor(r3, g3, b3);
	iFilledCircle(300, 100, radius);
	
}

void iMouseMove(int mx, int my)
// like drag and drop
{
		

}

void iMouse(int button, int state, int mx, int my)
{
	

	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{

	}
	if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
	}
}
/*iPassiveMouseMove is called to detect and use
the mouse point without pressing any button */

void iPassiveMouseMove(int mx,int my)
{
	//place your code here

 mposx = mx;
 mposy = my;
 if(mx== 2){}        /*Something to do with mx*/
 else if(my== 2){}   /*Something to do with my*/

}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/

void iKeyboard(unsigned char key)
{
	if(key == 'q')
	{
		
	}
	
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
*/
void iSpecialKeyboard(unsigned char key)
{

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.
	iSetTimer(150, changeColor);
	iInitialize(500, 500, "nothing");

	
	
	

	getchar();
	return 0;
}



void xstrcpy(char *str1, char *str2) {
	int i;
	for (i = 0; i < strlen(str2) && str2[i] != '\0'; i++) {
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

void xstrcat(char *str1, char *str2)
{
	int i, j;
	for (i = strlen(str1), j = 0; str2[j] != '\0'; i++, j++) {
		//nothing
		str1[i] = str2[j];
	}
	str1[i] = '\0';
}

