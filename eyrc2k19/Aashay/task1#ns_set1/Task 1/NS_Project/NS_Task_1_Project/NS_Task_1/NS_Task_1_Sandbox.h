#include "NS_Task_1_Predef.h"
extern unsigned int color_sensor_pulse_count;
/*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the nodes specified
* Example Call: forward_wls(2) //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node);

void left_turn_wls(void);

void right_turn_wls(void);

void Square(void);

void Task_1_1(void);

void Task_1_2(void);

void red_pick(int i);
void green_pick(int j);
void check_color(void);
void nutsearch();
int follow_line();
void linefollow();

/*
int placeAt(int destn);
int pickUpFrom(int destn);
int moveAlong(int *path);
int moveTo(int dest);




*/