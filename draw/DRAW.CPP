/******Draw - a program written for GUI development*******/
//# define AXE

#include <dir.h>
#include <process.h>
#include <math.h>
#include <graphics.h>
#include <string.h>
#include <alloc.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <mouse.h>
#include "d:\prog\c\draw\console.h"
#include "d:\prog\c\draw\draw.h"
#include "d:\prog\c\draw\objects.cpp"
#include "d:\prog\c\draw\filesio.cpp"
#include "d:\prog\c\draw\modifier.cpp"
#include "d:\prog\c\draw\redraw.cpp"
#include "d:\prog\c\draw\vobj.h"
#include "d:\prog\c\draw\attrobj.cpp"
#include "D:\prog\c\draw\toolbox.h"
#include "d:\prog\c\draw\codes.h"

int __obj = 0;
int __grid=1;

int resolution =10;
int err= 3;
unsigned int color=15;
unsigned int line_style=SOLID_LINE;
unsigned int thickness=1;
unsigned int fillpattern=SOLID_FILL;
unsigned int fillcolor=7;
unsigned int font=DEFAULT_FONT;
unsigned int direction=HORIZ_DIR;
unsigned int size=2;
char cuspattern[8] = {0,0,0,0,0,0,0,0};


int main()
{
struct mouse_status mouse;
unsigned int quit=0;
intro();
int key=G_YesNoDialog("VISIONIZZER","Start a new session ?");
if (key == -1)
	{
_dos_setfileattr("\\text.$$$"	,FA_ARCH);
_dos_setfileattr("\\fill.$$$"	,FA_ARCH);
_dos_setfileattr("\\circ.$$$"	,FA_ARCH);
_dos_setfileattr("\\line.$$$"	,FA_ARCH);
_dos_setfileattr("\\rect.$$$"	,FA_ARCH);
_dos_setfileattr("\\pie.$$$",FA_ARCH);
_dos_setfileattr("\\cmd.$$$",FA_ARCH);
_dos_setfileattr("\\$$$.$$$",FA_ARCH);
_dos_setfileattr("\\code.$$$",FA_ARCH);
	remove("files\\code.h");
	remove("files\\cmd.$$$");
key = G_YesNoDialog("VISIONIZZER","Open an existing file in" ,"the current workspace");
	char *file = (char *)calloc(1,100);
	if (key == 1)
		{
		G_input_box(file,"VISIONIZZER","Enter the name of the file","you want to open","",13);
		openfile(file);
		}//end of opening an existing file
	free(file);
	}//end of if
if (key == 1)
	{
	remove("\\text.$$$");
	remove("\\fill.$$$");
	remove("\\circ.$$$");
	remove("\\line.$$$");
	remove("\\rect.$$$");
	remove("\\pie.$$$");
	remove("\\cmd.$$$");
	remove("\\$$$.$$$");
	remove("\\code.$$$");
	}
						/*******start processing********/
						/***global declerations******/
						/******main lopp body***/
cleardevice();
draw_grid(resolution);
StatusLine("Strike F1 for help",__LINE__,__FILE__);
#ifdef MOUSE__
	show_mouse();
#endif
mouse_change(_TARGET_CUR,8,8);
hide_mouse();
redraw();
msgbox("Welcome to VISIONIZZER","graphics package for C/C++");
show_mouse();
while (!quit)
{
if (kbhit())
	{
	key=getch();
	if (key == 0)
		key = 1000+getch();
	}
mouse=status();
//	gotoxy(50,1);printf("=%d=",coreleft());
	gotoxy(72,1);
	printf("(%03d,%03d)",mouse.x,mouse.y);
						/*********mouse processes********/
if (mouse.button)
{
	if (mouse.button==LEFT_CLICK)
	{

	}//end of left cllick
	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
	}//end of middle click
	if (mouse.button == RIGHT_CLICK)
	{
		key=toolbox();
		StatusLine("Strike F1 for help",__LINE__,__FILE__);
	}//end of right click
	if (mouse.button == BOTH_CLICK || key == 111)
	{
		hide_mouse();
		for (int x=0;x <getmaxx();x+=2)
		{
		for (int y=0;y <getmaxy();y+=2)
			putpixel(x,y,0);
		}
		StatusLine("Quit this session of VISIONIZZER ???",__LINE__,__FILE__);
		if (1==	G_YesNoDialog("VISIONIZZER","Do you want to really","quit ???"))
			{
// 		if (1==G_YesNoDialog("VISIONIZZER","Do you want to save this file"	))
//				msgbox("File Successfully","saved");
			quit =1;
			}//end of quit
		else
		{
			closegraph();
			intro();
			draw_grid(resolution);
			redraw();
			show_mouse();
			StatusLine("Strike F1 for Help",__LINE__,__FILE__);
		}//end of don't quit
		}//bothclick

}//end of mouse processes
switch (key)
{
		case 1071:
			position_mouse(mouse.x-resolution,mouse.y-resolution);
			break;
		case 1073:
			position_mouse(mouse.x+resolution,mouse.y-resolution);
			break;
		case 1081:
			position_mouse(mouse.x+resolution,mouse.y+resolution);
			break;
		case 1079:
			position_mouse(mouse.x-resolution,mouse.y+resolution);
			break;
			case 1076:
			position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
			break;
		case 1072://up arrow key
			position_mouse(mouse.x,mouse.y-resolution);
			break;
		case 1077://right arrow
			position_mouse(mouse.x+resolution,mouse.y);
			break;
		case 1080://down arrow
			position_mouse(mouse.x,mouse.y+resolution);
			break;
		case 1075://left arrow
			position_mouse(mouse.x-resolution,mouse.y);
			break;

case 9 ://enter
	if (__grid == 0) __grid = 1;
	else if (__grid == 1) __grid = 0;
	cleardevice();
	hide_mouse();
	draw_grid(resolution);
	redraw();
	show_mouse();
	StatusLine("Press a key to continue",__LINE__,__FILE__);
	show_mouse();
	break;
case 27 ://escape
hide_mouse();
if (1==	G_YesNoDialog("VISIONIZZER","Do you want to really","start a new session ???"))
	{
	remove("\\text.$$$");
	remove("\\fill.$$$");
	remove("\\circ.$$$");
	remove("\\line.$$$");
	remove("\\rect.$$$");
	remove("\\pie.$$$");
	remove("\\cmd.$$$");
	remove("\\$$$.$$$");
	remove("\\code.$$$");
	msgbox("New Session of","VISIONIZZER started ..");
	}
	cleardevice();
	closegraph();
	intro();
	draw_grid(resolution);
	redraw();
	StatusLine("Press f1 for help",__LINE__,__FILE__);
	show_mouse();
	break;
case 1060 : //save using F2
	StatusLine("Press f1 for help",__LINE__,__FILE__);
	spawnl(P_WAIT,"savefile.exe",NULL);
	{
	char *fname = (char *)calloc(1,100);
	char *buffer = (char *)calloc(1,100);
	G_input_box(fname,"Save File","Enter the name to be saved");

	for (int i=0;*(fname+i) != '.' && *(fname+i) != NULL;i++)
		buffer[i] = *(fname+i);
	strcat(buffer,".drw");
	rename("tmp.sav",buffer);
	remove("tmp.sav");
	free(fname);
	free(buffer);
	}//end of renameing file
	hide_mouse();
	cleardevice();
	closegraph();
	intro();
	draw_grid(resolution);
	redraw();
	show_mouse();break;
case 'd':
case 'D':
	hide_mouse();
	cleardevice();
	closegraph();
	intro();
	draw_grid(resolution);
	redraw();
	StatusLine("Press f1 for help",__LINE__,__FILE__);
	show_mouse();break;
case 32://space bar
	easter_egg();break;
case 'C':
case 'c':
	o_circle(0);break;
case 'p':
case 'P':
	o_circle(1);break;
case 'l':
case 'L':
	o_line(0);break;
case 'w':
case 'W':
		{
		hide_mouse();
		for (int a=0;a <getmaxx();a+=2)
		{
		for (int b=0;b <getmaxy();b+=2)
			putpixel(a,b,0);
		}}
	char *path = (char *)calloc(1,100);
	strcpy(path,"");
	G_input_box(path,"VISIONIZZER","Enter a valid filname to save","the program","",20);
	mkdir(path);
	spawnl(P_WAIT,"codegen.exe",path,path,NULL);
	strcat(path,"\\prog.cpp");
	show_code(path);
	free(path);
	cleardevice();
	draw_grid(resolution);
	redraw();
	show_mouse();
	StatusLine("The Required Program has been written",__LINE__,__FILE__);
	msgbox("The program for the","objects has been written");
	break;
case 15: //ctrl +o
setactivepage(1);
hide_mouse();
draw_grid(resolution);
redraw();
setactivepage(0);

char *val[31];
struct ffblk ffblk;
int done = 0;
done = findfirst("*.drw",&ffblk,0);

for (int i=0;i < 30;i++)
	{
	val[i] = (char *)calloc(1,100);
	if (!done)
		sprintf(val[i],"%s", ffblk.ff_name);
	else
		strcpy(val[i]," ");
	done = findnext(&ffblk);
	}

{
char selected[100];
filedialog("File Open" ,val,selected,30);
openfile(selected);
//if (-1 == spawnl(P_WAIT,"openfile.exe",selected,NULL))
//	printf(" ");
}

for (i=0;i<30;i++)
	if (val[i])
		free(val[i]);

setvisualpage(1);
cleardevice();
draw_grid(resolution);
redraw();
setvisualpage(0);
break;

case '`':
	properties();break;
case 'r':
case 'R':
	o_line(1);break;
case 1059: // help
	cleardevice();
	closegraph();
	spawnl(P_WAIT,"readme.com",NULL);
	intro();
	draw_grid(resolution);
	redraw();
	show_mouse();
	break;
case 'f':
case 'F':
	paint();
	break;
case 't':
case 'T':
	text();break;
case 1083://delete
case 'S':
case 's':
	select();break;
case '[':
	select_color();break;
case '1':
	{
	char *b = (char *)calloc(1,100);
	sprintf(b,"Command_%d",__obj++);
	add("command",b);
	free(b);
	break;
	}
case '2':
	{
	char *b = (char *)calloc(1,100);
	sprintf(b,"Label_%d",__obj++);
	add("label",b);
	free(b);
	break;
	}
case '3':
	{
	char *b = (char *)calloc(1,100);
	sprintf(b,"Text_%d",__obj++);
	add("text",b);
	free(b);
	break;
	}
case '0':
	code_write();
	break;
case '9':
	attr();
	break;
}// end of switch case
key=0;
fflush(stdin);
}//end of main loop body
remove("\\text.$$$");
remove("\\fill.$$$");
remove("\\circ.$$$");
remove("\\line.$$$");
remove("\\rect.$$$");
remove("\\pie.$$$");
remove("\\cmd.$$$");
remove("\\$$$.$$$");
remove("\\code.$$$");
cleardevice();
closegraph();
clrscr();
textattr(7);
kbhit();
puts("Thank you for using VISIONIZZER 2.0");
puts("Any suggestions for the improvement of the software");
puts("are welcome.");
puts("Don't Forget to copy all the files in the files ");
puts("directory to the directory where your output program");
puts("is stored");

return 0;}

