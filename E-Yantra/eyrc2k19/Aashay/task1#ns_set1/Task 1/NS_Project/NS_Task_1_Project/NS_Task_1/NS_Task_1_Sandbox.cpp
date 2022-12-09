/*
*Team Id: 3310
*Author List: Rachit Rathi, Aashay Phirke, Sudhanshu Lodha, Sarah Sonje
*Filename: NS_Task_1_Sandbox.cpp
*Theme: Nutty Squirrel
*Functions: Task_1_1,linefollow,node_x (x is from 1 to 12)
*Global Variables: NONE
*/
#include "NS_Task_1_Sandbox.h"
#include<stdio.h>
#include<stdlib.h>
#include <limits.h>
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
	int x = (int)node;
	while (x != 0)
	{
		unsigned char left_sensor, centre_sensor, right_sensor;
		left_sensor = ADC_Conversion(1);//Read values from left sensor
		centre_sensor = ADC_Conversion(2);//Read values from centre sensor
		right_sensor = ADC_Conversion(3);//Read values from right sensor
		printf("\n %d %d %d ", left_sensor, centre_sensor, right_sensor);
		forward();
		velocity(100, 100);

		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor >= 100)//FORWARD
		{
			_delay_ms(500);
			stop();
			_delay_ms(500);
			x--;
		}
	}
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
		velocity(100, 100);
	}
	stop();
	_delay_ms(100);
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
		velocity(100, 100);
	}
	stop();
	_delay_ms(1000);
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
}

typedef struct node
{
	int cost;
	int reqAlign;
	int futAlign;
}node;

node graph[23][23];
int present;
int presAlign;
int n;
int pathLength;

void makeNode(int i, int j, int cost, int reqAlign, int futAlign)
{
	graph[i][j].cost = cost;
	graph[i][j].reqAlign = reqAlign;
	graph[i][j].futAlign = futAlign;
}
int createGraph()
{
	printf("Creating graph\n");
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			graph[i][j].cost = 0;
			graph[i][j].reqAlign = 0;
			graph[i][j].futAlign = 0;
		}
	}


	makeNode(0, 1, 2, 0, 0);
	makeNode(1, 0, 2, 180, 180);

	makeNode(1, 2, 8, 0, 0);
	makeNode(2, 1, 8, 180, 180);
	makeNode(1, 11, 3, 90, 135);
	makeNode(11, 1, 3, 315, 270);
	makeNode(1, 18, 3, 270, 225);
	makeNode(18, 1, 3, 45, 90);

	makeNode(2, 5, 3, 90, 90);
	makeNode(5, 2, 3, 270, 270);
	makeNode(2, 13, 3, 270, 270);
	makeNode(13, 2, 3, 90, 90);

	makeNode(3, 6, 5, 180, 180);
	makeNode(6, 3, 5, 0, 0);
	makeNode(3, 4, 3, 270, 270);
	makeNode(4, 3, 3, 90, 90);

	makeNode(4, 5, 3, 270, 270);
	makeNode(5, 4, 3, 90, 90);
	makeNode(4, 7, 4, 180, 180);
	makeNode(7, 4, 4, 0, 0);

	makeNode(6, 8, 5, 225, 180);
	makeNode(8, 6, 5, 0, 45);
	makeNode(6, 7, 4, 315, 315);//DOUBT
	makeNode(7, 6, 4, 135, 135);//DOUBT

	makeNode(7, 11, 6, 180, 225);//DOUBT 
	makeNode(11, 7, 6, 45, 0);//DOUBT

	makeNode(8, 12, 3, 180, 180);
	makeNode(12, 8, 3, 0, 0);
	makeNode(8, 9, 3, 270, 270);
	makeNode(9, 8, 3, 90, 90);

	makeNode(9, 10, 1, 270, 270);
	makeNode(10, 9, 1, 90, 90);

	makeNode(10, 11, 3, 0, 315);
	makeNode(11, 10, 3, 135, 180);
	makeNode(10, 19, 7, 180, 0);
	makeNode(19, 10, 7, 180, 0);

	makeNode(13, 15, 3, 270, 270);
	makeNode(14, 14, 3, 90, 90);

	makeNode(14, 15, 3, 270, 270);
	makeNode(15, 14, 3, 90, 90);
	makeNode(14, 16, 4, 180, 180);
	makeNode(16, 14, 4, 0, 0);

	makeNode(15, 17, 5, 180, 180);
	makeNode(17, 15, 5, 0, 0);

	makeNode(16, 17, 4, 225, 225);
	makeNode(17, 16, 4, 45, 45);
	makeNode(16, 18, 6, 180, 135);
	makeNode(18, 16, 6, 315, 0);


	makeNode(17, 21, 5, 135, 180);
	makeNode(21, 17, 5, 0, 315);

	makeNode(18, 19, 3, 225, 180);
	makeNode(19, 18, 3, 0, 45);

	makeNode(19, 20, 1, 270, 270);
	makeNode(20, 19, 1, 90, 90);

	makeNode(20, 21, 3, 270, 270);
	makeNode(21, 20, 3, 90, 90);

	makeNode(21, 22, 3, 180, 180);
	makeNode(22, 21, 3, 0, 0);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%d ", graph[i][j].cost);
			printf("%d ", graph[i][j].reqAlign);
			printf("%d ", graph[i][j].futAlign);
		}
		printf("\n");
	}
	return 1;
}
int minDistance(int dist[], int sptSet[])
{
	int min = INT_MAX, min_index;
	int v;
	for (v = 0; v < n; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;
	return min_index;
}
int* printSolution(int dist[], int parent[], int destn)
{
	int src = present;
	int * path = (int*)malloc(1 * sizeof(int));
	path[0] = destn;
	int i, j, k;
	for (i = 1; path[i - 1] != src; i++)
	{
		path = (int *)realloc(path, (i + 1) * sizeof(int));
		path[i] = parent[path[i - 1]];
	}
	for (j = i - 1, k = 0; j >= i / 2; j--, k++)
	{
		int temp = path[k];
		path[k] = path[j];
		path[j] = temp;
	}
	for (j = 0; j < i; j++)
	{
		printf(" %d ", path[j]);
	}
	pathLength = i;
	return path;
}
int* findPathTo(int destn)
{
	int src = present;
	int parent[24];
	int i, count;

	int dist[24];
	int sptSet[24];
	for (i = 0; i < n; i++)
	{
		parent[i] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = 0;
	}
	dist[src] = 0;

	for (count = 0; count < n - 1; count++)
	{
		int u = minDistance(dist, sptSet);
		sptSet[u] = 1;
		int v;
		for (v = 0; v < n; v++)
			if (!sptSet[v] && graph[u][v].cost && dist[u] != INT_MAX && dist[u] + graph[u][v].cost < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + graph[u][v].cost;
			}
	}
	printf("Path made\n");
	int *path = printSolution(dist, parent, destn);
	_delay_ms(200);
	return path;
}
int turn(int degTurn)
{
	printf("THe current angle is %d", degTurn);
	if (degTurn == 0)
		forward_wls(1);
	else if (degTurn == 45)
		right_turn_wls();
	else if (degTurn == 135)
		left_turn_wls();
	else if (degTurn == 90)
		right_turn_wls();
	else if (degTurn == -90)
		left_turn_wls();
	else if (degTurn == 180)
	{
		left_turn_wls();
		left_turn_wls();
	}
	printf("Turn %ds \n", degTurn); //COMMENT THIS
	return 1;
}
int isObstacle()
{
	if (ADC_Conversion(FRONT_IR_ADC_CHANNEL) < 100)
		return 1;
	else
		return 0;
}
int nodeEncountered()
{
	unsigned char left_sensor, centre_sensor, right_sensor;
	left_sensor = ADC_Conversion(1);
	centre_sensor = ADC_Conversion(2);
	right_sensor = ADC_Conversion(3);
	if (left_sensor >= 200 && centre_sensor >= 200 && right_sensor >= 00)
	{
		return 1;
	}
	return 0;
}
int follow_line()
{

	unsigned char left_sensor, centre_sensor, right_sensor;

	while (nodeEncountered() != 1)
	{
		printf("no obstacle");
		if (isObstacle() == 1)
		{
			return 0;
		}
		printf("Following line");	//follow line until next node encountered


		left_sensor = ADC_Conversion(1);
		centre_sensor = ADC_Conversion(2);
		right_sensor = ADC_Conversion(3);
		printf("\n %d %d %d ", left_sensor, centre_sensor, right_sensor);

		if (left_sensor <= 200 && centre_sensor >= 100 && right_sensor <= 200)//FORWARD
		{
			forward();
			velocity(100, 100);
		}
		if (left_sensor <= 200 && centre_sensor <= 200 && right_sensor >= 100)//RIGHT
		{

			soft_right();
			velocity(100, 100);
		}
		if (left_sensor >= 100 && centre_sensor <= 200 && right_sensor <= 200)//LEFT
		{
			soft_left();
			velocity(100, 100);
		}
		if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor <= 200)//LEFT
		{
			soft_left();
			velocity(100, 100);
		}
		if (left_sensor <= 200 && centre_sensor >= 100 && right_sensor >= 100)//LEFT
		{
			soft_right();
			velocity(100, 100);
		}

		if (left_sensor <= 200 && centre_sensor <= 200 && right_sensor <= 200)//STOP
		{

			while (1)
			{
				stop();

			}
		}
		if (left_sensor >= 200 && centre_sensor >= 200 && right_sensor >= 00)
		{
			_delay_ms(500);
			stop();
			_delay_ms(500);
			break;
		}
	}
	stop();
	_delay_ms(100);
	return 1;
}



int moveTo(int dest)
{
	printf("moveto");
	int reqAlign = graph[present][dest].reqAlign;
	turn(reqAlign - presAlign);
	int result = follow_line();
	if (result == 0)
	{
		graph[present][dest].cost = 10000;
		return 0;
	}
	else
	{
		printf("\nReached node %d\n", dest);
		presAlign = graph[present][dest].futAlign;
		present = dest;
		return 1;
	}
}
int moveAlong(int *path)
{
	printf("movealong");
	int i;
	for (i = 1; i < pathLength; i++)
	{
		printf("Next Hop: %d\n", path[i]);
		int result = moveTo(path[i]);
		_delay_ms(200);
		if (result == 0)
		{
			return 0;
		}
	}
	return 1;
}
int pickUpFrom(int destn)
{
	int *path = findPathTo(destn);
	printf("\nPath Finalized\n");
	_delay_ms(200);
	while (moveAlong(path) == 0)
	{
		free(path);
		right_turn_wls();//180
		presAlign = (presAlign + 180) % 360;
		path = findPathTo(destn);
	}
	pick();
	return 1;
}
int placeAt(int destn)
{
	int * path = findPathTo(destn);
	_delay_ms(200);
	while (moveAlong(path) != 1)
	{
		free(path);
		right_turn_wls();//180
		presAlign = (presAlign + 180) % 360;
		path = findPathTo(destn);
	}
	place();
	return 1;
}
void check_color(void)
{
	unsigned int red_pulse_count, green_pulse_count, blue_pulse_count, filter_clear_pulse_count;
	filter_red();
	red_pulse_count = color_sensor_pulse_count;
	_delay_ms(200);
	filter_green();
	green_pulse_count = color_sensor_pulse_count;
	_delay_ms(200);
	filter_blue();
	blue_pulse_count = color_sensor_pulse_count;
	filter_clear();
	filter_clear_pulse_count = color_sensor_pulse_count;
	printf("\n%d   %d    %d    %d", red_pulse_count, green_pulse_count, blue_pulse_count, filter_clear_pulse_count);
	_delay_ms(1000);
	int i = 0, j = 0;
	if (red_pulse_count >= 2000 && green_pulse_count <= 2000 && blue_pulse_count <= 2000)
	{
		printf("Color is RED");
		//red_pick(i);
		i++;
	}
	if (red_pulse_count <= 2000 && green_pulse_count >= 2000 && blue_pulse_count <= 2000)
	{
		printf("Color is GREEN");
		//green_pick(j);
		j++;
	}
	if (red_pulse_count <= 2000 && green_pulse_count <= 2000 && blue_pulse_count >= 2000)
	{
		printf("Color is BLUE");
	}
}
void red_pick(int i)
{
	pick();
	//function for node
	if (i == 0)
	{
		moveAlong(findPathTo(12));		//move to 13 change it to 6
		place();
	}
	if (i == 1)
	{
		//move to 10 change it to 7
		place();
	}
}
void green_pick(int i)
{
	pick();
	if (i == 0)
	{
		moveAlong(findPathTo(20));		//move to 21 change it to 8
		place();
	}
	if (i == 1)
	{
		moveAlong(findPathTo(22));//move to 23 change it to 9
		place();
	}

}
void scan() //360 scan
{
	for (int i = 4; i < 7; i++) //for loop through array
	{
		right_turn_wls();
		check_color();
	}
}

void Task_1_2(void)
{
	int a[6] = { 4,5,6,14,15,16 };
	n = 23;
	present = 0;
	presAlign = 0;
	createGraph();
	forward_wls(1);
	for (int i = 0; i < 6; i++)
		pickUpFrom(a[i]);
}
void linefollow(void)
{
	unsigned char left_sensor, centre_sensor, right_sensor;
	float Kp = 107, Ki = 0.7, Kd = 5, error = 0;
	float  P = 0, I = 0, D = 0, PID_value = 0;
	float previous_error = 0, previous_I = 0;
	int initial_motor_velocity = 100;
	while (1)
	{
		left_sensor = ADC_Conversion(1);//Read values from left sensor
		centre_sensor = ADC_Conversion(2);//Read values from centre sensor
		right_sensor = ADC_Conversion(3);//Read values from right sensor
		//printf("\n %d %d %d ", left_sensor, centre_sensor, right_sensor);

		if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor <= 100)//FORWARD
		{

			error = 0;
		}
		else if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor >= 100)//HARD RIGHT
		{

			error = 1;
		}
		else if (left_sensor <= 100 && centre_sensor >= 100 && right_sensor >= 100)//RIGHT
		{

			error = 2;
		}
		else if (left_sensor >= 100 && centre_sensor <= 100 && right_sensor <= 100)//HARD LEFT
		{

			error = -1;
		}
		else if (left_sensor >= 100 && centre_sensor >= 100 && right_sensor <= 100)//LEFT
		{
			error = -2;
		}
		else if (left_sensor <= 100 && centre_sensor <= 100 && right_sensor <= 100)//STOP
		{
			while (1)
			{
				stop();
			}

		}

		void calculate_pid();
		{
			P = error;
			I = I + previous_I;
			D = error - previous_error;

			PID_value = (Kp*P) + (Ki*I) + (Kd*D);
			printf("\n %f %f ", PID_value, error);
			previous_I = I;
			previous_error = error;
		}
		void motor_control();
		{
			forward();
			velocity(200 + PID_value, 200 - PID_value);
		}
	}
} 