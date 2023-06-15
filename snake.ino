#include "lib.h"

int* generateFruit(){
	/* int (*temp)[2] = body; */ 
	/* body = new int[len][2]{}; */
	/* memcpy(body, temp, sizeof(int[2]) * (len - 1)); */
	/* memcpy(body[len - 1], tail, sizeof(int[2]) */

	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){

		}
	}
	return new int[2]{};
}

int snake(){
	int len{1}, dir{}, last{}, score{};
	int (*body)[2] = new int[1][2]{ { 3, 3 } };
	int* fruit{};

	while (1){
		for (int i = len - 1; i > 0; --i)
			matrix[body[i][0]][body[i][1]] = 1;

		if (!fruit){
			fruit = generateFruit();
			matrix[fruit[0]][fruit[1]] = 1;
		}

		update();

		int input = joystickEvent();
		if (input % 2 != dir % 2)
			dir = input;
		
		if (millis() - last >= 750){
			int tail[2];

			for (int i = len - 1; i > 0; --i)
				matrix[body[i][0]][body[i][1]] = 0;

			for (int i = 1; i < len; ++i){
				body[i][0] = body[i - 1][0];
				body[i][1] = body[i - 1][1];
				memcpy(tail, body[i], sizeof(int[2]));
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
				matrix[body[i][0]][body[i][1]] = 1;
			
			int x = body[0][0], y = body[1][1];
			if (x < 0 || x > 7 || y < 0 || y > 7)
				break;

			if (matrix[x][y]){
				if (fruit && fruit[0] == x && fruit[1] == y){
					matrix[fruit[0]][fruit[1]] = 0;
					fruit == nullptr;
					++score;

					++len;
					int (*temp)[2] = body; 
					body = new int[len][2]{};
					memcpy(body, temp, sizeof(int[2]) * (len - 1));
					memcpy(body[len - 1], tail, sizeof(int[2]));
				}
				else{
					break;
				}
			}
			else{
				matrix[x][y] = 1;
			}
			
			last = millis();
			update();
		}
	}

	return score;
}
