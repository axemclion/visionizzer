# define XSTART 10
# define YSTART 5
# define XEND 70
# define YEND 20

void scroll(int,int,int,int);

int show_code(char *fname)
{
	setfillstyle(SOLID_FILL,0);
	setlinestyle(0,0,3);
	bar(60,55,565,325);
	rectangle(60,52,565,325);
	line(60,297,565,297);
	setcolor(7);
	rectangle(62,54,567,327);
	line(62,299,565,299);
	gotoxy(XSTART,YEND+3);printf("Program for : %16s",fname);
	setlinestyle(0,0,1);
	FILE *fp;
	fp = fopen(fname,"rt");
	if (!fp)
		return -1;
	int buf = 0;
	int x,y;
	x = XSTART+1;
	y = YSTART;
	fflush(stdin);
	while (!feof(fp) && !kbhit())
	{
		buf = fgetc(fp);
		x++;
		if (x > XEND) {y++;x=XSTART+1;}
		if (buf == '\n') {x= XSTART+1;y++;buf = ' ';}
		if (y > YEND)
			{
			scroll(XSTART,YSTART,XEND,YEND);
			for (int i= XSTART+1;i <= XEND;i++)
				{
				gotoxy(i,YEND);
				printf(" ");
				}//end of this for loop
			y= YEND;
			}

		gotoxy(x,y);
		{REGS i;i.h.bh=0;i.h.bl=14;i.x.cx=1;i.h.al='²';i.h.ah=9;int86(0x10,&i,&i);}
		delay(random(40));
		gotoxy(x,y); printf("%c",buf);
	}
	gotoxy(x,y);{REGS i;i.h.bh=0;i.h.bl=142;i.x.cx=1;i.h.al='²';i.h.ah=9;int86(0x10,&i,&i);}
	getch();
	fclose(fp);
	return 0;
}//end of code showing

void scroll(int x1,int y1,int x2,int y2)
{
	REGS i;
	i.h.ah = 6;
	i.h.al =1;
	i.h.bh = 0;
	i.h.ch = y1-1;
	i.h.cl = x1;
	i.h.dh = y2;
	i.h.dl = x2-1;
	int86(0x10,&i,&i);
}//end of the scrolling function

void easter_egg()
{
	show_mouse();

	int addx=1;int addy=1;
	mouse_status mouse;
	mouse = status();
			char word1[64] = {255,15,255,55,255,91,191,109,159,181,143,217,175,225,183,254,55,255,59,224,219,247,237,249,117,254,154,255,228,255,248,255,0,240,0,200,0,164,64,146,96,74,112,38,80,30,72,1,200,0,196,31,36,8,18,6,138,1,101,0,27,0,7,0};
			char word2[64] = {248,255,228,255,154,255,117,254,237,249,219,247,59,224,55,255,183,254,175,225,175,217,159,181,191,109,255,91,255,55,255,15,7,0,27,0,101,0,138,1,18,6,36,8,196,31,200,0,72,1,80,30,80,38,96,74,64,146,0,164,0,200,0,240};
			char word3[64] = {240,255,236,255,218,255,182,253,173,249,155,245,135,245,127,237,255,236,3,220,247,219,207,183,63,175,255,92,255,51,255,15,15,0,19,0,37,0,73,2,82,6,100,10,120,10,128,18,0,19,252,35,8,36,48,72,192,80,0,163,0,204,0,240};
			char word4[64] = {255,31,255,7,255,1,127,128,31,128,15,192,63,192,127,224,15,224,51,241,89,243,109,251,182,255,154,255,205,255,242,255,0,224,0,216,0,166,128,81,96,72,48,36,192,34,128,17,240,19,204,10,166,12,146,4,73,0,101,0,50,0,13,0};

	while (!kbhit())//&& x.button != LEFT_CLICK);
	{
		delay(3);
		mouse.x=mouse.x+addx;
		mouse.y=mouse.y+addy;
		if (mouse.x >= getmaxx())
			addx = -random(2);
		if (mouse.x <= 0)
			addx = random(2);
		if (mouse.y >= getmaxy())
			addy = -random(2);
		if (mouse.y <= 0)
			addy=random(2);
		if (mouse.x <= 0 || mouse.y <=0 || mouse.x >=getmaxx() || mouse.y >=getmaxy())
			{
			if (addx >0  && addy > 0)
					mouse_change(word1);
			else if (addx >0  && addy < 0)
					mouse_change(word2);
			else if (addx <0  && addy > 0)
					mouse_change(word3);
			else if (addx <0  && addy < 0)
					mouse_change(word4);
			}//end of changing the mouse
		position_mouse(mouse.x,mouse.y);
	}//end of animation
}//end of easter egg*/

