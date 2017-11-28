#include <stdio.h>
#include <SDL2/SDL.h>

int main(){
//variables
int j;
int i;
int mul=20;
int xsize=40;
int ysize=30;
int tab[xsize][ysize];
int r,g,b;
int r2,g2,b2;
SDL_Event input;
char direction = "d";
int posx,posy;
SDL_Renderer *renderer;

posx=10;
posy=10;

r=0;
g=150;
b=150;

r2=150;
g2=150;
b2=0;

//clearing tab
int tabclear(){
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++)tab[i][j]=0;
	}
}

//functions
void pixel(int x, int y){
	SDL_RenderDrawPoint(renderer, x, y);
}

void square(int x, int y, int s){
	int i;
	int j;
	SDL_SetRenderDrawColor(renderer, r, g, b, 0);
	for(j=x;j<x+s;j++){
		for(i=y;i<y+s;i++)pixel(j,i);
	}
	SDL_SetRenderDrawColor(renderer, r2, g2, b2, 0);
	for(i=x;i<x+s;i++)pixel(i,y);
	for(j=y;j<y+s;j++)pixel(x,j);
	for(i=x;i<x+s;i++)pixel(i,y+s-1);
	for(j=y;j<y+s;j++)pixel(x+s-1,j);
	SDL_SetRenderDrawColor(renderer, r, g, b, 0);

}




//game functions and variables
int snake[xsize*ysize][2];
int tail;
int aplstat=0;
int aplx;
int aply;

int borders(){
	for(i=0;i<ysize;i++){
		tab[0][i]=1;
		tab[xsize-1][i]=1;
	}
	for(i=0;i<xsize;i++){
		tab[i][0]=1;
		tab[i][ysize-1]=1;
	}
}

int reset(){
	tail=2;
	snake[0][0]=3;
	snake[0][1]=3;
	snake[1][0]=2;
	snake[1][1]=3;
	snake[2][0]=1;
	snake[2][1]=3;
}

reset();

int push(int x, int y){
	//sprawdzenie czy nie wchodzi w szyje
	if(snake[1][0]==x && snake[1][1]==y){
		x=snake[0][0]+(snake[0][0]-snake[1][0]);
		y=snake[0][1]+(snake[0][1]-snake[1][1]);
	}
	//faktyczny push
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
			i = rand()%((xsize-2)*(ysize-2))-1;
			printf("%d\n",i);
			aply=i/(xsize-2)+1;
			aplx=i%(xsize-2)+1;
			if (tab[aplx][aply]>0);
			else break;
		}
		aplstat=1;
	}
	tab[aplx][aply]=2;
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






//SDL
SDL_Init( SDL_INIT_VIDEO );

SDL_Window *window;
SDL_CreateWindowAndRenderer(xsize*mul, ysize*mul, 0, &window, &renderer);



//main loop
while(1){

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

	SDL_RenderClear(renderer);

	tabclear();

	//write snake and apples to tab (aplgen must be after writing snake to tab), and borders
	for(i=0;i<=tail;i++) tab[ (snake[i][0]) ] [ (snake[i][1]) ]=1;
	aplgen();
	borders();

	//displaying the tab
	for(i=0;i<xsize;i++){
		for(j=0;j<ysize;j++){if(tab[i][j]>0)square(i*mul,j*mul,mul);}
	}
	SDL_RenderPresent(renderer);

	//checking user input
	//SDL_WaitEvent(&input);
	SDL_Delay(100);
	for(;;){
		if(SDL_PollEvent(&input)==0)break;
		if(input.key.type==SDL_KEYDOWN) direction=input.key.keysym.sym;
	}
	
	if(input.key.keysym.sym=='q')break;

	switch(direction){
	case 'w':mov(1);
		break;
	case 's':mov(2);
		break;
	case 'd':mov(3);
		break;
	case 'a':mov(4);
		break;
	}
	if(tab[snake[0][0]][snake[0][1]]==1)reset();
}

SDL_Quit();
return 0;
}
