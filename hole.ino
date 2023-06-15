int holeInTheWall(){
	/* constexpr int walls[][8]{{1,1,1,1,1,1,0,0},{1,1,1,1,1,0,0,1},{1,1,1,1,0,0,1,1},{1,1,1,0,0,1,1,1},{1,1,0,0,1,1,1,1},{1,0,0,1,1,1,1,1},{0,0,1,1,1,1,1,1},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,1,1,1,1,1,0},{1,0,1,1,1,1,0,1},{1,1,0,1,1,0,1,1},{1,1,1,1,0,0,0,0},{0,1,1,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,1,1,0},{0,0,0,0,1,1,1,1},{1,1,0,0,0,0,1,1},{1,0,0,0,0,1,1,1},{1,1,1,0,0,0,0,1}, {0,1,1,0,0,1,1,0}}; */

	/* short wallIndex{random(sizeof(walls)/sizeof(walls[0]))}; */

	/* class : Object{ */
	/* 	unsigned long playerLast{}, playerSpeed{250}, score{}; */
	/* } player; */
	/* player.size = 1; */
	/* player.positions = new int[]{3, 3}; */

	/* class : Object{ */
	/* 	unsigned long wallLast{}, wallSpeed{1000}; */
	/* 	short wallPos{}, wallDir{random(4)}; */
	/* } wall; */

	/* objects = new Object*[]{ &player, &wall }; */

	/* while (1){ */
	/* 	clear(); */ 

	/* 	if ((millis() - player.playerLast) >= player.playerSpeed){ */ 
	/* 		switch joystick_event(){ */
	/* 			case Direction::UP: */
	/* 				if (player.positions[0][1] > 0) */ 
	/* 					--player.positions[0][1]; player.playerLast = millis(); */
	/* 				break; */
	/* 			case Direction::DOWN: */
	/* 				if (player.positions[0][1] < 7) */ 
	/* 					++player.positions[0][1]; player.playerLast = millis(); */ 
	/* 				break; */
	/* 			case Direction::RIGHT: */
	/* 				if (player.positions[0][0] < 7) */ 
	/* 					++player.positions[0][0]; player.playerLast = millis(); */ 
	/* 				break; */
	/* 			case Direction::LEFT: */
	/* 				if (player.positions[0][0] > 0) */ 
	/* 					--player.positions[0][0]; player.playerLast = millis(); */ 
	/* 				break; */
	/* 			case Direction::NONE: */
	/* 				break; */
	/* 		} */
		
	/* 	if ((millis() - wall.wallLast) >= wall.wallSpeed){ */
	/* 		if (++wallPos > 7){ */ 
	/* 			wall.wallDir = random(4), wallPos = 0; */ 
	/* 			wallIndex = random(sizeof(walls)/sizeof(walls[0])); */ 
	/* 			wall.wallSpeed -= 20; */ 
	/* 			++player.score; */ 
	/* 		} */

	/* 		wall.wallLast = millis(); */ 
	/* 	} */    

	/* 	if (!(wallDir%2)){ */ 
	/* 		for (int i = 0; i < 8; ++i) */
	/* 			wallDir == 0 ? matrix[i][wallPos] = walls[wallIndex][i] : matrix[i][7-wallPos] = walls[wallIndex][i]; */ 
	/* 	} */
	/* 	else{ */ 
	/* 		for (int i = 0; i < 8; ++i) */
	/* 			wallDir == 1 ? matrix[wallPos][i] = walls[wallIndex][i] : matrix[7-wallPos][i] = walls[wallIndex][i]; */
	/* 	} */

	/* 	update(); */ 

	/* 	if (matrix[yPos][xPos]){ */ 
	/* 		clear(); */
	/* 		screenAnimation(); */ 
			
	/* 		for (int i = 0; i < 15; ++i) */
	/* 			matrix[i/3][(i%3)] = numbers[score/10][i]; */ 
	/* 		for (int i = 0; i < 15; ++i) */
	/* 			matrix[i/3][(i%3)+5] = numbers[score%10][i]; */ 

	/* 		unsigned long lastFrame{}, screenTime{millis()}; */
	/* 		bool visible = false; */
	/* 		while (!(analogRead(A0) >= 895 || */ 
	/* 				analogRead(A0) <= 128 || */
	/* 				analogRead(A1) >= 895 || */
	/* 				analogRead(A1) <= 128) || (millis()-screenTime) <= 3000){ */
	/* 			if ((millis()-lastFrame) >= 750){ */
	/* 				visible = !visible; */	
	/* 				lastFrame = millis(); */	
	/* 			} */

	/* 			if (visible){ */
	/* 				matrix[6][3] = 1, matrix[6][4] = 1; */
	/* 				matrix[7][3] = 1, matrix[7][4] = 1; */
	/* 			} */
	/* 			else{ */
	/* 				matrix[6][3] = 0, matrix[6][4] = 0; */
	/* 				matrix[7][3] = 0, matrix[7][4] = 0; */
	/* 			} */

	/* 			update(false); */ 
	/* 		} */

	/* 		clear(); */
	/* 		screenAnimation(); */ 
			
	/* 		xPos = 3, yPos = 3, score = 0; */
	/* 		wallPos = 0, wallDir = random(4), wallIndex = random(sizeof(walls)/sizeof(walls[0])), wallSpeed = 1000; */
	/* 		wallLast = millis(), playerLast = millis(); */
	/* 	} */
	/* 	} */
}
