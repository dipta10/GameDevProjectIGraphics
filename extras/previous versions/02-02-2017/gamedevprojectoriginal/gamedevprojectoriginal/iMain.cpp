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

/*
	MOVEMENT:
	He can't sit again one he's aready sat.
	He can't jump when I has sat already once.
	can't sit while jumping/on air.
*/



#include "iGraphics.h"
#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <iostream>
//#define SCOOBY_IMAGE_RENDER_SPEED_MS 150

int SCOOBY_IMAGE_RENDER_SPEED_MS = 100;
using namespace std;

#define HEIGHT 564 
#define WIDTH 1200
#define numberOfGhost1 20

int totalScore = 0;


int numberOfGhost1atm = 2;
int numberOfGhots2atm = 2;

const int relative = 1;
int mposx,  mposy;

const int slideShowSpeed = 20 * relative;

bool insideTheGame = true;
bool onlyForOnceStoryLine = true;
bool showingFullStoryDone = false;
bool stillSliding = false;
bool stopCheckingEverything = false;
bool slideOutOfScreen = false;
bool gameOver = false;
bool gameOverNameGiven = false;
char userName[50] ;
int userNameLen = 0;
char enterNameImage[] = "Images\\enter name.bmp";
char pauseImage[] = "Images\\paused.bmp";
int tfx1 = 519, tfy1 = 263, tfx2 = 893;
int tfy2 = tfy1 + 50;
bool tfClicked = false;

void setEachAndEverything();

void dip_reverse(char str[], int len)
{
	int start, end;
	char temp;
	for (start = 0, end = len - 1; start < end; start++, end--) {
		temp = *(str + start);
		*(str + start) = *(str + end);
		*(str + end) = temp;
	}
}

char* dip_itoa(int num, char* str, int base)
{
	int i = 0;
	bool isNegative = false;

	/* A zero is same "0" string in all base */
	if (num == 0) {
		str[i] = '0';
		str[i + 1] = '\0';
		return str;
	}

	/* negative numbers are only handled if base is 10
	otherwise considered unsigned number */
	if (num < 0 && base == 10) {
		isNegative = true;
		num = -num;
	}

	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'A' : rem + '0';
		num = num / base;
	}

	/* Append negative sign for negative numbers */
	if (isNegative){
		str[i++] = '-';
	}

	str[i] = '\0';

	dip_reverse(str, i);

	return str;
}

int score = 0;
char showScore[4];

struct SCORE {
	int score;
	char scoreStr[10];
	char name[100];
}scores[15];
struct SCORE myscore;
int n;
FILE *file1;


void sortFile() {
	file1 = fopen("score.txt", "r");
	fscanf(file1, "%d", &n);

	if (n == 0) {
		fclose(file1);
		fopen("score.txt", "w");
		fprintf(file1, "1\n");
		fprintf(file1, "%d %s\n", myscore.score, myscore.name);

		fclose(file1);
		return;
	}
	for (int i = 0; i < n; i++) {

		fscanf(file1, "%d %[^\n]", &scores[i].score, scores[i].name);
		//       fscanf(file1, "%d %[^\n]", x, scores[i].name);


	}

	scores[n].score = myscore.score;
	strcpy(scores[n].name, myscore.name);
	n++;
	fclose(file1);
	fopen("score.txt", "w ");
	cout << n << endl;



	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (scores[j].score <= scores[j + 1].score) {
				struct SCORE temp;
				temp.score = scores[j].score;
				strcpy(temp.name, scores[j].name);

				strcpy(scores[j].name, scores[j + 1].name);
				scores[j].score = scores[j + 1].score;

				strcpy(scores[j + 1].name, temp.name);
				scores[j + 1].score = temp.score;
			}
		}
	}
	if (n > 10) {
		n = 10;
	}
	fprintf(file1, "%d\n", n);

	for (int i = 0; i < n; i++) {
		fprintf(file1, "%d %s\n", scores[i].score, scores[i].name);
		printf("%d %s\n", scores[i].score, scores[i].name);
	}

	fclose(file1);
}

int showFilesx = 700;
int showFilesy = HEIGHT - 150;
void readFile() {
	file1 = fopen("score.txt", "r");
	fscanf(file1, "%d", &n);
	char temp[10];
	for (int i = 0; i < n; i++) {

		fscanf(file1, "%d %[^\n]", &scores[i].score, scores[i].name);
		dip_itoa(scores[i].score, scores[i].scoreStr, 10);
		//       fscanf(file1, "%d %[^\n]", x, scores[i].name);
	}


	fclose(file1);
}
void showScores() {	
	readFile();
	int temp = showFilesy;
	char tempstr[10];
	for (int i = 0; i < n; i++) {
		dip_itoa((i + 1), tempstr, 10);
		if (i + 1 < 10) {
			iText(showFilesx - 20, showFilesy, tempstr, GLUT_BITMAP_HELVETICA_18);
		}
		else {
			iText(showFilesx - 20 - 10, showFilesy, tempstr, GLUT_BITMAP_HELVETICA_18);
		}
		iText(showFilesx, showFilesy, scores[i].name, GLUT_BITMAP_HELVETICA_18);
		iText(showFilesx + 300, showFilesy, scores[i].scoreStr, GLUT_BITMAP_HELVETICA_18);
		showFilesy -= 30;
	}

	showFilesy = temp;
}

char movingBackgroungImages[8][100] = {
	"Images\\moving background\\1.bmp",
	"Images\\moving background\\2.bmp",
	"Images\\moving background\\3.bmp",
	"Images\\moving background\\4.bmp",
	"Images\\moving background\\5.bmp",
	"Images\\moving background\\6.bmp",
	"Images\\moving background\\7.bmp",
	"Images\\moving background\\8.bmp"
};

int mbSpeed = 5;
int distanceBetweenImages = 200;
int numberOfMovingBackgroundImages1 = 7;
struct movingBackground {
	int x;
	int y;
	char image[100];
	int number;
	void setPosition() {
		y = 0;
		x = number * distanceBetweenImages;
	}
	void showImage() {
		iShowBMP(x, y, image);
		changeCoordinates();
	}

	void changeCoordinates() {
		//x -= mbSpeed;
		if (x <= -distanceBetweenImages) {
			x = (numberOfMovingBackgroundImages1 - 1)* distanceBetweenImages;
		}
	}

}mb[8];

void copyImage() {
	for (int i = 0; i < numberOfMovingBackgroundImages1; i++) {
		mb[i].number = i + 1;
		strcpy(mb[i].image, movingBackgroungImages[i]);
		mb[i].setPosition();
		printf("%s\n", mb[i].image);
	}
}

void displayMovingBackground1() {
	for (int i = 0; i < numberOfMovingBackgroundImages1; i++) {
		mb[i].showImage();
	}
}


void pressedOnGivenField(int mx, int my) {
	if (mx >= tfx1 && mx <= tfx2 && my >= tfy1 && my <= tfy2) {
		tfClicked = true;
	}
	else tfClicked = false;
}
void drawFieldForName() {
	iText(493, 33, "CLICK ON THE RECTANGLE TO ENTER YOUR NAME", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(555, 215, "You've scored: ", GLUT_BITMAP_TIMES_ROMAN_24);
	iText(712, 215, showScore, GLUT_BITMAP_TIMES_ROMAN_24);
	if (tfClicked) {
		iSetColor(255, 0, 0);
	}
	else {
		iSetColor(255, 255, 255);
	}
	iText(tfx1 + 20, tfy1 + 15, userName, GLUT_BITMAP_TIMES_ROMAN_24);
	iRectangle(tfx1, tfy1, tfx2 - 519, 50);
	iSetColor(0, 0, 0);
}

/*
bool stopCheckingEverything = false;
	if this variable is true then, momentarily checking everything will be stopped
*/

int healthBarMaxLen = 126;
// @Change health here
int healthBarLenatm = healthBarMaxLen;
//int healthBarLenatm = 10;
int healthBarHeight = 17;

void drawHealthBar() {
	iSetColor(255, 0, 0);
	iFilledRectangle(53, 488, healthBarLenatm, healthBarHeight);
	iSetColor(255, 255, 255);
}
void decreaseHelth(int value) {
	value *= (-1);
	healthBarLenatm += value;
	if (healthBarLenatm <= 0) {
		gameOver = true;
		
	}
}
void increaseHealth(int value) {
	healthBarLenatm += value;
	if (healthBarLenatm > healthBarMaxLen) {
		healthBarLenatm = healthBarMaxLen;
	}
}



int ghost1Dead = 0;
char ghostDeadStr[5] = "10";
void drawScore() {
	// while playing the game
	dip_itoa(score, showScore, 10);
	dip_itoa(ghost1Dead, ghostDeadStr, 10);
	iText(90, 380, showScore, GLUT_BITMAP_TIMES_ROMAN_24);
	iText(90, 275, ghostDeadStr, GLUT_BITMAP_TIMES_ROMAN_24);
}



char scoobyRunningDemo[] = "Images\\scooby running right 1.bmp";
char image[] = "scooby test.bmp";
char mainMenuImage[] = "Images\\MainMenu.bmp";
char aboutPage[] = "Images\\aboutPage.bmp";
char gameNameImage[] = "Images\\GameName.bmp";
char storyLineImages[6][100] = {"Images\\StoryLine\\Story line 1.bmp", "Images\\StoryLine\\Story line 1 text.bmp",
								"Images\\StoryLine\\Story line 2 text.bmp",
								"Images\\StoryLine\\Story line 3.bmp", "Images\\StoryLine\\Story line 3 text.bmp", 
								"Images\\StoryLine\\Story line 4.bmp" };

bool scoobyRunningLeft = true;
bool scoobyRunningRight = false;
bool scoobyStoppingFromLeft = false;
bool scoobyStoppingFromRight = false;
bool scoobyJumpingFromRight = false;
bool scoobyJumpingFromLeft = false;
bool scoobyOnAir = false;
bool scoobySitting = false;
bool scoobyGoingUp = false;
bool scoobyGoingDown = false;
bool scoobyOnAirDouble = false;
bool bounceBackFlag1 = false;

int scoobyX = 100;
int scoobyY = 42;
int scoobyGround = scoobyY;
int scoobySpeed = 5;
int scoobyImageHeight = 72;
int scoobyImageWidth = 100;

int scoobyWindowLimitWidth = WIDTH - scoobyImageWidth;
int scoobyWindowLimitHeight = HEIGHT - scoobyImageHeight;
int scoobyWindowLimitWidth2 = 200;
int scoobyJumpHeight = 23 * 2;
//int scoobyBounceBackHeight = scoobyJumpHeight + 10;

int scoobyJumpPeak = scoobyY + scoobyJumpHeight;
int scoobyBounceBackHeight = scoobyJumpPeak + 15 + 40;
bool scoobyBounceBack = false;

int ghost1Timer = 1;


int storyLineImageX = WIDTH + 100;
int storyLineTextX = WIDTH + 100;
int storyLineTextY = HEIGHT / 2;
int PlayButtonCordinates[4] = { 380 + 70, 664 + 130, 403, 522 };
int highScoreButtonCoordinates[4] = { 342 + 70, 695 + 130, 312, 356 };
int	aboutButtonCoordinates[4] = { 412 + 70, 599 + 130, 222, 271 };
int	exitButtonCoordinates[4] = { 422 + 70, 573 + 130, 129, 181 };
int scoobyImageCurrentIndex = 0;
int lifeCurrentIndex = 0;



enum STAGES { SHOWGAMENAME, MAINMENU, PLAY, HIGHSCORE, ABOUT, EXIT, RESUME, PAUSE, SHOWSTORY };
enum STORYLINE { part1, part2, part3, part4, part5 };
enum LEVEL { STAGE1, STAGE2, STAGE3, STAGE4 };
int currentStoryLine = part1;
// @changed stage here
int currentLevel = STAGE2;
int CurrentScreen = SHOWGAMENAME;

char scoobyRunningRightImages[7][100] = {
	"Images\\scooby doo running right\\scooby running right 1.bmp",
	"Images\\scooby doo running right\\scooby running right 2.bmp",
	"Images\\scooby doo running right\\scooby running right 3.bmp",
	"Images\\scooby doo running right\\scooby running right 4.bmp",
	"Images\\scooby doo running right\\scooby running right 5.bmp",
	"Images\\scooby doo running right\\scooby running right 6.bmp",
	"Images\\scooby doo running right\\scooby running right 7.bmp"
};

char scoobyRunningLeftImages[7][100] = {
	"Images\\scooby doo running left\\scooby running left 1.bmp",
	"Images\\scooby doo running left\\scooby running left 2.bmp",
	"Images\\scooby doo running left\\scooby running left 3.bmp",
	"Images\\scooby doo running left\\scooby running left 4.bmp",
	"Images\\scooby doo running left\\scooby running left 5.bmp",
	"Images\\scooby doo running left\\scooby running left 6.bmp",
	"Images\\scooby doo running left\\scooby running left 7.bmp"
};

char scoobyStoppingFromRightImages[7][100] = {
	"Images\\scooby stopping from right\\scooby stopping from right 1.bmp",
	"Images\\scooby stopping from right\\scooby stopping from right 2.bmp",
	"Images\\scooby stopping from right\\scooby stopping from right 3.bmp",
	"Images\\scooby stopping from right\\scooby stopping from right 4.bmp",
	"Images\\scooby stopping from right\\scooby stopping from right 5.bmp",
	"Images\\scooby stopping from right\\scooby stopping from right 6.bmp",
	"Images\\scooby stopping from right\\scooby stopping from right 7.bmp"
};

char scoobyStoppingFromLeftImages[7][100] = {
	"Images\\scooby stopping from left\\scooby stopping from left 1.bmp",
	"Images\\scooby stopping from left\\scooby stopping from left 2.bmp",
	"Images\\scooby stopping from left\\scooby stopping from left 3.bmp",
	"Images\\scooby stopping from left\\scooby stopping from left 4.bmp",
	"Images\\scooby stopping from left\\scooby stopping from left 5.bmp",
	"Images\\scooby stopping from left\\scooby stopping from left 6.bmp",
	"Images\\scooby stopping from left\\scooby stopping from left 7.bmp"
};

char scoobyJumpingFromLeftImages[7][100] = {
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 1.bmp",
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 2.bmp",
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 3.bmp",
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 4.bmp",
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 5.bmp",
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 6.bmp",
	"Images\\scooby doo jumping from left\\scooby doo jumping from left 7.bmp"
};

char scoobyJumpingFromRightImages[7][100] = {
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 1.bmp",
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 2.bmp",
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 3.bmp",
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 4.bmp",
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 5.bmp",
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 6.bmp",
	"Images\\scooby doo jumping from right\\scooby doo jumping from left 7.bmp"
};

char ghost1MovingHorizontalImages[7][100] = {
	"Images\\ghost1 images\\ghost 1.bmp",
	"Images\\ghost1 images\\ghost 2.bmp",
	"Images\\ghost1 images\\ghost 3.bmp",
	"Images\\ghost1 images\\ghost 4.bmp",
	"Images\\ghost1 images\\ghost 5.bmp",
	"Images\\ghost1 images\\ghost 6.bmp",
	"Images\\ghost1 images\\ghost 7.bmp"
};

char ghost1MovingHorizontalImagesLeave[7][100] = {
	"Images\\ghost1 images leave\\ghost 1.bmp",
	"Images\\ghost1 images leave\\ghost 2.bmp",
	"Images\\ghost1 images leave\\ghost 3.bmp",
	"Images\\ghost1 images leave\\ghost 4.bmp",
	"Images\\ghost1 images leave\\ghost 5.bmp",
	"Images\\ghost1 images leave\\ghost 6.bmp",
	"Images\\ghost1 images leave\\ghost 7.bmp"
};

char ghost1MovingHorizontalImagesInactive[7][100] = {
	"Images\\ghost1 images inactive\\ghost 1.bmp",
	"Images\\ghost1 images inactive\\ghost 2.bmp",
	"Images\\ghost1 images inactive\\ghost 3.bmp",
	"Images\\ghost1 images inactive\\ghost 4.bmp",
	"Images\\ghost1 images inactive\\ghost 5.bmp",
	"Images\\ghost1 images inactive\\ghost 6.bmp",
	"Images\\ghost1 images inactive\\ghost 7.bmp"
};

char ghost2Images[7][100] = {
	"Images\\ghost2 images\\ghost 1.bmp",
	"Images\\ghost2 images\\ghost 2.bmp",
	"Images\\ghost2 images\\ghost 3.bmp",
	"Images\\ghost2 images\\ghost 4.bmp",
	"Images\\ghost2 images\\ghost 5.bmp",
	"Images\\ghost2 images\\ghost 6.bmp",
	"Images\\ghost2 images\\ghost 7.bmp",
};

char life1[3][100] = {
	"Images\\life\\life 1.bmp",
	"Images\\life\\life 2.bmp",
	"Images\\life\\life 3.bmp"
};
int life1x = WIDTH/2, life1y = HEIGHT;
int life1ImageHeight = 60;
int life1ImageWidth = 50;
void life1SetPosition() {
	life1x = rand() % WIDTH - life1ImageWidth;
	if (life1x < 200) {
		life1x = 200 + rand() % 100;
	}
	life1y = HEIGHT + 1000;
}
int lifeSign = 1;
void life1ChangePosition() {
	life1y -= rand() % 4 + 1;
	life1x += (lifeSign)* (rand() % 10);
	if (life1x > WIDTH - life1ImageWidth || life1x <= 200) {
		lifeSign *= -1;
	}
	if (life1y < scoobyGround) {
		life1SetPosition();
	}
	int life1Frontx = life1x + life1ImageWidth;
	int scoobyFrontX = scoobyX + scoobyImageWidth;
	if (life1x >= scoobyX && life1x <= scoobyFrontX && life1y >= scoobyY && life1y <= scoobyY + scoobyImageHeight) {
		cout << "LIFE FOUND 1" << endl;
		increaseHealth(10);
		
		life1SetPosition();
	}
	if (life1Frontx >= scoobyX && life1Frontx <= scoobyFrontX && life1y >= scoobyY && life1y <= scoobyY + scoobyImageHeight) {
		cout << "LIFE FOUND 2" << endl;
		increaseHealth(10);
		life1SetPosition();
	}
}

char boneImage[] = "Images\\bone.bmp";
int boneImageWidth = 50;
struct bone1 {
	int x = 200 + rand() % (WIDTH - 200 - 150);
	int y = HEIGHT + rand() % 1000 + 1000;
	int speed = rand() % 3 + 2;
	int sign = 1;
	void reset() {
		x = 200 + rand() % (WIDTH - 200 - 150);
		y = HEIGHT;
		speed = rand() % 3 + 2;
	}
	void display() {
		iShowBMP2(x, y, boneImage, 0);
		changePosition();
	}
	void changePosition() {
		y -= speed;
		if (currentLevel == STAGE2 && scoobyRunningRight) {
			x -= mbSpeed;
		}
		if (y <= scoobyGround) {
			reset();
		}
		x += (speed * sign);
		if (x >= WIDTH - boneImageWidth || x <= 200) {
			sign *= (-1);
		}
		int scoobyFrontX = scoobyX + scoobyImageWidth - 10;
		int scoobyFrontY = scoobyY + scoobyImageHeight;
		int frontX = x + boneImageWidth;
		if (x >= scoobyX && x <= scoobyFrontX && y >= scoobyY && y <= scoobyFrontY) {
			score += 10 + rand() % 3;
			reset();
		}
		if (frontX >= scoobyX && frontX <= scoobyFrontX && y >= scoobyY && y <= scoobyFrontY) {
			score += 10 + rand() % 3;
			reset();
		}
	}
	void checkCollision() {
		
	}
}bones1[3];
void showBones() {
	for (int i = 0; i < 3; i++) {
		bones1[i].display();
	}
}



void xstrcat(char *str1, char *str2);
void setScoobyRunningRightImageLocation();
void xstrcpy(char *str1, char *str2);
void changeScoobyImageIndex();
bool checkIfClickedOnPlayButton(int mousex, int mousey);


struct Ghost1 {
	int x = WIDTH + (rand() % 100);
	int y = scoobyGround;
	int imageWidth = 80;
	int imageHeight = 66;
	bool active = true;
	char image[7][100];
	char imageInactive[7][100];
	bool alive = true;
	int value = 10;

	int imageIndex = (rand() % 7);
	int speed = rand() % 5 + 2;
	int scoobyFrontX;

	void copyImages() {
		for (int i = 0; i < 7; i++) {
			xstrcpy(image[i], ghost1MovingHorizontalImages[i]);
			xstrcpy(imageInactive[i], ghost1MovingHorizontalImagesInactive[i]);

		}
		//		setSpeed();
	}

	/*	void setSpeed() {
			int c = rand() % 5;
			switch (c) {
			case 0: speed = 3;
			case 1: speed = 4;
			case 2: speed = 5;
			case 3: speed = 6;
			case 4: speed = 7;
			default: 5;
			}
			speed *= relative;
			}
			*/

	int checkCollision() {
		/*
		if (scoobyY + 5 >= scoobyGround && scoobyRunningRight && scoobyX+scoobyImageWidth >= x) {
		cout << "GHOST DEAD" << endl;

		reset();
		return 1;
		}
		else if (scoobyFrontX >= x) {
		cout << "SCOOBY DEAD" << endl;
		reset();
		return 2;
		}
		
		

		if ((scoobyBounceBack)) {
			if (scoobyJumpingFromLeft && ((scoobyFrontX >= x && scoobyFrontX <= x + imageWidth) || (scoobyX >= x && scoobyX <= x + imageWidth)) && scoobyY >= scoobyGround &&scoobyY <= scoobyGround + imageHeight - 20) {
				cout << "GHOST DEAD" << endl;
				active = false;
				alive = false;
				ghost1Dead++;
				increaseHealth(1);
				score += value;
				cout << "YES" << endl;
				cout << ghost1Dead << endl;
				speed = 5 + rand() % 2;
				if (ghost1Dead % 20 == 0) {
					numberOfGhost1atm++;
				}
			}

			return 0;
		}

		else if ((scoobyFrontX >= x && scoobyY >= scoobyGround + 10 && (scoobyJumpingFromLeft))){
			
			cout << "GHOST DEAD" << endl;
			increaseHealth(1);
			active = false;
			alive = false;
			ghost1Dead++;
			cout << "YES" << endl;
			score += value;
			cout << ghost1Dead << endl;
			speed = 5 + rand() % 2;
			if (ghost1Dead % 20 == 0) {
				numberOfGhost1atm++;
			}
		}
		else if ((scoobyX >= x && scoobyX <= x + imageWidth) || (scoobyFrontX >= x && scoobyFrontX <= x + imageWidth)) {
			cout << "Scooby dead" << endl;
			decreaseHelth(value);
			for (int i = 0; i < 7; i++) {
				xstrcpy(image[i], ghost1MovingHorizontalImagesLeave[i]);
			}
			active = false;
			speed = 80;
		}
		*/

		if (!active) return 0;
		scoobyFrontX = scoobyX + scoobyImageWidth - 15;
		int scoobyFrontY = scoobyY + scoobyImageHeight;
		if ((scoobyX >= x && scoobyX <= x + imageWidth) || (scoobyFrontX >= x && scoobyFrontX <= x + imageWidth)) {
			if ((scoobyY >= y && scoobyY <= y + imageHeight) || (scoobyFrontY >= y && scoobyFrontY <= y + imageHeight)) {
				if (scoobyY >= scoobyGround + 10 && scoobyJumpingFromLeft) {
					cout << "GHOST DEAD" << endl;
					cout << "GHOST DEAD" << endl;
					active = false;
					alive = false;
					ghost1Dead++;
					increaseHealth(1);
					score += value;
					cout << "YES" << endl;
					cout << ghost1Dead << endl;
					speed = 5 + rand() % 2;
					if (ghost1Dead % 20 == 0) {
						numberOfGhost1atm++;
					}
				}
				else {
					cout << "SCOOBY DEAD" << endl;
					cout << "Scooby dead" << endl;
					decreaseHelth(value);
					for (int i = 0; i < 7; i++) {
						xstrcpy(image[i], ghost1MovingHorizontalImagesLeave[i]);
					}
					active = false;
					speed = 80;
				}
			}
		}

		return 0;
	}

	void changeX() {
		
		if (!active && !alive) {
			if (currentLevel == STAGE2 && (scoobyRunningRight)) {
				cout << "RUNNING RIGHT" << endl;
				x -= ( mbSpeed);
			}
			
				y += speed;
			
			if (x < 200 || y > HEIGHT) {
				reset();
			}

			return;
		}

		if (currentLevel == STAGE2 && (scoobyRunningRight)) {
			cout << "RUNNING RIGHT" << endl;
			x -= (speed + mbSpeed);
		}
		else {
			x -= speed;
		}

		if (x < 200 || y > HEIGHT) {
			reset();
		}

		
	}

	void reset() {
		x = WIDTH + (rand() % 500);
		y = scoobyGround;
		active = true;
		imageIndex = rand() % 7;
//		setSpeed();
		speed = rand() % 5 + 2;
		copyImages();
		alive = true;

	}

	void changeImageIndex() {
		imageIndex++;
		if (imageIndex >= 7) {
			imageIndex = 0;
		}
	}

	void iShowBMPForGhost1() {
		if (active || alive) {
			iShowBMP2(x, y, image[imageIndex], 0);
		}
		else if (!active && !alive) {
			iShowBMP2(x, y, imageInactive[imageIndex], 0);
		}
		changeX();
		if (active) checkCollision();
	}
};
Ghost1 ghost1[numberOfGhost1];

int ghost2Width = 97;
int ghost2Height = 100;
int ghost2InitialSpeed = 5;

struct GHOST2 {
	int x = 200 + rand() % (WIDTH - 200 - ghost2Width);
	int y = HEIGHT + rand() % 500;
	int index = rand() % 7;
	int ghost2Speed = ghost2InitialSpeed + rand() % 3;

	void reset() {
		x = 200 + rand() % (WIDTH - 200 - ghost2Width);
		y = HEIGHT + rand() % 500;
		ghost2Speed = ghost2InitialSpeed + rand() % 3;
		index = rand() % 7;
	}

	void decide() {
		if (y-(ghost2Height/2) <= scoobyY) {
			score += 12;
			ghost1Dead++; 
		}
		else {
			decreaseHelth(12);
		}
	}

	void checkCollision() {
		int scoobyFrontX = scoobyX + scoobyImageWidth;
		int scoobyFrontY = scoobyY + scoobyImageHeight;
		int frontX = x + ghost2Width;
		int frontY = y + ghost2Height;
		if (x >= scoobyX && x <= scoobyFrontX) {
			if ((y + 10) >= scoobyY && (y + 10) <= scoobyFrontY) {
				decide();
				reset();
			}
			else if (frontY >= scoobyY && frontY <= scoobyFrontY) {
				decide();
				reset();
			}
		}
		else if (frontX >= scoobyX && frontX <= scoobyFrontX) {
			if ((y + 10) >= scoobyY && (y + 10) <= scoobyFrontY) {
				decide();
				reset();
			}
			else if (frontY >= scoobyY && frontY <= scoobyFrontY) {
				decide();
				reset();
			}
		}
	}

	void changeScore() {

	}

	void changeCoordinate() {
		y -= ghost2Speed;
		if (currentLevel == STAGE2 && scoobyRunningRight) {
			x -= mbSpeed;
		}
		if (y <= scoobyGround) {
			reset();
		}
		checkCollision();
	}

	void iShowBMPForGhost2() {
		iShowBMP2(x, y, ghost2Images[index], 0);
		changeCoordinate();
	}
};

GHOST2 ghost2[numberOfGhost1];

void showGhost2() {
	for (int i = 0; i < numberOfGhost1atm; i++) {
		ghost2[i].iShowBMPForGhost2();
	}
}

void changeGhost2Index() {
	for (int i = 0; i < numberOfGhost1; i++) {
		ghost2[i].index++;
		if (ghost2[i].index >= 7) {
			ghost2[i].index = 0;
		}
	}
}



//int CurrentScreen = PLAY;
/*
int PlayCordinates[4] = { 380, 664, 403, 522 };
	index 0 and 1 are for starting and finishing X_cordinates repectively
	index 2 and 3 are for starting and finishing Y_cordinates respectively
*/




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
			Scooby Doo will be running 	
*/

void makeScoobySitOnly() {
	if (scoobyOnAir) {
		return;
	}

	scoobySitting = true;
	

	if (scoobyRunningRight) {
		
		scoobyStoppingFromRight = true;
		scoobyRunningRight = false;
	}

	if (scoobyRunningLeft) {
		scoobyStoppingFromLeft = true;
		scoobyRunningLeft = false;
		
		return;
	}
	
	
}

void checkWhenAirRelativeTo(int height) {
	
	if (scoobyY >= height) {
		scoobyGoingDown = true;
		scoobyGoingUp = false;
	}
	if (scoobyY < scoobyGround) {
		scoobyOnAir = false;
		scoobyGoingDown = false;
		scoobyGoingUp = false;
		scoobyY = scoobyGround;


		if (scoobyJumpingFromRight) {
			scoobyRunningLeft = true;
			scoobyJumpingFromRight = false;
		}

		if (scoobyJumpingFromLeft) {
			scoobyRunningRight = true;
			scoobyJumpingFromLeft = false;
		}
		
			scoobyBounceBack = false;
			bounceBackFlag1 = false;
		
		scoobyImageCurrentIndex = 0;
	}



	if (scoobyJumpingFromLeft) scoobyX += scoobySpeed;
	if (scoobyJumpingFromRight) scoobyX -= scoobySpeed;

	if (scoobyGoingUp) {
		scoobyY += 2;
	}
	else if (scoobyGoingDown) {
		scoobyY -= 2;
	}
}


void checkWhenScoobyOnAir() {
	

	if (scoobyBounceBack) {
		
		if (scoobyJumpingFromRight && !bounceBackFlag1) {
			scoobyJumpingFromLeft = true;
			scoobyJumpingFromRight = false;
		}
		else if (scoobyJumpingFromLeft && !bounceBackFlag1) {
			scoobyJumpingFromRight = true;
			scoobyJumpingFromLeft = false;
		}

		bounceBackFlag1 = true;

		checkWhenAirRelativeTo(scoobyBounceBackHeight);

		return;
	}

	checkWhenAirRelativeTo(scoobyJumpPeak);

	/*
	if (scoobyY >= scoobyJumpPeak) {
		scoobyGoingDown = true;
		scoobyGoingUp = false;
	} 
	if (scoobyY < scoobyGround) {
		scoobyOnAir = false;
		scoobyGoingDown = false;
		scoobyGoingUp = false;
		scoobyY = scoobyGround;

		
		if (scoobyJumpingFromRight) {
			scoobyRunningLeft = true;
			scoobyJumpingFromRight = false;
		}

		if (scoobyJumpingFromLeft) {
			scoobyRunningRight = true;
			scoobyJumpingFromLeft = false;
		}

		scoobyImageCurrentIndex = 0;
	}

	

	if (scoobyJumpingFromLeft) scoobyX += scoobySpeed;
	if (scoobyJumpingFromRight) scoobyX -= scoobySpeed;

	if (scoobyGoingUp) {
		scoobyY++;
	}
	else if (scoobyGoingDown) {
		scoobyY--;
	}

	*/
}

bool inAPositionToBounce() {
	if (scoobyY >= scoobyJumpHeight / 2 + scoobyGround) return true;

	return false;
}

void checkScoobyCordinates() {
	if (scoobyX <= scoobyWindowLimitWidth2) {
		scoobyX = scoobyWindowLimitWidth2 + 1;
		if (!scoobyOnAir) makeScoobySitOnly();
		if (scoobyOnAir && scoobyGoingUp) {
			scoobyBounceBack = true;
			scoobyImageCurrentIndex = 0;
			scoobyY += 10 * 1;
			
		}
	}
	//if (scoobyY <= 0) scoobyY = 0;
	if (scoobyX >= scoobyWindowLimitWidth) {
		scoobyX = scoobyWindowLimitWidth - 1;
		if (!scoobyOnAir) makeScoobySitOnly();
		if (scoobyOnAir && scoobyGoingUp) {
			scoobyBounceBack = true;
			scoobyImageCurrentIndex = 0;
			scoobyY += 10 * 1;
			
		}
	}
	if (scoobyY >= scoobyWindowLimitHeight) scoobyY = scoobyWindowLimitHeight;
}

void movingBackgroundGoLeft1() {
	for (int i = 0; i < numberOfMovingBackgroundImages1; i++) {
		mb[i].x -= mbSpeed;
	}
}

void setScoobyImagesStage1() {
	if (scoobyRunningLeft) {
		iShowBMP2(scoobyX, scoobyY, scoobyRunningLeftImages[scoobyImageCurrentIndex], 0);
		scoobyX -= scoobySpeed;
		checkScoobyCordinates();
	}
	else if (scoobyRunningRight) {
		iShowBMP2(scoobyX, scoobyY, scoobyRunningRightImages[scoobyImageCurrentIndex], 0);
		scoobyX += scoobySpeed;
		checkScoobyCordinates();

	}
	else if (scoobyStoppingFromLeft) {
		iShowBMP2(scoobyX, scoobyY, scoobyStoppingFromLeftImages[scoobyImageCurrentIndex], 0);
		checkScoobyCordinates();
	}
	else if (scoobyStoppingFromRight) {
		iShowBMP2(scoobyX, scoobyY, scoobyStoppingFromRightImages[scoobyImageCurrentIndex], 0);
		checkScoobyCordinates();
	}
	else if (scoobyJumpingFromLeft) {
		iShowBMP2(scoobyX, scoobyY, scoobyJumpingFromLeftImages[scoobyImageCurrentIndex], 0); // towards right
		checkWhenScoobyOnAir();
		checkScoobyCordinates();
		
	}
	else if (scoobyJumpingFromRight) {
		iShowBMP2(scoobyX, scoobyY, scoobyJumpingFromRightImages[scoobyImageCurrentIndex], 0); // towards right
		checkWhenScoobyOnAir();
		checkScoobyCordinates();
	}
	
}

void setScoobyImagesStage2() {
	if (scoobyRunningLeft) {
		iShowBMP2(scoobyX, scoobyY, scoobyRunningLeftImages[scoobyImageCurrentIndex], 0);
		scoobyX -= scoobySpeed;
		checkScoobyCordinates();
	}
	else if (scoobyRunningRight) {
		iShowBMP2(scoobyX, scoobyY, scoobyRunningRightImages[scoobyImageCurrentIndex], 0);
		movingBackgroundGoLeft1();

	}
	else if (scoobyStoppingFromLeft) {
		iShowBMP2(scoobyX, scoobyY, scoobyStoppingFromLeftImages[scoobyImageCurrentIndex], 0);
		checkScoobyCordinates();
	}
	else if (scoobyStoppingFromRight) {
		iShowBMP2(scoobyX, scoobyY, scoobyStoppingFromRightImages[scoobyImageCurrentIndex], 0);
		checkScoobyCordinates();
	}
	else if (scoobyJumpingFromLeft) {
		iShowBMP2(scoobyX, scoobyY, scoobyJumpingFromLeftImages[scoobyImageCurrentIndex], 0); // towards right
		checkWhenScoobyOnAir();
		checkScoobyCordinates();

	}
	else if (scoobyJumpingFromRight) {
		iShowBMP2(scoobyX, scoobyY, scoobyJumpingFromRightImages[scoobyImageCurrentIndex], 0); // towards right
		checkWhenScoobyOnAir();
		checkScoobyCordinates();
	}

}

void checkStages() {
	if (ghost1Dead == 30) {
		ghost1Dead = 0;
		currentLevel = STAGE2;
	}
}


bool showGameName = true;
bool paused = false;
	
void iDraw()
{

	iClear();
	iSetColor(255, 0, 0);
	if (paused) {
		iShowBMP(0, 0, pauseImage);
		return;
	}

	
	if (gameOver) {
		iShowBMP(0, 0, enterNameImage);
		drawFieldForName();

		return;
	}
	
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
		iShowBMP(0, 0, "Images\\highscore.bmp");
		showScores();
	}
	if (CurrentScreen == PLAY) {
/*
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
				if (slideOutOfScreen) {
					iShowBMP(0, 0, "Images\\GameName 2.bmp");
				}
				iShowBMP(storyLineImageX, 0, storyLineImages[0]);

				iShowBMP2(storyLineTextX, storyLineTextY, storyLineImages[2], 0);

				if (storyLineTextX >= WIDTH / 2 - 300 + 100 && !slideOutOfScreen) {
					storyLineTextX -= slideShowSpeed;
					stillSliding = true;
					return;
				}

				stillSliding = false;
				//slideOutOfScreen = true;

				if (slideOutOfScreen && storyLineImageX <= WIDTH) {
					//********************************ADD AND IMGE HERE ********************************
					
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
				printf("part3");
				iShowBMP(0, 0, "Images\\GameName 2.bmp");
				
				//iShowBMP2(storyLineImageX, 0, storyLineImages[3], 0);
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
				
				if (!slideOutOfScreen) {
					iShowBMP(0, 0, "Images\\GameName 2.bmp");
				}

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
					onlyForOnceStoryLine = false; //MADE ONLY_FOR_ONCE_STORY_LINE ********FALSE******** HERE ************
				}


				
			}

//			iShowBMP(0, 0, gameNameImage);
//			INSIDEGAME = STAGE1;
			return;
		}

//*/

		if (currentLevel == STAGE1) {
			iShowBMP(0, 0, "asdfdsafdsafadsfasdfasdfafsd.bmp");
			
			
			
			
			setScoobyImagesStage1();

			life1ChangePosition();
			iShowBMP2(life1x, life1y, life1[lifeCurrentIndex], 0);
			showGhost2();
			

			for (int i = 0; i < numberOfGhost1atm; i++) {
				ghost1[i].iShowBMPForGhost1();
				ghost1[i].checkCollision();
			}
			showBones();
			checkStages();
			
			iShowBMP(0, 0, "scoreboard.bmp");
			drawHealthBar();
			drawScore();
			
		}
		else if (currentLevel == STAGE2) {
			
			displayMovingBackground1();
			

			for (int i = 0; i < numberOfGhost1atm; i++) {
				ghost1[i].iShowBMPForGhost1();
				ghost1[i].checkCollision();
			}
			
			life1ChangePosition();
			iShowBMP2(life1x, life1y, life1[lifeCurrentIndex], 0);
			showGhost2();

			setScoobyImagesStage2();
			showBones();

			

			iShowBMP(0, 0, "scoreboard.bmp");
			drawHealthBar();
			drawScore();
		}
		else if (currentLevel == STAGE3) {

		}
		else if (currentLevel == STAGE4) {

		}
		else if (currentLevel == PAUSE) {
			
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
		printf("%d %d\n", mx, my);
		//place your codes here
		if (stopCheckingEverything) {
			stopCheckingEverything = false;
		}
		if (gameOver) {
			pressedOnGivenField(mx, my);
		}

		if (!stillSliding && CurrentScreen == PLAY) {
			slideOutOfScreen = true;
		}

		if (CurrentScreen == SHOWGAMENAME) {
			CurrentScreen = MAINMENU;
		}

		if (CurrentScreen == MAINMENU) {
			setCurrentScreen(mx, my);
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
int tempScreen = 0;
void cutOneChar() {
	userName[userNameLen] = '\0';
	userNameLen--;
	if (userNameLen < 0) {
		userNameLen = 0;
	}
	userName[userNameLen] = '\0';
}

void iKeyboard(unsigned char key)
{
	if (CurrentScreen == PLAY && !gameOver) {
		
		if (key == 'p') {
			if (paused == false) {
				paused = true;
			}
			else {
				paused = false;
			}
			cout << "PAUSED" << endl;
			return;
		}
	}
	if (paused && CurrentScreen == PLAY) {
		if (key == 27) {
			cout << "ESCAPEE!!!!" << endl;
			setEachAndEverything();
			return;
		}
	}


	
	if (scoobyOnAir) return;

	if (gameOver) {
		
		if (tfClicked) {
			if (key == '\r') {
				cout << userName << endl;
				myscore.score = score;
				strcpy (myscore.name, userName);
				sortFile();
				setEachAndEverything();
				
			}
			else if (key == '\b') {
				cutOneChar();
				cout << "backslash" << endl;
				//fflush(stdin);
			}
			else {
				userName[userNameLen++] = key;
			}
		}


		return;
	}

	if (key == 's' || key == 'S' && !scoobySitting && !scoobyOnAir) {
		scoobyImageCurrentIndex = 0;
		scoobySitting = true;
		if (scoobyRunningLeft) {
			scoobyStoppingFromLeft = true;
			scoobyRunningLeft = false;
		}
		if (scoobyRunningRight) {
			scoobyStoppingFromRight = true;
			scoobyRunningRight = false;
		}
	}

	if(key == 'q')
	{
		//do something with 'q'
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
	if (scoobyOnAir) return;

	if (paused) {
		if (key == 27) {
			cout << "ESCAPSE 2" << endl;
		}
	}

	if (key == GLUT_KEY_DOWN && !scoobySitting && !scoobyOnAir) {
		scoobyImageCurrentIndex = 0;
		scoobySitting = true;
		if (scoobyRunningLeft) {
			scoobyStoppingFromLeft = true;
			scoobyRunningLeft = false;
		}
		if (scoobyRunningRight) {
			scoobyStoppingFromRight = true;
			scoobyRunningRight = false;
		}
	}

	if (key == GLUT_KEY_UP && !scoobySitting) {
		scoobyImageCurrentIndex = 0;
		scoobyOnAir = true;
		scoobyGoingUp = true;
		if (scoobyRunningLeft) {
			scoobyJumpingFromRight = true;
			scoobyRunningLeft = false;
			
		}
		else if (scoobyRunningRight) {
			scoobyJumpingFromLeft = true;
			scoobyRunningRight = false;
		}
	}

	if (key == GLUT_KEY_RIGHT ) {
		scoobySitting = false;
		scoobyOnAir = false;
		scoobyRunningRight = true;
		scoobyRunningLeft = false;
		scoobyStoppingFromLeft = false;
		scoobyStoppingFromRight = false;
	}
	if (key == GLUT_KEY_LEFT ) {
		scoobySitting = false;
		scoobyOnAir = false;
		scoobyRunningRight = false;
		scoobyRunningLeft = true;
		scoobyStoppingFromLeft = false;
		scoobyStoppingFromRight = false;
	}
	

	if(key == GLUT_KEY_END)
	{
		exit(0);
	}

	
	//place your codes for other keys here
}

int main()
{
	//place your own initialization codes here.
	srand(time(NULL));
	copyImage();
	
	int n;
	
	for (int i = 0; i < numberOfGhost1; i++) {
		ghost1[i].copyImages();

	}


	iSetTimer(SCOOBY_IMAGE_RENDER_SPEED_MS, changeScoobyImageIndex);
	iSetTimer(400, changeGhost2Index);
	iInitialize(WIDTH, HEIGHT, "demooo");



	getchar();
	return 0;
}

void changeLifeIndex() {
	lifeCurrentIndex++;
	if (lifeCurrentIndex >= 3) {
		lifeCurrentIndex = 0;
	}
}
int timerForScoobyBounceBack = 1;
void changeScoobyImageIndexOnly() {

	if (scoobyBounceBack) {
		timerForScoobyBounceBack ++;
		if (timerForScoobyBounceBack % 2 == 0) {
			++scoobyImageCurrentIndex;
			if (scoobyImageCurrentIndex == 7) {
				scoobyImageCurrentIndex = 6;
			}
		}

		return;
	}

	++scoobyImageCurrentIndex;
	if (scoobyStoppingFromLeft || scoobyStoppingFromRight) {

	}
	if (scoobyImageCurrentIndex == 7 && (scoobyStoppingFromLeft || scoobyStoppingFromRight)) {

		scoobyImageCurrentIndex = 6;
		return;
	}
	if (scoobyOnAir && scoobyImageCurrentIndex == 7) {
		scoobyImageCurrentIndex = 6;
		return;
	}
	if (scoobyImageCurrentIndex == 7) {

		scoobyImageCurrentIndex = 0;
	}
}

void changeScoobyImageIndex() {
	ghost1Timer++;
	
	
	if (ghost1Timer % 2 == 0) {
//		for (int i = 0; i < numberOfGhost1; i++) {
//			ghost1[i].changeImageIndex();
//		}
	}
	for (int i = 0; i < numberOfGhost1; i++) {
		ghost1[i].changeImageIndex();
	}

	
	changeScoobyImageIndexOnly();
	changeLifeIndex();
}



void xstrcat(char *str1, char *str2) {
	int j = 0, i;
	for (i = strlen(str1); str2[j] != '\0'; i++, j++) {
		str1[j] = str2[j];
	}
	str1[i] = '\0';
}


void xstrcpy(char *str1, char *str2) {
	int i;
	for (i = 0; str2[i] != '\0'; i++) {
		str1[i] = str2[i];
	}
	str1[i] = '\0';
}

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


void setEachAndEverything(){

	for (int i = 0; i <= userNameLen; i++) {
		userName[i] = 0;
	}

	paused = false;
	showGameName = true;


	totalScore = 0;

	numberOfGhost1atm = 2;

	


//	insideTheGame = true;
//	onlyForOnceStoryLine = true;
//	showingFullStoryDone = false;
//	stillSliding = false;
	stopCheckingEverything = false;
	slideOutOfScreen = false;
	gameOver = false;
	gameOverNameGiven = false;
	userName[50];
	userNameLen = 0;
	tfClicked = false;

	healthBarMaxLen = 126;
	healthBarLenatm = healthBarMaxLen;
	score = 0;



	scoobyRunningLeft = true;
	scoobyRunningRight = false;
	scoobyStoppingFromLeft = false;
	scoobyStoppingFromRight = false;
	scoobyJumpingFromRight = false;
	scoobyJumpingFromLeft = false;
	scoobyOnAir = false;
	scoobySitting = false;
	scoobyGoingUp = false;
	scoobyGoingDown = false;
	scoobyOnAirDouble = false;

	scoobyX = 100;
	scoobyY = 42;
	scoobyGround = scoobyY;
	scoobySpeed = 5;
	scoobyImageHeight = 72;
	scoobyImageWidth = 100;

	scoobyWindowLimitWidth = WIDTH - scoobyImageWidth;
	scoobyWindowLimitHeight = HEIGHT - scoobyImageHeight;
	scoobyWindowLimitWidth2 = 200;
	scoobyJumpHeight = 23 * 2;
	//int scoobyBounceBackHeight = scoobyJumpHeight + 10;

	scoobyJumpPeak = scoobyY + scoobyJumpHeight;
	scoobyBounceBackHeight = scoobyJumpPeak + 15 + 40;
	scoobyBounceBack = false;

	ghost1Dead = 0;

	ghost1Timer = 1;

	currentStoryLine = part1;
	currentLevel = STAGE1;
	CurrentScreen = SHOWGAMENAME;

	for (int i = 0; i < numberOfGhost1atm; i++) {
		ghost1[i].reset();
	}

}