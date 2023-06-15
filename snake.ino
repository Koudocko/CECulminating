#include "lib.h"

int* generateFruit(){
	int (*areas)[2]{NULL};
	int len{};

	bool last{1};
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			if (!matrix[i][j] && last){
				++len;
				areas = (int(*)[2])realloc(areas, sizeof(int[2]) * len);
				areas[len - 1][0] = i * 8 + j;
				areas[len - 1][1] = 0;
			}
			else if (matrix && !last){
				areas[len - 1][1] = i * 8 + j - 1;
			}
		}
	}

	int* randArea = areas[random(len)];
	int randVal = random(randArea[0], randArea[1]);
	free(areas);

	int* fruit = (int*)malloc(sizeof(int[2]));
	fruit[0] = randVal % 8; fruit[1] = randVal / 8;
	return fruit; 
}

int snake(){
	unsigned long last{};
	int len{1}, dir{Direction::DOWN}, score{};
	int (*body)[2] = (int(*)[2])malloc(sizeof(int[2]));
	body[0][0] = 3; body[0][1] = 3;
	
	int* fruit{};

	while (1){
		for (int i = len - 1; i >= 0; --i)
			matrix[body[i][1]][body[i][0]] = 1;

		if (!fruit){
			fruit = generateFruit();
			matrix[fruit[1]][fruit[0]] = 1;
		}

		update();

		int input = joystickEvent();
		if ((input % 2 != dir % 2) && input != Direction::NONE)
			dir = input;
		
		if (millis() - last >= 250){
			last = millis();
			int tail[2]{};

			for (int i = len - 1; i >= 0; --i){
				matrix[body[i][1]][body[i][0]] = 0;
			}

			memcpy(tail, body[len - 1], sizeof(int[2]));
			for (int i = len; i > 0; --i){
				memmove(body[i], body[i - 1], sizeof(int[2]));
			}

			switch (dir){
				case Direction::UP:
					--body[0][1];
					break;
				case Direction::DOWN:
					++body[0][1];
					break;
				case Direction::LEFT:
					--body[0][0];
					break;
				case Direction::RIGHT:
					++body[0][0];
					break;
			}

			for (int i = len - 1; i > 0; --i)
				matrix[body[i][1]][body[i][0]] = 1;
			
			int x = body[0][0], y = body[0][1];
			if (x < 0 || x > 7 || y < 0 || y > 7)
				break;

			if (matrix[y][x]){
				if (fruit && fruit[0] == x && fruit[1] == y){
					matrix[fruit[1]][fruit[0]] = 0;
					free(fruit);
					fruit = nullptr;
					++score;

					++len;
					body = (int(*)[2])realloc(body, sizeof(int[2]) * len);
					memcpy(body[len - 1], tail, sizeof(int[2]));
				}
				else{
					break;
				}
			}
			else{
				matrix[y][x] = 1;
			}
		}

		update();
	}

	free(body);
	if (fruit) free(fruit);
	return score;
}
