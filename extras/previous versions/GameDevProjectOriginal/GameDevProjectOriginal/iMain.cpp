/*
    Original Author: S. M. Shahriar Nirjon
    Last Modified by: Mohammad Saifur Rahman
    last modified: October 13, 2015
    Version: 2.0
*/

/*
	Game Name	:	Not Fixed yet :3
	Characters	:	Scooby Doo
					Shaggy Rogers


	Story		:
		Scooby Doo and Shaggy Rogers are best friends. They've faced a lot of ghosts, and so far they have
		successfully averted all the mayhem that could have've happened. Though this time, they don't have
		their friends with them.

		Scooby Doo and Shaggy Rogers decided to leave their friends and travel to the AUST,
		When they reached #SOMEWHERE they encountered a ghost. Both of them started to run for their life,
		Though Scooby Doo somehow managed to escape, the ghost took his best friend Shaggy Rogers.
		Now Scooby Doo is sad, and he won't go back without his friend.
		Help Scooby rescue his friend.
*/



#include "iGraphics.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define HEIGHT 564 
#define WIDTH 1000

const int relative = 1;
int mposx,  mposy;

const int slideShowSpeed = 20 * relative;

bool insideTheGame = true;
bool onlyForOnceStoryLine = true;
bool showingFullStoryDone = false;
bool stillSliding = false;
bool stopCheckingEverything = false;
bool slideOutOfScreen = false;
/*
bool stopCheckingEverything = false;
	if this variable is true then, momentarily checking everything will be stopped
*/

char image[] = "scooby test.bmp";
char mainMenuImage[] = "Images\\MainMenu.bmp";
char aboutPage[] = "Images\\aboutPage.bmp";
char gameNameImage[] = "Images\\GameName.bmp";
char storyLineImages[6][100] = {"Images\\StoryLine\\Story line 1.bmp", "Images\\StoryLine\\Story line 1 text.bmp",
								"Images\\StoryLine\\Story line 2 text.bmp",
								"Images\\StoryLine\\Story line 3.bmp", "Images\\StoryLine\\Story line 3 text.bmp", 
								"Images\\StoryLine\\Story line 4.bmp" };

int storyLineImageX = WIDTH + 100;
int storyLineTextX = WIDTH + 100;
int storyLineTextY = HEIGHT / 2;
int PlayButtonCordinates[4] = { 380, 664, 403, 522 };
int highScoreButtonCoordinates[4] = { 342, 695, 312, 356 };
int	aboutButtonCoordinates[4] = {412, 599, 222 ,271};
int	exitButtonCoordinates[4] = { 422, 573, 129, 181};


enum STAGES {SHOWGAMENAME, MAINMENU, PLAY, HIGHSCORE, ABOUT, EXIT, RESUME, PAUSE, SHOWSTORY, STAGE1, STAGE2, STAGE3, STAGE4 };
enum STORYLINE {part1, part2, part3, part4, part5};
int currentStoryLine = part1;
int CurrentScreen = SHOWGAMENAME;
/*
int PlayCordinates[4] = { 380, 664, 403, 522 };
	index 0 and 1 are for starting and finishing X_cordinates repectively
	index 2 and 3 are for starting and finishing Y_cordinates respectively
*/

bool checkIfClickedOnPlayButton(int mousex, int mousey) {
	if (stopCheckingEverything) return false;
	if (CurrentScreen != MAINMENU) return false;
	if (mousex >= PlayButtonCordinates[0] && mousex <= PlayButtonCordinates[1]) {
		if (mousey >= PlayButtonCordinates[2] && mousey <= PlayButtonCordinates[3]) {
			return true;
		}
	}
	return false;
}

bool checkIfClickedOnExitButton(int mousex, int mousey) {
	if (stopCheckingEverything) return false;
	if (CurrentScreen != MAINMENU) return false;
	if (mousex >= exitButtonCoordinates[0] && mousex <= exitButtonCoordinates[1]) {
		if (mousey >= exitButtonCoordinates[2] && mousey <= exitButtonCoordinates[3]) {
			return true;
		}
	}
	return false;
}

bool checkIfClickedOnHighScoreButton(int mousex, int mousey) {
	if (stopCheckingEverything) return false;
	if (CurrentScreen != MAINMENU) return false;
	if (mousex >= highScoreButtonCoordinates[0] && mousex <= highScoreButtonCoordinates[1]) {
		if (mousey >= highScoreButtonCoordinates[2] && mousey <= highScoreButtonCoordinates[3]) {
			return true;
		}
	}
	return false;
}

bool checkIfClickedOnAboutButton(int mousex, int mousey) {
	if (stopCheckingEverything) return false;
	if (CurrentScreen != MAINMENU) return false;
	if (mousex >= aboutButtonCoordinates[0] && mousex <= aboutButtonCoordinates[1]) {
		if (mousey >= aboutButtonCoordinates[2] && mousey <= aboutButtonCoordinates[3]) {
			return true;
		}
	}
	return false;
}
void setCurrentScreen(int mousex, int mousey) {
	/*
		need to set this only when I'm on the main menu, else there's no need to use this function anywhere in the program
	*/
	if (stopCheckingEverything) return;
	if (checkIfClickedOnPlayButton(mousex, mousey)) {
		CurrentScreen = PLAY;
		printf("Play\n");
	}
	if (checkIfClickedOnAboutButton(mousex, mousey)) {
		CurrentScreen = ABOUT;
		printf("ABOUT\n");
	}
	if (checkIfClickedOnHighScoreButton(mousex, mousey)) {
		CurrentScreen = HIGHSCORE;
		printf("High Score\n");
	}

	if (checkIfClickedOnExitButton(mousex, mousey)) {
		CurrentScreen = EXIT;
		exit(0);
		printf("High Score\n");
	}

}

void setCurrentScreenInPlay() {

}

void makeEverythingFalse() {
	
}
/*
	NOTE:
		First Stage:
			Scooby Doo should will be running 	
*/


/*
	function iDraw() is called again and again by the system.
*/
bool showGameName = true;

void iDraw()
{

	

	iClear();
	
	if (stopCheckingEverything) {
		iShowBMP(0, 0, gameNameImage);
		return;
	}

	if (CurrentScreen == SHOWGAMENAME) {
		iShowBMP(0, 0, gameNameImage);

		//CurrentScreen = MAINMENU;
	}


	if (CurrentScreen == MAINMENU) {
		//iShowBMP(0, 0, aboutPage);
		iShowBMP(0, 0, mainMenuImage);
	}

	if (CurrentScreen == ABOUT) {
		iShowBMP(0, 0, aboutPage);
	}
	else if (CurrentScreen == HIGHSCORE) {

	}
	if (CurrentScreen == PLAY) {



		if (onlyForOnceStoryLine) {
			printf("1");
			if (currentStoryLine == part1) {

				iShowBMP(0, 0, mainMenuImage);
				iShowBMP(storyLineImageX, 0, storyLineImages[0]);
				iShowBMP2(storyLineTextX, storyLineTextY, storyLineImages[1], 0);
				
				if (storyLineTextX >= WIDTH / 2 - 300 && !slideOutOfScreen) {
					storyLineTextX -= slideShowSpeed;
					stillSliding = true;
				}
				if (storyLineImageX > 0 && !slideOutOfScreen) {
					storyLineImageX -= slideShowSpeed;
					stillSliding = true;
					return;
				}

				stillSliding = false;
				//slideOutOfScreen = true;

				if (slideOutOfScreen) {
					storyLineTextX += slideShowSpeed;
				}

				if (storyLineTextX > WIDTH) {
					currentStoryLine = part2;
					stillSliding = true;
					slideOutOfScreen = false;
					storyLineImageX = 0;
					storyLineTextX = WIDTH + 100;
					storyLineTextY = 100; // only for this one maybe :/
				}

			}
			else if (currentStoryLine == part2) {
				iShowBMP(storyLineImageX, 0, storyLineImages[0]);

				iShowBMP2(storyLineTextX, storyLineTextY, storyLineImages[2], 0);

				if (storyLineTextX >= WIDTH / 2 - 300 && !slideOutOfScreen) {
					storyLineTextX -= slideShowSpeed;
					stillSliding = true;
					return;
				}

				stillSliding = false;
				//slideOutOfScreen = true;

				if (slideOutOfScreen && storyLineImageX <= WIDTH) {
					storyLineTextX += slideShowSpeed;
					storyLineImageX += slideShowSpeed;
					
					return;
				}
				if (storyLineImageX > WIDTH) {
					currentStoryLine = part3;
					stillSliding = true;
					slideOutOfScreen = false;
					storyLineImageX = WIDTH + 100;
					storyLineTextX = WIDTH + 100;
				}

				
			}
			else if (currentStoryLine == part3) {
				
				
				iShowBMP2(storyLineImageX, 0, storyLineImages[3], 0);
				iShowBMP2(storyLineTextX, 0, storyLineImages[4], 0);

				if (storyLineTextX > 0 && !slideOutOfScreen) {
					storyLineTextX -= slideShowSpeed;
					stillSliding = true;
				}
				if (storyLineImageX > 0 && !slideOutOfScreen) {
					storyLineImageX -= slideShowSpeed;
					stillSliding = true;
					return;
				}

				stillSliding = false;
				//slideOutOfScreen = true;

				if (slideOutOfScreen) {
					storyLineTextX += slideShowSpeed;
					storyLineImageX += slideShowSpeed;
				}

				if (storyLineTextX > WIDTH) {
					currentStoryLine = part4;
					stillSliding = true;
					slideOutOfScreen = false;
					storyLineImageX = WIDTH + 100;
					storyLineTextX = WIDTH + 100;
					storyLineTextY = 100; // only for this one maybe :/
				}
			}

			else if (currentStoryLine == part4) {
				
				iShowBMP(storyLineImageX, 0, storyLineImages[5]);
				

				if (storyLineImageX > 0 && !slideOutOfScreen) {
					storyLineImageX -= slideShowSpeed;
					stillSliding = true;
					return;
				}

				stillSliding = false;
				//slideOutOfScreen = true;

				if (slideOutOfScreen && storyLineImageX <= WIDTH) {
					storyLineTextX += slideShowSpeed;
					storyLineImageX += slideShowSpeed;

					return;
				}
				if (storyLineImageX > WIDTH) {
					currentStoryLine = part3;
					stillSliding = true;
					slideOutOfScreen = false;
					storyLineImageX = WIDTH + 100;
					storyLineTextX = WIDTH + 100;
					onlyForOnceStoryLine = false;
				}


				
			}

//			iShowBMP(0, 0, gameNameImage);

			return;
		}

		if (CurrentScreen == STAGE1) {

		}
		else if (CurrentScreen == STAGE2) {

		}
		else if (CurrentScreen == STAGE3) {

		}
		else if (CurrentScreen == STAGE4) {

		}
		else if (CurrentScreen == PAUSE) {

		}
	}
	else if (CurrentScreen == HIGHSCORE) {

	}
	else if (CurrentScreen == EXIT) {

	}



	
	//place your drawing codes here
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouseMove(int mx, int my)
{
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
*/
void iMouse(int button, int state, int mx, int my)
{
	if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		//place your codes here
		if (stopCheckingEverything) {
			stopCheckingEverything = false;
		}

		if (!stillSliding && CurrentScreen == PLAY) {
			slideOutOfScreen = true;
		}

		if (CurrentScreen == SHOWGAMENAME) {
			CurrentScreen = MAINMENU;
		}

		if (CurrentScreen == MAINMENU) {
			setCurrentScreen(mx, my);
			printf("%d %d\n", mx, my);
		}
		else if (!stopCheckingEverything && (CurrentScreen == ABOUT || CurrentScreen == HIGHSCORE)) {
			CurrentScreen = MAINMENU;
		}
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
		//do something with 'q'
	}

	if (key == 'p' || key == 27) {
		printf("paused\n");
	}
	//place your codes for other keys here
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
//
int main()
{
	//place your own initialization codes here.
	iInitialize(WIDTH, HEIGHT, "demooo");



	getchar();
	return 0;
}
