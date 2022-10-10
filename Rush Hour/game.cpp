//============================================================================
// Name        : i210582_Project.cpp
// Author      : FAST CS Department
// Version     : final
// Copyright   : (c) Reserved
// Description : Basic 2D game of Rush Hour...
//============================================================================

#ifndef RushHour_CPP_
#define RushHour_CPP_
#include "util.h"
#include <iostream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <cmath>
using namespace std;
//array for the whole grid it stores the cars the taxi the obstacles the passnegers and everything 
char display_array[20][20] = {
		{
		'T', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//1
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//2
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//3
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//4
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//5
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//6
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//7
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//8
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//9
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//10
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//11
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//12
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//13
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//14
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//15
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//16
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//17
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//18
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' },	//19
	{
		' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' }
};	//20
//GLOBAL VARIBALES
//prev_direction of the car so if the current direction is 0 the orientation will be according to the previous direction
int prev_direction = 2;
//timer variable
int display_timer = 0;
//color choice of the variables
char colorchoice = '0';
//easy hard and medium mode
char modechoice = ' ';
//counter for buildings
int buildings_count = 0;
//stores the screen mode
string Screenmode = "title";
//variables for players data
string playername;
string s_highscore[11];
int i_highscore[11];
//start time 
int start_time = 0;
//cuurent direciton
int DIRECTION = 0;	//indices(moving in row)
int dir = 0;	//pixels(for animation)
int screen1check = 0;
//number of cars for a particular mode : 
int maxCars = 0;
//counters
int moveTaxiCallCount = 0;	//counter for calls of the function (moveTaxi)
int passengers_dropped = 0;	//number of passengers dropped
int scoreboard_count = 0;	//number of names in the file 
//row and column of the taxi
int row = 0, col = 0;
int xI = 0, yI = 19 * 42;
//destination row and column
int d_row = 0, d_col = 0;
//score initally 0
float min_speed_factor = 0;	//min speed factor different for different modes
int min_speed = 0;	//maximum delay in function call which inturn determines the minimum speed
int score = 0;	//score
int TaxiSpeed = 0;	//speed of the taxi based on color
float Carspeed = 1;	//minimum speed at(1) decreses by time
int o_score = 0, c_score = 0;
//max cars 10:[n][0] for rows and[n][1] for columns
int **car_position;	//DMA based on the number of cars
// current direction of the cars:
int *car_direction;
int **cars_coordinates;
int *moveCarCallCount;
int car_count = 0;
// bool check if the taxi is occupied or not
bool occupied = 0;

void SetCanvasSize(int width, int height)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1);	// set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//funciton to draw taxi based on its curent orientation a light is turned on if the taxi is occupied and different colors based on the color of car chosen 
void drawTaxi()
{
	int direct = DIRECTION;
	if (direct == 0)
	{
		direct = prev_direction;
	}
	if (direct == 1 || !direct || direct == 2)
	{
		if (colorchoice == 'r' || colorchoice == 'R')
		{
			DrawRectangle(xI + 5, yI + 7, 32, 12, colors[RED]);
		}
		else
		{
			DrawRectangle(xI + 5, yI + 7, 32, 12, colors[ORANGE]);
		}
		DrawRectangle(xI + 10, yI + 18, 22, 13, colors[SNOW]);
		DrawLine(xI + 21, yI + 18, xI + 21, yI + 18 + 13, 2, colors[BLACK]);
		if (direct == 1)
		{
			if (occupied)
			{
				DrawRectangle(xI + 12, yI + 26, 5, 4, colors[RED]);
			}
			else
			{
				DrawRectangle(xI + 12, yI + 26, 5, 4, colors[BLACK]);
			}
		}
		else if (direct == 2)
		{
			if (occupied)
			{
				DrawRectangle(xI + 24, yI + 26, 5, 4, colors[RED]);
			}
			else
			{
				DrawRectangle(xI + 24, yI + 26, 5, 4, colors[BLACK]);
			}
		}
		DrawCircle(xI + 10, yI + 7, 5, colors[BLACK]);
		DrawCircle(xI + 32, yI + 7, 5, colors[BLACK]);
	}
	if (direct == 3 || direct == 4)
	{
		int xb = 0, xW = 0, xT = 0;
		int xL = 0, yL = 0;	//light indicator
		if (direct == 3)
		{
			xb = 24;
			xW = 13;
			xT = 35;
			xL = 15;
			yL = 24;
		}
		if (direct == 4)
		{
			xb = 9;
			xW = 20;
			xT = 9;
			xL = 24;
			yL = 10;;
		}
		if (colorchoice == 'r' || colorchoice == 'R')
		{
			DrawRectangle(xI + xb, yI + 5, 11, 32, colors[RED]);
		}
		else
		{
			DrawRectangle(xI + xb, yI + 5, 11, 32, colors[ORANGE]);
		}
		DrawRectangle(xI + xW, yI + 8, 13, 22, colors[SNOW]);
		DrawLine(xI + xW, yI + 18, xI + xW + 12, yI + 18, 2, colors[BLACK]);
		if (occupied)
		{
			DrawRectangle(xI + xL, yI + yL, 4, 5, colors[RED]);
		}
		else
		{
			DrawRectangle(xI + xL, yI + yL, 4, 5, colors[BLACK]);
		}
		DrawCircle(xI + xT, yI + 10, 5, colors[BLACK]);
		DrawCircle(xI + xT, yI + 30, 5, colors[BLACK]);
	}

	glutPostRedisplay();
}
//drawCar function that has loop for all the current cars on the board if the number of cars on the board increase so does the 
//loopcount, the direction of the cars is stored in an array and so are the coordinates on the baird and position in the array
//drawing different colored cars based on teh index of the array
void drawCar()
{
	for (int i = 0; i < car_count; i++)
	{
		int direct = car_direction[i];
		if (direct == 3 || direct == 0 || direct == 4)
		{
			if (i % 4 == 0)
			{
				DrawRectangle(cars_coordinates[i][1] + 5, cars_coordinates[i][0] + 7, 32, 12, colors[GREEN]);
			}
			else if (i % 4 == 1)
			{
				DrawRectangle(cars_coordinates[i][1] + 5, cars_coordinates[i][0] + 7, 32, 12, colors[LIGHT_BLUE]);
			}
			else if (i % 4 == 2)
			{
				DrawRectangle(cars_coordinates[i][1] + 5, cars_coordinates[i][0] + 7, 32, 12, colors[MAGENTA]);
			}
			else if (i % 4 == 3)
			{
				DrawRectangle(cars_coordinates[i][1] + 5, cars_coordinates[i][0] + 7, 32, 12, colors[MAROON]);
			}
			DrawRectangle(cars_coordinates[i][1] + 10, cars_coordinates[i][0] + 18, 22, 13, colors[SNOW]);
			DrawLine(cars_coordinates[i][1] + 21, cars_coordinates[i][0] + 18, cars_coordinates[i][1] + 21, cars_coordinates[i][0] + 18 + 13, 2, colors[BLACK]);
			DrawCircle(cars_coordinates[i][1] + 10, cars_coordinates[i][0] + 7, 5, colors[BLACK]);
			DrawCircle(cars_coordinates[i][1] + 32, cars_coordinates[i][0] + 7, 5, colors[BLACK]);
		}
		if (direct == 1 || direct == 2)
		{
			int xb = 0, xW = 0, xT = 0;

			if (direct == 1)
			{
				xb = 24;
				xW = 13;
				xT = 35;
			}
			if (direct == 2)
			{
				xb = 9;
				xW = 20;
				xT = 9;
			}
			if (i % 4 == 0)
			{
				DrawRectangle(cars_coordinates[i][1] + xb, cars_coordinates[i][0] + 5, 11, 32, colors[GREEN]);
			}
			else if (i % 4 == 1)
			{
				DrawRectangle(cars_coordinates[i][1] + xb, cars_coordinates[i][0] + 5, 11, 32, colors[LIGHT_BLUE]);
			}
			else if (i % 4 == 2)
			{
				DrawRectangle(cars_coordinates[i][1] + xb, cars_coordinates[i][0] + 5, 11, 32, colors[MAGENTA]);
			}
			else if (i % 4 == 3)
			{
				DrawRectangle(cars_coordinates[i][1] + xb, cars_coordinates[i][0] + 5, 11, 32, colors[MAROON]);
			}
			DrawRectangle(cars_coordinates[i][1] + xW, cars_coordinates[i][0] + 8, 13, 22, colors[SNOW]);
			DrawLine(cars_coordinates[i][1] + xW, cars_coordinates[i][0] + 18, cars_coordinates[i][1] + xW + 12, cars_coordinates[i][0] + 18, 2, colors[BLACK]);
			DrawCircle(cars_coordinates[i][1] + xT, cars_coordinates[i][0] + 10, 5, colors[BLACK]);
			DrawCircle(cars_coordinates[i][1] + xT, cars_coordinates[i][0] + 30, 5, colors[BLACK]);
		}
	}
	glutPostRedisplay();
}
//draws buildings by checking the right left top and down if theres a building draw a rectangle which connects with the other buikldings for symmetry
void drawBuildings(int j, int i)
{
	DrawSquare(j *42, (19 - i) *42, 43, colors[BROWN]);
	DrawSquare(j *42 + 5, (19 - i) *42 + 6, 33, colors[BLACK]);
	if (i - 1 != 0)
	{
		if (display_array[i - 1][j] == 'b')
			DrawRectangle(j *42 + 5, (19 - i) *42 + 38, 33, 10, colors[BLACK]);
	}
	if (i + 1 != 20)
	{
		if (display_array[i + 1][j] == 'b')
			DrawRectangle(j *42 + 5, (19 - i) *42, 33, 7, colors[BLACK]);
	}
	if (j + 1 != 20)
	{
		if (display_array[i][j + 1] == 'b')
			DrawRectangle(j *42 + 37, (19 - i) *42 + 6, 10, 33, colors[BLACK]);
	}
	if (j - 1 != 0)
	{
		if (display_array[i][j - 1] == 'b')
			DrawRectangle(j *42, (19 - i) *42 + 6, 10, 33, colors[BLACK]);
	}
}
//drawing the stick figures based om position in the array
void drawPerson(int c, int r)
{
	DrawCircle(c *42 + 20, (19 - r) *42 + 30, 5, colors[BLACK]);
	DrawLine(c *42 + 20, (19 - r) *42 + 13, c *42 + 20, (19 - r) *42 + 30, 5, colors[BLACK]);
	DrawLine(c *42 + 14, (19 - r) *42 + 17, c *42 + 20, (19 - r) *42 + 23, 3, colors[BLACK]);
	DrawLine(c *42 + 26, (19 - r) *42 + 17, c *42 + 20, (19 - r) *42 + 23, 3, colors[BLACK]);
	DrawLine(c *42 + 16, (19 - r) *42 + 3, c *42 + 21, (19 - r) *42 + 15, 4, colors[BLACK]);
	DrawLine(c *42 + 24, (19 - r) *42 + 3, c *42 + 20, (19 - r) *42 + 15, 4, colors[BLACK]);
}
//drawing the trees in the map
void drawTree(int c, int r)
{
	DrawRectangle(c *42 + 17, (19 - r) *42, 10, 20, colors[BROWN]);
	DrawCircle(c *42 + 21, (19 - r) *42 + 33, 9, colors[GREEN_YELLOW]);
	DrawRoundRect(c *42 + 7, (19 - r) *42 + 15, 28, 20, colors[GREEN_YELLOW], 9);
}
//function for overtake cehks top and bottom if motion  is horizontal and left and right if the motion is vertical
void overtake(int r, int c, bool hor_ver)	//horizontal or vertical mov check
{
	if ((display_array[r + 1][c] == 'c' || display_array[r - 1][c] == 'c') && hor_ver)
		score++;
	else if ((display_array[r][c + 1] == 'c' || display_array[r][c - 1] == 'c') && !hor_ver)
		score++;
}
//function for the random movement of the cars the cars change the direction only in one out of seven cases however
//if theres a obstacles in the way they will change th direction
void rand_mov(int i, int j, int index)
{
	if (moveCarCallCount[index] == 0)
	{
		bool score_sub = false;
		int loop_count = 0;
		bool loop_ter = false;
		int temp_row = i, temp_col = j;
		int temp = rand() % 7;	// change direction only 1 out 0f 7 checks
		if (temp != 6 && car_direction[index])
		{
			if (car_direction[index] == 1)	//up
			{
				temp_row = i - 1;
			}
			else if (car_direction[index] == 2)	//down
			{
				temp_row = i + 1;
			}
			else if (car_direction[index] == 3)	//left
			{
				temp_col = j - 1;
			}
			else if (car_direction[index] == 4)	//right
			{
				temp_col = j + 1;
			}
			if (!(temp_row < 0 || temp_row > 19 || temp_col < 0 || temp_col > 19))
			{
				if (display_array[temp_row][temp_col] == ' ')
				{
					display_array[i][j] = ' ';
					display_array[temp_row][temp_col] = 'c';
					loop_ter = true;
				}
				else if (display_array[temp_row][temp_col] == 'T')
					if (!score_sub)
					{
						score -= c_score;
						score_sub = true;
					}
			}
		}

		while (!loop_ter)
		{
			car_direction[index] = 0;
			int direction = rand() % 4 + 1;
			temp_col = j;
			temp_row = i;
			if (direction == 1)	//up
			{
				temp_row = i - 1;
			}
			else if (direction == 2)	//down
			{
				temp_row = i + 1;
			}
			else if (direction == 3)	//left
			{
				temp_col = j - 1;
			}
			else if (direction == 4)	//right
			{
				temp_col = j + 1;
			}
			if (!(temp_row < 0 || temp_row > 19 || temp_col < 0 || temp_col > 19))
			{
				if (display_array[temp_row][temp_col] == ' ')
				{
					display_array[i][j] = ' ';
					display_array[temp_row][temp_col] = 'c';
					loop_ter = true;
					car_direction[index] = direction;
				}
				else if (display_array[temp_row][temp_col] == 'T')
					if (!score_sub)
					{
						score -= c_score;
						score_sub = true;
					}
			}
			loop_count++;
			if (loop_count == 50)
			{
				int chek = 0;
				if (!(i + 1 < 0 || i + 1 > 19))
				{
					if (display_array[i + 1][j] == ' ')
					{
						display_array[i][j] = ' ';
						chek = 1;
					}
				}
				else if (!(i - 1 < 0 || i - 1 > 19))
				{
					if (display_array[i - 1][j] == ' ')
					{
						display_array[i][j] = ' ';
						chek = 1;
					}
				}
				else if (!(j + 1 < 0 || j + 1 > 19))
				{
					if (display_array[i][j + 1] == ' ')
					{
						display_array[i][j + 1] = 'c';
						chek = 1;
					}
				}
				else if (!(j - 1 < 0 || j - 1 > 19))
				{
					if (display_array[i][j - 1] == ' ')
					{
						display_array[i][j - 1] = 'c';
						chek = 1;
					}
				}
				if (chek == 0)
				{
					car_direction[index] = 0;
					temp_row = i;
					temp_col = j;
					display_array[i][j] = 'c';
				}
				else
				{
					display_array[i][j] = ' ';
				}
				break;
			}
		}
		car_position[index][0] = temp_row;
		car_position[index][1] = temp_col;
		cars_coordinates[index][0] = (19 - i) *42;
		cars_coordinates[index][1] = j * 42;
	}

	if (car_direction[index] == 1)
		cars_coordinates[index][0] += 6;
	else if (car_direction[index] == 2)
		cars_coordinates[index][0] -= 6;
	else if (car_direction[index] == 3)
		cars_coordinates[index][1] -= 6;
	else if (car_direction[index] == 4)
		cars_coordinates[index][1] += 6;
	moveCarCallCount[index]++;
	if (moveCarCallCount[index] == 7)
	{
		moveCarCallCount[index] = 0;
	}
}
//checks if the next element is ekpty for the car tom move if theres a object in that position it subtracts the scores based on the color of the color of the taxi
bool check_empty_element(int n_row, int n_col)
{
	if (n_row < 0 || n_row > 19 || n_col < 0 || n_col > 19)
		return false;
	if (display_array[n_row][n_col] != ' ' && display_array[n_row][n_col] != 'D')
	{
		if (DIRECTION)
		{
			if (display_array[n_row][n_col] == 'p')
				score -= 5;
			if (display_array[n_row][n_col] == 'B' || display_array[n_row][n_col] == 't')
				score -= o_score;
			if (display_array[n_row][n_col] == 'c')
				score -= c_score;
		}
		return false;
	}

	display_array[row][col] = ' ';
	return true;

}
//move the taxi only changes the direction on every seventh call for smoother animation 
void moveTaxi()
{
	if (moveTaxiCallCount == 0)
	{
		if (DIRECTION != 0)
		{
			prev_direction = DIRECTION;
		}
		dir = 0;
		if (DIRECTION == 1)
		{
			if (check_empty_element(row, col - 1))
			{
				dir = DIRECTION;
				col = col - 1;
			}
			overtake(row, col, 1);
		}
		else if (DIRECTION == 2)
		{
			if (check_empty_element(row, col + 1))
			{
				dir = DIRECTION;
				col += 1;
			}
			overtake(row, col, 1);
		}
		else if (DIRECTION == 3)
		{
			if (check_empty_element(row - 1, col))
			{
				dir = DIRECTION;
				row -= 1;
			}
			overtake(row, col, 0);
		}
		else if (DIRECTION == 4)
		{
			if (check_empty_element(row + 1, col))
			{
				dir = DIRECTION;
				row += 1;
			}
			overtake(row, col, 0);
		}
		DIRECTION = 0;
	}
	//for smoother animaation
	if (dir == 1)
		xI -= 6;
	else if (dir == 2)
		xI += 6;
	else if (dir == 3)
		yI += 6;
	else if (dir == 4)
		yI -= 6;

	moveTaxiCallCount++;
	if (moveTaxiCallCount == 7)
	{
		moveTaxiCallCount = 0;
	}
	display_array[row][col] = 'T';
}
//for smoother motion of all the cars there is call counter array that stores teh counter fro every car and changes the direction on the seventh call
//calls another funciton (random movement)
void moveCar()
{
	for (int i = 0; i < car_count; i++)
	{
		rand_mov(car_position[i][0], car_position[i][1], i);
	}
}
//to display the current time on the screen 
void display_time()
{
	int t = time(0) - start_time;
	int sec = t % 60;
	if (sec < 10)
	{
		DrawString(900, 750, to_string(t / 60) + " : 0" + to_string(t % 60), colors[SNOW]);
	}
	else
	{
		DrawString(900, 750, to_string(t / 60) + " : " + to_string(t % 60), colors[SNOW]);
	}
}
//genreates random item in the arrays based on the varibles passed 
//the number of items in the array is random within the particular range
void Random_item_generator(char name, int num)
{
	int r, c;
	int tmp = rand() % num + num;
	for (int k = 1; k <= tmp; k++)
	{

		if (name == 'c')
		{
			do { 	r = rand() % 20;
				c = rand() % 20;
			} while (display_array[r][c] != ' ');
			display_array[r][c] = name;
			car_position[car_count][0] = r;
			car_position[car_count][1] = c;
			cars_coordinates[car_count][0] = (19 - r) *42;
			cars_coordinates[car_count][1] = c * 42;
			car_count++;
		}
		else
		{
			do { 	r = rand() % 18 + 1;
				c = rand() % 18 + 1;
			} while (display_array[r][c] != ' ' || display_array[r + 1][c] != ' ' || display_array[r - 1][c] != ' ' || display_array[r][c + 1] != ' ' || display_array[r][c - 1] != ' ');
			display_array[r][c] = name;
		}
	}

	glutPostRedisplay();
}
//sorts teh scores as well the names based on the points scored
void sortindex(int count)
{
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = i; j < count; j++)
		{
			if (i_highscore[i] < i_highscore[j])
			{
				int temp = i_highscore[i];
				i_highscore[i] = i_highscore[j];
				i_highscore[j] = temp;
				string temps = s_highscore[i];
				s_highscore[i] = s_highscore[j];
				s_highscore[j] = temps;
			}
		}
	}
}
//for writing the file in the data if the file is empty and the user couldnt make it in the highscore the string nill is passed into the file
void writingfile()
{
	if (score >= 100)
	{
		i_highscore[scoreboard_count] = score;
		s_highscore[scoreboard_count] = playername;
		scoreboard_count += 1;
	}
	sortindex(scoreboard_count);
	fstream highscorers;
	highscorers.open("highscore.txt", ios::out);
	for (int j = 0; j < scoreboard_count && j < 10; j++)
	{
		highscorers << s_highscore[j] << "," << i_highscore[j];
		if (j == scoreboard_count - 1 || j == 9)
			break;
	}
	if (scoreboard_count == 0)
	{
		highscorers << "nill";
	}
	highscorers.close();

}
//sfor selcting the difficulty level of the game, each diffuclty has differnt number of maximum cars and differnt speeds and differnt max speed
void difficultyselector()
{
	if (modechoice == 'e' || modechoice == 'E')
	{
		min_speed = 120;	//fps
		maxCars = 7;
		min_speed_factor = 0.45;
	}
	else if (modechoice == 'M' || modechoice == 'm')
	{
		min_speed = 100;
		maxCars = 9;
		min_speed_factor = 0.43;
	}
	else if (modechoice == 'h' || modechoice == 'H')
	{
		min_speed = 75;
		maxCars = 12;
		min_speed_factor = 0.4;
	}
	Screenmode = "gameplay";

	car_direction = new int[maxCars];
	car_position = new int *[maxCars];
	cars_coordinates = new int *[maxCars];
	moveCarCallCount = new int[maxCars];
	for (int i = 0; i < maxCars; i++)
	{
		car_direction[i] = 0;
		moveCarCallCount[i] = 0;
		car_position[i] = new int[2];
		cars_coordinates[i] = new int[2];
	}
	Random_item_generator('B', 2);
	Random_item_generator('t', 2);
	Random_item_generator('c', 2);
	Random_item_generator('p', 3);
}
//displays the leaderboard after the game ends:
void displayLeaderboard()
{
	DrawRectangle(0, 0, 1100, 840, colors[BLACK]);
	DrawString(500, 800, "LEADERBOARD", colors[RED]);
	DrawString(250, 730, "Sr.No", colors[WHITE]);
	DrawString(470, 730, "NAME", colors[WHITE]);
	DrawString(730, 730, "SCORE", colors[WHITE]);
	static int t = 0;
	if (score < 100 && t == 0)
	{
		scoreboard_count--;
		t = 1;
	}
	for (int i = 0; i < 10; i++)
	{
		if (i < scoreboard_count)
		{
			DrawString(250, 65 *(10 - i) + 10, to_string(i + 1), colors[WHITE]);
			DrawString(400, 65 *(10 - i) + 10, s_highscore[i], colors[WHITE]);
			DrawString(750, 65 *(10 - i) + 10, to_string(i_highscore[i]), colors[WHITE]);
		}
		else
		{
			DrawString(250, 65 *(10 - i) + 10, to_string(i + 1), colors[WHITE]);
			DrawString(400, 65 *(10 - i) + 10, "--------------", colors[WHITE]);
			DrawString(750, 65 *(10 - i) + 10, "----", colors[WHITE]);
		}
	}
}
void drawScreen5()
{
	static int SCORE = score;
	DrawRectangle(0, 0, 1100, 840, colors[BLACK]);
	DrawString(380, 700, "YOUR SCORE = " + to_string(SCORE), colors[BLACK]);
	DrawRoundRect(350, 250, 400, 400, colors[BLACKO], 10);
	if (score >= 100)
		DrawString(500, 550, "YOU WIN", colors[BLACK]);
	else
		DrawString(500, 550, "YOU LOSE", colors[BLACK]);
	DrawRoundRect(420, 300, 250, 150, colors[GREEN], 10);
	DrawString(480, 370, "CONTINUE", colors[BLACK]);

}
//displays the didicukty levels
void displaydifficultymenu()
{
	DrawRectangle(0, 0, 1100, 840, colors[BLACK]);
	DrawRoundRect(350, 250, 400, 400, colors[WHITE], 10);
	DrawRoundRect(360, 260, 380, 380, colors[MISTY_ROSE], 8);
	DrawString(380, 540, "==>  PRESS 'E' FOR EASY", colors[BLACK]);
	DrawString(380, 460, "==>  PRESS 'M' FOR MEDIUM", colors[BLACK]);
	DrawString(380, 380, "==>  PRESS 'H' FOR HARD", colors[BLACK]);
}
//displays a menu on teh screnn to chose a color
void displaycolormenu()
{
	DrawRectangle(0, 0, 1100, 840, colors[BLACK]);
	DrawRoundRect(350, 250, 400, 400, colors[WHITE], 10);
	DrawRoundRect(360, 260, 380, 380, colors[MISTY_ROSE], 8);
	DrawString(380, 540, "==>  PRESS 'R' FOR RED", colors[BLACK]);
	DrawString(380, 460, "==>  PRESS 'Y' FOR YELLOW", colors[BLACK]);
	DrawString(380, 380, "==>  PRESS 'E' FOR RANDOM", colors[BLACK]);
}
//display name input screen
void displaynameinput()
{
	DrawRectangle(0, 0, 1100, 840, colors[BLACK]);
	DrawRoundRect(350, 250, 400, 400, colors[WHITE], 10);
	DrawRoundRect(360, 260, 380, 380, colors[RED], 8);
	DrawString(430, 540, "ENTER NAME", colors[BLACK]);
	DrawRoundRect(400, 350, 300, 150, colors[BLACK], 30);
	DrawRoundRect(410, 360, 280, 130, colors[SNOW], 30);
	DrawString(420, 430, playername, colors[BLACK]);
	DrawString(380, 120, "Click anywhere on the screen to continue", colors[WHITE]);
}
//dispoplay the highscores read from the file
void displayHighscore(int count)
{
	DrawRectangle(0, 0, 1100, 840, colors[BLACK]);
	DrawString(500, 800, "LEADERBOARD", colors[RED]);
	DrawString(250, 730, "Sr.No", colors[WHITE]);
	DrawString(470, 730, "NAME", colors[WHITE]);
	DrawString(730, 730, "SCORE", colors[WHITE]);
	for (int i = 0; i < 10; i++)
	{
		if (i < count)
		{
			DrawString(250, 65 *(10 - i) + 10, to_string(i + 1), colors[WHITE]);
			DrawString(400, 65 *(10 - i) + 10, s_highscore[i], colors[WHITE]);
			DrawString(750, 65 *(10 - i) + 10, to_string(i_highscore[i]), colors[WHITE]);
		}
		else
		{
			DrawString(250, 65 *(10 - i) + 10, to_string(i + 1), colors[WHITE]);
			DrawString(400, 65 *(10 - i) + 10, "--------------", colors[WHITE]);
			DrawString(750, 65 *(10 - i) + 10, "----", colors[WHITE]);
		}
	}
	DrawString(400, 20, "PRESS SPACEBAR TO CONTINUE", colors[DARK_MAGENTA]);
}
//for reading from the file 
void filehandling()
{
	fstream highscorers;
	highscorers.open("highscore.txt", ios:: in);
	int i = 0;
	if (highscorers)
	{
		while (!highscorers.eof() && i < 10)
		{

			string str;
			do { 	getline(highscorers, str);
			} while (str == "");
			if (str != "nill")
			{
				int pos = str.find(",");
				s_highscore[i] = str.substr(0, pos);
				str = str.substr(pos + 1);
				i_highscore[i] = stoi(str);
				i++;
			}
		}
	}
	scoreboard_count = i;
	highscorers.close();

}
//displays the initial menu
void displaymenu()
{
	DrawRectangle(0, 0, 1120, 840, colors[BLACK]);
	DrawString(400, 750, "-----------------------", colors[WHITE]);
	DrawString(430, 705, "   R U S H - H O U R", colors[WHITE]);
	for (int i = 0; i < 4; i++)
	{
		DrawRectangle(400 + i *71 + 5, 630 + 7, 32, 12, colors[RED]);
		DrawRectangle(400 + i *71 + 10, 630 + 18, 22, 13, colors[SNOW]);
		DrawCircle(400 + i *71 + 10, 630 + 7, 5, colors[SNOW]);
		DrawCircle(400 + i *71 + 32, 630 + 7, 5, colors[SNOW]);
	}
	DrawString(400, 615, "-----------------------", colors[WHITE]);
	DrawString(430, 565, "        MAIN MENU", colors[WHITE]);
	DrawString(435, 540, "    ~~~~~~~~~~~~~", colors[WHITE]);

	//left button
	DrawRoundRect(175 + 140, 190 + 30, 130, 70, colors[SNOW], 10);
	DrawRectangle(150 + 140, 100 + 30, 180, 100, colors[RED]);
	DrawCircle(180 + 140, 90 + 30, 25, colors[SNOW]);
	DrawCircle(300 + 140, 90 + 30, 25, colors[SNOW]);
	DrawString(325, 170, "PLAY GAME", colors[WHITE]);

	//right button
	DrawRoundRect(175 + 460, 190 + 30, 130, 70, colors[SNOW], 10);
	DrawRectangle(150 + 460, 100 + 30, 180, 100, colors[ORANGE]);
	DrawCircle(180 + 460, 90 + 30, 25, colors[SNOW]);
	DrawCircle(300 + 460, 90 + 30, 25, colors[SNOW]);
	DrawString(290 + 340, 170, "LEADERBOARD", colors[BLACK]);
}
//draws teh boundary on the game grid
void drawBoundary()
{
	int xi = 0, yi = 0;
	bool flag = true;
	do {
		if (flag)
		{
			DrawLine(0, yi, 0, yi + 20, 15, colors[BLACK]);
			flag = false;
		}
		else if (!flag)
		{
			DrawLine(0, yi, 0, yi + 20, 15, colors[RED]);
			flag = true;
		}
		yi += 19;
	} while (yi < 840);
	xi = 0;
	yi = 0;
	do {
		if (flag)
		{
			DrawLine(840, yi, 840, yi + 20, 4, colors[BLACK]);
			flag = false;
		}
		else if (!flag)
		{
			DrawLine(840, yi, 840, yi + 20, 4, colors[RED]);
			flag = true;
		}
		yi += 19;
	} while (yi < 840);
	xi = 0;
	yi = 0;
	do {
		if (flag)
		{
			DrawLine(xi, 1, xi + 20, 1, 4, colors[BLACK]);
			flag = false;
		}
		else if (!flag)
		{
			DrawLine(xi, 1, xi + 20, 1, 4, colors[RED]);
			flag = true;
		}
		xi += 19;
	} while (xi < 840);
	xi = 0;
	do {
		if (flag)
		{
			DrawLine(xi, 840, xi + 20, 840, 4, colors[BLACK]);
			flag = false;
		}
		else if (!flag)
		{
			DrawLine(xi, 840, xi + 20, 840, 4, colors[RED]);
			flag = true;
		}
		xi += 19;
	} while (xi < 830);
}
void GameDisplay()
{

	glClearColor(0, 0, 0.0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	if (Screenmode == "title")
	{
		//for displaying the title and first screen of the game
		displaymenu();
	}
	else if (Screenmode == "highscore")
	{
		if (screen1check == 0)
		{

			screen1check = 1;
		}
		// for displaying the highscores
		displayHighscore(scoreboard_count);
	}
	else if (Screenmode == "nameinput")
	{
		//for entering the name of the user
		displaynameinput();
	}
	else if (Screenmode == "carcolor")
	{
		//for chosing the car color
		displaycolormenu();
	}
	else if (Screenmode == "difficultylevel")
	{
		//chosing difficulty
		displaydifficultymenu();
	}
	else if (Screenmode == "win/lose")
	{
		drawScreen5();
	}
	else if (Screenmode == "leaderboard")
	{
		//displaying leaderboard
		displayLeaderboard();
	}
	else if (Screenmode == "gameplay")	// The gameplay
	{
		DrawSquare(0, 0, 840, colors[BLACKO]);
		display_time();
		DrawString(890, 800, "SCORE = " + to_string(score), colors[WHITE]);

		for (int i = 19; i >= 0; i--)
		{
			for (int j = 0; j <= 19; j++)
			{
				DrawRectangle(j *42 + 20, (19 - i) *42, 3, 30, colors[ORANGE_RED]);
				if (display_array[i][j] == 't')	//trees
				{
					drawTree(j, i);
				}
				else if (display_array[i][j] == 'p')	//passenger
				{
					drawPerson(j, i);
				}
				else if (display_array[i][j] == 'b')	//buildings
				{
					drawBuildings(j, i);
				}
				else if (display_array[i][j] == 'B')	//boxes
				{
					DrawSquare(j *42 + 7, (19 - i) *42 + 6, 29, colors[ORANGE_RED]);
					DrawSquare(j *42 + 10, (19 - i) *42 + 10, 23, colors[BROWN]);
				}
			}
		}
		//occupied true only works then
		if (occupied)
		{

			display_array[d_row][d_col] = 'D';
			static int cont = 0;
			//blinking block
			if (cont % 50 >= 24)
			{
				DrawSquare(d_col *42, (19 - d_row) *42, 43, colors[GREEN_YELLOW]);
			}
			cont++;
		}
		//draws all the cars
		drawCar();
		//draws the taxi
		drawTaxi();
		//draws the boundary
		drawBoundary();
	}
	glutSwapBuffers();

}
//random destination
void destination()
{
	int r, c;
	do {
		r = rand() % 20;
		c = rand() % 20;
	} while (display_array[r][c] != ' ' || display_array[r + 1][c] != ' ' || display_array[r - 1][c] != ' ' || display_array[r][c + 1] != ' ' || display_array[r][c - 1] != ' ');
	d_row = r;
	d_col = c;
	display_array[r][c] = 'D';
	glutPostRedisplay();

}

//sets the direction of the car:
void NonPrintableKeys(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		DIRECTION = 1;
	}
	else if (key == GLUT_KEY_RIGHT)
	{
		DIRECTION = 2;
	}
	else if (key == GLUT_KEY_UP)
	{
		DIRECTION = 3;
	}
	else if (key == GLUT_KEY_DOWN)
	{
		DIRECTION = 4;
	}
	glutPostRedisplay();

}
//different speed for yellow and red cars
void color_val()
{
	int rnd = 0;
	if (colorchoice == 'e' || colorchoice == 'E')
		rnd = rand() % 2 + 1;
	if (colorchoice == 'r' || colorchoice == 'R' || rnd == 1)
	{
		o_score = 2;
		c_score = 3;
		TaxiSpeed = 20;
	}
	else if (colorchoice == 'y' || colorchoice == 'Y' || rnd == 2)
	{
		o_score = 4;
		c_score = 2;
		TaxiSpeed = 15;
	}
}
void PrintableKeys(unsigned char key, int x, int y)
{
	if (Screenmode == "difficultylevel")
	{
		// slecting difficulty:
		if (key == 'm' || key == 'h' || key == 'e' || key == 'M' || key == 'H' || key == 'E')
			modechoice = key;
		difficultyselector();
	}
	if (Screenmode == "carcolor")
	{
		//selecting color
		if (key == 'r' || key == 'y' || key == 'e' || key == 'R' || key == 'Y' || key == 'E')
		{
			colorchoice = key;
			color_val();
			Screenmode = "difficultylevel";
		}
	}
	if (Screenmode == "nameinput")
	{
		//appends the string and the key entered only if its printable and not equal to delimeter
		if (key == 8)
		{
			playername = playername.substr(0, playername.length() - 1);
		}
		else if (playername.length() <= 15 && key != ',')
		{
			playername += key;
		}
	}
	if (key == 27)
	{
		exit(1);	// exit the program when escape key is pressed.
	}
	if (key == ' ')
	{
		if (Screenmode == "highscore")
		{
			Screenmode = "nameinput";
		}
		else if (Screenmode == "nameinput")
			playername += " ";
		else if (Screenmode == "gameplay")
		{
			if (key == 'f' || key == 'F')	//Key for placing the bomb
			{
				glutFullScreen();
			}
			if (!occupied)
			{
			 	//to pickup the passengers from adjacent places
				if (display_array[row + 1][col] == 'p')
				{
					display_array[row + 1][col] = ' ';
					occupied = 1;
				}
				else if (display_array[row - 1][col] == 'p')
				{
					display_array[row - 1][col] = ' ';
					occupied = 1;
				}
				else if (display_array[row][col + 1] == 'p')
				{
					display_array[row][col + 1] = ' ';
					occupied = 1;
				}
				else if (display_array[row][col - 1] == 'p')
				{
					display_array[row][col - 1] = ' ';
					occupied = 1;
				}
				destination();
			}
			else
			{
			 	//if dropped chekces conditons to increase speed based on the mode slected and increases the cars on teh basisi of mode selected
				if (display_array[row][col] == 'D')
				{
					score += 10;
					display_array[row][col] = ' ';
					occupied = 0;
					passengers_dropped++;
					if (passengers_dropped % 2 == 0 && Carspeed >= min_speed_factor)
					{
						if (car_count < maxCars)
							Random_item_generator('c', 1);
						Carspeed -= (0.04 *(rand() % 4 + 1));
						if (Carspeed < min_speed_factor)
							Carspeed = min_speed_factor;
					}
					Random_item_generator('p', 1);
				}
			}
		}
	}

	glutPostRedisplay();
}

void TimerTaxi(int m)
{
	static bool check = true;
	if (Screenmode == "gameplay" && check)
	{
		// stores the time when game starts
		start_time = time(0);
		check = false;
		score = 0;
	}
	if (start_time)
	{

		static bool time_over = true;
		if (time(0) - start_time >= 180 && time_over)
		{
			writingfile();
			Screenmode = "win/lose";
			time_over = false;
		}
	}
	//to move the taxi based on car color
	moveTaxi();
	glutTimerFunc(TaxiSpeed, TimerTaxi, 0);
}

void TimerCar(int m)
{
	//calling move car fuction after a certainperiod of time which decrease with time
	moveCar();
	glutTimerFunc(min_speed *Carspeed, TimerCar, 0);
}

void MousePressedAndMoved(int x, int y)
{
	glutPostRedisplay();
}

void MouseMoved(int x, int y)
{
	glutPostRedisplay();
}

void MouseClicked(int button, int state, int x, int y)
{
	//different values for different 
	//differnt coorisntas for buttons for differnent screen
	if (button == GLUT_LEFT_BUTTON)
	{
		if (Screenmode == "title")
		{

			if (x >= 360 && x <= 545 && y <= 597 && y >= 514)
			{
				filehandling();
				Screenmode = "nameinput";
			}
			if (x >= 759 && x <= 979 && y <= 597 && y >= 514)
			{
				filehandling();
				Screenmode = "highscore";
			}
		}
		else if (Screenmode == "nameinput")
		{
			if (playername.length() >= 3)
				Screenmode = "carcolor";
		}
		else if (Screenmode == "win/lose")
		{
			DrawRoundRect(400, 300, 250, 150, colors[GREEN], 10);
			if (x >= 525 && x <= 831 && y >= 330 && y <= 450)
			{
				Screenmode = "leaderboard";
				display_timer = time(0);
			}
		}
		else if (Screenmode == "leaderboard")
		{
			if (time(0) - display_timer >= 10)
				exit(1);
		}
	}
	glutPostRedisplay();
}
//random buildings generator
void Random_buildings()
{
	//generates a total of 100 buildings
	int count = 0, square_count = 0;
	do {
		int arr[] = { 1, 1, 1, 1, 1, 1, 1, 2, 2, 3 };
		int shape = arr[rand() % 9];
		//genrates a sqaure only in one out of three cases
		if ((shape == 2 || shape == 3) && square_count < 2)	//print square of buildings
		{
			square_count++;
			int r, c;
			do { 	r = rand() % 20;
				c = rand() % 20;
			} while (display_array[r][c] != ' ' || r == 0 || c == 0);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j <= 2; j++)
				{
					if (!(r + i <= 0 || r + i > 18) || c + j <= 0 || c + j > 18)
					{
						if (display_array[r + i][c + j] == ' ' && r + i != 0)
						{
							display_array[r + i][c + j] = 'b';
							count++;
						}
					}
				}
			}
		}
		else	//else draws a rectangle of width 1 in random direction of a random size
		{
			int size = rand() % 4 + 3;
			int dir = rand() % 4 + 1;
			int r, c;
			do { 	r = rand() % 20;
				c = rand() % 20;
			} while (display_array[r][c] != ' ' || r == 0 || c == 0);
			for (int i = 0; i < size; i++)
			{
				if (dir == 1)
				{
					if (r - 1 > 0)
					{
						if (display_array[r - 1][c] == ' ')
						{
							display_array[r - 1][c] = 'b';
							r -= 1;
							count++;
						}
					}
					else
					{
						dir = rand() % 4 + 1;
					}
				}
				if (dir == 2)
				{
					if (r + 1 < 19)
					{
						if (display_array[r + 1][c] == ' ')
						{
							display_array[r + 1][c] = 'b';
							r += 1;
							count++;
						}
					}
					else
					{
						dir = rand() % 4 + 1;
					}
				}
				if (dir == 3)
				{
					if (c - 1 > 0)
					{
						if (display_array[r][c - 1] == ' ')
						{
							display_array[r][c - 1] = 'b';
							c -= 1;
							count++;
						}
					}
					else
					{
						dir = rand() % 4 + 1;
					}
				}
				if (dir == 4)
				{
					if (c + 1 < 19)
					{
						if (display_array[r][c + 1] == ' ')
						{
							display_array[r][c + 1] = 'b';
							c += 1;
							count++;
						}
					}
					else
					{
						dir = rand() % 4 + 1;
					}
				}
			}
		}
	} while (count < 100);	//loop continues until the atleast 25 percent of the board is filled with buildings
}
//main 
int main(int argc, char *argv[])
{
	srand(time(0));
	int width = 1100, height = 845;
	InitRandomizer();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(width, height);
	glutCreateWindow("Rush Hour by i21-0582");
	SetCanvasSize(width, height);
	//function for generating random buildins at random places in the map
	Random_buildings();
	glutDisplayFunc(GameDisplay);
	glutSpecialFunc(NonPrintableKeys);
	glutKeyboardFunc(PrintableKeys);
	//timer for taxi
	glutTimerFunc(1000.0, TimerTaxi, 0);
	//timer for cars
	glutTimerFunc(1000.0, TimerCar, 0);

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved);
	glutMotionFunc(MousePressedAndMoved);
	glutMainLoop();
	return 1;
}
#endif /*RushHour_CPP_ */
