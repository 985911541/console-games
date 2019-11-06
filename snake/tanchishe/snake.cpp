#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

static const string diamond = "�~";
static const int MAXSNAKE = 1600; //�ߵ���󳤶�
static int snakelenth = 3;   //�ߵĳ�ʼ����
static int snakelive = 1; //�ߵ�״̬ 0��ʾ�������� 1��ʾ�ߴ��
static int foodture = 1; //ʳ���Ƿ������ȷ, 1��ʾ��ȷ 0 ��ʾ����
static int ch = 0;   //�жϼ����������������
//static const int height = 100;
//static const int weight = 40;

static void gotoxy(int, int);  //��꺯��

typedef struct snake
{
	int x;
	int y;
	//snake* next;
}snake1;//�߽ṹ

typedef struct food
{
	int x;
	int y;
	//snake* next;
}food1;//ʳ��ṹ

snake1 snakeall[MAXSNAKE];
food1 food;
//snake1* head;
//snake1* tail;

class Snake
{
public:
	
public:
	void printsnake(); //��ӡ��
	void movesnake(); //�ƶ���
	void starsnake(); //�ʼ����
	void gameover(); //�ж��Ƿ���Ϸ����
	void eatfood(); //��ʳ���ж�
	//void changesnake();
};

class Show
{
public:
	void interfaceshow(); //�߿��ӡ

};

class Food
{
public:
	void creatfood(); //����ʳ��
	void printfood(); //��ӡʳ��

};

class Controller
{
public:
	void stargame(); //������Ϸ��ʼ
};

int main()
{
	Controller controller;
	controller.stargame();

	return 0;
}

void Show::interfaceshow()
{
	system("mode con cols=100 lines=50");
	for (int i = 0; i < 40; ++i)
	{
		cout << diamond;
	}
	cout << endl;
	for (int i = 0; i < 38; ++i)
	{
		for (int j = 0; j < 40; ++j)
		{
			if (j == 0 || j == 39)
			{
				cout << diamond;
			}
			else
			{
				cout << "  ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < 40; ++i)
	{
		cout << diamond;
	}
}

void Snake::starsnake()
{
	for (int i = 0; i < snakelenth; ++i)
	{
		if (i == 0)
		{
			snakeall[i].x = 40;
			snakeall[i].y = 20;
		}
		else
		{
			snakeall[i].x = snakeall[i - 1].x + 2;
			snakeall[i].y = snakeall[i - 1].y;
		}
	}
}

void Snake::printsnake()
{
	for (int i = 0; i < snakelenth; ++i)
	{
		gotoxy(snakeall[i].x, snakeall[i].y);
		cout << diamond;
		//cout << "  ";
		gotoxy(90, 40);
	}
	gotoxy(90, 40);
	cout << "��ķ���:";
}

static void gotoxy(int x, int y)
{
	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
	HANDLE hConsoleOut;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	csbiInfo.dwCursorPosition.X = x;
	csbiInfo.dwCursorPosition.Y = y;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void Controller::stargame()
{
	Show show;
	Snake snake;
	Food food;
	show.interfaceshow();
	snake.starsnake();
	while (1)
	{
		food.creatfood();
		food.printfood();
		while (1)
		{
			snake.printsnake();
			snake.gameover();
			Sleep(300);
			snake.movesnake();
			snake.eatfood();
			if (!foodture)
			{
				//snake.changesnake();
				break;
			}	
		}
	}
}

void Snake::movesnake()
{
	gotoxy(snakeall[snakelenth - 1].x, snakeall[snakelenth - 1].y);
	cout << "  ";
	if (_kbhit())
	{
		ch = _getch();
		switch (ch)
		{
		case 'w':
		case 'W':
			for (int i = snakelenth-1; i > 0; --i)
			{
				snakeall[i].x = snakeall[i - 1].x;
				snakeall[i].y = snakeall[i - 1].y;
			}
			snakeall[0].x = snakeall[1].x;
			snakeall[0].y = snakeall[1].y - 1;
			break;
		case 's':
		case 'S':
			for (int i = snakelenth - 1; i > 0; --i)
			{
				snakeall[i].x = snakeall[i - 1].x;
				snakeall[i].y = snakeall[i - 1].y;
			}
			snakeall[0].x = snakeall[1].x;
			snakeall[0].y = snakeall[1].y + 1;
			break;
		case 'a':
		case 'A' :
			for (int i = snakelenth - 1; i > 0; --i)
			{
				snakeall[i].x = snakeall[i - 1].x;
				snakeall[i].y = snakeall[i - 1].y;
			}
			snakeall[0].x = snakeall[1].x - 2;
			snakeall[0].y = snakeall[1].y;
			break;
		case 'd':
		case 'D':
				for (int i = snakelenth - 1; i > 0; --i)
				{
					snakeall[i].x = snakeall[i - 1].x;
					snakeall[i].y = snakeall[i - 1].y;
				}
				snakeall[0].x = snakeall[1].x + 2;
				snakeall[0].y = snakeall[1].y;
			break;
		default:
			break;
		}
		
	}
	else //Ĭ������
	{
		ch = 'W';
		for (int i = snakelenth - 1; i > 0; --i)
		{
			snakeall[i].x = snakeall[i - 1].x;
			snakeall[i].y = snakeall[i - 1].y;
		}
		snakeall[0].x = snakeall[1].x;
		snakeall[0].y = snakeall[1].y - 1;
	}
}

void Snake::gameover()
{
	if (snakeall[0].y == 1 || snakeall[0].y >39|| snakeall[0].x == 2 || snakeall[0].x < 2 || snakeall[0].x > 78)
	{
		snakelive = 0;
	}
	if (!snakelive)
	{
		gotoxy(85, 45);
		cout << "GameOver" << endl;
		exit(1);
		system("pause");
	}

}

void Food::creatfood()
{
	while (1)
	{
		srand((unsigned)time(NULL));
		//food.x = (rand() % 80) * 2;
		food.x = rand() % (78 - 2);
		//food.y = (rand() % 40);
		food.y = rand() % (39 - 1);
		if (food.x % 2 == 0 && (food.x != snakeall[0].x && food.y != snakeall[0].y))
		{
			foodture = 1;
			break;
		}
	}
}

void Food::printfood()
{
	gotoxy(food.x, food.y);
	cout << diamond;
}

void Snake::eatfood()
{
	if (snakeall[0].x == food.x && snakeall[0].y == food.y)
	{
		gotoxy(food.x, food.y);
		cout << "  ";
		foodture = 0;
		snakelenth++;
	}
	return;
}

/*
   �����ߣ� ���Ľ�
   ʱ��  :  2019.10.31  
*/