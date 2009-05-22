# define max(a,b) a>b ? a:b
# define min(a,b) a<b ? a:b
# define FORE 13
# define BACK 5

#include <math.h>
#include <dos.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <mouse.h>
# include <string.h>
# include <button.cls>
# include <alloc.h>

void intro();
void redraw();
void create_cursor();
void create_grid();
void edit(char *,int,int,int);
void writeani(const char *fname);
char word[64];

	int aniflag = 1;
	int cur[16][16];
	int back[16][16];
	int hotx=0,hoty=0;
	char curlib[100];
	int curcount= 0,curtotal=0;

void StatusLine(char *text)
{
static char msg1[100];
setcolor(0);
putpixel(getmaxx()/2,(getmaxy()-textheight(text))/2,7);
settextjustify(1,0);
if (strcmp(msg1,text) != 0)
	{
	setcolor(7);
	outtextxy(getmaxx()/2,getmaxy() - textheight(text)/2,msg1);
	setcolor(0);
	outtextxy(getmaxx()/2,getmaxy() - textheight(text)/2,text);
	strncpy(msg1,text,100);
	}//end of if statement
	settextjustify(LEFT_TEXT,TOP_TEXT);
}//end of staus line


int main(void)
{

	intro();
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
		for (int q=0;q<16;q++)
			for (int w=0;w<16;w++)
				{
				back[q][w] =0;
				cur[q][w] = 0;
				}//end of printing the word

	char temp[103];
	sprintf(temp,"Hot %c",15);
	button hot(570,270,620,320,temp);
	button ani(570,330,620,380,"Anim");
	button copy(160,410,140+150,390,"To Library");
	button lib(140+160,410,450,390,"Change library");
	button create(10,390,150,440,"Exit");
	button file(160,420,310+140,440,"Output to file ...");
	button del(460,390,460+140,440,"Delete cursor");

	sprintf(temp,"%c",27);button fleft(0,290,50,270,temp);
	sprintf(temp,"%c",26);button fright(60,290,110,270,temp);
	sprintf(temp,"%c",24);button fup(130,290,180,270,temp),ffill(130,300,240,320,"Fill All");
	sprintf(temp,"%c",25);button fdown(190,290,240,270,temp),fclear(0,300,110,320,"Clear All");

	button test(250,90,310,115,"Test");
	button reset(250,150,310,125,"Reset");
	button prev(250,10,310,70,"Prev");
	button next(250,230,310,170,"Next");

	sprintf(temp,"%c",27);button bleft(320 +0,290,320 +50,270,temp);
	sprintf(temp,"%c",26);button bright(320 +60,290,320 +110,270,temp);
	sprintf(temp,"%c",24);button bup(320 +130,290,320 +180,270,temp),bfill(320 +130,300,320 +240,320,"Fill All");
	sprintf(temp,"%c",25);button bdown(320 +190,290,320 +240,270,temp),bclear(320 +0,300,320 +110,320,"Clear All");
	button bcopy(570,130,620,30,"Copy");
	button bnot(570,240,620,140,"Not");

	button fcleft(0,330,110,350,"Copy to left");
	button fcright(130,330,240 ,350,"Copy to right");
	button fcup(0,360,110,380,"Copy to top");
	button fcdown(130,360,240,380,"Copy to down");
	button bcleft(320+0,330,320+110,350,"Copy to left");
	button bcright(320+130,330,240+320 ,350,"Copy to right");
	button bcup(320+0,360,320+110,380,"Copy to top");
	button bcdown(320+130,360,320+240,380,"Copy to down");
/*********************drawing starts*************************/

	setcolor(2);
	for (q=0;q <= 240; q+=15)
		{
		line(0,q,240,q);
		line(q,0,q,240);
		line(320,q,320+240,q);
		line(q+320,0,q+320,240);
		}//end of for loop*/
	setcolor(10);

	rectangle(0,0,240,240);rectangle(320,0,320+240,240);

	line(0,120,240,120);	line(320,120,320+240,120);
	line(120,0,120,240);	line(320+120,0,320+120,240);
	setlinestyle(3,0,1);
	line(0,60,240,60);	line(320,60,320+240,60);
	line(0,180,240,180);	line(320,180,320+240,180);
	setlinestyle(2,0,1);
	line(60,0,60,240);	line(320+60,0,320+60,240);
	line(180,0,180,240);	line(320+180,0,320+180,240);
	setfillstyle(SOLID_FILL,7);
	floodfill(241,241,10);
	button t(250,270,310,380," ");t.draw();
	setlinestyle(0,0,1);
	setfillstyle(SOLID_FILL,14);
	for (int i=0;i < 16;i++)
		{
		setcolor(i);
		line(251,271+i,309,271+i);
		}
	setlinestyle(0,0,3);
	for (i=0;i < 16;i++)
		{
		setcolor(i);
		line(251,287+i*3,309,287+i*3);
		}
	setfillstyle(SOLID_FILL,13);
	bar(251,336,309,379);
	del.draw();lib.draw();ani.draw();
	bcopy.draw();fcup.draw();fcright.draw();
	fcleft.draw();fcdown.draw();
	bcup.draw();bcright.draw();
	bcleft.draw();bcdown.draw();
	prev.draw();next.draw();
	bnot.draw();reset.draw();
	hot.draw();
	test.draw();
	file.draw();
	bfill.draw();
	bclear.draw();
	bleft.draw();bright.draw();
	bup.draw();bdown.draw();
	copy.draw();
	create.draw();ffill.draw();
	create.up();fclear.draw();
	fleft.draw();fright.draw();
	fup.draw();fdown.draw();
	t.depress();
///////////**********************************///////////
	mouse_status mouse = {0,0,0};
	show_mouse();
	int quit = 0;
	quit = 0;

	while (!quit)
	{
		mouse = status();
		gotoxy(72,1);
		printf("(%3d,%3d)",mouse.x,mouse.y);
		int key;
		sprintf(temp,"Change cursor library. Current library :%s %3d",curlib,curtotal);

if (test.in(mouse.x,mouse.y)) StatusLine("Change current cursor to developed cursor");
else if (reset.in(mouse.x,mouse.y)) StatusLine("Reset the cursor to pointer");
else if (prev.in(mouse.x,mouse.y)) StatusLine("Load Previous cursor form library");
else if (next.in(mouse.x,mouse.y)) StatusLine("Load next cursor from library");
else if (hot.in(mouse.x,mouse.y)) StatusLine("Change the Hotspot in Cursor - Hotspot Mode");
else if (copy.in(mouse.x,mouse.y)) StatusLine("Copy the cursor string as char word[64] ={ ...} to cursor.c");
else if (file.in(mouse.x,mouse.y)) StatusLine("Append the code to change cursor in a file");
else if (create.in(mouse.x,mouse.y)) StatusLine("Exit the Software - Your change may not be saved !");
else if (fright.in(mouse.x,mouse.y)) StatusLine("Mirror left half to right half");
else if (fleft.in(mouse.x,mouse.y)) StatusLine("Mirror right half to left half");
else if (fup.in(mouse.x,mouse.y)) StatusLine("Mirror Bottom half to top half");
else if (fdown.in(mouse.x,mouse.y)) StatusLine("Mirror Top half to Bottom Half");
else if (bright.in(mouse.x,mouse.y)) StatusLine("Mirror left half to right half");
else if (bleft.in(mouse.x,mouse.y)) StatusLine("Mirror right half to left half");
else if (bup.in(mouse.x,mouse.y)) StatusLine("Mirror Bottom half to top half");
else if (bdown.in(mouse.x,mouse.y)) StatusLine("Mirror Top half to Bottom Half");
else if (fcleft.in(mouse.x,mouse.y)) StatusLine("Copy Right Side to Left Side");
else if (fcright.in(mouse.x,mouse.y)) StatusLine("Copy Left Side to Right Side");
else if (fcdown.in(mouse.x,mouse.y)) StatusLine("Copy Top to Bottom");
else if (fcup.in(mouse.x,mouse.y)) StatusLine("Copy Bottom to Top");
else if (bcleft.in(mouse.x,mouse.y)) StatusLine("Copy Right Side to Left Side");
else if (bcright.in(mouse.x,mouse.y)) StatusLine("Copy Left Side to Right Side");
else if (bcdown.in(mouse.x,mouse.y)) StatusLine("Copy Top to Bottom");
else if (bcup.in(mouse.x,mouse.y)) StatusLine("Copy Bottom to Top");
else if (bcopy.in(mouse.x,mouse.y)) StatusLine("Copy Cursor mask to Screen Mask");
else if (bnot.in(mouse.x,mouse.y)) StatusLine("Copy Inverted cursor mask to screen mask");
else if (ffill.in(mouse.x,mouse.y)) StatusLine("Fill the current area");
else if (fclear.in(mouse.x,mouse.y)) StatusLine("Clear the current area");
else if (bfill.in(mouse.x,mouse.y)) StatusLine("Fill the current area");
else if (bclear.in(mouse.x,mouse.y)) StatusLine("Clear the current area");
else if (t.in(mouse.x,mouse.y)) StatusLine("Test Area - Click here for mouse tests");
else if (del.in(mouse.x,mouse.y)) StatusLine("Delete the current cursor form library");
else if (ani.in(mouse.x,mouse.y)) StatusLine("Switches between animated and static cursor modes");
else if (lib.in(mouse.x,mouse.y)) StatusLine(temp);

if (inarea(mouse.x,mouse.y,0,0,240,240))
{
	StatusLine("Click in this area to create cursor mask area");
	int x,y;
	x = mouse.x/15;
	y = mouse.y /15;
	if (mouse.button == RIGHT_CLICK)
	{
		setfillstyle(SOLID_FILL,0);
		hide_mouse();
		bar(15*x+1,15*y+1,x*15+14,y*15+14);
		cur[x][y] = 0;
		show_mouse();
	}//end of right click
	if (mouse.button == LEFT_CLICK)
	{
		setfillstyle(SOLID_FILL,FORE);
		hide_mouse();
		bar(15*x+1,15*y+1,x*15+14,y*15+14);
		cur[x][y] = 1;
		show_mouse();
	}//end of left click
}//in the cursor mask area

if (inarea(mouse.x,mouse.y,320,0,320+240,240))
{
	StatusLine("Click in this area to create screen mask area");
	int x,y;
	x = (mouse.x-320)/15;
	y = mouse.y /15;

	if (mouse.button == RIGHT_CLICK)
	{
		setfillstyle(SOLID_FILL,0);
		hide_mouse();
		bar(15*x+1+320,15*y+1,x*15+14+320,y*15+14);
		back[x][y] = 0;
		show_mouse();
	}//end of right click

	if (mouse.button == LEFT_CLICK)
	{
		setfillstyle(SOLID_FILL,BACK);
		hide_mouse();
		bar(15*x+1+320,15*y+1,x*15+14+320,y*15+14);
		back[x][y] = 1;
		show_mouse();
	}//end of left click
}//end of screen mask
if (mouse.button == LEFT_CLICK)
{
			if (lib.in(mouse.x,mouse.y))
			{
				hide_mouse();
				strcpy(lib.text," ");
				lib.draw();
				lib.depress();
				show_mouse();
				strcpy(curlib,"");
				edit(curlib,8,140+162,395);
				hide_mouse();
				lib.draw();
				strcpy(lib.text,"Change Library");
				char *buffer = (char *)calloc(1,15);
				for (int i=0;*(curlib+i) != '.' && *(curlib+i) != NULL;i++)
					buffer[i] = *(curlib+i);
				strcat(buffer,".cpp");
				strcpy(curlib,buffer);
				free(buffer);
				lib.draw();
				show_mouse();
				FILE *fp;
				fp =fopen(curlib,"rt");
				int ch=0;
				curtotal = 0;
				if (fp != NULL)
				{
					while (!feof(fp))
					{
						ch = fgetc(fp);
						if (ch == '{')
						curtotal++;
							}//end of file acheived
						fclose(fp);
					}//file available
			}//end of changing the library

			if (hot.in(mouse.x,mouse.y))
			{
			strcpy(hot.text,"Draw");
			hide_mouse();
			hot.draw();
			hot.depress();
			show_mouse();
			mouse_status mouse;
			mouse = status();
			position_mouse(120,120);
			int hotx1,hoty1;
			do
			{
				mouse = status();
				if (inarea(mouse.x,mouse.y,0,0,240,240) && mouse.button == LEFT_CLICK)
				{
					hotx1=hotx;hoty1=hoty;
					hotx=mouse.x/15;
					hoty=mouse.y/15;
					hide_mouse();
					if (cur[hotx1][hoty1])
						setfillstyle(SOLID_FILL,FORE);
					else
						setfillstyle(SOLID_FILL,0);
					bar(15*hotx1+1,15*hoty1+1,15*hotx1+14,15*hoty1+14);
					setfillstyle(INTERLEAVE_FILL,14);
					bar(15*hotx+1,15*hoty+1,15*hotx+14,15*hoty+14);
					show_mouse();
				}//inside area
			}while(!(hot.in(mouse.x,mouse.y) && mouse.button == LEFT_CLICK));

			xclick();
			strcpy(hot.text,"Hot");
			hide_mouse();
			hot.draw();
			show_mouse();
			}//end of marking the hot spot
			if (ani.lclick(mouse.x,mouse.y))
			{
			hide_mouse();
			if (aniflag == 1)
				{
					aniflag = 0;
					strcpy(ani.text,"Stat");
					ani.draw();
					ani.depress();
				}//end of changing to static cursor
			else
				{
					aniflag = 1;
					strcpy(ani.text,"Anim");
					ani.draw();
				}//end of the other case
			show_mouse();
			}//end of switching modes

			if (del.lclick(mouse.x,mouse.y) && curtotal > 0)
			{
				FILE *fp,*tmp;
				fp = fopen(curlib,"rt");
				tmp = fopen("tmp.tmp","wt");
					if (!tmp) exit(1);
				if (fp != NULL)
				{
					char *buf = (char*)calloc(1,300);
					for (int c=0;c < curcount-1;c++)
						{
						strcpy(buf,NULL);
						fgets(buf,300,fp);
						fprintf(tmp,"%s",buf);
						}//end of rewriting file
						fgets(buf,300,fp);
						strcpy(buf,NULL);
						while (!feof(fp))
						{
						strcpy(buf,NULL);
						fgets(buf,300,fp);
						fprintf(tmp,"%s",buf);
						}//next session of read - write
				free(buf);
				fclose(fp);
				fclose(tmp);
				remove(curlib);
				rename("tmp.tmp",curlib);
				curtotal --;
				curcount = 0;
				}//file is avaliable
			}//end of deleting current cursor;


			if (create.lclick(mouse.x,mouse.y))
				quit = 1;

			if (fcright.lclick(mouse.x,mouse.y))
				{
				for (int a=0;a<8;a++)
					for (int b=0;b < 16;b++)
						cur[a+8][b] = cur[a][b];
				}
			if (fcleft.lclick(mouse.x,mouse.y))
				{
				for (int a=8;a<16;a++)
					for (int b=0;b < 16;b++)
						cur[a-8][b] = cur [a][b];
				}
			if (fcdown.lclick(mouse.x,mouse.y))
				{
				for (int a=0;a<16;a++)
					for (int b=0;b < 8;b++)
						cur[a][b+8] = cur[a][b];
				}
			if (fcup.lclick(mouse.x,mouse.y))
				{
				for (int a=0;a<16;a++)
					for (int b=8;b < 16;b++)
						cur[a][b-8] = cur[a][b];
				}


			if (bcright.lclick(mouse.x,mouse.y))
				{
				for (int a=0;a<8;a++)
					for (int b=0;b < 16;b++)
						back[a+8][b] = back[a][b];
				}
			if (bcleft.lclick(mouse.x,mouse.y))
				{
				for (int a=8;a<16;a++)
					for (int b=0;b < 16;b++)
						back[a-8][b] = back[a][b];
				}
			if (bcdown.lclick(mouse.x,mouse.y))
				{
				for (int a=0;a<16;a++)
					for (int b=0;b < 8;b++)
						back[a][b+8] = back[a][b];
				}
			if (bcup.lclick(mouse.x,mouse.y))
				{
				for (int a=0;a<16;a++)
					for (int b=8;b < 16;b++)
						back[a][b-8] = back[a][b];
				}

			if (bnot.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
					if (cur[a][b] == 0)
						back[a][b] = 1;
					else
						back[a][b] = 0;
			}//end of previous

			if (bcopy.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
					back[a][b] = cur[a][b];

			}//end of previous
			if (bleft.lclick(mouse.x,mouse.y))
			 {
			 for (int a=8;a<16;a++)
				for (int b=0;b < 16;b++)
					back[7-a+8][b] = back[a][b];
			}//end of previous
			if (bright.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<8;a++)
				for (int b=0;b < 16;b++)
					back[7-a+8][b] = back[a][b];
			}//end of previous
			if (bup.lclick(mouse.x,mouse.y))
			{
			 for (int a=0;a<16;a++)
				for (int b=8;b < 16;b++)
					back[a][7-b+8] = back[a][b];
			}//end of previous
			if (bdown.lclick(mouse.x,mouse.y))
			{
			 for (int a=0;a<16;a++)
				for (int b=0;b < 8;b++)
					back[a][7-b+8] = back[a][b];
			}//end of previous
			if (bfill.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
					back[a][b] = 1;

			}//end of previous
			if (bclear.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
					back[a][b] = 0;
			}//end of previous


			if (fleft.lclick(mouse.x,mouse.y))
			 {
			 for (int a=8;a<16;a++)
				for (int b=0;b < 16;b++)
					cur[7-a+8][b] = cur[a][b];
			}//end of previous
			if (fright.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<8;a++)
				for (int b=0;b < 16;b++)
					cur[7-a+8][b] = cur[a][b];
			}//end of previous
			if (fup.lclick(mouse.x,mouse.y))
			{
			 for (int a=0;a<16;a++)
				for (int b=8;b < 16;b++)
					cur[a][7-b+8] = cur[a][b];
			}//end of previous
			if (fdown.lclick(mouse.x,mouse.y))
			{
			 for (int a=0;a<16;a++)
				for (int b=0;b < 8;b++)
					cur[a][7-b+8] = cur[a][b];
			}//end of previous
			if (ffill.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
					cur[a][b] = 1;

			}//end of previous
			if (fclear.lclick(mouse.x,mouse.y))
			{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
					cur[a][b] = 0;
			}//end of previous

			if (prev.lclick(mouse.x,mouse.y))
			{
				FILE *fp;
				if (curcount < 0)
					curcount = curtotal-1;
				fp = fopen(curlib,"rt");
				if (fp != NULL)
					{
					int c=0,ch=0;
					int nowcount=0;
					while ( !feof(fp) && nowcount < curtotal-curcount)
						{
						while (c != '{')
							c = fgetc(fp);
						for (ch=0;ch <64 && !feof(fp);ch++)
							{
							c=0;
							word[ch] = 0;
							while (c != '}' && c != ',')
								{
								c = fgetc(fp);
								if (c >= '0' && c <= '9')
									word[ch] = word[ch] * 10 + c-'0';
								}
							}//end of parsing 64 inpouts
						nowcount++;
						}//end ofopenming file
					fclose(fp);
					}//file available
				curcount--;
				create_grid();
			}//end of previous
			if (next.lclick(mouse.x,mouse.y))
			{
				FILE *fp;
				if (curcount >= curtotal)
					curcount = 0;
				fp = fopen(curlib,"rt");
				if (fp != NULL)
					{
					int c=0,ch=0;
					int nowcount=0;
					while ( !feof(fp) && nowcount <= curcount)
						{
						while (c != '{' && !feof(fp))
							c = fgetc(fp);
						for (ch=0;ch <64 && !feof(fp);ch++)
							{
							c=0;
							word[ch] = 0;
							while (c != '}' && c != ',' && !feof(fp))
								{
								c = fgetc(fp);
								if (c >= '0' && c <= '9')
									word[ch] = word[ch] * 10 + c-'0';
								}
							}//end of parsing 64 inpouts
						nowcount++;
						}//end ofopenming file
					fclose(fp);
					}//file available
				curcount++;
				create_grid();
			}//end of previous

			if (t.lclick(mouse.x,mouse.y))
			{
			setfillstyle(SOLID_FILL,random(15));
			hide_mouse();
			fillellipse(mouse.x,mouse.y,1,1);
			show_mouse();
			t.depress();
			}//end of trest area

			if (test.lclick(mouse.x,mouse.y))
			{
			create_cursor();
			mouse_change(word,hotx,hoty);
			}//end of testing

			if (reset.lclick(mouse.x,mouse.y))
			{
			REGS ia;
			ia.x.ax = 0;
			int86(0x33,&ia,&ia);
		for (int i=0;i < 16;i++)
		{
		setcolor(i);
		line(251,271+i,309,271+i);
		}
	setlinestyle(0,0,3);
	for (i=0;i < 16;i++)
		{
		setcolor(i);
		line(251,287+i*3,309,287+i*3);
		}
	setlinestyle(0,0,1);
	setfillstyle(SOLID_FILL,13);
	bar(251,336,309,379);
			show_mouse();
			position_mouse(mouse.x,mouse.y);
			}//end of mouse.h

			if (copy.lclick(mouse.x,mouse.y))
			{
			create_cursor();
			char *fname = (char *)calloc(1,100);
			strcpy(copy.text," ");
			hide_mouse();
			copy.draw();
			copy.depress();
			show_mouse();
			edit(fname,10,165,397);
			hide_mouse();
			setfillstyle(SOLID_FILL,7);
			bar(160,410,140+150,390);
			strcpy(copy.text,"To library");
			copy.draw();
			show_mouse();
			FILE *fp;
			fp = fopen(curlib,"at");
			if (fp != NULL)
				{
				fprintf(fp,"char %s[64] = {%d",fname,word[0]);
				for (int i=1;i < 64;i++)
					fprintf(fp,",%d",word[i]);
				fprintf (fp,"};\n");
				fclose (fp);
				}//close the file
			free(fname);
			curtotal++;
			}//inside copy to clipboard

			if (file.lclick(mouse.x,mouse.y))
			{
			char *fname = (char *)calloc(1,50);
			settextstyle(12,0,1);

			strcpy(file.text," ");
			hide_mouse();
			file.draw();
			file.depress();
			show_mouse();

			edit(fname,50,165,427);
			fflush(stdin);
			hide_mouse();
			strcpy(file.text," ");
			file.draw();
			strcpy(file.text,"Output to file ...");
			file.draw();
			show_mouse();
			create_cursor();
			if (aniflag == 0)
			{
			FILE *fp;
			fp = fopen(fname,"at");
				if (fp)
				{
					fprintf(fp,"\n\nchar word[64] = {%d",word[0]);
				for (int i=1;i < 64;i++)
					fprintf(fp,",%d",word[i]);
					fprintf(fp,"};\nREGS _i;\nSREGS _s;\n_i.x.ax = 9;\n");
					fprintf(fp,"_i.x.bx = %d;\n_i.x.cx=%d;\n",hotx,hoty);
					fprintf(fp,"_i.x.dx = FP_OFF(word);\n_s.es = FP_SEG(word);\n");
					fprintf(fp,"int86x(0x33,&_i,&_i,&_s);");
					fclose(fp);
				}//end of opening file
			}//written to the static cursor
			else
				writeani(fname);
				free(fname);
			}//end of writing to fil

			if (prev.lclick(mouse.x,mouse.y))
			{
			}//end of mouse.h

for (int a=0;a<16;a++)
	for (int b=0;b < 16;b++)
		{
		if (cur[a][b] == 1)
			setfillstyle(SOLID_FILL,FORE);
		else if (cur[a][b] == 0)
			setfillstyle(SOLID_FILL,0);
		bar (a*15+1,b*15+1,a*15+14,b*15+14);
		if (back[a][b] == 1)
			setfillstyle(SOLID_FILL,BACK);
		else if (back[a][b] == 0)
			setfillstyle(SOLID_FILL,0);
		bar (a*15+1+320,b*15+1,a*15+14+320,b*15+14);
		}// end of redrawing

}//end of lieft click
	}//end of while loop
closegraph();
return 0;
}

void create_grid()
{
	int curs[16][16];
	for (int c=0;c < 16;c++)
		for (int a=0;a < 16;a++)
			cur[a][c] = back[a][c] =0;

	int buf;
	for (c=0;c < 32;c++)
		{
			buf = (unsigned char)word[c];

			for (a=0;a < 8 ;a++)
			{
			curs[a][c/2] = buf %2;
			buf /= 2;
			}//end of  for loop
			c++;
			buf = (unsigned char)word[c];

			for (a=8; a  < 16;a++)
			{
			curs[a][c/2] = buf %2;
			buf /= 2;
			}//end of  for loop
		}//end of conversions

			for (a=0;a<16;a++)
				for (c=0;c < 16;c++)
					back[a][c] = curs[15-a][c];
	for (c=0;c < 32;c++)
		{
			buf = (unsigned char)word[c+32];

			for (a=0;a < 8 ;a++)
			{
			curs[a][c/2] = buf %2;
			buf /= 2;
			}//end of  for loop
			c++;
			buf = (unsigned char)word[c+32];

			for (a=8; a  < 16;a++)
			{
			curs[a][c/2] = buf %2;
			buf /= 2;
			}//end of  for loop
		}//end of conversions

			for (a=0;a<16;a++)
				for (c=0;c < 16;c++)
					cur[a][c] = curs[15-a][c];

}//end of function creation

void create_cursor()
{
	for (int x=0;x < 64;x++)
	word[x] = 0;
	int cury[16][16];
int c=0;

			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
				  cury[15-a][b]=back[a][b];

	for (x=0;x<16;x++,c++)
	{
		for (int y1=0;y1<8;y1++)
			word[c] = word[c] +pow(2,y1)*cury[y1][x];
		c++;
		for (y1=8;y1<16;y1++)
			word[c] = word[c] +pow(2,y1-8)*cury[y1][x];
	}///end of parsing all lines             */
{
			for (int a=0;a<16;a++)
				for (int b=0;b < 16;b++)
				  cury[15-a][b]=cur[a][b];
}
	c=32;
	for (x=0;x<16;x++,c++)
	{
		for (int y1=0;y1<=8;y1++)
			word[c] = word[c] +pow(2,y1)*cury[y1][x];
		c++;
		for (y1=8;y1<=16;y1++)
			word[c] = word[c] +pow(2,y1-8)*cury[y1][x];
	}///end of parsing all lines

}

void edit(char *fname,int max,int x1,int y1)
{
				int key=0;
				int count =0;
				while (key != 13)
				{
				key = getch();
				char a[2];
					if (key == 8 && strlen(fname) > 0)
						{
						char *b = (char *)calloc(1,strlen(fname)+3);
						strncpy(b,fname,strlen(fname)-1);
						setcolor(7);
						outtextxy(x1,y1,fname);
						strcpy(fname,b);
						setcolor(0);
						outtextxy(x1,y1,fname);
						free(b);
						count--;
						}//end of backspace
					if (key > 32 && key < 126 && count < max)
						{
						count++;
						sprintf(a,"%c",key);
						strcat(fname,a);
						hide_mouse();
						setcolor(0);
						outtextxy(x1,y1,fname);
						position_mouse(x1+10+textwidth(fname),y1);
						show_mouse();
						}
				}//end of word typed

}//end of tex editing


void intro()
{
	char buffer[100];
	int count=0;
	FILE *fp;
	fp = fopen("help.txt","rt");
	printf("Mouseware - tool for creating cursors in DOS \n\t\tProgramming - its what your fingers are for ... \n");
	if (fp != NULL)
	{
		while (!feof(fp) || kbhit())
			{
			fgets(buffer,100,fp);
			count ++;
			if (strcmp(buffer,"The cursor library is\n") == 0)
				{
				strcpy(buffer,"");
				fscanf(fp,"%s",curlib);
				}
			if (count > 24)
				{
				printf("\n---------------  Press a key for next page --------------\n");
				count = 0;
				getch();
				}
			printf("%s ",buffer);
			}//end of file attained
		printf("\bThe current cursor library is <%s>\n",curlib);
		fclose(fp);
	}//end of file opening
	puts("Press any key to continue .......");
	fp =fopen(curlib,"rt");
	int ch=0;
	if (fp != NULL)
	{
		while (!feof(fp))
			{
				ch = fgetc(fp);
				if (ch == '{')
					curtotal++;
			}//end of file acheived
	fclose(fp);
	}//file available

	getch();
}//end of inreoduction

void writeani(const char *fname)
{
	FILE *fp,*lib;
	fp = fopen(fname,"at");
	lib = fopen(curlib,"rt");
	if (fp == NULL || lib == NULL)
		return;
	fprintf(fp,"char word[%d][64] = {\n",curtotal);
	unsigned char ch=10;
	for (int i=0;i < curtotal;i++)
	{
		if (i != 0)
			fprintf(fp,",\n");
		while (ch != '=')
			ch = fgetc(lib);
		while (ch != '}' )
			{
			ch = fgetc(lib);
			fputc(ch,fp);
			}//written the actual data
	}//end of while (!feof(lib))
	fprintf(fp,"};");
	fclose(fp);
	fclose(lib);
}//end of writing the animated cursor to the file