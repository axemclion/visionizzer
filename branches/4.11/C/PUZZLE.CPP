#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include "d:\prog\c\mouse.h"
#include "d:\prog\c\button.cls"

# define X 100
# define Y 100
# define WIDTH  40
# define HEIGHT 40
# define ROW 4
# define COL 4

static int grid[ROW][COL];
button but[ROW][COL];

void setgrid()
{
	int sample[ROW*COL];
	for (int i=0;i < ROW*COL;i++)
		sample[i] = i;
	int sample_set = ROW*COL;
	for (i=0;i <ROW;i++)
	for (int j=0;j < COL;j++)
		{
			int elem = 0;
			elem = random(sample_set);
			grid[i][j] = sample[elem];
			for (int q=elem;q < sample_set-1;q++)
				sample[q] = sample[q+1];
			sample_set--;

		}//finsihed for one element

}//end of setting grid


void has_won()
{
int flag = 0;
int counter = 1;
for (int i=0;i < ROW;i++)
for (int j=0;j < COL;j++)
	if (grid[j][i] != counter++ && grid[j][i] != 0)
		flag = 1;

if (flag == 0)
{
setfillstyle(SOLID_FILL,7);
bar(X,Y,X+ROW*WIDTH,Y+COL*HEIGHT);
outtextxy((X+ROW*WIDTH)/2,(Y+COL*HEIGHT)/2,"You WIN");
getch();
closegraph();
exit(0);
}//flag has been set
}//end of user winnig the game

void redraw()
{
	hide_mouse();
	for (int i=0;i < ROW;i++)
		for (int j = 0 ;j<COL;j++)
		{
			sprintf(but[i][j].text,"%d",grid[i][j]);
			if (strcmp(but[i][j].text,"0"))
				but[i][j].init(X+WIDTH*i,Y+HEIGHT*j,WIDTH-3+X+WIDTH*i,HEIGHT-3+Y+HEIGHT*j,but[i][j].text);
			else
				but[i][j].init(X+WIDTH*i,Y+HEIGHT*j,WIDTH-3+X+WIDTH*i,HEIGHT-3+Y+HEIGHT*j," ");
			but[i][j].draw();

			if (strcmp(but[i][j].text," ") == 0)
				but[i][j].depress();
		}//end of all initialisations
	show_mouse();
}//end of redrawing diagram

void change(int x,int y)
{
	if (grid[x-1][y] == 0 && x-1 >= 0)
	{
		grid[x-1][y] = grid[x][y];
		grid[x][y] = 0;
	}//end of empty left

	else if (grid[x+1][y] == 0 && x+1 < ROW)
	{
		grid[x+1][y] =grid[x][y];
		grid[x][y] = 0;
	}//end of empty left

	else if (grid[x][y+1] == 0 && y+1 < COL)
	{
		grid[x][y+1] =grid[x][y];
		grid[x][y] = 0;
	}//end of empty left
	else if (grid[x][y-1] == 0 && y-1 >= 0)
	{
		grid[x][y-1] =grid[x][y];
		grid[x][y] = 0;
	}//end of empty left
	redraw();
	has_won();
}//end of checking fo victory


int main(void)
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
   {
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
      printf("Press any key to halt:");
		getch();
      exit(1);             /* return with error code */
	}
	mouse_present();
	setgrid();
	mouse_status mouse = {0,0,0};
	int quit=0;
	button finish(X + ROW * WIDTH + 40,Y, X+ROW*WIDTH+150,Y+50,"Quit");
	button shuffle(X + ROW * WIDTH + 40,Y+70, X+ROW*WIDTH+150,Y+70+50,"Shuffle");
	button t(80,80,270+ROW*WIDTH,120+COL*HEIGHT,"");t.draw();

char word[4][64] = {
{127,254,63,252,31,248,127,254,127,254,123,222,185,157,192,3,192,3,185,157,123,222,127,254,127,254,31,248,63,252,127,254,128,1,192,3,224,7,128,1,128,1,132,33,70,98,63,252,63,252,70,98,132,33,128,1,128,1,224,7,192,3,128,1},
{255,255,127,254,63,252,31,248,127,254,119,238,179,205,193,131,193,131,179,205,119,238,127,254,31,248,63,252,127,254,255,255,0,0,128,1,192,3,224,7,128,1,136,17,76,50,62,124,62,124,76,50,136,17,128,1,224,7,192,3,128,1,0,0},
{255,255,255,255,127,254,63,252,31,248,111,246,167,229,195,195,195,195,167,229,111,246,31,248,63,252,127,254,255,255,255,255,0,0,0,0,128,1,192,3,224,7,144,9,88,26,60,60,60,60,88,26,144,9,224,7,192,3,128,1,0,0,0,0},
{255,255,127,254,63,252,31,248,127,254,119,238,179,205,193,131,193,131,179,205,119,238,127,254,31,248,63,252,127,254,255,255,0,0,128,1,192,3,224,7,128,1,136,17,76,50,62,124,62,124,76,50,136,17,128,1,224,7,192,3,128,1,0,0}};

	t=button(90,90,110+ROW*WIDTH,110+COL*HEIGHT,"");
	t.draw();t.depress();shuffle.draw();
	t= button (273+ROW*WIDTH,110,400+ROW*WIDTH,90+COL*HEIGHT,"");t.draw();
	t= button (110,50,240+ROW*WIDTH,78,"PUZZLE");t.draw();
	finish.draw();
	redraw();
	mouse = click();
	show_mouse();

	while (quit == 0)
	{
		anim(word,4,8);
		mouse = status();
		if (finish.lclick(mouse.x,mouse.y) && mouse.button == LEFT_CLICK)
			quit = 1;
		if (shuffle.lclick(mouse.x,mouse.y) && mouse.button == LEFT_CLICK)
			{
			setgrid();
			redraw();
			}

		for (int i=0;i < ROW;i++)
		for (int j=0;j < COL;j++)
		if (but[i][j].in(mouse.x,mouse.y) && mouse.button == LEFT_CLICK)
			{
			but[i][j].depress();
			mouse = status();
			while (mouse.button != 0)
			mouse = status();
			but[i][j].up();
			change(i,j);
			}
	}//end of main loop
	closegraph();
   return 0;
}
