/*
*Team Id: 3310
*Author List: Rachit Rathi, Aashay Phirke, Sudhanshu Lodha, Sarah Sonje
*Filename: NS_Task_1_Sandbox.cpp
*Theme: Nutty Squirrel 
*Functions: Task_1_1,linefollow,node_x (x is from 1 to 12)
*Global Variables: NONE
*/
#include "NS_Task_1_Sandbox.h"
/*
*
* Function Name: forward_wls
* Input: node
* Output: void
* Logic: Uses white line sensors to go forward by the number of nodes specified
* Example Call: forward_wls(2); //Goes forward by two nodes
*
*/
void forward_wls(unsigned char node)
{

}
/*
*
* Function Name: left_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn left until black line is encountered
* Example Call: left_turn_wls(); //Turns right until black line is encountered
*
*/
void left_turn_wls(void)//For Turning Left at the Node
{
	left();
	_delay_ms(150);
	while (ADC_Conversion(2) < 200)
	{
		left();
		velocity(200, 200);
	}
	stop();
	_delay_ms(2000);
}

/*
*
* Function Name: right_turn_wls
* Input: void
* Output: void
* Logic: Uses white line sensors to turn right until black line is encountered
* Example Call: right_turn_wls(); //Turns right until black line is encountered
*/
void right_turn_wls(void)//For Turning Right at the Node
{
	right();
	_delay_ms(150);
	while (ADC_Conversion(2) < 200)
	{
		right();
		velocity(200, 200);
	}
	stop();
	_delay_ms(2000);
}

/*
*
* Function Name: Square
* Input: void
* Output: void
* Logic: Use this function to make the robot trace a square path on the arena
* Example Call: Square();
*/

void Square(void)
{

}

/*
*
* Function Name: Task_1_1
* Input: void
* Output: void
* Logic: Main Program from which other sub functions are called.
* Example Call: Task_1_1();
*/
void Task_1_1(void)//MAIN PROGRAM
{
	unsigned char left_sensor, centre_sensor, right_sensor;
	while (1)
	{
		left_sensor = ADC_Conversion(1);//Read values from left sensor
		centre_sensor = ADC_Conversion(2);//Read values from centre sensor
		right_sensor = ADC_Conversion(3);//Read values from right sensor
		printf("\n %d %d %d ", left_sensor, centre_sensor, right_sensor);

		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor <= 100)//FORWARD
		{
			forward();
			velocity(200, 200);
		}
		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor >= 100)//RIGHT
		{
			soft_right();
			velocity(200, 200);
		}
		
		if (left_sensor >= 100 && centre_sensor <= 100 && right_sensor <= 100)//LEFT
		{
			soft_left();
			velocity(200, 200);
		}

		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor <= 100)//STOP
		{
			stop();
			_delay_ms(500);
		}

		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor >= 100)
		{
			_delay_ms(180);
			stop();
			_delay_ms(1000);
			node_1();
		}
	}
}
/*
*
* Function Name: node 1-13
* Input: void
* Output: void
* Logic: Use this function to call all the nodes 
* Example Call: node_1();
*/

void node_1()//At node 1
{
	right_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(650);
	stop();
	_delay_ms(500);
	node_2();
}
void node_2()//at node 2
{
	left_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(350);
	left();
	_delay_ms(150);
	node_3();
}
void node_3()//at node 3
{
	left_turn_wls();
	right();
	_delay_ms(20);
	linefollow();
	stop();
	_delay_ms(500);
	left();
	_delay_ms(100);
	forward();
	_delay_ms(200);
	node_4();
}
void node_4()//at node 4
{
	left_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(350);
	right();
	_delay_ms(100);
	node_5();
}
void node_5()//at node 5
{
	right_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(250);
	right();
	_delay_ms(10);
	node_6();
}
void node_6()//at node 6
{

	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(250);
	right();
	_delay_ms(50);
	node_7();
}
void node_7()//at node 7
{
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(300);
	right();
	_delay_ms(100);
	node_8();
}

void node_8()//at node 8
{
	right_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(300);
	node_9();
}
void node_9()//at node 9
{
	left_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(400);
	left();
	_delay_ms(150);
	node_10();
}
void node_10()//at node 10
{
	left_turn_wls();
	linefollow();
	stop();
	_delay_ms(500);
	forward();
	_delay_ms(300);
	left();
	_delay_ms(50);
	node_11();
}

void node_11()//at node 11
{
	left_turn_wls();
	forward();
	_delay_ms(300);
	right();
	_delay_ms(60);
	linefollow();
	forward();
	_delay_ms(300);
	right();
	_delay_ms(100);
	node_12();
}

void node_12()//at node 12
{
	right_turn_wls();
	linefollow();
	node_13();
}

void node_13()//at node 13
{
	while (1)
	{
		stop();//Robot stops at the GOAL position.
	}
}
/*
* Function Name: linefollow
* Input: void
* Output: void
* Logic: Detects values from the sensors and based on the values follows the black line
* Example Call: linefollow();
*
*/
void linefollow(void)
{
	unsigned char left_sensor, centre_sensor, right_sensor;
	while (1)
	{
		left_sensor = ADC_Conversion(1);
		centre_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		printf("\n %d %d %d ", left_sensor, centre_sensor, right_sensor);
		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor <= 100)//FORWARD
		{
			forward();
			velocity(200, 200);
		}
		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor >= 100)//RIGHT
		{
			soft_right();
			velocity(200, 200);
		}
		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor >= 100)//RIGHT
		{
			soft_right();
			velocity(200, 200);
		}
		if (left_sensor >= 100 && centre_sensor <= 100 && right_sensor <= 100)//LEFT
		{
			soft_left();
			velocity(200, 200);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor <= 100)//LEFT
		{
			soft_left();
			velocity(200, 200);
		}

		if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor <= 100)//STOP
		{
			stop();
			_delay_ms(2000);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor >= 100)
		{
			break;
		}
	}
}
void Task_1_2(void)
{

}