int matrix[8][8];

Direction joystickEvent(){
	static unsigned long last{};

	if (millis() - last >= 100){
		last = millis();

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
