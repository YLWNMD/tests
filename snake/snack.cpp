#include <graphics.h>
#include<stdio.h>
#include<windows.h> 
#include<conio.h>
#include<easyx.h>
#include<math.h>
#include<time.h>
#include<setjmp.h>

#define SNAKENUM 50

struct snake
{
	int dir;
	int speed;
	int size;
	POINT coor[SNAKENUM];
}snake;

struct apple
{
	int flag;
	POINT pos;

}apple;

struct score
{
	int sc;
}score;

int applefl=0;
int posfl=0;
int num=0;

enum DIR
{UP,DOWN,RIGHT,LEFT};

void GAMEINIT()
{
	initgraph(800,600,SHOWCONSOLE);
	snake.speed=10;	
	snake.size=3;
	snake.dir=RIGHT;	
	for(int i=0;i<snake.size;i++)
	{
		snake.coor[i].x=60-10*i;
		snake.coor[i].y=10;
	}

}

void gamedraw()
{
	BeginBatchDraw();
	setbkcolor(RGB(28,115,120));
	cleardevice();
	for(int i=0;i<snake.size;i++)
	{
		circle(snake.coor[i].x,snake.coor[i].y,5);
	}
	EndBatchDraw();
}

void snake_move()
{
	int a[50];
	int b[50];
	a[0]=snake.coor[0].x;
	b[0]=snake.coor[0].y;
	for(int i=0;i<snake.size-1;i++)
	{
		a[i+1]=snake.coor[i+1].x;
		b[i+1]=snake.coor[i+1].y;
		snake.coor[i+1].x=a[i];
		snake.coor[i+1].y=b[i];
		
	}
	switch(snake.dir)
	{
		case UP:
			snake.coor[0].y-=snake.speed;
			break;
		case DOWN:
			snake.coor[0].y+=snake.speed;
			break;
		case RIGHT:
			snake.coor[0].x+=snake.speed;
			break;
		case LEFT:
			snake.coor[0].x-=snake.speed;
			break;			
	}
}

void control()
{
	if(_kbhit())
	{
		switch(_getch())
		{
		case 'w':
		case 'W':
		case 72:
			if(snake.dir==DOWN)
			{
				break;
			}
			snake.dir=UP;
			break;
		case 'a':
		case 'A': 
		case 75:
			if(snake.dir==RIGHT)
			{
				break;
			}
			snake.dir=LEFT;
			break;
		case 's':
		case 'S':
		case 82:
			if(snake.dir==UP)
			{
				break;
			}
			snake.dir=DOWN;
			break;
		case 'd':
		case 'D':
		case 77:
			if(snake.dir==LEFT)
			{
				break;
			}
			snake.dir=RIGHT;
			break;
		}
	} 
}

void applepos()
{
	int a,b;
	if(posfl==0)
	{
		apple.pos.x=rand()%391+110;
		apple.pos.y=rand()%457+110;
		posfl++;
	}
	circle(apple.pos.x,apple.pos.y,1);
}

void eat_apple()
{
	double pos_x,pos_y;
	pos_x=fabs(apple.pos.x-snake.coor[0].x);
	pos_y=fabs(apple.pos.y-snake.coor[0].y);
	int wm;
	wm=0;
	if(pos_x*pos_x+pos_y*pos_y<=50.0)
	{
		if(apple.flag==0)
		{
			wm++;
			snake.size++;
			posfl=0;
			score.sc++;
		}
		if(apple.flag==1&&wm==0)
		{
			wm=0;
			snake.size++;
			posfl=0;
			score.sc++;
		}	
	}
}

void screen()
{
	char bh[5];
	sprintf(bh,"%d",score.sc);
	outtextxy(750,50,bh);
	outtextxy(705,50,"SCORE:");
}

void snakedead()
{
	
	for(int i=1;i<snake.size;i++)
	{
		if(snake.coor[0].x>snake.coor[i].x-5&&snake.coor[0].x<snake.coor[i].x+5&&snake.coor[0].y>snake.coor[i].y-5&&snake.coor[0].y<snake.coor[i].y+5)
		{
			while(1)
			{
				outtextxy(350,250,"game over");
				outtextxy(300,300,"Press any key to contiue");
				if(_kbhit())
				{
					break; 
				}
			}
		}
		if(snake.coor[0].x+5>=800||snake.coor[0].y+5>=600||snake.coor[0].x-5<=0||snake.coor[0].y-5<=0)
		{
			while(1)
			{
				outtextxy(350,250,"GAME OVER");
				outtextxy(300,300,"Press any key to contiue");
				if(_kbhit())
				{
					break;
				}
			}
		}
	}
}

void title()
{	
	outtextxy(350,300,"press any key");
	while(1)
	{
		if(_kbhit())
		{
			break;
		}
	}
	num=1;
}

int main()
{
	score.sc=0;
	apple.flag=0;
	srand((unsigned)time(NULL));
	GAMEINIT();
	
	while(1)
	{
		gamedraw();	
				
		screen();
		if(num==0)
		{
			title();
		}
		control();
		eat_apple();
		applepos();
		snake_move();
		snakedead();
		Sleep(150);
		
	}
	return 0;
}
