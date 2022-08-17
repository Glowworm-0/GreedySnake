/*WARM TIP:This program runs under Windows10,and occasionally the snake's food pointer cannot
  be free and the program cannot be refreshed(that is,sometimes the food will disappear for a bug short time*/
/*SCREEN COLOR VALUES:
====================================
character constant   #    value    #
---------------------#-------------#
       BLACK         #      0      #
	   BLUE          #      1      #
	   GREEN         #      2      #
	   CYAN          #      3      #
	   RED           #      4      #
	 MAGENTA         #      5      #
	  BROWN          #      6      #
	LIGHTGRAY        #      7      #
	DARKGRAY         #      8      #
	LIGHTBLUE        #      9      #
	LIGHTGREEN       #     10      #
	LIGHTCYAN        #     11      #
	LIGHTRED         #     12      #
	LIGHTMAGENTA     #     13      #
	  YELLOW         #     14      #
	  WHITE          #     15      #
====================================*/
#include<stdio.h>
#include<processenv.h>
#include<unistd.h>
#include<time.h>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

typedef struct snake /*Snake body of the one node*/
{
	int x;
	int y;
	struct snake*next;
}snake;

int score = 0, add = 10;
int HighScore = 0;
int status, sleeptime = 200;/*Snake advance status,and everytime move the time interval*/
snake*head, *food;
snake*q;/*Ergodic snake of the used are point*/
int endgamestatus = 0;
HANDLE hOut;/*Console outputs handle*/
void gotoxy(int x, int y);
int color(int c);
void printsnake();
void welcometogame();
void createMap();
void scoreandtips();
void initsnake();
void createfood();
int biteselt();
void cantcrosswall();
void speedup();
void speeddown();
void snakemove();
void keyboardControl();
void Lostdraw();
void endgame();
void choose();
void File_out();
void File_in();
void explation();
/*The define color */
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);/*The change word color*/
	return 0;
}
/*Set cursor location*/
void gotoxy(int x, int y)
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void printsnake()
{
	gotoxy(35, 1);
	color(6);
	printf("/^\\/^\\");/*Snake eyebrow*/

	gotoxy(34, 2);
	printf("|__O|  O|");/*Snake eyes*/

	gotoxy(33, 2);
	color(2);
	printf("_");

	gotoxy(25, 3);
	color(12);
	printf("\\V");

	gotoxy(31, 3);
	color(2);
	printf("/");

	gotoxy(37, 3);
	color(6);
	printf("\\_/");

	gotoxy(41, 3);
	color(10);
	printf(" \\");

	gotoxy(26, 4);
	color(12);
	printf("\\____");

	gotoxy(32, 4);
	printf("_________/");

	gotoxy(31, 4);
	color(2);
	printf("|");

	gotoxy(43, 4);
	color(10);
	printf("\\");

	gotoxy(32, 5);
	color(2);
	printf("\\_______");

	gotoxy(44, 5);
	color(10);
	printf("\\");

	gotoxy(39, 6);
	printf("|    |                        \\");

	gotoxy(38, 7);
	printf("/     /                          \\");

	gotoxy(37, 8);
	printf("/     /                          \\ \\");

	gotoxy(35, 9);
	printf("/     /                             \\ \\");

	gotoxy(34, 10);
	printf("/     /                               \\ \\");

	gotoxy(33, 11);
	printf("/     /              _----_             \\ \\");

	gotoxy(32, 12);
	printf("/     /          _ -~         ~-_        | |");

	gotoxy(31, 13);
	printf("(     (        _-~      _--_      ~-_    _/  |");

	gotoxy(32, 14);
	printf("\\     ~-____-~      _-~     ~-_     ~-_-~   /");

	gotoxy(33, 15);
	printf("~-_          _-~                ~-_      _-~");

	gotoxy(35, 16);
	printf("~-_____-~                         ~-___-~");
}

void welcometogame()
{
	int n;
	int i, j = 1;
	gotoxy(43, 18);
	color(11);/*Yellow edging*/
	printf("GREEDY SNAKE PLAY");
	for (i = 20; i <= 26; i++)/*Output the up and down edging*/
	{
		for (j = 27; j <= 74; j++)/*Output the left and right edging*/
		{
			gotoxy(j, i);
			color(14);
			if (i == 20 || i == 26)
			{
				printf("-");
			}
			else if (j == 27 || j == 74)
			{
				printf("|");
			}
		}
	}
	color(12);
	gotoxy(35, 22);
	printf("1.Start Play");
	gotoxy(55, 22);
	printf("2.Play Explain");
	gotoxy(35, 24);
	printf("3.Exit Play");
	gotoxy(29, 27);
	color(3);
	printf("Please choose[1 2 3]:[]\b\b");
	color(14);
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		system("cls");
		createMap();
		initsnake();
		createfood();
		keyboardControl();
		break;
	case 2:
		explation();
		break;
	case 3:
		exit(0);
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("Please enter a number between 1-3!");
		getch();
		system("cls");
		printsnake();
		welcometogame();
	}
}

void createMap()
{
	int i, j;
	for (i = 0; i <= 58; i += 2)/*The print up and down edging*/
	{
		gotoxy(i, 0);
		color(5);
		printf("¡õ");
		gotoxy(i, 26);
		printf("¡õ");
	}
	for (i = 1; i < 26; i++)/*The print left and right edging*/
	{
		gotoxy(0, i);
		printf("¡õ");
		gotoxy(58, i);
		printf("¡õ");
	}
	for (i = 2; i < 57; i++)/*The print middle grid*/
	{
		for (j = 1; j < 26; j++)
		{
			gotoxy(i, j);
			color(3);
			printf("¡ö\n\n");
		}
	}
}

void scoreandtips()
{
		File_out();
		gotoxy(64, 4);
		color(11);
		printf("¡ïHIGH SCORE ¡ï: %d", HighScore);
		gotoxy(64, 8);
		color(14);
		printf("Score: %d  ", score);
		color(13);
		gotoxy(73, 11);
		printf("Mini tips");
		gotoxy(60, 13);
		color(6);
		printf("¨p------------------------------------------------------------------- ¨p");
		gotoxy(60, 25);
		printf("¨p------------------------------------------------------------------- ¨p");
		color(3);
		gotoxy(64, 14);
		printf("Score per food: %d score", add);
		gotoxy(64, 16);
		printf("You can't go through the wall,you can't bite oneself!");
		gotoxy(64, 18);
		printf("Use ¡ü¡ý¡û¡úto control the movement of the snake respectively.");
		gotoxy(64, 20);
		printf("F1 Speedup,F2 Speeddown.");
		gotoxy(64, 22);
		printf("Space: Pause the game");
		gotoxy(64, 24);
		printf("ESC: Sign out game");
}

void File_out()
{
		FILE*fp;
		fp = fopen("HighScore.txt", "a+");/*Open high score save file*/
		fscanf(fp, "%d", &HighScore);/*Read file the high score*/
		fclose(fp);
}

void initsnake()/*Initializer snake body and drawing snake body*/
{
	snake *tail;
	int i;
	tail = (snake*)malloc(sizeof(snake));/*Start from the snake tail,insert the head method,and set the starting position with x and y*/
	tail->x = 24;
	tail->y = 5;
	tail->next = NULL;
	for (i = 1; i <= 2; i++)/*Set snake body,and length of three*/
	{
		head = (snake*)malloc(sizeof(snake));/*Initializer snake head*/
		head->next = tail;
		head->x = 24 + 2 * i;/*Set snake head position*/
		head->y = 4;
		tail = head;
	}
	while (tail != NULL)/*Form head to tail,and output the snake body*/
	{
		gotoxy(tail->x, tail->y);
		color(14);
		printf("¡ò");/*Output the snake body,and snake body use ¡òcomposition*/
		tail = tail->next;
	}
}

void createfood()
{
	snake*food_1;
	srand((unsigned)time(NULL));
	food_1=(snake*)malloc(sizeof(snake));/*Initializer food_1*/
	/*Make sure it is even number,so that the food is aligned with the snake head,and then the food will appear on the grid line*/ 
	while ((food_1->x % 6)!= 0)
	{
		food_1->x = rand() % 53 + 1;/*Set the X coordinate of food to appear randomly,and the coordinate of food X is between 1 and 53*/
	}
	food_1->y = rand() % 24 + 1;
	q = head;
	while (q->next == NULL)
	{
		if (q->x == food_1->x&&q->y == food_1->y)/*Judge whether the snake boby overlaps whith the food*/ 
		{
			free(food_1);/*If snake body and the food overlap,that frees the food pointer*/
			createfood();
		}
		q = q->next;
	}
	gotoxy(food_1->x, food_1->y);/*Set food the position*/
	food = food_1;
	color(12);
	printf("¡ñ");/*Output food*/
}
/*Judge whether biteself*/
int biteself()
{
		snake *self;
		self = head->next;
		while (self != NULL)
		{
			if (self->x == head->x&&self->y == head->y)/*If the nodes on selt and snake head coincide*/
			{
				return 1;
			}
			self = self->next;
		}
		return 0;
}
/*The speed up,or press F1,Can the automatic speedup*/
void speedup()
{
		if (sleeptime >= 50)
		{
			sleeptime = sleeptime - 5;
			add = add + 2;/*Reduce the score by 2 everytime your eat food*/
			if (sleeptime == 320)
			{
				add = 2;
			}
		}
}
/*Press F2,Can the automatic speeddown*/
void speeddown()
{
		if (sleeptime < 350)
		{
			sleeptime = sleeptime + 30;
			add = add - 2;
			if (sleeptime == 350)
			{
				add = 1;
			}
		}
}
/*Snake move direction,up,down,left and right*/
void snakemove()
{
		snake*nexthead;
		cantcrosswall();
		nexthead = (snake*)malloc(sizeof(snake));/*Open up space for the next step*/
		if (status == UP)
		{
			nexthead->x = head->x;/*When moving up,x coordinate does not move,and y coordinate -1*/ 
			nexthead->y = head->y - 1;
			nexthead->next = head;
			head = nexthead;
			q = head;
			/*If there is food next,the coordinates of the next position are the same as those of the food*/
			if (nexthead->x == food->x&&nexthead->y == food->y)
			{
				while (q != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");/*Original food the position,and change from ¡ñto ¡ò*/
					q = q->next;
				}
				score = score + add;/*Ate a food,add the food score to the total score*/
				speedup();
				createfood();
			}
			else
			{
				while (q->next->next != NULL)/*If you don't encounter food*/     
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(3);
				printf("¡ö");
				free(q->next);/*After output ¡ö,free the point to the next pointer*/
				q->next = NULL;
			}
		}
		if (status == DOWN)
		{
			nexthead->x = head->x;/*When moving down,x coordinate does not move,y coordinate +1*/
			nexthead->y = head->y + 1;
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (nexthead->x == food->x&&nexthead->y == food->y)/*There is food*/
			{
				while (q != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				score = score + add;
				speedup();
				createfood();
			}
			else/*No food*/
			{
				while (q->next->next != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(3);
				printf("¡ö");
				free(q->next);
				q->next = NULL;
			}
		}
		if (status == LEFT)
		{
			nexthead->x = head->x - 2;/*When moving left,x coordinate moves to the left -2,y coordinate does not move*/
			nexthead->y = head->y;
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (nexthead->x == food->x&&nexthead->y == food->y)
			{
				while (q != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				score = score + add;
				speedup();
				createfood();
			}
			else
			{
				while (q->next->next != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(3);
				printf("¡ö");
				free(q->next);
				q->next = NULL;
			}
		}
		if (status == RIGHT)
		{
			nexthead->x = head->x + 2;/*When moving right,x coordinate moves to the right +2,y coordinate does not move*/
			nexthead->y = head->y;
			nexthead->next = head;
			head = nexthead;
			q = head;
			if (nexthead->x == food->x&&nexthead->y == food->y)
			{
				while (q != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				score = score + add;
				speedup();
				createfood();
			}
			else
			{
				while (q->next->next != NULL)
				{
					gotoxy(q->x, q->y);
					color(14);
					printf("¡ò");
					q = q->next;
				}
				gotoxy(q->next->x, q->next->y);
				color(3);
				printf("¡ö");
				free(q->next);
				q->next = NULL;
			}
		}
		if (biteself() == 1)
		{
			endgamestatus = 2;
			endgame();
		}
}
/*Control keyboard keys*/
void keyboardControl()
{
		status = RIGHT;/*Iniaial snake moves to the right*/
		while (1)
		{
			scoreandtips();
			/*The GetAsyncKeyState function is used to judge the state of the specified virtual key when the function is called;
			If the snake is not moving down,press the up key to execute the up operation*/
			if (GetAsyncKeyState(VK_UP) && status != DOWN)
			{
				status = UP;
			}
			/*If the snake is not moving up,press the down key to execute the down operation*/
			else if (GetAsyncKeyState(VK_DOWN) && status != UP)
			{
				status = DOWN;
			}
			/*If the snake is not moving right,press the left key to execute the left operation*/
			else if (GetAsyncKeyState(VK_LEFT) && status != RIGHT)
			{
				status = LEFT;
			}
			/*If the snake is not moving left,press the right key to execute the right operation*/
			else if (GetAsyncKeyState(VK_RIGHT) && status != LEFT)
			{
				status = RIGHT;
			}
			/*Prees the pause key,execute the pause function*/
			if (GetAsyncKeyState(VK_SPACE))
			{
				while (1)
				{
					Sleep(300);/*Sleep()function,head file:#include<unistd.h>,Pause the process,
					           until the time of reaching the parameters set inside*/
					if (GetAsyncKeyState(VK_SPACE))
					{
						break;
					}
				}
			}
			else if (GetAsyncKeyState(VK_ESCAPE))/*Press the ESC key,go directly to the end interface*/
			{
				endgamestatus = 3;
				break;
			}
			else if (GetAsyncKeyState(VK_F1))/*Press the F1 key,speed up*/
			{
				speedup();
			}
			else if (GetAsyncKeyState(VK_F2))/*Press the F2 key,speed down*/
			{
				if (sleeptime < 350)
				{
					sleeptime = sleeptime + 30;
					add = add - 2;
					if (sleeptime == 350);
					{
					    add = 1;/*The minimum guaranteed score is 1*/
					}
				}
			}
			Sleep(sleeptime);
			snakemove();
		}
}
/*Fail interface*/
void Lostdraw()
{
		system("cls");
		int i, j;
		gotoxy(45, 2);
		color(6);
		printf(" \\\\\\|///");
		gotoxy(43, 3);
		printf("\\\\");
		gotoxy(47, 3);
		color(15);
		printf(".-.-");
		gotoxy(54, 3);
		color(6);
		printf("//");

		gotoxy(44, 4);
		color(14);
		printf("(");

		gotoxy(47, 4);
		color(15);
		printf(".@.@");

		gotoxy(54, 4);
		color(14);
		printf(")");

		gotoxy(17, 5);
		color(11);
		printf("+------------------");

		gotoxy(35, 5);
		color(14);
		printf("oOOo");

		gotoxy(39, 5);
		color(11);
		printf("+--------");

		gotoxy(48, 5);
		color(14);
		printf("(_)");

		gotoxy(51, 5);
		color(11);
		printf("--------+");

		gotoxy(61, 5);
		color(14);
		printf("oOOo");

		gotoxy(65, 5);
		color(11);
		printf("-----------------+");

		for (i = 6; i <= 19; i++)/*Vertical border*/
		{
			gotoxy(17, i);
			printf("|");
			gotoxy(82, i);
			printf("|");
		}

		gotoxy(17, 20);
		printf("+------------------------------------");

		gotoxy(52, 20);
		color(14);
		printf("¡î¡î¡î¡å");

		gotoxy(60, 20);
		color(11);
		printf("----------------------+");
}

void endgame()
{
		system("cls");
		if (endgamestatus == 1)
		{
			Lostdraw();
			gotoxy(35, 9);
			color(12);
			printf("Sorry,your hit the wall.Game over!");
		}
		else if (endgamestatus == 2)
		{
			Lostdraw();
			gotoxy(35, 9);
			color(12);
			printf("Sorry,your biteself.Game over!");
		}
		else if (endgamestatus == 3)
		{
			Lostdraw();
			gotoxy(40, 9);
			color(12);
			printf("You have finished the game.");
		}
		gotoxy(43, 12);
		color(13);
		printf("You score is: %d", score);
		if (score >= HighScore)
		{
			color(10);
			gotoxy(33, 16);
			printf("It's a record!The highest score break by you,Great!!!");
			File_in();
		}
		else
		{
			color(10);
			gotoxy(33, 16);
			printf("\b\b\b\b\b\b\b\b\b\b\b\bKeep trying...You're still far from the highest score: %d", HighScore - score);
		}
		choose();
}

void cantcrosswall()
{
	if (head->x == 0 || head->x == 56 || head->y == 0 || head->y == 26)/*If the snake head hits the wall*/
	{
		endgamestatus = 1;/*Return to the first case*/
		endgame();
	}
}
/*Save the high score in in file*/
void File_in()
{
		FILE*fp;
		fp = fopen("Highscore.txt", "w+");
		fprintf(fp, "%d", score);
		fclose(fp);
}

void choose()
{
		int n;
		gotoxy(25, 23);
		color(12);
		printf("I'm going to play another game--------1");
		gotoxy(52, 23);
		printf("Stop playing and quit---------2");
		gotoxy(46, 25);
		color(11);
		printf("Choose: ");
		scanf("%d", &n);
		switch (n)
		{
		case 1:
			system("cls");
			score = 0;
			sleeptime = 200;
			add = 10;
			printsnake();
			welcometogame();
			break;
		case 2:
			exit(0);
			break;
		default:
			gotoxy(35, 27);
			color(12);
			printf("¨w¨wYour input is incorrect,please re-enter ¨w¨w");
			system("pause>nul");
			endgame();
			choose();
			break;
		}
}

void explation()
{
		int i, j = 1;
		system("cls");
		color(13);
		gotoxy(65, 3);
		printf("Game Explain");
		color(2);
		for (i = 6; i <= 22; i++)/*Output the up and down edging ====*/
		{
			for (j = 20; j <= 75; j++)/*Output the left and right edging ||*/
			{
				gotoxy(j, i);
				if (i == 5 || i == 22)printf("=");
				else if (j == 20 || j == 75)printf("||");
			}
		}
		color(3);
		gotoxy(30, 8);
		printf("\b\b\b\b\bTip1: Not crossed wall,Not biteself!");
		color(10);
		gotoxy(30, 11);
		printf("\b\b\b\b\bTip2: Use ¡ü¡ý¡û¡ú to control the movement of the snake respectively.");
		color(14);
		gotoxy(30, 14);
		printf("\b\b\b\b\bTip3: F1 Speedup,F2 Speeddown.");
		color(11);
		gotoxy(30, 17);
		printf("\b\b\b\b\bTip4: Press the space bar to pause the game,and then press the space bar to continue.");
		color(4);
		gotoxy(30, 20);
		printf("\b\b\b\b\bTip5: ESC: quit game. Space: pause game");
		getch();
		system("cls");
		printsnake();
		welcometogame();
}

int main()
{
	system("Mode con cols=100||lines=30");
	printsnake();
	welcometogame();
	createMap();
	scoreandtips();
	initsnake();
	createfood();
	biteself();
	cantcrosswall();
	speedup();
	speeddown();
	snakemove();
	keyboardControl();
	Lostdraw();
	endgame();
	choose();
	File_out();
	File_in();
	explation();
	return 0;
}
