/*基本原理

对于贪吃蛇怎么在屏幕上移动，当初自己也是懵逼，哈哈。其实就是不断刷新屏幕，在一个循环里，每一次循环就像一张图片，以计算机的强大计算速度，连接成动态移动的蛇轻而易举。

代码由5个主要函数组成：

1.首先初始化地图，包括围墙，蛇和食物。

2.是否产生食物，判别条件为蛇头是否与食物坐标重合。

3.获取移动速度，蛇越长移速越快，移速由一个Sleep函数体现。

4.移动蛇，其实实现蛇的移动只需要考虑蛇头，其余每一节取代前一节的坐标。

5.蛇是否死亡，即游戏结束条件，我的设置是撞墙和自食死亡。

其中还有一个控制台光标移动的函数gotoxy，用于将光标定位。*/


#include <stdio.h>
//#include <windows.h>
#include <time.h>
#include <conio.h>


#define frame_height 20 //define map size
#define frame_width 40
#define UP 'w' //define operate key
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'


int i,j,k;
char ch=UP; //initial direction
int grow=0; //flag: if snake grow


struct Food{
int x;
int y;
}food;
struct Snake{
int x[50];
int y[50];
int len;
int speed;
}snake; //snake[0] is head


void init_map(void);
void update_food(void);
void move_snake(void);
int is_alive(void);
void get_speed(void);
void gotoxy(int x, int y);


int main()
{
init_map(); //初始化地图
while(1)
{
update_food();
//是否产生食物
get_speed(); //获取速度
move_snake(); //移动蛇身
Sleep(snake.speed);
//移动速度
if(!(is_alive()))
//蛇的死活(撞墙或自食)
break;
}
printf("Game Over!");
getch();


return 0;
}
//initialize
void init_map(void)
{
//initial food
srand(time(NULL));
food.x=rand()%(frame_height-2)+1;
food.y=rand()%(frame_width-2)+1;
gotoxy(food.x, food.y);
printf("!");
//initial snake
snake.x[0]=frame_height/2;
snake.y[0]=frame_width/2;
gotoxy(snake.x[0], snake.y[0]);
printf("@");
snake.len=3;
snake.speed=200;
for(k=1;k<snake.len;k++)
{
snake.x[k]=snake.x[k-1]+1;
snake.y[k]=snake.y[k-1];
gotoxy(snake.x[k], snake.y[k]);
printf("@");
}
//initial bar
for(j=0;j<frame_width;j++)
{
gotoxy(0, j);
printf("#");
gotoxy(frame_height-1, j);
printf("#");
}
for(i=1;i<frame_height-1;i++)
{
gotoxy(i, 0);
printf("#");
gotoxy(i, frame_width-1);
printf("#");
}
}
//generate food
void update_food()
{
if(snake.x[0]==food.x&&snake.y[0]==food.y)
{
srand(time(NULL));
food.x=rand()%(frame_height-2)+1;
food.y=rand()%(frame_width-2)+1;
gotoxy(food.x, food.y);
printf("!");


snake.len++;
grow=1;
}
}
//move snake
void move_snake()
{
if(kbhit())
ch=getch();
if(!grow)
{
gotoxy(snake.x[snake.len-1], snake.y[snake.len-1]);
printf(" ");
}
for(k=snake.len-1;k>0;k--)
{
snake.x[k]=snake.x[k-1];
snake.y[k]=snake.y[k-1];
}
switch(ch)
{
case UP: snake.x[0]--;break;
case DOWN:  snake.x[0]++;break;
case LEFT: snake.y[0]--;break;
case RIGHT: snake.y[0]++;break;
default: break;
}
gotoxy(snake.x[0], snake.y[0]);
printf("@");
grow=0;
gotoxy(frame_height, 0);
}
//is alive
int is_alive(void)
{
if(snake.x[0]==0||snake.x[0]==frame_height-1||snake.y[0]==frame_width-1||snake.y[0]==0)
return 0;
for(k=1;k<snake.len;k++)
if(snake.x[k]==snake.x[0]&&snake.y[k]==snake.y[0])
return 0;
return 1;
}
//speed up
void get_speed(void)
{
if(snake.len<=6)
snake.speed=200;
else if(snake.len<=10)
snake.speed=100;
else if(snake.len<=20)
snake.speed=50;
else if(snake.len<=30)
snake.speed=30;
else snake.speed=20;
}
//move cursor
void gotoxy(int x, int y)
{
HANDLE hout;
COORD cor;
hout=GetStdHandle(STD_OUTPUT_HANDLE);
cor.X=y;
cor.Y=x;
SetConsoleCursorPosition(hout,cor);
}
