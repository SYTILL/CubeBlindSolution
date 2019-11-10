#include "stdafx.h"
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <iostream>


int cornerPer[8]; //cornerPermutation
int cornerOri[8]; //cornerOrientation
int cornerTurnKey[6][4] = 
{{1,5,8,4 },  //F
{ 2,3,7,6 },  //B
{ 4,3,2,1 },  //U
{ 5,6,7,8 },  //D
{ 1,2,6,5 },  //R
{ 3,4,8,7 } };//L

int edgePer[12]; //edgePermutation
int edgeOri[12]; //edgeOrientation
int edgeTurnKey[6][4] =
{{1, 5, 9, 8 },  //F
{ 3, 7,11, 6 },  //B
{ 4, 3, 2, 1 },  //U
{ 9,10,11,12 },  //D
{ 2, 6,10, 5 },  //R
{ 4, 8,12, 7 } };//L

int keyStack[25][2]; //[range][side/turn] 1 - right turn , 2 - 180 turn , 3 - left turn

int range = 1;

//functions
void turnCube();
void resetValues();
void printSolution();

//----------------------------------------------main start--------------------------------------------------------
int main() {
	
	resetValues();

	turnCube();

	printSolution();

	system("pause");

	return 0;
}
//----------------------------------------------main end----------------------------------------------------------


void turnCube() {
	int i, j, temp;
	for (i = 0; i < range; i++) {
		printf("%d", i);
		for (j = 0; j < keyStack[i][1]; j++) {
			temp = cornerPer[ cornerTurnKey[ keyStack[i][0] ][ 0 ]];
			cornerPer[cornerTurnKey[keyStack[i][0]][0]] = cornerPer[cornerTurnKey[keyStack[i][0]][1]];
			cornerPer[cornerTurnKey[keyStack[i][0]][1]] = cornerPer[cornerTurnKey[keyStack[i][0]][2]];
			cornerPer[cornerTurnKey[keyStack[i][0]][2]] = cornerPer[cornerTurnKey[keyStack[i][0]][3]];
			cornerPer[cornerTurnKey[keyStack[i][0]][3]] = temp;
			printf("turn ");

			temp = edgePer[edgeTurnKey[keyStack[i][0]][0]];
			edgePer[edgeTurnKey[keyStack[i][0]][0]] = edgePer[edgeTurnKey[keyStack[i][0]][1]];
			edgePer[edgeTurnKey[keyStack[i][0]][1]] = edgePer[edgeTurnKey[keyStack[i][0]][2]];
			edgePer[edgeTurnKey[keyStack[i][0]][2]] = edgePer[edgeTurnKey[keyStack[i][0]][3]];
			edgePer[edgeTurnKey[keyStack[i][0]][3]] = temp;
		}
		printf("\n");
	}
}


void resetValues() {
	int i, j;
	for (i = 0; i < 6; i++) {
		for (j = 0; j < 4; j++) {
			cornerTurnKey[i][j] -= 1;
			edgeTurnKey[i][j] -= 1;
		}
	}

	for ( i = 0; i < 8; i++) { //reset corner
		cornerPer[i] = i + 1;
		cornerOri[i] = 0;
	}
	for ( i = 0; i < 12; i++) { //reset edge
		edgePer[i] = i + 1;
		edgeOri[i] = 0;
	}

	srand(time(NULL)); //set random seed
	
	/*range = (rand() % 10) + 15; //range 15~25

	for ( i = 0; i<range; i++) { //fill keyStack
		keyStack[i][0] = rand() % 6;
		
		if (0 < i) 
			while (keyStack[i - 1][0] == keyStack[i][0]) //prevent from creating same key
				keyStack[i][0] = rand() % 6; //choose random side (0 ~ 5)
		
		keyStack[i][1] = rand() % 3 + 1; //choose random turn direction (1 ~ 3)
		
		//keyStack[i][0] = 2;
		//keyStack[i][1] = 2;
	}*/

	keyStack[0][0] = 0; //random side(0~5) F B U D R L
	keyStack[0][1] = 2; //random turn dir (1~3)
}


void printSolution() {
	int i;
	
	//range------------------------------------------------------------------
	printf("Scramble Length: %d \n\n", range);


	//key stack------------------------------------------------------------------
	printf("Scramble: ");
	for (i = 0; i < range; i++){
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
	printf("\n\n");


	//corner orientation------------------------------------------------------------------
	printf("Corner Orientation: ");
	for (i = 0; i < 8; i++)
		printf("%d ", cornerOri[i]);
	printf("\n\n");


	//corner permutation------------------------------------------------------------------
	int startKey = 0;
	bool keyCheck[8];
	int currentKey;

	for (i = 0; i < 8; i++) keyCheck[i] = false; //reset keyCheck array

	printf("Corner Permutation: ");

	for (startKey = 1; startKey < 9; startKey++) {
		if (!keyCheck[startKey-1]) {
			printf("( ");
			currentKey = startKey;
			while (!keyCheck[currentKey - 1]) {
				printf("%d ", currentKey);
				keyCheck[currentKey - 1] = true;
				currentKey = cornerPer[currentKey - 1];
			}
			printf("),");
			
		}
	}
	printf("\n\n");


	//edge orientation------------------------------------------------------------------
	printf("Edge Orientation: ");
	for (i = 0; i < 12; i++)
		printf("%d ", edgeOri[i]);
	printf("\n\n");


	//edge permutation------------------------------------------------------------------
	printf("Edge Permutation: ");
	for (i = 0; i < 12; i++)
		printf("%d ", edgePer[i]);
	printf("\n\n");

}