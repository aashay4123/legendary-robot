/*
*Team Id: 3310
*Author List: Rachit Rathi, Aashay Phirke, Sudhanshu Lodha, Sarah Sonje
*Filename: NS_Task_1_Sandbox.h
*Theme: Nutty Squirrel
*Functions: Task_1_1,linefollow,node_x (x is from 1 to 12)
*Global Variables: NONE
*/
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
/*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); 
*
*/
void left_turn_wls(void);
/*
* Function Name:  right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls();
*
*/
void right_turn_wls(void);

void Square(void);
/*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Main program and calling functions are written.
* Example Call: Task_1_1(); 
*
*/
void Task_1_1(void);

void Task_1_2(void);
/*
* Function Name: linefollow
* Input: void
* Output: void
* Logic: Detects values from the sensors and based on the values follows the black line
* Example Call: linefollow(); 
*
*/
void linefollow(void);
/*
* Function Name: node_x();(x from 1 to 12)
* Input: void
* Output: void
* Logic:Used to perform operations on the node
* Example Call: node_x(x from 1 to 12)
*
*/
void node_13(void);
void node_12(void);
void node_11(void);
void node_10(void);
void node_9(void);
void node_8(void);
void node_7(void);
void node_6(void);
void node_5(void);
void node_4(void);
void node_3(void);
void node_2(void);
void node_1(void);
