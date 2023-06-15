#include "zelda.h"
#include "hole.h"
#include "snake.h"
#include "lib.h"

constexpr int rowPins[8]{ 8, 7, 6, 5, 4, 3, 2, 1 }, 
	colPins[8]{ A3, A4, A5, 13, 12, 11, 10, 9 };

constexpr short numbers[10][15]
{
	{ 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1 }, 
	{ 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 }, 
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1 }, 
	{ 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1 },  
	{ 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1 },  
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1, 1 }, 
	{ 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, 
	{ 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1 }, 
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1 }, 
	{ 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1 }
}; 

void setup() {
	for (int i = 0; i < 8; ++i){
		pinMode(rowPins[i], 1); 
		pinMode(colPins[i], 1); 
		digitalWrite(colPins[i], 1); 
	}
	pinMode(A0, 0);
	pinMode(A1, 0);
	pinMode(A2, INPUT_PULLUP);
}

void clear(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			matrix[i][j] = 0;    
		}
	}
}

void update(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			digitalWrite(colPins[j], !matrix[i][j]); 
		}

		digitalWrite(rowPins[i], 1); 
		delay(1);
		digitalWrite(rowPins[i], 0); 
	}
}

void screenAnimation(){
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			unsigned long start{millis()}; 

			matrix[i][j] = 1;
			while ((millis() - start) < 25) 
				update();
		}
	}
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			unsigned long start{millis()}; 

			matrix[i][j] = 0;
			while ((millis() - start) < 25) 
				update();
		}
	}
}

void menuAnimation(bool img[4][4]){
	static unsigned long last{};
	static bool state{};
	
	matrix[0][0] = state; matrix[0][1] = state; matrix[1][0] = state;
	matrix[0][6] = state; matrix[0][7] = state; matrix[1][7] = state;
	matrix[6][0] = state; matrix[7][0] = state; matrix[7][1] = state;
	matrix[6][7] = state; matrix[7][6] = state; matrix[7][7] = state;
	for (int i = 0; i < 4; ++i){
		for (int j = 0; j < 4; ++j){
			matrix[i + 2][j + 2] = img[i][j];
		}
	}

	if (millis() - last >= 500){
		state = !state;
		last = millis();
	}

	update();
}

void loop(){
	constexpr static bool gameLogos[][4][4]
	{
		{
			{ true, true, true, true },
			{ false, false, false, true },
			{ true, true, true, true },
			{ true, false, false, false },
		},
		{
			{ false, false, false, true },
			{ false, false, true, false },
			{ true, true, false, false },
			{ true, true, false, false },
		},
		{
			{ false, false, false, true },
			{ false, false, false, true },
			{ true, false, false, false },
			{ false, false, false, true },
		}
	};
	constexpr static int (*games[])(){ snake, zelda, hole };
	int static gameIdx{0};

	switch (joystickEvent()){
		case Direction::LEFT:
			if (gameIdx > 0) 
				--gameIdx;
			break;
		case Direction::RIGHT:
			if (gameIdx < sizeof(games) / sizeof(games[0]) - 1)
				++gameIdx;
			break;
	}

	if (buttonEvent()){
		screenAnimation();
		int score = games[gameIdx]();
		screenAnimation();

		for (int i = 0; i < 15; ++i)
			matrix[i / 3][(i % 3)] = numbers[score / 10][i]; 
		for (int i = 0; i < 15; ++i)
			matrix[i / 3][(i % 3) + 5] = numbers[score % 10][i]; 

		int last{};
		do{
			if (millis() - last >= 750){
				if (!matrix[6][3]){
					matrix[6][3] = 1, matrix[6][4] = 1;
					matrix[7][3] = 1, matrix[7][4] = 1;
				}
				else{
					matrix[6][3] = 0, matrix[6][4] = 0;
					matrix[7][3] = 0, matrix[7][4] = 0;
				}

				last = millis();
			}

			update();
		} while (!buttonEvent());

		screenAnimation();
	}

	menuAnimation(gameLogos[gameIdx]);
}
