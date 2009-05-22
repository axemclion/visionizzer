#include <time.h>
#include <conio.h>
#include <stdio.h>
#include <graphics.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
#include "d:\prog\c\mouse.h"
# define DEL 3


int x1,y1;
int grid[9];
int rot(int);
int ref(int);
int rotate;

char word[8][64] = {
 {31,248,231,231,251,223,253,191,253,191,254,127,254,127,254,127,254,127,254,127,254,127,253,191,253,191,251,223,231,231,31,248,224,7,24,24,4,32,2,64,2,64,1,128,1,128,1,128,1,128,1,128,1,128,2,64,2,64,4,32,24,24,224,7},
 {255,255,63,252,207,243,247,239,251,223,251,223,253,191,253,191,253,191,253,191,251,223,251,223,247,239,207,243,63,252,255,255,0,0,192,3,48,12,8,16,4,32,4,32,2,64,2,64,2,64,2,64,4,32,4,32,8,16,48,12,192,3,0,0},
 {255,255,255,255,63,252,207,243,247,239,247,239,251,223,251,223,251,223,251,223,247,239,247,239,207,243,63,252,255,255,255,255,0,0,0,0,192,3,48,12,8,16,8,16,4,32,4,32,4,32,4,32,8,16,8,16,48,12,192,3,0,0,0,0},
 {255,255,255,255,255,255,63,252,223,251,239,247,247,239,247,239,247,239,247,239,239,247,223,251,63,252,255,255,255,255,255,255,0,0,0,0,0,0,192,3,32,4,16,8,8,16,8,16,8,16,8,16,16,8,32,4,192,3,0,0,0,0,0,0},
 {255,255,255,255,255,255,255,255,63,252,223,251,239,247,239,247,239,247,239,247,223,251,63,252,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,192,3,32,4,16,8,16,8,16,8,16,8,32,4,192,3,0,0,0,0,0,0,0,0},
 {255,255,255,255,255,255,63,252,223,251,239,247,247,239,247,239,247,239,247,239,239,247,223,251,63,252,255,255,255,255,255,255,0,0,0,0,0,0,192,3,32,4,16,8,8,16,8,16,8,16,8,16,16,8,32,4,192,3,0,0,0,0,0,0},
 {255,255,255,255,63,252,207,243,247,239,247,239,251,223,251,223,251,223,251,223,247,239,247,239,207,243,63,252,255,255,255,255,0,0,0,0,192,3,48,12,8,16,8,16,4,32,4,32,4,32,4,32,8,16,8,16,48,12,192,3,0,0,0,0},
 {255,255,63,252,207,243,247,239,251,223,251,223,253,191,253,191,253,191,253,191,251,223,251,223,247,239,207,243,63,252,255,255,0,0,192,3,48,12,8,16,4,32,4,32,2,64,2,64,2,64,2,64,4,32,4,32,8,16,48,12,192,3,0,0}};


void messagebox(const char *msg1,char *msg2="")
{
	fflush(stdin);
	setlinestyle(0,0,1);
	hide_mouse();
	setcolor(8);
	for (int i=10;i < 200 ;i++)
		{
		setcolor(15);
		line (x1+200+i,y1+40,x1+200+i,y1+140);
		setcolor(8);
		line (x1+200+i-1,y1+40,x1+200+i-1,y1+140);
		putpixel(x1+200+i-1,y1+40,15);
		putpixel(x1+200+i-1,y1+128,15);
		putpixel(x1+200+i-1,y1+140,15);
		delay(1);
		}
	settextstyle(5,0,1);
	setcolor(15);
	outtextxy(x1+220,y1+45,msg1);
	outtextxy(x1+220,y1+50+textheight(msg1),msg2);
	settextstyle(12,0,0);
	outtextxy(x1+210,y1+130,"Press a key to continue");
	getch();
	setcolor(0);
	for (i=200;i > 10 ;i--)
		{
		setcolor(15);
		line (x1+200+i-1,y1+40,x1+200+i-1,y1+140);
		setcolor(0);
		line (x1+200+i,y1+10,x1+200+i,y1+170);
		delay(2);
		}
show_mouse();
}//end of messagebox

void draw()
{
	int gdriver = VGA, gmode=VGAMED, errorcode;
	int x, y, ht;
	initgraph(&gdriver, &gmode,"");
	errorcode = graphresult();	if (errorcode != grOk)  // an error occurred
		{
		printf("Graphics error:");
		printf("Press any key to halt:");
		getch();
		exit(1);
		}

setcolor(15);
setlinestyle(0,0,1);
setfillstyle(SOLID_FILL,7);
bar(x1,y1,x1+200,y1+180);
bar(x1+200,y1+35,x1+210,y1+145);
line(x1+80,y1+40,x1+80,y1+160);
line(x1+120,y1+40,x1+120,y1+160);
line(x1+40,y1+80,x1+160,y1+80);
line(x1+40,y1+120,x1+160,y1+120);
setcolor(8);
rectangle(x1,y1,x1+200,y1+180);
setcolor(15);
line(x1,y1,x1+200,y1);
line(x1,y1,x1,y1+180);


setcolor(8);
line(x1+79,y1+39,x1+79,y1+159);
line(x1+119,y1+39,x1+119,y1+159);
line(x1+39,y1+79,x1+159,y1+79);
line(x1+39,y1+119,x1+159,y1+119);

rectangle(x1+20,y1+35,x1+180,y1+170);
rectangle(x1+2,y1+3,x1+198,y1+28);
setcolor(15);
line(x1+180,y1+35,x1+180,y1+170);
line(x1+20,y1+170,x1+180,y1+170);
line(x1+2,y1+3,x1+2,y1+28);
line(x1+2,y1+3,x1+198,y1+3);
//////////////////
settextstyle(7,0,1);
outtextxy(x1+45,y1+3,"Tic-Tac-Toe");
setcolor(8);
outtextxy(x1+45,y1+4,"Tic-Tac-Toe");
}//end of redrawing of the 2-D objects
void putmark(int,int);

void userget()
{
	mouse_status temp ={0,0,0};
	mouse_status mouse={0,0,0};
	while (mouse.button != 0)
		{
		mouse = status();
		anim(word,8,DEL);
		}
	while (mouse.button == 0)
		{
		mouse = status();
		anim(word,8,DEL);
		}
	while (temp.button != 0)
		{
		temp = status();
		anim(word,8,DEL);
		}
	mouse.x=(mouse.x-x1)/40;
	mouse.y=(mouse.y-y1)/40;
	int pos =0,pos1=0;

	pos1 =mouse.x+mouse.y*3-4;
	pos = pos1;
	switch(rotate)
	{
	case 1:
		pos = rot(pos1);
		pos = rot(pos);
		pos = rot(pos);
		break;
	case 2:
		pos = rot(pos1);
		pos = rot(pos);
		break;
	case 3:
		pos = rot(pos1);
		pos = rot(pos);
		pos = rot(pos);
		pos = rot(pos);
		pos = rot(pos);break;
	}//end of switch case
	if (grid[pos] != 0)
		{
		messagebox("You cannot place ","counter here ...");
		userget();
		}
	else
		{
		grid[pos] = 1;
		putmark(1,pos);
		}//end of epty position
click();
}//end of user getting

void has_won()
{
	setlinestyle(2,0,3);
	int result=0;
	if (grid[0] == grid [1] && grid[1] == grid[2] && grid[0] != 0)
		{
		line (x1+40,y1+60,x1+160,y1+60);
		result =grid[0];
		}
	if (grid[3] == grid [4] && grid[4] == grid[5] && grid[5] != 0)
		{
		line (x1+40,y1+100,x1+160,y1+100);
		result =grid[3];
		}
	if (grid[6] == grid [7] && grid[7] == grid[8] && grid[8] != 0)
		{
		line (x1+40,y1+120,x1+160,y1+120);
		result =grid[6];
		}

	if (grid[0] == grid [3] && grid[3] == grid[6] && grid[0] != 0)
		{
		line (x1+60,y1+40,x1+60,y1+160);
		result =grid[0];
		}
	if	(grid[1] == grid [4] && grid[4] == grid[7] && grid[7] != 0)
		{
		line (x1+100,y1+40,x1+100,y1+160);
		result =grid[1];
		}
	if (grid[2] == grid [5] && grid[5] == grid[8] && grid[5] != 0)
		{
		line (x1+160,y1+40,x1+160,y1+160);
		result =grid[2];
		}

	if (grid[0] == grid [4] && grid[4] == grid[8] && grid[4] != 0)
		{
		line (x1+40,y1+40,x1+160,y1+160);
		result =grid[4];
		}
	if (grid[2] == grid [4] && grid[4] == grid[6] && grid[4] != 0)
		{
		line (x1+40,y1+160,x1+160,y1+40);
		result =grid[4];
		}

	if (result != 0)
	{
		messagebox("The Computer has","won the game");
		getch();
		closegraph();
		exit(0);
	}
}//end of functiopn


int rot(int pos1)
{
	int pos;
	switch (pos1)
	{
		case 4:
			pos =4;break;
		case 6:
			pos=0;break;
		case 0:
			pos =2;break;
		case 2:
			pos =8;break;
		case 8:
			pos =6;break;
		case 3:
			pos =1;break;
		case 1:
			pos =5;break;
		case 5:
			pos =7;break;
		case 7:
			pos =3;break;
	}//end of switch case
return pos;
}

void putmark(int player,int pos1)
{
anim(word,8,5);
grid[pos1] = player;
hide_mouse();
setlinestyle(0,0,0);
int pos=pos1;
switch (rotate)
{
	case 3:
		pos=rot(rot(rot(pos1)));break;
	case 2:
		pos=rot(rot(pos1));break;
	case 1:
		pos=rot(pos1);break;
}
	setlinestyle(0,0,1);
	if (player == 1)
	{
		for (int i=1;i < 360;i++)
		{
			setcolor(15);
			arc(pos%3 *40+x1+60,pos / 3*40+y1+60,1,i,15);
			setcolor(8);
			arc(pos%3 *40+x1+60-1,pos / 3*40+y1+60-1,1,i,15);
			delay(1);
		}
	}
	if (player == 2)
		{
		setcolor(15);
		moveto(pos%3 *40+x1+60-10,pos / 3*40+y1+60-10);
		delay(10);
		for (int i=0;i < 20;i++)
			{
				putpixel(pos%3 *40+x1+60-10+i,pos / 3*40+y1+60-10+i,15);
				putpixel(pos%3 *40+x1+60-9+i,pos / 3*40+y1+60-11+i,8);
				delay(10);
			}
		for (i=0;i < 20;i++)
			{
				putpixel(pos%3 *40+x1+60+10-i,pos / 3*40+y1+60-10+i,15);
				putpixel(pos%3 *40+x1+60+9-i,pos / 3*40+y1+60-11+i,8);
				delay(10);
			}
		}
show_mouse();
}//end of putting function

void oneof(int x,int y,int z)
{
	int result=-1;
	if (grid[x] == grid[y] && grid[z] ==0 && grid[x] == 2 && grid[y] == 2)
		result= z;
	if (grid[z] == grid[y] && grid[x] ==0 && grid[z] == 2 && grid[y] == 2)
		result= x;
	if (grid[x] == grid[z] && grid[y] ==0 && grid[x] == 2 && grid[z] == 2)
		result= y;
	if (result != -1)
	{
		grid[result] =2;
		putmark(2,result);
		has_won();
	}//end of win
}

void force_win()
{
	oneof(0,1,2);
	oneof(3,4,5);
	oneof(6,7,8);

	oneof(0,3,6);
	oneof(1,4,7);
	oneof(2,5,8);

	oneof(0,4,8);
	oneof(2,4,6);
}//end of force win
int save(int a,int b,int c)
{
	int result=-1;
	if (grid[a] == grid[b] && grid[a] == 1 && grid[c] == 0)
		result = c;
	if (grid[b] == grid[c] && grid[b] == 1 && grid[a] == 0)
		result = a;
	if (grid[a] == grid[c] && grid[c] == 1 && grid[b] == 0)
		result = b;
	if (result != -1)
		putmark(2,result);
	return result;
}//end of game

int savegame()
{
	int result = 0;
	if (save(0,1,2) != -1) result = 1;
	if (save(3,4,5) != -1) result = 1;
	if (save(6,7,8) != -1) result = 1;

	if (save(0,3,6) != -1) result = 1;
	if (save(1,4,7) != -1) result = 1;
	if (save(2,5,8) != -1) result = 1;

	if (save(0,4,8) != -1) result = 1;
	if (save(2,4,6) != -1) result = 1;
	return result;
}
void putanywhere()
{
		for (int i=0;i < 9;i++)
			if (grid[i] == 0)
				{
				putmark(2,i);
				break;
				}
}

int main()
{
	rotate = 0;
	x1=y1=100;
	draw();
	mouse_present();
	char w[64] = {0x3f,0xfc,0xdf,0xfb,0x6f,0xf6,0xb7,0xed,0xdb,0xdb,0x6d,0xb6,0xb6,0x6d,0x5a,0x5a,0x5a,0x5a,0xb6,0x6d,0x6d,0xb6,0xdb,0xdb,0xb7,0xed,0x6f,0xf6,0xdf,0xfb,0x3f,0xfc,0xc0,0x3,0x20,0x4,0x90,0x9,0x48,0x12,0x24,0x24,0x92,0x49,0x49,0x92,0xa5,0xa5,0xa5,0xa5,0x49,0x92,0x92,0x49,0x24,0x24,0x48,0x12,0x90,0x9,0x20,0x4,0xc0,0x3};	show_mouse();
	mouse_change(w);
	bind_mouse(x1+40,y1+40,x1+140,y1+140);
	userget();
	if (grid[4] == 1)
	{
		putanywhere();

		userget();
		force_win();
		if (savegame() == 0)
		{
			if (grid[0] == 1 || grid [8] == 1)
				putmark(2,6);
			else if (grid[6] == 1 || grid[2] == 1)
				putmark(2,0);
			else
				putanywhere();
		}

		userget();
		force_win();
		if (savegame() == 0)
			putanywhere();
		userget();
		force_win();
		if (savegame() == 0)
			putanywhere();
		userget();
	}
	else if (grid[1] == 1 || grid[3] == 1 || grid [5]== 1 || grid [7] == 1)
	{
		putmark(2,4);
		userget();
		if (savegame()==0)
		{
			if (grid[3] == 1 || grid[1] == 1)
				putmark(2,0);
			else if (grid[5] == 1 || grid[7] == 1)
				putmark(2,8);
			else
				putanywhere();
		}
		userget();
		force_win();
		if (savegame()==0)
			putanywhere();
		userget();
		force_win();
		if (savegame()==0)
			putanywhere();
		userget();
	}//end of second possibility
	else if (grid[0] == 1 || grid [2] == 1 || grid [6] == 1 || grid [8] == 1)
	{
		putmark(2,4);
		userget();
		if (savegame() == 0)
			{
				if (grid[0] == 1 && grid[8] == 1)
					putmark(2,1);
				else if (grid[6] == 1 && grid[2] == 1)
					putmark(2,7);
				else if (grid[0] == 1)
					{
					if (grid[7] == 1) putmark(2,6);
					else if (grid[5] == 1) putmark (2,2);
					else putanywhere();
					}
				else if (grid[2] == 1)
					{
					if (grid[7] == 1) putmark(2,8);
					else if (grid[3] == 1) putmark (2,0);
					else putanywhere();
					}
				else if (grid[6] == 1)
					{
					if (grid[1] == 1) putmark(2,0);
					else if (grid[5] == 1) putmark (2,8);
					else putanywhere();
					}

				else if (grid[8] == 1)
					{
					if (grid[1] == 1) putmark(2,2);
					else if (grid[3] == 1) putmark (2,6);
					else putanywhere();
					}
			}
	userget();
	force_win();
	if (savegame() == 0)
		putanywhere();
	userget();
	force_win();
	if (savegame() == 0)
		putanywhere();
	userget();
	}//end of corners
	messagebox("The game has ended","in a draw");
	getch();
	closegraph();
	return 0;
}