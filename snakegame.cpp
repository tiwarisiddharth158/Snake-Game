#include<iostream>
#include<conio.h>
#include<ctime>
#include<windows.h>
using namespace std;
bool gameOver;

const int width = 20; //map dimensions
const int height = 20;
int x,y; //snake head positions
int fruitX,fruitY; //fruit positions
int score;
int tailX[100],tailY[100];// x and y coordinate of the tail which goes in pair
int nTail;// to specify the length of the tail

enum eDirection{STOP=0,LEFT,RIGHT,UP,DOWN}; //to control the directions of the snake
eDirection dir;

void setUp()
{
    gameOver = false;
    dir = STOP;//Snake will not move until we start moving it
    x = width/2;// Snake head will be centered
    y = height/2;// on the map
    fruitX = rand()%width;// we need to place the fruit
    fruitY = rand()%height;//randomly on the map
    score = 0;
}
void draw()
{
    system("cls");//to clear the console
    for(int i=0;i<width+2;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            if(j==0)
            {
                cout<<"#";
            }
            if(i == y && j == x)//printing snake's head
            {
                cout<<"O";
            }
            else if(i == fruitY && j == fruitX)//printing snake's fruit
            {
                cout<<"F";
            }
            else
            {
                bool print = false;
                for(int k=0;k<nTail;k++)// to print the tail
                {
                    if(tailX[k] == j && tailY[k] == i)
                    {
                        cout<<"o";
                        print = true;
                    }
                }
                if(!print)
                {
                    cout<<" ";
                }
            }
            if(j == width-1)
            {
                cout<<"#";
            }
        }
        cout<<endl;
    }
    for(int i=0;i<width+2;i++)
    {
        cout<<"#";
    }
    cout<<endl;
    cout<<"Score : "<<score;
}
void input()
{
    if(kbhit())// Determines if a keyboard key was pressed
    {
        switch(getch())//Get char entry from the console
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':
            gameOver = true;
            break;
        }
    }
}
void logic()
{
    int prevX = tailX[0];// to remember the previous coordinate of the first segment of tailX
    int prevY = tailY[0];// to remember the previous coordinate of the first segment of tailY
    int prev2X,prev2Y;
    tailX[0] = x;
    tailY[0] = y;
    for(int i=1;i<nTail;i++)//for loop to move the tail..i starts with 1 because we already have the coordinate of the first one
    {
        prev2X = tailX[i];// to remember the
        prev2Y = tailY[i];// coordinates
        tailX[i] = prevX;// of the
        tailY[i] = prevY;//previous
        prevX = prev2X;// segments
        prevY = prev2Y;
    }
    switch(dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    default:
        break;
    }

//    if(x > width || x < 0 || y > height || y < 0 )// if snake head goes out of the map boundary
//    {
//        gameOver = true;
//    }
    if (x >= width) x = 0; else if (x < 0) x = width - 1;//to make the snake the move through the wall
    if (y >= height) y = 0; else if (y < 0) y = height - 1;


    for(int i=0;i<nTail;i++)// if the head of the snake's collide with the snake's tail
    {
        if(tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }

    if(x == fruitX && y == fruitY)
    {
        score = score + 10;
        fruitX = rand()%width;
        fruitY = rand()%height;
        nTail++; // increase the length of the tail by ! after the fruit is being eaten
    }
}
int main()
{
    setUp();
    while(!gameOver)
    {
        draw();
        input();
        logic();
        Sleep(20);// to slow the speed
    }
}
