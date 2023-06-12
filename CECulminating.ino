/* Computer Engineering Culminating
   Author: Braeden Zammit, Tyler Wehrle*/

//Array of integers mapping to row and column pins of the 8x8 matrix
constexpr int rowPins[8]{8,7,6,5,4,3,2,1}, colPins[8]{A3,A4,A5,13,12,11,10,9};
//2D array of integers representing the state of each pixel on the 8x8 matrix
int matrix[8][8];
//2D array of integers representing wall presets to be display on the 8x8 matrix
constexpr int walls[][8]{{1,1,1,1,1,1,0,0},{1,1,1,1,1,0,0,1},{1,1,1,1,0,0,1,1},{1,1,1,0,0,1,1,1},{1,1,0,0,1,1,1,1},{1,0,0,1,1,1,1,1},{0,0,1,1,1,1,1,1},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,1,1,1,1,1,0},{1,0,1,1,1,1,0,1},{1,1,0,1,1,0,1,1},{1,1,1,1,0,0,0,0},{0,1,1,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,1,1,0},{0,0,0,0,1,1,1,1},{1,1,0,0,0,0,1,1},{1,0,0,0,0,1,1,1},{1,1,1,0,0,0,0,1}, {0,1,1,0,0,1,1,0}};
//Index representing the current wall to be displayed on the 8x8 matrix (chosen at random)
short wallIndex{random(sizeof(walls)/sizeof(walls[0]))};

//2D array of integers containing numbers of size 5x3 pixels to be displayed on the 8x8 matrix
constexpr short numbers[10][15]{{1,1,1,1,0,1,1,0,1,1,0,1,1,1,1}, //Number 0
								{0,0,1,0,0,1,0,0,1,0,0,1,0,0,1}, //Number 1
								{1,1,1,0,0,1,1,1,1,1,0,0,1,1,1}, //Number 2
								{1,1,1,0,0,1,1,1,1,0,0,1,1,1,1}, //Number 3 
								{1,0,1,1,0,1,1,1,1,0,0,1,0,0,1}, //Number 4 
								{1,1,1,1,0,0,1,1,1,0,0,1,1,1,1}, //Number 5
								{1,1,1,1,0,0,1,1,1,1,0,1,1,1,1}, //Number 6
								{1,1,1,0,0,1,0,0,1,0,0,1,0,0,1}, //Number 7
								{1,1,1,1,0,1,1,1,1,1,0,1,1,1,1}, //Number 8
								{1,1,1,1,0,1,1,1,1,0,0,1,0,0,1}}; //Number 9 

//Integers containing the time of the last player move, the player speed in milliseconds per pixel, and the player's score
unsigned long playerLast, playerSpeed{250}, score;
//X and Y coordinates of the player
short xPos{3}, yPos{3};

//The time recorded when the wall last moved and the wall speed in milliseconds per pixel
unsigned long wallLast, wallSpeed{1000};
//The position of the wall relative to its direction and the direction it's moving in (chosen at random)
short wallPos, wallDir{random(4)};

void setup() {
    //Sets the matrix pins to output and turns all columns off.
    for (int i = 0; i < 8; ++i){
        pinMode(rowPins[i], 1); //Set row pins to output
        pinMode(colPins[i], 1); //Set column pins to output
        digitalWrite(colPins[i], 1); //Clear the 8x8 matrix by setting column pins to high
    }
    //Sets the joystick pins to input
    pinMode(A0, 0);
    pinMode(A1, 0);
}

//Clears gameplay field matrix by iterating through 2D array and setting pixels to off
void clear(){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
            matrix[i][j] = 0;    
        }
    }
}

//Writes the player and walls to the 8x8 matrix, one row at a time creating the illusion of a connected image
void update(bool flag){
    for (int i = 0; i < 8; ++i){
        for (int j = 0; j < 8; ++j){
			//Writes the opposite of the data stored in the 2D array, because columns must be set to low to light the pixel
            digitalWrite(colPins[j], !matrix[i][j]); 
        }
        if (i == yPos && flag) digitalWrite(colPins[xPos], 0); //Writes the player to the 8x8 matrix when its row is reached

        digitalWrite(rowPins[i], 1); //Write high to the current row, lighting up one row of pixels
        delay(1);
        digitalWrite(rowPins[i], 0); //Turn row's pixels off so it may light the next row
    }
}

//Runs the screen animation to clear the screen on death
void screenAnimation(){
	//Light up all the pixels sequentially on the 8x8 matrix
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			unsigned long start{millis()}; //Used to keep track of last light enable

			matrix[i][j] = 1;
			while ((millis()-start) < 25) //Turns on one pixel every 25ms
				update(false);
		}
	}
	//Turn off all the pixels sequentially on the 8x8 matrix
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			unsigned long start{millis()}; //Used to keep track of last light disable

			matrix[i][j] = 0;
			while ((millis()-start) < 25) //Turns off one pixel every 25ms
				update(false);
		}
	}
}

void loop() {
	clear(); //Clear 2D array at the start of every frame

	//Joystick handler. Updates player position based on joystick movements.
	if ((millis()-playerLast) >= playerSpeed){ //Only executes every playerSpeed milliseconds, set to 250ms
		if (analogRead(A0) >= 895){ //If joystick is moved right
			if (xPos < 7) ++xPos; //Increment player x position if not at border
			playerLast = millis();
		}
		else if (analogRead(A0) <= 128){ //If joystick is moved left
			if (xPos > 0) --xPos; //Decrement player x position if not at border
			playerLast = millis();
		}    
		else if (analogRead(A1) >= 895){ //If joystick is moved down
			if (yPos < 7) ++yPos; //Decrement player y position if not at border
			playerLast = millis();
		}
		else if (analogRead(A1) <= 128){ //If joystick is moved up
			if (yPos > 0) --yPos; //Increment player y position if not at border
			playerLast = millis();
		}
	}
	
	//Handle the position, direction, and speed of the wall.
	if ((millis()-wallLast) >= wallSpeed){
		if (++wallPos > 7){ //If wall has moved 8 pixels
			wallDir = random(4), wallPos = 0; //Change the wall direction randomly, set number of wall moves to 0
			wallIndex = random(sizeof(walls)/sizeof(walls[0])); //Pick a new wall pattern from the presets at random
			wallSpeed -= 20; //Decrement delay between wall movements by 20ms
			++score; //Increment the player's score
		}
		wallLast = millis(); //Update the last wall movement time
	}    

	//Update the wall's position in the gameplay field matrix.
	if (!(wallDir%2)){ //If the direction is 0 or 2
		for (int i = 0; i < 8; ++i)
			//Update the 2D array with the position of the walls
			wallDir == 0 ? matrix[i][wallPos] = walls[wallIndex][i] : matrix[i][7-wallPos] = walls[wallIndex][i]; 
	}
	else{ //If the direction is 1 or 3
		for (int i = 0; i < 8; ++i)
			//Update the 2D array with the position of the walls
			wallDir == 1 ? matrix[wallPos][i] = walls[wallIndex][i] : matrix[7-wallPos][i] = walls[wallIndex][i];
	}

	update(true); //Update the 8x8 matrix with the current 2D array

	//Collision check between player and wall    
	if (matrix[yPos][xPos]){ //If the player's position conicides with a wall
		clear();
		screenAnimation(); //Play the screen refresh animation
		
		for (int i = 0; i < 15; ++i)
			matrix[i/3][(i%3)] = numbers[score/10][i]; //Write the tens column of the score to the screen
		for (int i = 0; i < 15; ++i)
			matrix[i/3][(i%3)+5] = numbers[score%10][i]; //Write the ones column of the score to the screen

		unsigned long lastFrame{}, screenTime{millis()};
		bool visible = false;
		//Display game results until three seconds have passed and the player moves the joystick
		while (!(analogRead(A0) >= 895 || 
				analogRead(A0) <= 128 ||
    			analogRead(A1) >= 895 ||
		    	analogRead(A1) <= 128) || (millis()-screenTime) <= 3000){
			if ((millis()-lastFrame) >= 750){
				visible = !visible;	
				lastFrame = millis();	
			}

			//Write a flashing dot to the 8x8 matrix depending on the state of visible
			if (visible){
				matrix[6][3] = 1, matrix[6][4] = 1;
				matrix[7][3] = 1, matrix[7][4] = 1;
			}
			else{
				matrix[6][3] = 0, matrix[6][4] = 0;
				matrix[7][3] = 0, matrix[7][4] = 0;
			}

			update(false); //Update the 8x8 matrix, excluding the player position
		}

		clear();
		screenAnimation(); //Play the screen refresh animation once more before resetting game
		
		//Reset global variables containing game states and important values
		xPos = 3, yPos = 3, score = 0;
		wallPos = 0, wallDir = random(4), wallIndex = random(sizeof(walls)/sizeof(walls[0])), wallSpeed = 1000;
		wallLast = millis(), playerLast = millis();
	}
}
