extern unsigned int color;
extern unsigned int line_style;
extern unsigned int thickness;
extern int resolution;
extern unsigned int fillpattern;
extern unsigned int fillcolor;
extern unsigned int font,direction,size;
extern char cuspattern[8];

void draw_all();
void StatusLine(const char *msg,int line,char *file);

void redraw()
{
	setlinestyle(0,0,1);
	draw_all();
	hide_mouse();
	FILE *fp;
	int x,y,x1,y1,sr,er,c,t,fpattern,fstyle,ls;
	setcolor(15);
	x=y=x1=y1=sr=er=c=t=fpattern=fstyle=ls=0;
	if ((fp=fopen("\\circ.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&sr,&er,&x1,&y1,&c,&t,&fpattern,&fstyle);
	setcolor(c);
	setlinestyle(0,0,t);
	ellipse(x,y,sr,er,x1,y1);
	}
	fclose(fp);
}///////////////////end ofcircle
	x=y=x1=y1=sr=er=c=t=fpattern=fstyle=ls=0;
	if ((fp=fopen("\\rect.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&x1,&y1,&c,&t,&ls);
	setcolor(c);
	setlinestyle(ls,0,t);
	rectangle(x,y,x1,y1);
	}
	fclose(fp);
}////////////end of recetangl//////////////////////////
	x=y=x1=y1=sr=er=c=t=fpattern=fstyle=ls=0;
	if ((fp=fopen("\\line.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&x1,&y1,&c,&t,&ls);
	setcolor(c);
	setlinestyle(ls,0,t);
	line(x,y,x1,y1);
	}
	fclose(fp);
}//end of line/////////////////////
	x=y=x1=y1=sr=er=c=t=fpattern=fstyle=ls=0;
	if ((fp=fopen("\\pie.$$$","r+t"))!=NULL)
{
	while (!feof(fp))
	{
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&sr,&er,&x1,&y1,&c,&t,&fpattern,&fstyle);
	setfillstyle(fpattern,fstyle);
	setcolor(c);
	setlinestyle(0,0,t);
	sector(x,y,sr,er,x1,y1);
	}
	fclose(fp);
}///////////////////////////end of sector/////
	x=y=x1=y1=sr=er=c=t=fpattern=fstyle=ls=0;
	if ((fp=fopen("\\text.$$$","r+t"))!=NULL)
{
	char *res;
	res = (char *)calloc(1,100);
	*res = NULL;
	if (res == NULL) error("TEXT WRITING\nUnable to alocate res");
	while (!feof(fp))
	{
		fscanf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,%s\n",&c,&x,&y,&x1,&y1,&sr,res);
		setcolor(c);
		settextstyle(x1,y1,sr);
		char *buf;
		int c=0;
		buf = (char far*)calloc(1,100);
		if (!buf) error("ERROR Allocating buffer memory in Text module");
		*buf = *res;
		while (*(res+c) != NULL)
		{
			if (*(res+c) ==253)
				*(buf+c)=' ';
			else
				*(buf+c)=*(res+c);
			c++;
		}
		outtextxy(x,y,buf);
		free(buf);
	}//end of while
	fclose(fp);
	if (res) free (res);
}////////////////////end of text
	x=y=x1=y1=sr=er=c=t=fpattern=fstyle=ls=-1;
	if ((fp=fopen("\\fill.$$$","r+t"))!=NULL)
{
	char c1[8]={0,0,0,0,0,0,0,0};
	while (!feof(fp))
	{
	fscanf(fp,"%03d,%03d,%02d,%02d,%02d, p %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&c,&sr,&er,&c1[0],&c1[1],&c1[2],&c1[3],&c1[4],&c1[5],&c1[6],&c1[7]);
	if (!(x==-1 && y==-1 && c==-1 && x1==-1 && y1==-1))
	{
	if (er == 8)
		{
		setfillstyle(sr,12);
		floodfill(x,y,c);
		}
		if (sr == 12)
		{
			setfillpattern(c1,er);
			floodfill(x,y,c);
		}//end of cus pattern
		else
		{
		setfillstyle(sr,er);
		floodfill(x,y,c);
		}
	 }//end of emplty -file read check - if
	}//end of while
fclose(fp);
}//end of floodfill
	draw_all();
	show_mouse();
}//end of function

void paint()
{
mouse_status mouse;
mouse.button = 0;
{
char word[64] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xc0,0x3,0x40,0x2,0x40,0x2,0xc0,0x3,0x40,0x2,0xc0,0x3,0xc0,0x3,0x40,0x2,0xe0,0x7,0x10,0x8,0xf0,0xf,0xf0,0xf,0xf0,0xf,0xf0,0xf,0x50,0x5,0x50,0x5};
mouse_change(word,8,15);
}
int colx=0;
colx=color_card();

StatusLine("Select the Outline Color",__LINE__,__FILE__);

while (mouse.button == 0)
	mouse=status();

if (colx !=-1 && mouse.button == LEFT_CLICK)
	{
	hide_mouse();

	if (fillcolor == 8)
		{
		setfillstyle(fillpattern,12);
		floodfill(mouse.x,mouse.y,colx);
		}

	setfillstyle(fillpattern,fillcolor);
	floodfill(mouse.x,mouse.y,colx);

	if (fillpattern == 12)
	{
		setfillpattern(cuspattern,fillcolor);
		floodfill(mouse.x,mouse.y,colx);
	}
	show_mouse();
	FILE *fp;
	fp=fopen("\\fill.$$$","at");
	fprintf(fp,"%03d,%03d,%02d,%02d,%02d, p %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",mouse.x,mouse.y,colx,fillpattern,fillcolor,cuspattern[0],cuspattern[1],cuspattern[2],cuspattern[3],cuspattern[4],cuspattern[5],cuspattern[6],cuspattern[7]);
	fclose(fp);
	}//end of fillstyle
	mouse_change(_TARGET_CUR);
}//end of paint

void text(void)
{

setactivepage(1);
cleardevice();
draw_grid(resolution);
redraw();
setactivepage(0);
StatusLine("Current mode is text mode. Hit 'ESC' to exit text mode",__LINE__,__FILE__);
xclick();
mouse_status mouse;
mouse = click();
int key=0;
setcolor(color);
settextstyle(font,direction,size);
int x=mouse.x,y=mouse.y;

char *result;
result =(char *)calloc(1,80);
int x1,y1;
x1=x;y1=y;
mouse_change(_TEXT_CUR,1,1);
while (key != 27 )
{
show_mouse();
position_mouse(x,y);

if (kbhit())
	key=getch();

	if (x >= getmaxx())
		{
		FILE* fp;
		fp=fopen("\\text.$$$","at");
		if (fp ==NULL) fprintf(stderr,"TEXT : Word Wrap,ERROR OPENMING FILE");
		if (strlen(result) != 0) fprintf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,%s\n",color,x1,y1,font,direction,size,result);
		fclose(fp);
		strcpy(result,"");
		x=0;y=y+textheight("²");
		x1=0;y1=y;
		}

if ((key >=32 && key < 127) || key == 253)
	{
	char *buffer = (char *)calloc(1,4);
	if (!buffer) error("TEXT\nError allacating memory for buffer");
	sprintf(buffer,"%c",key);
	hide_mouse();
	outtextxy(x,y,buffer);
	strcat(result,buffer);
	show_mouse();
	x+=textwidth(buffer);
	free(buffer);
	key=0;
	}//end of printable characters if

	if (key == 8 && strlen(result) > 0)//backspace
	{
	hide_mouse();

	char *buffer=(char*)calloc(1,strlen(result)+1);
	if (!buffer) error("TEXT\nUnable to allocate memory for text screen save");
	char *sr=(char *)calloc(1,2);
	if (!sr) error("TEXT\nUnable to allocate memory for text screen save");

	*sr=*(result+strlen(result)-1);

	for (int i=0;i <strlen(result)-1;i++)
		*(buffer+i)=*(result + i);

	x=x-textwidth(sr) ;
	bar(x,y,x+textwidth(sr),y+textheight(sr)+10);
	char *scr=(char *) malloc(imagesize(x,y,x+textwidth(sr),10+y+textheight(sr)));
	setactivepage(1);
	getimage(x,y,x+textwidth(sr),y+textheight(sr)+10,scr);
	setactivepage(0);
	putimage(x,y,scr,COPY_PUT);
	free(scr);


	strcpy(result,buffer);
	free(buffer);
	free(sr);
	key= 0;
	show_mouse();
	}//end of backspace

}//end of main while

	FILE* fp;
	fp=fopen("\\text.$$$","at");
	if (fp ==NULL) fprintf(stderr,"Text : ERROR OPENMING FILE");

	char *buffer=(char*)calloc(1,100);
	if (buffer == NULL) error("ERROR in writing buffer string");

	for (int i=0;i < strlen(result);i++)
	{
		if (*(result+i) == ' ')
				*(buffer+i) = 253;
		else
				*(buffer+i) = *(result+i);
	}//end of for loop
	strcpy(result,buffer);
	free(buffer);
	if (strlen(result) != 0) fprintf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,%s\n",color,x1,y1,font,direction,size,result);
	fclose(fp);
	free(result);
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
	mouse_change(_TARGET_CUR);
}//end of text function

void o_circle(int type=0)
{
	click();
	hide_mouse();
	setactivepage(1);
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	StatusLine("Click to mark the centre of CIRCLE",__LINE__,__FILE__);
	int x,y,stangle=0,endangle=360,xradius=10,yradius=10;
	mouse_status mouse;
	mouse.button=0;
	show_mouse();
	while (!mouse.button)
	{
		mouse=status();
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);
		if (mouse.button==LEFT_CLICK)
		{x=mouse.x;y=mouse.y;}
	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button =0;

	}//end of middle click

	}//end of first click
	click();
	StatusLine("Move mouse to increase/decrease radius, arrow keys for arcs",__LINE__,__FILE__);
	setcolor(color);
	setfillstyle(fillpattern,fillcolor);
	if (fillpattern ==12)
		setfillpattern(cuspattern,fillcolor);
	setlinestyle(line_style,0,thickness);
	int x1,y1,key=0;
	mouse_present();
	{
//	char word[64] = {0x7f,0xfe,0x3f,0xfc,0x1f,0xf8,0x7f,0xfe,0x7f,0xfe,0x7b,0xde,0xf9,0x9f,0x40,0x2,0x40,0x2,0xf9,0x9f,0x7b,0xde,0x7f,0xfe,0x7f,0xfe,0x1f,0xf8,0x3f,0xfc,0x7f,0xfe,0x80,0x1,0xc0,0x3,0xe0,0x7,0x80,0x1,0x80,0x1,0x84,0x21,0x6,0x60,0xbf,0xfd,0xbf,0xfd,0x6,0x60,0x84,0x21,0x80,0x1,0x80,0x1,0xe0,0x7,0xc0,0x3,0x80,0x1};
	char word[64] ={0x7f,0xfe,0x3f,0xfc,0x1f,0xf8,0x7f,0xfe,0x3f,0xfc,0x5b,0xda,0xe9,0x97,0x40,0x2,0x40,0x2,0xe9,0x97,0x5b,0xda,0x3f,0xfc,0x7f,0xfe,0x1f,0xf8,0x3f,0xfc,0x7f,0xfe,0x80,0x1,0xc0,0x3,0xe0,0x7,0x80,0x1,0xc0,0x3,0xa4,0x25,0x16,0x68,0xbf,0xfd,0xbf,0xfd,0x16,0x68,0xa4,0x25,0xc0,0x3,0x80,0x1,0xe0,0x7,0xc0,0x3,0x80,0x1};
	mouse_change(word);
	}

	while(key!=-1)
	{
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);
		x1=mouse.x;y1=mouse.y;
		mouse=status();
		if (kbhit())
			key=getch();

		if (x1>mouse.x)
		xradius++;
		if (x1<mouse.x)
		xradius--;
		if (y1>mouse.y)
		yradius++;
		if (y1<mouse.y)
		yradius--;
		if (key) {x1=2;y1=1;}
		switch (key)
		{
		case 72://up
			stangle++;break;
		case 80://down
			stangle--;break;
		case 75://left
			endangle++;break;
		case 77://right
			endangle--;break;
		case '+':
			xradius++;break;
		case '-':
			xradius--;break;
		case '/':
			yradius--;break;
		case '*':
			yradius++;break;
		}//end of swithc
		key=0;
		if (mouse.button==LEFT_CLICK) key = -1;//to exit the while loop

		if (mouse.x<=0)
			position_mouse(getmaxx()-10,mouse.y);
		if (mouse.y<=0)
			position_mouse(mouse.x,getmaxy()-10);
		if (mouse.x>=getmaxx())
			position_mouse(10,mouse.y);
		if (mouse.y>=getmaxy())
			position_mouse(mouse.x,10);


		if(!xradius) xradius=1;
		if(!yradius) yradius=1;
		if(xradius > x-3) xradius=x-3;
		if(yradius > y-3) yradius=y-3;
		if(xradius > getmaxx()-x-1) xradius=getmaxx()-x-1;
		if(yradius > getmaxy()-y-1) yradius=getmaxy()-y-1;

		if (mouse.x!=x1 || mouse.y !=y1)
		{
		hide_mouse();
		char *buffer=(char*)malloc(imagesize(82,82,0,0));
		for (int a=x-xradius-1;a<x+xradius+1;a=a+80){
		for (int b=y-yradius-1;b<y+yradius+1;b=b+80)
		{
			if (a+81 > getmaxx())
			{
			setactivepage(1);
			getimage(getmaxx()-82,b-1,getmaxx()-1,b+81,buffer);
			setactivepage(0);
			putimage(getmaxx()-82,b-1,buffer,COPY_PUT);
			}//end of x out of bounds

			setactivepage(1);
			getimage(a-1,b-1,a+81,b+81,buffer);
			setactivepage(0);
			putimage(a-1,b-1,buffer,COPY_PUT);

		}}//end of fornext
		free(buffer);

		}//end of redrawing if
		setcolor(color);
		if (!type) 	ellipse(x,y,stangle,endangle,xradius,yradius);
		if (type) 	sector(x,y,stangle,endangle,xradius,yradius);
		show_mouse();

	}//end of second while
	redraw();
	FILE* fp;

	if (!type)
		fp=fopen("\\circ.$$$","at");
	if (type)
		fp=fopen("\\pie.$$$","at");

	if (fp ==NULL) fprintf(stderr,"Circle : ERROR OPENMING FILE");
	fprintf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",x,y,stangle,endangle,xradius,yradius,color,thickness,fillpattern,fillcolor);

	fclose(fp);
	redraw();
	click();
	mouse_change(_TARGET_CUR);
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
}//end of function

void o_line(int type)
{
	//inside line
	click();
	//active pages
	hide_mouse();
	setactivepage(1);
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	setcolor(color);
	int sx=0,sy=0,ex=0,ey=0;
	StatusLine("Inside line mode",__LINE__,__FILE__);
	mouse_status mouse;
	show_mouse();
	mouse = click();
	mouse.button=0;
	StatusLine("Click to mark the start of line",__LINE__,__FILE__);
	while (mouse.button == 0)
	{
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);
		mouse=click();
		if (mouse.button==LEFT_CLICK)
		{sx=mouse.x;sy=mouse.y;}
		if (mouse.button == MIDDLE_CLICK)
		{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button=0;
		}
		if (mouse.button == RIGHT_CLICK || mouse.button == BOTH_CLICK) mouse.button =0;
	}//end of while
	click();
	setcolor(color);
	setlinestyle(line_style,0,thickness);
	mouse.button=0;
	int x1,y1;
	StatusLine("Click to mark the end",__LINE__,__FILE__);
	hide_mouse();
	setcolor(color);
	setlinestyle(line_style,0,thickness);
	while (!mouse.button)
	{
		x1=mouse.x;y1=mouse.y;
		mouse=status();
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);
		if (mouse.x < 3) mouse.x =3;
		if (mouse.y < 3) mouse.y =3;
		ex=mouse.x;
		ey=mouse.y;

		if (mouse.x!=x1 || mouse.y !=y1)
		{
			if (type)
			{
			char *uffer = (char *)malloc(imagesize(0,0,10,60));
			char *buffer = (char *)malloc(imagesize(0,0,10,60));
			setfillstyle(SOLID_FILL,3);
			for (int a=min(sx,x1);a<=max(sx,x1);a=a+60)
				{
			if (a+58 > getmaxx())
			{
			setactivepage(1);
			getimage(getmaxx()-58,sy-1,getmaxx()-1,sy+1,buffer);
			getimage(getmaxx()-58,y1-1,getmaxx()-1,y1+1,uffer);
			setactivepage(0);
			putimage(getmaxx()-58,sy-1,buffer,COPY_PUT);
			putimage(getmaxx()-58,y1-1,uffer,COPY_PUT);
			}//end of x out of bounds
				setcolor(color);
				setactivepage(1);
				getimage(a-1,sy-1,a+58,sy+1,buffer);
				getimage(a-1,y1-1,a+58,y1+1,uffer);
				setactivepage(0);
				putimage(a-1,sy-1,buffer,COPY_PUT);
				putimage(a-1,y1-1,uffer,COPY_PUT);
				}
			for (a=min(sy,y1);a<=max(sy,y1);a=a+60)
				{
				setactivepage(1);
				getimage(sx-1,a-1,sx+1,a+58,buffer);
				getimage(x1-1,a-1,x1+1,a+58,uffer);
				setactivepage(0);
				putimage(sx-1,a-1,buffer,COPY_PUT);
				putimage(x1-1,a-1,uffer,COPY_PUT);
				}
			free(uffer);
			free(buffer);
			}//end of rectangle selection

		if (!type)
		{
		char *buffer=(char*)malloc(imagesize(42,42,0,0));
		for (int a=min(sx,x1);a<=max(sx,x1);a=a+40){
		for (int b=min(sy,y1);b<=max(sy,y1);b=b+40)
		{
		if (a+41 > getmaxx())
			{
			setactivepage(1);
			getimage(getmaxx()-42,b-1,getmaxx()-1,b+41,buffer);
			setactivepage(0);
			putimage(getmaxx()-42,b-1,buffer,COPY_PUT);
			}//end of x out of bounds
		setactivepage(1);
		getimage(a-1,b-1,a+41,b+41,buffer);
		setactivepage(0);
		putimage(a-1,b-1,buffer,COPY_PUT);
		}}//end of fornext
					free(buffer);
			}//end of line redrawibng
		}//end of if

		if (!type) line(sx,sy,ex,ey);
		if (type) rectangle(sx,sy,ex,ey);

	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button=0;
	}//end of middle click

	}//end of second while
	FILE* fp;

	if (!type)
		fp=fopen("\\line.$$$","at");
	if (type)
		fp=fopen("\\rect.$$$","at");

	if (fp ==NULL) fprintf(stderr,"LINE : ERROR OPENING FILE");
	fprintf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",sx,sy,ex,ey,color,thickness,line_style);

	fclose(fp);
	click();
	show_mouse();
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
}

void cus_pattern()
{
	char pattern[8][8];
	{
		char words[64] ={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0x1,0x80,0xfd,0xbf,0x5,0xa0,0xf5,0xaf,0x15,0xa8,0xd5,0xab,0x55,0xaa,0x55,0xaa,0xd5,0xab,0x15,0xa8,0xf5,0xaf,0x5,0xa0,0xfd,0xbf,0x1,0x80,0xff,0xff};		mouse_change(words);
		for (int x=0;x<8;x++)
		for (int y=0;y<8;y++)
			pattern[x][y]=0;
	}//end of initialisation

	char *scr= (char *) calloc(1,imagesize(219,99,381,261));
	if (scr== NULL)
		error("In Creating Customer Pattern\nCustomer Pattern Creation Module");
	getimage(219,99,381,261,scr);

	setfillstyle(SOLID_FILL,0);
	bar(220,100,381,261);
	setcolor(8);
	for (int i = 220;i <= 380;i=i+20)
		line(i,100,i,260);
	for (i = 100;i <= 260;i=i+20)
		line(220,i,380,i);
	setcolor(15);

	rectangle(219,99,381,261);

	mouse_status mouse = {0,0,0};
	show_mouse();
	int quit = 0;
	while(!quit)
	{
	mouse = status();
	if (mouse.button == LEFT_CLICK && !inarea(mouse.x,mouse.y,219,99,381,261))
		quit = 1;
	if ( mouse.x > 220 && mouse.x < 380 && mouse.y > 100 && mouse.y < 260 && (mouse.button == 1 || mouse.button == 2))
	{
		int x,y;
		x = (mouse.x-220) /20;
		y = (mouse.y-100) /20;

		hide_mouse();
		if (mouse.button == 1)
			{
			setfillstyle (1,12);
			floodfill(mouse.x,mouse.y,8);
			pattern[x][y] = 1;
			}

		if (mouse.button == 2)
			{
			setfillstyle (1,0);
			floodfill(mouse.x,mouse.y,8);
			pattern[x][y] = 0;
			}

		show_mouse();
	}//end of if
	}//end of while
	for (int x=0;x < 8;x++)
			cuspattern[x] =0;
	for (x=0;x<8;x=x+1)
	{
		for (int y=0;y<8;y=y+1)
		cuspattern[x] =cuspattern[x] + pattern[y][x] * pow(2,7-y);
	}
	hide_mouse();
	putimage(219,99,scr,COPY_PUT);
	free(scr);
	{
	char word[64] = {0x7,0xe0,0x77,0xee,0x37,0xec,0x17,0xe8,0x77,0xee,0x77,0xee,0xf7,0xef,0x7,0xe0,0x7,0xe0,0xf7,0xef,0x77,0xee,0x77,0xee,0x17,0xe8,0x37,0xec,0x77,0xee,0x7,0xe0,0xf8,0x1f,0x88,0x11,0xc8,0x13,0xe8,0x17,0x88,0x11,0x88,0x11,0x8,0x10,0xf8,0x1f,0xf8,0x1f,0x8,0x10,0x88,0x11,0x88,0x11,0xe8,0x17,0xc8,0x13,0x88,0x11,0xf8,0x1f};
	mouse_change(word);
	}
	show_mouse();

}//end of pattern


