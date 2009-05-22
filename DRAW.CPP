/******Draw - a program written for GUI development*******/
//#define AXE
#include <dir.h>
#include <process.h>
#include <math.h>
#include <graphics.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <mouse.h>
#include <ctype.h>
#include "d:\prog\c\draw\bmploade.cpp"
#include "d:\prog\c\draw\console.h"
#include "d:\prog\c\draw\clip.h"
#include "d:\prog\c\draw\draw.h"
#include "d:\prog\c\draw\objects.cpp"
#include "d:\prog\c\draw\redraw.cpp"
#include "d:\prog\c\draw\vobj.h"
#include "D:\prog\c\draw\toolbox.h"
#include "d:\prog\c\draw\codes.h"
#include "d:\prog\c\draw\attr.h"
#include "d:\prog\c\draw\modifier.cpp"

# define GRID_COLOR 8

int __obj = 1;
int __grid=1;

int resolution =10;
int err= 3;
unsigned int color=15;
unsigned int upattern=0;
unsigned int line_style=SOLID_LINE;
unsigned int thickness=1;
unsigned int fillpattern=SOLID_FILL;
unsigned int fillcolor=7;
unsigned int font=DEFAULT_FONT;
unsigned int direction=HORIZ_DIR;
unsigned int size=2;
char cuspattern[8] = {0,0,0,0,0,0,0,0};
char filetmp[15];

int nothing()
{
if (1==	G_YesNoDialog( "Do you want to quit this ","session"))
	{
	closegraph();
	return 0;
	}
cleardevice();draw_grid(resolution);redraw();
gotoxy(72,1);
return 1;
}

int main()
{
strcpy(filetmp,"draw.tmp");
ctrlbrk(nothing);
struct mouse_status mouse;
unsigned int quit=0;
intro();
loadbmp("intro.vsn");
getch();
cleardevice();
mouse_present();
show_mouse();
loadcur("cursor","word",0,0);
int key = 0;
{
struct ffblk ffblk;
int done;
done = findfirst("draw.tmp",&ffblk,0);
if (done == 0)
	{
	 key = 	G_YesNoDialog( "Restore a recent unsaved",
									"work that was found on the",
									"system ?? ",
									"Open recent file");
	 if (key == -1)
		{
		remove("draw.tmp");
		remove("object.tmp");
		remove("code.tmp");
		}

	}//end of seeing a recent part
}//end of finding
{FILE *fp;fp = fopen("draw.tmp","at");fclose(fp);}
{FILE *fp;fp = fopen("object.tmp","at");fclose(fp);}
						/*******start processing********/
						/***global declerations******/
						/******main lopp body***/
cleardevice();
draw_grid(resolution);
StatusLine("Strike F1 for help",__LINE__,__FILE__);
#ifdef MOUSE__
	show_mouse();
#endif
hide_mouse();
redraw();
show_mouse();
quit = 0;
gotoxy(72,1);
while (!quit)
{
if (kbhit())
	{
	key=getch();
	if (key == 0)
		key = 1000+getch();
	}
mouse=status();
	gotoxy(72,1);
	printf("(%3d,%3d)",mouse.x,mouse.y);
	gotoxy(72,1);
						/*********mouse processes********/
if (key == 32)
	key = 1+toolbox(1);
if (key > 2000)
	{
	char *fname = (char *)calloc(1,100);
	if (addobj(key,fname) == 10)
		{
		closegraph();
		if (-1 == spawnl(P_WAIT,fname,NULL))
			msgbox("Unable to execute a plugin",
					"loaded to memory. This may be",
					"due to low memory.");
		hide_mouse();
		intro();
		cleardevice();
		draw_grid(resolution);
		redraw();
		mouse_present();
		StatusLine("Plugin has just been executed",__LINE__,__FILE__);
		show_mouse();
		}
	free(fname);
	}

if (mouse.button)
{
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
			putpixel(x,y,8);
		}
		StatusLine("Quit this session of VISIONIZZER ???",__LINE__,__FILE__);
		if (1==	G_YesNoDialog( "Do you want to quit this ","session"))
			quit =1;
		else
		{
			cleardevice();
			draw_grid(resolution);
			redraw();
			show_mouse();
			StatusLine("Strike F1 for Help",__LINE__,__FILE__);
		}//end of don't quit
	}//bothclick
}//end of mouse processes

switch (key)
{
		case 63 : //????
			setactivepage(1);
			loadbmp("about.vsn",145,32);
			setvisualpage(1);
			getch();
			setvisualpage(0);
			cleardevice();
			draw_grid(resolution);
			redraw();
			setactivepage(0);
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
case 1102:
	error("This is a demonstration of error detection",__FILE__,__LINE__);
	break;
case 9 ://tab
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
case '\\':
case 9998:
	lines();
	break;
case 9999://
	cus_pattern();
	fillpattern = 12;
	break;
case 27 ://escape
	hide_mouse();
	if (1 == G_YesNoDialog("Start a new session ?"))
			{FILE *fp;fp = fopen("draw.tmp","wt");fclose(fp);}
	cleardevice();
	closegraph();
	intro();
	draw_grid(resolution);
	redraw();
	StatusLine("Press f1 for help",__LINE__,__FILE__);
	show_mouse();
	break;
case 1060 : //save using F2
	StatusLine("Type a name to save the given file",__LINE__,__FILE__);
	{
	char *buffer = (char *)calloc(1,20);
	int c = 0;
	G_input_box(buffer,"Save a File","Please enter the name","of the file to be saved");
	while(buffer[c] != NULL && buffer[c] != '.' && c < 9)
		c++;

	buffer[c] = NULL;
	strcat(buffer,".drw");
	fc("draw.tmp",NULL,"tmp.tmp");
	rename("tmp.tmp",buffer);

	buffer[c] = NULL;
	strcat(buffer,".ojt");
	fc("object.tmp",NULL,"tmp.tmp");
	rename("tmp.tmp",buffer);

	buffer[c] = NULL;strcat(buffer,".cde");
	fc("code.tmp",NULL,"tmp.tmp");
	rename("tmp.tmp",buffer);
	free(buffer);
	}
	cleardevice();
	draw_grid(resolution);
	redraw();
	break;
case 'd':
case 'D':
	mouse = status();
	mouse_present();
	loadcur("cursor","word",0,0);
	cleardevice();
	draw_grid(resolution);
	redraw();
	position_mouse(mouse.x,mouse.y);
	StatusLine("Press f1 for help",__LINE__,__FILE__);
	show_mouse();break;
case 1004:
			hide_mouse();
			loadbmp("quick1.vsn",0,0);
			getch();
			loadbmp("quick2.vsn",0,0);
			getch();
			loadbmp("quick3.vsn",0,0);
			getch();
			loadbmp("quick4.vsn",0,0);
			getch();
			cleardevice();
			draw_grid(resolution);
			redraw();
			show_mouse();
			StatusLine("Quick Reference card displayed",__LINE__,__FILE__);
			break;
case 19:
	o_bmp();break;
case 3:
	o_circle(2);
	break;
case 16:
	o_poly(1);break;
case 'i':
	print();break;
case 12:
	o_poly(0);break;
case 18:
	o_line(2);break;
case 'C':
case 'c':
	o_circle(0);break;
case 'p':
case 'P':
	o_circle(1);break;
case 'l':
case 'L':
	o_line(0);break;
case 21:
case 22:
case 23:
	StatusLine("Generating code for the lines",__LINE__,__FILE__);
	char *path = (char *)calloc(1,100);
	strcpy(path,"");
	G_input_box(path,"Code Generate Dialog","Enter a valid directory","to save the program","",20);
	mkdir(path);
	closegraph();
	if (key == 21)
		spawnl(P_WAIT,"ccoder.exe",path,path,NULL);
	else if (key == 22)
		spawnl(P_WAIT,"cppcoder.exe",path,path,NULL);
	else if (key == 23)
		spawnl(P_WAIT,"jcoder.exe",path,path,NULL);

	strcat(path,"\\prog.cpp");
	fc("code",NULL,path);
	hide_mouse();
	intro();
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
	{
	char *buffer = (char *)calloc(1,20);
	int c = 0;
	G_input_box(buffer,"Open new File","Please enter the name","of the file to be opened");
	while(buffer[c] != NULL && buffer[c] != '.' && c < 9)
		c++;
	remove("draw.tmp");remove("object.tmp");remove("code.tmp");
	buffer[c] = NULL;strcat(buffer,".drw");rename(buffer,"draw.tmp");
	buffer[c] = NULL;strcat(buffer,".ojt");rename(buffer,"object.tmp");
	buffer[c] = NULL;strcat(buffer,".cde");rename(buffer,"code.tmp");
	hide_mouse();
	draw_grid(resolution);
	redraw();
	StatusLine("Press f1 for help",__LINE__,__FILE__);
	show_mouse();
	{FILE *fp;fp = fopen("draw.tmp","at");fclose(fp);}
	{FILE *fp;fp = fopen("object.tmp","at");fclose(fp);}

	free(buffer);
	break;
	}
case '`':
	properties();break;
case 'r':
case 'R':
	o_line(1);break;
case 1059: // help
	closegraph();
	spawnl(P_WAIT,"readme.com",NULL);
	intro();
	draw_grid(resolution);
	redraw();
	mouse_present();
	show_mouse();
	break;
case 'f':
case 'F':
	paint();
	break;
case 't':
case 'T':
	text();break;
case 'e':
	codegen();
	struct ffblk ffblk;
	int done;
	done = findfirst("codehere.tmp",&ffblk,0);
	if (done != 0)
		{
		cleardevice();
		mouse_present();
		draw_grid(resolution);
		redraw();
		show_mouse();
		break;
		}

	StatusLine("Cannot find the editor. Please reinstall the software",__LINE__,__FILE__);
	closegraph();
	spawnl(P_WAIT,"edit","codehere","codehere.tmp",NULL);
	fc("code.tmp","codehere.tmp","aaa.tmp");
	remove("code.tmp");
	rename("aaa.tmp","code.tmp");
	remove("codehere.tmp");
	remove("ttt.tmp");
	# ifdef AXE
		getch();
	#endif
	hide_mouse();
	intro();
	draw_grid(resolution);
	redraw();
	mouse_present();
	show_mouse();
	break;
case 12020:
	undelete();
	StatusLine("Object Undeleted....",__LINE__,__FILE__);
	break;
case 2000:
	attr();
	remove("objtmp.tmp");
	break;
case 5000:
case 1083://delete
case 'S':
case 's':
		selector();
		hide_mouse();
		cleardevice();
		draw_grid(resolution);
		redraw();
		setactivepage(1);
		cleardevice();
		draw_grid(resolution);
		redraw();
		setactivepage(0);
		show_mouse();
		StatusLine("Press F1 to continue",__LINE__,__FILE__);
		break;
}// end of switch case
key=0;
fflush(stdin);
}//end of main loop body
if (1 == G_YesNoDialog("Do you want to save","your work  ??"))
	{
	char *b = (char *)calloc(1,30);
	cleardevice();
	G_input_box(b,"Save file Dialog","Enter the filename");
	rename("draw.tmp",b);
	free(b);
	}//end of saving the work
remove("draw.tmp");
remove("object.tmp");
remove("code.tmp");
remove("undel.tmp");
cleardevice();
closegraph();
return 0;
}

