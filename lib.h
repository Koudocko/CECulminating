#ifndef LIB 
#define LIB

enum Direction{ UP, LEFT, DOWN, RIGHT, NONE };

extern bool matrix[8][8];

Direction joystickEvent();
bool buttonEvent();

#endif
