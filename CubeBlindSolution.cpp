#include "stdafx.h"
#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>

#pragma warning(disable:4996)

int cornerPer[8]; //cornerPermutation
int cornerOri[8]; //cornerOrientation
int cornerTurnKey[6][4] = //position of pieces on the side of cube
{{1,5,8,4 },  //F
{ 2,3,7,6 },  //B
{ 4,3,2,1 },  //U
{ 5,6,7,8 },  //D
{ 1,2,6,5 },  //R
{ 3,4,8,7 } };//L

int edgePer[12]; //edgePermutation
int edgeOri[12]; //edgeOrientation
int edgeTurnKey[6][4] = //position of pieces on the side of cube
{{1, 5, 9, 8 },  //F
{ 3, 7,11, 6 },  //B
{ 4, 3, 2, 1 },  //U
{ 9,10,11,12 },  //D
{ 2, 6,10, 5 },  //R
{ 4, 8,12, 7 } };//L

int keyStack[25][2]; //[range][side/turn] 1 - right turn , 2 - 180 turn , 3 - left turn

int range; //length of scamble

int speed = 30;

//functions
void turnCube();
void resetValues();
void printSolution();
void title();
void firstReset();

//----------------------------------------------main start--------------------------------------------------------
int main() {
	firstReset();

	title();
	printf("\n\nPress any key to start!");
	_getch(); //pause until user press the key

	do {
		system("CLS"); //clear screen(console) before run

		resetValues(); //set the values

		turnCube(); //turn the side by swaping values

		printSolution(); //print solution

		Sleep(speed*5); //prevent from user spaming keys
		
		printf("\n \nPress 'R' for another scamble or other keys to quit \n");
	} while (_getch() == 'r');

	return 0;
}
//----------------------------------------------main end----------------------------------------------------------

void title() {
	FILE *fileName;

	char c;

	// Open file 
	fileName = fopen("title.txt", "r");
	if (fileName == NULL)
	{
		printf("Cannot load the title screen\n");
		exit(0);
	}

	// Read contents from file 
	c = fgetc(fileName);
	while (c != EOF)
	{
		printf("%c", c);
		c = fgetc(fileName);
	}

	fclose(fileName);
	
	printf("  by SYTILL\n");
}

void turnCube() {
	int i, j, temp;
	for (i = 0; i < range; i++) {
		for (j = 0; j < keyStack[i][1]; j++) {
			temp = cornerPer[ cornerTurnKey[ keyStack[i][0] ][ 0 ]]; //swap 4 corner pieces --> turn the side 
			cornerPer[cornerTurnKey[keyStack[i][0]][0]] = cornerPer[cornerTurnKey[keyStack[i][0]][1]];
			cornerPer[cornerTurnKey[keyStack[i][0]][1]] = cornerPer[cornerTurnKey[keyStack[i][0]][2]];
			cornerPer[cornerTurnKey[keyStack[i][0]][2]] = cornerPer[cornerTurnKey[keyStack[i][0]][3]];
			cornerPer[cornerTurnKey[keyStack[i][0]][3]] = temp;

			temp = edgePer[edgeTurnKey[keyStack[i][0]][0]]; //swap 4 edge pieces --> turn the side
			edgePer[edgeTurnKey[keyStack[i][0]][0]] = edgePer[edgeTurnKey[keyStack[i][0]][1]];
			edgePer[edgeTurnKey[keyStack[i][0]][1]] = edgePer[edgeTurnKey[keyStack[i][0]][2]];
			edgePer[edgeTurnKey[keyStack[i][0]][2]] = edgePer[edgeTurnKey[keyStack[i][0]][3]];
			edgePer[edgeTurnKey[keyStack[i][0]][3]] = temp;
		}
	}
}

void firstReset() {
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			cornerTurnKey[i][j] -= 1;
			edgeTurnKey[i][j] -= 1;
		}
	}
}

void resetValues() {
	int i;

	for ( i = 0; i < 8; i++) { //reset corner
		cornerPer[i] = i + 1;
		cornerOri[i] = 0;
	}

	for ( i = 0; i < 12; i++) { //reset edge
		edgePer[i] = i + 1;
		edgeOri[i] = 0;
	}

	srand(time(NULL)); //set random seed
	
	range = (rand() % 10) + 15; //set scamble length (15~25)

	for ( i = 0; i<range; i++) { //create scamble keys
		keyStack[i][0] = rand() % 6;
		
		if (0 < i) 
			while (keyStack[i - 1][0] == keyStack[i][0]) //prevent from creating same key
				keyStack[i][0] = rand() % 6; //choose random side (0 ~ 5)
		
		keyStack[i][1] = rand() % 3 + 1; //choose random turn direction (1 ~ 3)
		
	}
}

void printSolution() {
	int i;
	int startKey = 0;
	bool cornerKeyCheck[8];
	bool edgeKeyCheck[12];

	//range
	Sleep(speed*5);
	printf("Scramble Length: %d \n\n", range);


	//key stack
	Sleep(speed*2);
	printf("Scramble: ");
	for (i = 0; i < range; i++){
		Sleep(speed);
		switch (keyStack[i][0]) {
			case 0:
				printf("F");
				break;
			case 1:
				printf("B");
				break;
			case 2:
				printf("U");
				break;
			case 3:
				printf("D");
				break;
			case 4:
				printf("R");
				break;
			case 5:
				printf("L");
				break;
		}
		
		switch (keyStack[i][1]) {
			case 1:
				printf("' ");
				break;
			case 2:
				printf("2 ");
				break;
			case 3:
				printf(" ");
				break;
		}
	}
	printf("\n\n\n");


	//corner orientation
	Sleep(speed*5);
	printf("Corner Orientation: ");
	for (i = 0; i < 8; i++) {
		Sleep(speed);
		printf("%d ", cornerOri[i]);
	}
	printf("\n\n");


	//corner permutation
	Sleep(speed*5);
	for (i = 0; i < 8; i++) cornerKeyCheck[i] = false; //reset keyCheck array

	printf("Corner Permutation: ");

	for (startKey = 1; startKey < 8 + 1; startKey++) {
		if (cornerPer[startKey - 1] == cornerPer[cornerPer[startKey - 1] - 1]) {} //dont print if the piece is in the right place
		else if (!cornerKeyCheck[startKey - 1]) {
			Sleep(speed);
			printf("( ");
			while (!cornerKeyCheck[startKey - 1]) {
				Sleep(speed);
				printf("%d ", startKey);
				cornerKeyCheck[startKey - 1] = true;
				startKey = cornerPer[startKey - 1];
			}
			printf("),");
		}

	}
	printf("\n\n");


	//edge orientation
	Sleep(speed*5);
	printf("Edge Orientation: ");
	for (i = 0; i < 12; i++) {
		Sleep(speed);
		printf("%d ", edgeOri[i]);
	}
	printf("\n\n");


	//edge permutation
	Sleep(speed*5);
	for (i = 0; i < 12; i++) edgeKeyCheck[i] = false; //reset keyCheck array

	printf("Edge Permutation: ");

	for (startKey = 1; startKey < 12 + 1; startKey++) {
		if (edgePer[startKey - 1] == edgePer[edgePer[startKey - 1] - 1]) {} //dont print if the piece is in the right place
		else if (!edgeKeyCheck[startKey - 1]) {
			Sleep(speed);
			printf("( ");
			while (!edgeKeyCheck[startKey - 1]) {
				Sleep(speed);
				printf("%d ", startKey);
				edgeKeyCheck[startKey - 1] = true;
				startKey = edgePer[startKey - 1];
			}
			printf("),");

		}
	}
	printf("\n\n");

}