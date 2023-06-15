#include "lib.h"

struct Enemy{
	short x{}, y{};
	bool attacking{}, alive{true};

	Enemy(int x, int y) : x{x}, y{y}{}
};

int zelda(){
	short hp{3}, x{3}, y{3}, dir{Direction::UP}, attackSwing{}, attackFrame{};
	int score{}, playerLast{}, attackLast{}, playerSpeed{250}, attackSpeed{100};
	Enemy* enemies{};
	int len{}, enemyLast{};
	bool attacking{};

	while (1){
		/* if (!len){ */
		/* 	int len = random(1, 4); */
		/* 	enemies = (Enemy*)malloc(sizeof(Enemy[len])); */

		/* 	for (int i = 0; i < len; ++i){ */
		/* 		enemies[i].x = random(8); */
		/* 		enemies[i].y = random(8); */
		/* 	} */
		/* } */	

		if (millis() - playerLast >= playerSpeed && !attacking){
			switch (joystickEvent()){
				case Direction::UP:
					if ((y > 0) && (dir == Direction::UP)){
						matrix[y][x] = 0; 
						--y; playerLast = millis();
					}

					dir = Direction::UP;
					break;
				case Direction::DOWN:
					if ((y < 7) && (dir == Direction::DOWN)){
						matrix[y][x] = 0; 
						++y; playerLast = millis(); 
					}

					dir = Direction::DOWN;
					break;
				case Direction::RIGHT:
					if ((x < 7) && (dir == Direction::RIGHT)){
						matrix[y][x] = 0;
						++x; playerLast = millis(); 
					}

					dir = Direction::RIGHT;
					break;
				case Direction::LEFT:
					if ((x > 0) && (dir == Direction::LEFT)){
						matrix[y][x] = 0; 
						--x; playerLast = millis(); 
					}

					dir = Direction::LEFT;
					break;
			}
		}

		matrix[y][x] = 1;

		if (((millis() - attackLast) >= (attackSpeed * 3) + 100) && !attacking){
			if (buttonEvent()){
				attacking = true; 
				attackLast = millis(); 
			}
		}

		if (attacking){
			if (!attackFrame)
				attackFrame = millis();

			for (int i = 0; i < 3; ++i)
				matrix[y - 1][x - 1 + i] = 0;
			for (int i = 0; i < 3; ++i)
				matrix[y + 1][x + 1 - i] = 0;
			matrix[y][x - 1] = 0;
			matrix[y][x + 1] = 0;

			int swordX{}, swordY{};
			switch (dir){
				case Direction::UP:
					swordY = y - 1;
					swordX = x - 1 + attackSwing;
					break;
				case Direction::DOWN:
					swordY = y + 1;
					swordX = x + 1 - attackSwing;
					break;
				case Direction::LEFT:
					swordY = y + 1 - attackSwing;
					swordX = x - 1;
					break;
				case Direction::RIGHT:
					swordY = y - 1 + attackSwing;
					swordX = x + 1;
					break;
			}

			matrix[swordY][swordX] = 1;
			for (int i = 0; i < len; ++i){
				if (enemies[i].y == swordY && enemies[i].x == swordX){
					++score;
					Enemy* newEnemies = (Enemy*)malloc(sizeof(Enemy[len - 1]));
					int count{};

					for (int j = 0; j < len; ++j){
						if (i != j){
							memcpy(newEnemies + count, enemies + j, sizeof(Enemy));
						}
					}

					--len;
					free(enemies);
					enemies = newEnemies;
				}
			}

			if ((millis() - attackFrame) >= attackSpeed){
				if (attackSwing < 2){
					++attackSwing; 
					attackFrame = millis();
				}
				else{
					attacking = false; 
					attackFrame = 0; 
					attackSwing = 0; 

					for (int i = 0; i < 3; ++i)
						matrix[y - 1][x - 1 + i] = 0;
					for (int i = 0; i < 3; ++i)
						matrix[y + 1][x + 1 - i] = 0;
					matrix[y][x - 1] = 0;
					matrix[y][x + 1] = 0;
				}
			}
		}

		if ((millis() - enemyLast >= 1000) && len){
			for (int i = 0; i < len; ++i){
				if (enemies[i].x < x){
					matrix[enemies[i].y][enemies[i].x] = 0;
					++enemies[i].x;
				}
				if (enemies[i].y < y){
					matrix[enemies[i].y][enemies[i].x] = 0;
					++enemies[i].y;
				}

				if (enemies[i].y == y && enemies[i].x == x){
					--hp;
					Enemy* newEnemies = (Enemy*)malloc(sizeof(Enemy[len - 1]));
					int count{};

					for (int j = 0; j < len; ++j){
						if (i != j){
							memcpy(newEnemies + count, enemies + j, sizeof(Enemy));
						}
					}

					--len;
					free(enemies);
					enemies = newEnemies;
				}
			}

			enemyLast = millis();
		}

		for (int i = 0; i < len; ++i)
			matrix[enemies[i].y][enemies[i].x] = 1;

		if (!hp)
			break;

		update();
	}

	return score;
}
