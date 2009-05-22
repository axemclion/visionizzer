# define MULT 10
# define DELAY 5
# define CURSOR '_'
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
		{REGS i;i.h.bh=0;i.h.bl=14;i.x.cx=1;i.h.al=CURSOR;i.h.ah=9;int86(0x10,&i,&i);}
		delay(random(DELAY) * MULT);
		gotoxy(x,y); printf("%c",buf);
	}
	gotoxy(x,y);{REGS i;i.h.bh=0;i.h.bl=142;i.x.cx=1;i.h.al=CURSOR;i.h.ah=9;int86(0x10,&i,&i);}
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


int fc(char *file1,char *file2,char *dest)
{
	FILE *src,*dst;
	src = fopen(file1,"rt");
	dst = fopen(dest,"at");
	if (dst == NULL)
		return 1;
	char *buffer = (char *)calloc(1,100);
	if (src != NULL)
	{
		fgets(buffer,100,src);
		do{
			fprintf(dst,"%s",buffer);
			fgets(buffer,100,src);
		}while (!feof(src));
		fclose(src);
	}

	src = fopen(file2,"rt");
	if (src != NULL)
	{
		fgets(buffer,100,src);
		do{
			fprintf(dst,"%s",buffer);
			fgets(buffer,100,src);
		}while (!feof(src));
		fclose(src);
	}
free(buffer);
fclose(dst);

return 0;
}

