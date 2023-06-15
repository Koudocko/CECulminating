int hole(){
	constexpr static bool walls[][8]{{1,1,1,1,1,1,0,0},{1,1,1,1,1,0,0,1},{1,1,1,1,0,0,1,1},{1,1,1,0,0,1,1,1},{1,1,0,0,1,1,1,1},{1,0,0,1,1,1,1,1},{0,0,1,1,1,1,1,1},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,1,1,1,1,1,0},{1,0,1,1,1,1,0,1},{1,1,0,1,1,0,1,1},{1,1,1,1,0,0,0,0},{0,1,1,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,1,1,0},{0,0,0,0,1,1,1,1},{1,1,0,0,0,0,1,1},{1,0,0,0,0,1,1,1},{1,1,1,0,0,0,0,1}, {0,1,1,0,0,1,1,0}};

	short wallPos{}, wallDir{random(4)}, wallIndex{random(sizeof(walls)/sizeof(walls[0]))};;
	unsigned long wallLast{}, wallSpeed{1000};

	int x{3}, y{3};
	unsigned long playerLast{}, playerSpeed{250}, score{};

	while (1){
		if ((millis() - playerLast) >= playerSpeed){ 
			switch (joystickEvent()){
				case Direction::UP:
					if (y > 0) 
						matrix[y][x] = 0;
						--y; playerLast = millis();
					break;
				case Direction::DOWN:
					if (y < 7) 
						matrix[y][x] = 0;
						++y; playerLast = millis(); 
					break;
				case Direction::RIGHT:
					if (x < 7) 
						matrix[y][x] = 0;
						++x; playerLast = millis(); 
					break;
				case Direction::LEFT:
					if (x > 0) 
						matrix[y][x] = 0;
						--x; playerLast = millis(); 
					break;
			}
		}
		
		if ((millis() - wallLast) >= wallSpeed){
			if (!(wallDir % 2)){
				for (int i = 0; i < 8; ++i)
					wallDir == 0 ? matrix[i][wallPos] = 0 : matrix[i][7 - wallPos] = 0; 
			}
			else{
				for (int i = 0; i < 8; ++i)
					wallDir == 1 ? matrix[wallPos][i] = 0 : matrix[7 - wallPos][i] = 0;
			}

			if (++wallPos > 7){ 
				wallDir = random(4), wallPos = 0; 
				wallIndex = random(sizeof(walls) / sizeof(walls[0])); 
				wallSpeed -= 20; 
				++score; 
			}

			wallLast = millis(); 
		}    

		if (!(wallDir % 2)){ 
			for (int i = 0; i < 8; ++i)
				wallDir == 0 ? matrix[i][wallPos] = walls[wallIndex][i] : matrix[i][7 - wallPos] = walls[wallIndex][i]; 
		}
		else{ 
			for (int i = 0; i < 8; ++i)
				wallDir == 1 ? matrix[wallPos][i] = walls[wallIndex][i] : matrix[7 - wallPos][i] = walls[wallIndex][i];
		}

		if (matrix[y][x])
			break;

		matrix[y][x] = 1;
		update();
		matrix[y][x] = 0;
	}
}
