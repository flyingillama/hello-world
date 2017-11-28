#include <stdio.h>
#include "gfx.h"
#include <stdlib.h>//for rand() func

int main(){
//variables
int j;
int i;
int mul=20;
int xsize=30;
int ysize=30;
int tab[xsize][ysize];
int r,g,b;
int r2,g2,b2;
char input;
int posx,posy;
int licznik=0;

r=0;
g=150;
b=150;

r2=150;
g2=150;
b2=0;

//clearing tab
void tabclear(){
	licznik++;
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++)tab[i][j]=0;
	}
}

tabclear();

//engine functions
void pixel(int x, int y){
	gfx_point(x,y);
}

void square(int x, int y, int s){
	int i;
	int j;
	gfx_color(r,g,b);
	for(j=x;j<x+s;j++){
		for(i=y;i<y+s;i++)pixel(j,i);
	}
	gfx_color(r2,g2,b2);
	for(i=x;i<x+s;i++)pixel(i,y);
	for(j=y;j<y+s;j++)pixel(x,j);
	for(i=x;i<x+s;i++)pixel(i,y+s-1);
	for(j=y;j<y+s;j++)pixel(x+s-1,j);
	gfx_color(r,g,b);

}


//game functions and variables
int snake[xsize*ysize][2];
int tail = 2;
int aplstat=0;
int aplx;
int aply;
snake[0][0]=3;
snake[0][1]=3;
snake[1][0]=2;
snake[1][1]=3;
snake[2][0]=1;
snake[2][1]=3;

int push(int x, int y){
	tail++;
	for(i=tail;i>=0;i--){
		snake[i][0]=snake[i-1][0];
		snake[i][1]=snake[i-1][1];
	}
	snake[0][0]=x;
	snake[0][1]=y;
}

int pop(){
	if(snake[0][0]==aplx && snake[0][1]==aply) 
		aplstat=0;
	else
		tail--;
}

int aplgen(){
	if (aplstat==0){
		while(1){
			i = rand()%(xsize*ysize)-1;
			printf("%d\n",i);
			aply=i/xsize;
			aplx=i%xsize;
			if (tab[aplx][aply]>0);
			else break;
		}
		aplstat=1;
	}
	tab[aplx][aply]=1;
}


int mov(int dir){
	posx=snake[0][0];
	posy=snake[0][1];
	switch(dir){
	case 1:
		push(posx,posy-1);
		break;
	case 2:
		push(posx,posy+1);
		break;
	case 3:
		push(posx+1,posy);
		break;
	case 4:
		push(posx-1,posy);
		break;
	}
	pop();
}







gfx_open(xsize*mul, ysize*mul, "square");
gfx_color(0,200,100);


//main loop
while(1){

	gfx_clear();
	
	tabclear();

	//write snake and apples to tab (aplgen must be after writing snake to tab)
	for(i=0;i<=tail;i++) tab[ (snake[i][0]) ] [ (snake[i][1]) ]=1;
	aplgen();
	
	
	//displaying the tab
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++){if(tab[i][j]>0)square(i*mul,j*mul,mul);}
	}
	gfx_flush();

	//checking user input
	input=gfx_wait();
	if(input=='q')break;

	switch(input){
	case 'w':mov(1);
		break;
	case 's':mov(2);
		break;
	case 'd':mov(3);
		break;
	case 'a':mov(4);
		break;
	}







}
return 0;
}
