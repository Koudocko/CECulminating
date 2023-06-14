class Object{
	int (*positions)[2];
	int size;

public:
		Object(int size, int (*positions)[2]) 
			: size{size}, positions{positions}{}
};

constexpr int rowPins[8]{ 8, 7, 6, 5, 4, 3, 2, 1 }, 
	colPins[8]{ A3, A4, A5, 13, 12, 11, 10, 9 };

int matrix[8][8];
Object** objects{};

enum Direction{ UP, LEFT, DOWN, RIGHT, NONE };

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

unsigned long playerLast, playerSpeed{250}, score;

unsigned long wallLast, wallSpeed{1000};
short wallPos, wallDir{random(4)};

void setup() {
	for (int i = 0; i < 8; ++i){
		pinMode(rowPins[i], 1); 
		pinMode(colPins[i], 1); 
		digitalWrite(colPins[i], 1); 
	}
	pinMode(A0, 0);
	pinMode(A1, 0);
	pinMode(A2, INPUT_PULLUP);

	randomSeed(analogRead(0));
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
			while ((millis()-start) < 25) 
				update();
		}
	}
	for (int i = 0; i < 8; ++i){
		for (int j = 0; j < 8; ++j){
			unsigned long start{millis()}; 

			matrix[i][j] = 0;
			while ((millis()-start) < 25) 
				update();
		}
	}
}

Direction joystickEvent(){
	if (analogRead(A0) >= 895){ 
		return Direction::RIGHT;
	}
	else if (analogRead(A0) <= 128){ 
		return Direction::LEFT;
	}    
	else if (analogRead(A1) >= 895){ 
		return Direction::DOWN;
	}
	else if (analogRead(A1) <= 128){ 
		return Direction::UP;
	}

	return Direction::NONE;
}

bool buttonEvent(){
	static unsigned long last{};

	if ((millis() - last) >= 100 && !digitalRead(A2)){
		last = millis();
		return true;
	}

	return false;
}

/* void holeInTheWall(){ */
/* 	constexpr int walls[][8]{{1,1,1,1,1,1,0,0},{1,1,1,1,1,0,0,1},{1,1,1,1,0,0,1,1},{1,1,1,0,0,1,1,1},{1,1,0,0,1,1,1,1},{1,0,0,1,1,1,1,1},{0,0,1,1,1,1,1,1},{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,1,1,1,1,1,0},{1,0,1,1,1,1,0,1},{1,1,0,1,1,0,1,1},{1,1,1,1,0,0,0,0},{0,1,1,1,1,0,0,0},{0,0,1,1,1,1,0,0},{0,0,0,1,1,1,1,0},{0,0,0,0,1,1,1,1},{1,1,0,0,0,0,1,1},{1,0,0,0,0,1,1,1},{1,1,1,0,0,0,0,1}, {0,1,1,0,0,1,1,0}}; */

/* 	short wallIndex{random(sizeof(walls)/sizeof(walls[0]))}; */

/* 	class : Object{ */
/* 		unsigned long playerLast{}, playerSpeed{250}, score{}; */
/* 	} player; */
/* 	player.size = 1; */
/* 	player.positions = new int[]{3, 3}; */

/* 	class : Object{ */
/* 		unsigned long wallLast{}, wallSpeed{1000}; */
/* 		short wallPos{}, wallDir{random(4)}; */
/* 	} wall; */

/* 	objects = new Object*[]{ &player, &wall }; */

/* 	while (1){ */
/* 		clear(); */ 

/* 		if ((millis() - player.playerLast) >= player.playerSpeed){ */ 
/* 			switch joystick_event(){ */
/* 				case Direction::UP: */
/* 					if (player.positions[0][1] > 0) */ 
/* 						--player.positions[0][1]; player.playerLast = millis(); */
/* 					break; */
/* 				case Direction::DOWN: */
/* 					if (player.positions[0][1] < 7) */ 
/* 						++player.positions[0][1]; player.playerLast = millis(); */ 
/* 					break; */
/* 				case Direction::RIGHT: */
/* 					if (player.positions[0][0] < 7) */ 
/* 						++player.positions[0][0]; player.playerLast = millis(); */ 
/* 					break; */
/* 				case Direction::LEFT: */
/* 					if (player.positions[0][0] > 0) */ 
/* 						--player.positions[0][0]; player.playerLast = millis(); */ 
/* 					break; */
/* 				case Direction::NONE: */
/* 					break; */
/* 			} */
		
/* 		if ((millis() - wall.wallLast) >= wall.wallSpeed){ */
/* 			if (++wallPos > 7){ */ 
/* 				wall.wallDir = random(4), wallPos = 0; */ 
/* 				wallIndex = random(sizeof(walls)/sizeof(walls[0])); */ 
/* 				wall.wallSpeed -= 20; */ 
/* 				++player.score; */ 
/* 			} */

/* 			wall.wallLast = millis(); */ 
/* 		} */    

/* 		if (!(wallDir%2)){ */ 
/* 			for (int i = 0; i < 8; ++i) */
/* 				wallDir == 0 ? matrix[i][wallPos] = walls[wallIndex][i] : matrix[i][7-wallPos] = walls[wallIndex][i]; */ 
/* 		} */
/* 		else{ */ 
/* 			for (int i = 0; i < 8; ++i) */
/* 				wallDir == 1 ? matrix[wallPos][i] = walls[wallIndex][i] : matrix[7-wallPos][i] = walls[wallIndex][i]; */
/* 		} */

/* 		update(); */ 

/* 		if (matrix[yPos][xPos]){ */ 
/* 			clear(); */
/* 			screenAnimation(); */ 
			
/* 			for (int i = 0; i < 15; ++i) */
/* 				matrix[i/3][(i%3)] = numbers[score/10][i]; */ 
/* 			for (int i = 0; i < 15; ++i) */
/* 				matrix[i/3][(i%3)+5] = numbers[score%10][i]; */ 

/* 			unsigned long lastFrame{}, screenTime{millis()}; */
/* 			bool visible = false; */
/* 			while (!(analogRead(A0) >= 895 || */ 
/* 					analogRead(A0) <= 128 || */
/* 					analogRead(A1) >= 895 || */
/* 					analogRead(A1) <= 128) || (millis()-screenTime) <= 3000){ */
/* 				if ((millis()-lastFrame) >= 750){ */
/* 					visible = !visible; */	
/* 					lastFrame = millis(); */	
/* 				} */

/* 				if (visible){ */
/* 					matrix[6][3] = 1, matrix[6][4] = 1; */
/* 					matrix[7][3] = 1, matrix[7][4] = 1; */
/* 				} */
/* 				else{ */
/* 					matrix[6][3] = 0, matrix[6][4] = 0; */
/* 					matrix[7][3] = 0, matrix[7][4] = 0; */
/* 				} */

/* 				update(false); */ 
/* 			} */

/* 			clear(); */
/* 			screenAnimation(); */ 
			
/* 			xPos = 3, yPos = 3, score = 0; */
/* 			wallPos = 0, wallDir = random(4), wallIndex = random(sizeof(walls)/sizeof(walls[0])), wallSpeed = 1000; */
/* 			wallLast = millis(), playerLast = millis(); */
/* 		} */
/* 		} */
/* } */

void snake(){
	while (1){
		clear();
		matrix[0][0] = 1;
		update();
	}

	/* int len{1}, x{3}, y{3}, dir{}, last{}; */

	/* while (1){ */
	/* 	int input = joystick_event(); */
	/* 	if (input % 2 != dir % 2) */
	/* 		dir = input; */

	/* 	clear(); */
	/* 		// do update s tuff */
	/* 	update(); */
	/* } */
}

void zelda(){
	while (1){
		clear();
		matrix[7][7] = 1;
		update();
	}
}

void menuAnimation(bool img[4][4]){
	static unsigned long last{};
	static bool state{};
	
	clear();
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

constexpr bool gameLogos[][4][4]
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
	}
};
constexpr void (*games[])(){ snake, zelda };

int gameIdx{};
void loop() {
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

	if (buttonEvent())
		games[gameIdx]();

	menuAnimation(gameLogos[gameIdx]);
}
