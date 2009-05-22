#include <time.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <dos.h>
#include <mouse.h>
#include <button.cls>

# define ROWS 8
# define COLS 8
# define MINES 10

# define X 0
# define Y 0
# define length 20
# define bredth 20

int check();
void msgbox(char *);
void edit();
void solve();

static signed char play[ROWS][COLS];
static signed char open[ROWS][COLS];

void intro()
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

//filling columns and rows with mines
	setfillstyle(SOLID_FILL,8);
	bar(X,Y,X+ROWS*length,Y+COLS*bredth);
	randomize();
	{
	for (int x =0;x < ROWS;x++)
		for (int y =0;y < COLS;y++)
			play[x][y] =0;
	}
	for (int i=0;i < MINES;i++)
	{
		int x = random(ROWS);
		int y = random(COLS);
		if (play[x][y] == -1)
			i--;
		else
			play[x][y] =-1;
	}
//filling with digits
	for (int x =0;x < ROWS;x++)
	for (int y =0;y < COLS;y++)
	{
		if (play[x][y] != -1)
			{
				int initx,inity,endx,endy;
				initx = x > 0 ? x-1:x;
				inity = y > 0 ? y-1:y;
				endx = x != ROWS-1?x + 1:ROWS-1;
				endy = y != COLS-1?y + 1:COLS-1;
				int counter = 0;
				int x1=0,y1=0;

				for (y1=inity;y1 <= endy;y1++)
					for (x1=initx;x1 <= endx;x1++)
						if (play[x1][y1] == -1)
							counter++;
					play[x][y] = counter;
			}//digit fill*/
			button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,"");
			t.draw();

	}//end of filling with numbers

}//end of introduction

int main(void)
{
	intro();
	int quit =0 ;
	mouse_status mouse;
	mouse_present();
	show_mouse();
	bind_mouse(X,Y,X+ROWS*length-1,Y+COLS*bredth-1);

char word[6][64] = {
 {255,254,127,254,31,254,7,254,1,254,1,254,0,254,255,254,255,254,255,254,255,254,255,254,255,254,127,252,63,248,63,248,0,1,128,1,96,1,24,1,6,1,2,1,255,1,0,1,0,1,0,1,0,1,0,1,0,1,128,3,64,4,192,7},
 {255,254,63,254,15,254,3,254,0,254,1,254,15,254,255,254,255,254,255,254,255,254,255,254,255,254,127,252,63,248,63,248,0,1,192,1,48,1,12,1,3,1,30,1,240,1,0,1,0,1,0,1,0,1,0,1,0,1,128,3,64,4,192,7},
 {255,254,63,254,3,254,0,254,1,254,7,254,15,254,255,254,255,254,255,254,255,254,255,254,255,254,127,252,63,248,63,248,0,1,192,1,60,1,3,1,6,1,24,1,240,1,0,1,0,1,0,1,0,1,0,1,0,1,128,3,64,4,192,7},
 {255,254,63,254,7,254,3,254,3,254,7,254,15,254,255,254,255,254,255,254,255,254,255,254,255,254,127,252,63,248,63,248,0,1,192,1,56,1,4,1,4,1,24,1,240,1,0,1,0,1,0,1,0,1,0,1,0,1,128,3,64,4,192,7},
 {255,254,63,254,7,254,7,254,7,254,7,254,31,254,255,254,255,254,255,254,255,254,255,254,255,254,127,252,63,248,63,248,0,1,192,1,56,1,8,1,8,1,24,1,224,1,0,1,0,1,0,1,0,1,0,1,0,1,128,3,64,4,192,7},
 {255,254,63,254,15,254,3,254,1,254,3,254,15,254,255,254,255,254,255,254,255,254,255,254,255,254,127,252,63,248,63,248,0,1,192,1,48,1,12,1,2,1,12,1,240,1,0,1,0,1,0,1,0,1,0,1,0,1,128,3,64,4,192,7}};

	int key = 0;
	while (!quit)
	{
		anim(word,6,10,8,15);
		key = 0;
		if (kbhit())
		{
			key = getch();
			if (key == 0)
				key = 1000+getch();
		}//end of getting key

		switch(key)
		{
			case 5 : //ctrl e
				hide_mouse();
				msgbox("Editing..");
				bar(X,Y,ROWS*length+X,COLS*bredth+Y);
				settextjustify(LEFT_TEXT,TOP_TEXT);
				show_mouse();
				edit();
				break;
			case 17: //ctrl q
				msgbox("Quitting..");
				quit = 1;
				break;
			case 1059: //F1
				solve();
			case 18: //ctrl R
				msgbox("Resetting..");
				hide_mouse();
				intro();
				bind_mouse(X,Y,X+ROWS*length-1,Y+COLS*bredth-1);
				show_mouse();
				break;
		}//end of switch case
		mouse = click();
			unsigned int x,y;
			x = mouse.x/length;
			y = mouse.y/bredth;

		if (mouse.button == BOTH_CLICK)
			quit = 1;
		else if (mouse.button == RIGHT_CLICK && open[x][y] != 1)
			{
				hide_mouse();
				bar(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1);
				if (open[x][y] == -1)
					{
					open[x][y] = -2;
					button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,"þ");
					t.draw();
					}//end of mark
				else if (open[x][y] == -2)
					{
					open[x][y] = 0;
					button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1," ");
					t.draw();
					}//end of question
				else if (open[x][y] == 0)
					{
					open[x][y] = -1;
					button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,"?");
					t.draw();
					}//end of clear
			show_mouse();
			}//end of roight click
		else if (mouse.button == LEFT_CLICK && open[x][y] == 0)
			{
			hide_mouse();
			if (open [x][y] == 0)
				open[x][y] = 1;
			char s[2];
			play[x][y] != 0 ? sprintf(s,"%1d",play[x][y]) : sprintf(s," ");
			s[1] = NULL;
			button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,s);
			t.draw();
			t.depress();

			//flood clearing
	if (play[x][y] == 0)
		{
			setactivepage(1);
			setfillstyle(SOLID_FILL,0);
			bar(0,0,ROWS,COLS);
			for (int x1 =0;x1 < ROWS;x1++)
				for (int y1 =0;y1 < COLS;y1++)
					if (play[x1][y1] != 0)
						putpixel(x1+1,y1+1,15);
			setfillstyle(SOLID_FILL,7);
			rectangle(0,0,ROWS+1,COLS+1);
			floodfill(x+1,y+1,15);
			for (x1 =0;x1 < ROWS;x1++)
				for (y1 =0;y1 < COLS;y1++)
					if (getpixel(x1+1,y1+1) == 7 && open[x1][y1] == 0)
						{
							open[x1][y1] = 1;
							setactivepage(0);
							button t(X+x1*length+1,Y+y1*bredth+1,X+x1*length+length-1,Y+y1*bredth+bredth-1,"");
							t.draw();
							t.depress();
							setactivepage(1);
						}//end of clearing
		}//end of clearing
			setactivepage(0);
			show_mouse();
			switch (check())
			{
				case 1:
					quit = 1;
					msgbox("You Win");
					break;
				case -1:
					quit = 1;

					msgbox("Mine Hit");
					break;
			}//end of check victory

			}//end of left click

	}//end of quitting
	closegraph();
	return 0;
}

void solve()
{
}

void edit()
{
	int quit = 0;
	for (int x=0;x < ROWS;x++)
		for (int y=0;y < COLS;y++)
		{
			char s[2];
			play[x][y] != 0 ? sprintf(s,"%1d",play[x][y]) : sprintf(s," ");
			s[1] = NULL;
			button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,s);
			t.draw();
			t.depress();
		}
	mouse_status mouse;

	while (!quit)
	{
		mouse = click();
		x = mouse.x/length;
		y = mouse.y/bredth;

		if (mouse.button == BOTH_CLICK)
			quit = 1;
		else if (mouse.button == RIGHT_CLICK)
			{
			hide_mouse();
			play[x][y]--;
			if (play[x][y] == -2)
				play[x][y] = 8;
			char s[2];
			play[x][y] != 0 ? sprintf(s,"%1d",play[x][y]) : sprintf(s," ");
			s[1] = NULL;
			bar(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1);
			button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,s);
			t.draw();
			show_mouse();
			}//end of this
		else if (mouse.button == LEFT_CLICK)
			{
			hide_mouse();
			play[x][y]++;
			if (play[x][y] == 9)
				play[x][y] = -1;
			char s[2];
			play[x][y] != 0 ? sprintf(s,"%1d",play[x][y]) : sprintf(s," ");
			s[1] = NULL;
			bar(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1);
			button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,s);
			t.draw();
			show_mouse();
			}//end of left_click
	}//end of quitting
	hide_mouse();
	for (x=0;x < ROWS;x++)
		for (y=0;y < COLS;y++)
		{
			bar(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1);
			button t(X+x*length+1,Y+y*bredth+1,X+x*length+length-1,Y+y*bredth+bredth-1,"");
			t.draw();
		}
		show_mouse();
}

int check()
{
	 for (int x = 0;x < ROWS;x++)
		for (int y=0;y < COLS;y++)
			if (open[x][y] == 1 && play[x][y] == -1)
				return -1;

	 for (x = 0;x < ROWS;x++)
		for (y=0;y < COLS;y++)
			if (open[x][y] == 0 && play[x][y] != -1)
				return 0;
	return 1;
}

void msgbox(char *str)
{
	hide_mouse();
	setfillstyle(SOLID_FILL,8);
	bar(X+length*ROWS/8,Y+bredth*COLS/4,X+length*ROWS*7/8,Y+bredth*COLS*3/4);
	rectangle(X+length*ROWS/8,Y+bredth*COLS/4,X+length*ROWS*7/8,Y+bredth*COLS*3/4);
	settextjustify(1,1);
	setcolor(7);
	outtextxy(X-1+ROWS/2*length,Y-1+COLS/2*bredth,str);
	outtextxy(1+X+ROWS/2*length,Y-1+COLS/2*bredth,str);
	outtextxy(X-1+ROWS/2*length,1+Y+COLS/2*bredth,str);
	outtextxy(1+X+ROWS/2*length,1+Y+COLS/2*bredth,str);
	setcolor(15);
	outtextxy(X+ROWS/2*length,Y+COLS/2*bredth,str);
	show_mouse();
getch();
}

