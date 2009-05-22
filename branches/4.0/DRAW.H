# define GRID_COLOR 8
void cus_pattern();

extern int __grid;
extern char cuspattern[8];
extern unsigned int color;
extern unsigned int line_style;
extern unsigned int thickness;
extern unsigned int fillpattern;
extern unsigned int fillcolor;
extern unsigned int font;
extern unsigned int direction;
extern unsigned int size;
extern int resolution;

#ifdef __cplusplus


#endif

void ccoder();
void bcoder();
void redraw();
void o_line(int type);
void o_circle(int type);
void o_text();
void paint();
void coder();
void error(const char*msg,char *,int);

void intro(void)
{
int gdriver = VGA, gmode=VGAMED, errorcode;
	initgraph(&gdriver, &gmode, "");
//	if (errorcode != grOk)
//		initgraph(&gdriver, &gmode, "");

errorcode = graphresult();
if (errorcode != grOk)  /* an error occurred */
{
  printf("Graphics error: %s\n", grapherrormsg(errorcode));
  printf("Press any key to halt:");
  getch();
  exit(1); /* terminate with an error code */
}
}

void draw_grid(int grid,int color=GRID_COLOR,int linestyle=0)
{
	bind_mouse(0,12,getmaxx(),getmaxy());
	setcolor(15);
	rectangle(0,0,getmaxx(),getmaxy());
	if (__grid == 0) return;
	if (grid < 0) grid = 1;
	setcolor(color);
	linestyle = 4;
	setlinestyle(linestyle,21845,1);
	hide_mouse();
	for (int i=0;i< getmaxx();i+=grid)
	{
		line (i,0,i,getmaxy());
		line (0,i,getmaxx(),i);
	}
	setlinestyle(0,0,1);
	for (i=0;i< getmaxx();i+=4*grid)
	{
		line (i,0,i,getmaxy());
		line (0,i,getmaxx(),i);
	}
	setlinestyle(0,0,1);
setcolor(15);
rectangle(0,0,getmaxx(),getmaxy());
show_mouse();
}

void StatusLine( const char *msg,int line,char *file)
{
	fflush(stdin);
	setlinestyle(0,0,0);
	loadbmp("status.vsn",1,0);
	setcolor(15);
	rectangle(1,10,566,10);
	rectangle(566,1,566,10);
	settextstyle(0,0,1);
	setcolor(8);outtextxy(20,3,msg);
	setcolor(15);outtextxy(19,2,msg);
	# ifdef AXE
		gotoxy(35,1);printf("%3d in %s",line,file);
	# endif
}

void error(const char *msg,char *file,int line)
{
hide_mouse();
# ifdef AXE
	fprintf(stderr,"ERROR in module:\n %s\n\n",msg);
	fprintf(stderr,"Filename    : %s\n",file);
	fprintf(stderr,"Line Number : %d\n",line);
#else
	loadbmp("error.vsn",100,50);
	errorclip(msg,line,file);
# endif
	getch();
	closegraph();
	exit(1);
}
void properties()
{
loadcur("cursor","attr",9,7);
click();
StatusLine("Click on properties to change them, outside to exit properties box.",__LINE__,__FILE__);
mouse_status mouse=click();
int toolx=mouse.x;
int tooly=mouse.y;
if (toolx+120 > getmaxx()) toolx=getmaxx()-125;
if (tooly+160 > getmaxy()) tooly=getmaxy()-165;
if (toolx <10) toolx=10;
if (tooly <10) tooly=10;

char *buffer=(char *)malloc(imagesize(0,0,120,160));
if (!buffer) error("Properties\nUnable to allocate memory for screen save",__FILE__,__LINE__);
hide_mouse();
getimage(toolx,tooly,toolx+120,tooly+160,buffer);
loadbmp("prop.vsn",toolx,tooly);
click();
position_mouse(toolx+30,tooly+30);
show_mouse();
mouse =status();
setcolor(color);

/*******drawing properties ********/

setfillstyle(SOLID_FILL,color);
bar (toolx+95,tooly+5,toolx+110,tooly+15);
// thickness
setcolor(15);
setlinestyle(0,0,thickness);
line (toolx+95,tooly+25,toolx+110,tooly+35);
//line style
setlinestyle(line_style,0,1);
line (toolx+95,tooly+45,toolx+110,tooly+55);
//backcolor
setfillstyle(SOLID_FILL,fillcolor);
bar (toolx+95,tooly+65,toolx+110,tooly+75);
//fillpattern
setfillstyle(fillpattern ,7);
bar (toolx+95,tooly+85,toolx+110,tooly+95);
if (fillpattern == 12)
	{
	setfillpattern(cuspattern ,7);
	bar (toolx+95,tooly+85,toolx+110,tooly+95);
	} // for customer defined pattern
//fontname and size
int quit=0;
while (quit==0)
{
	mouse=click();
	if (mouse.button==LEFT_CLICK || mouse.button == RIGHT_CLICK)
	{
	hide_mouse();
		if (mouse.x > toolx  && mouse.y > tooly && mouse.y <tooly+160 && mouse.x < toolx+120)
{
		mouse.y =(mouse.y-tooly)/20;
		switch(mouse.y)
		{
		case 0: //color
		if (mouse.button == LEFT_CLICK) 	color++;
		if (mouse.button == RIGHT_CLICK) color--;

		if (color > 15) color = 0;

		setfillstyle(SOLID_FILL,color);
		bar (toolx+95,tooly+5,toolx+110,tooly+15);
		break;

		case 1://thickness
		if (thickness==1) thickness =3;
		else if (thickness==3) thickness =1;

		setlinestyle(0,0,3);
		setcolor(7);
		line (toolx+95,tooly+25,toolx+110,tooly+35);
		setcolor(15);
		setlinestyle(0,0,thickness);
		line (toolx+95,tooly+25,toolx+110,tooly+35);
		break;

		case 2://linestyle
		if (mouse.button == LEFT_CLICK) 	line_style++;
		if (mouse.button == RIGHT_CLICK) line_style--;

		if (line_style > 3) line_style = 0;

		setcolor(7);setlinestyle(0,0,1);
		line (toolx+95,tooly+45,toolx+110,tooly+55);
		setlinestyle(line_style,0,1);setcolor(15);
		line (toolx+95,tooly+45,toolx+110,tooly+55);
		break;

		case 3://backcolor
		if (mouse.button == LEFT_CLICK)	fillcolor++;
		if (mouse.button == RIGHT_CLICK) 	fillcolor--;

		if (fillcolor > 15) fillcolor = 0;
		setfillstyle(SOLID_FILL,fillcolor);
		bar (toolx+95,tooly+65,toolx+110,tooly+75);
		break;

		case 4://fillpattern
		if (mouse.button == LEFT_CLICK) fillpattern++;
		if (mouse.button == RIGHT_CLICK) fillpattern--;

		if (fillpattern > 12) fillpattern = 0;
		setfillstyle(fillpattern ,7);
		bar (toolx+95,tooly+85,toolx+110,tooly+95);
		if (fillpattern == 12)
		{
				setfillpattern(cuspattern ,8);
				bar (toolx+95,tooly+85,toolx+110,tooly+95);
		}
		break; //end of fillpattern
		case 5:
		case 6://font

		if (mouse.button == LEFT_CLICK) 	font++;
		if (mouse.button == RIGHT_CLICK) 	font--;

		if (font>12) font = 0;
		setfillstyle(1,7);
		setfillstyle(SOLID_FILL,7);
		bar (toolx+1,tooly+104,toolx+118,tooly+138);
		settextstyle(0,0,1);
		{
	settextjustify(CENTER_TEXT,CENTER_TEXT);
	char *sr=(char*)malloc(100);
	sprintf(sr,"Font:%d",font);
	if (font == 10)
		settextstyle(0,0,2);
	else
		settextstyle(font,0,2);
	outtextxy(toolx+60,tooly+120,sr);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	free(sr);
		}//case 6
		break;

		case 7 ://size
		if (mouse.button == RIGHT_CLICK) 	size--;
		if (mouse.button == LEFT_CLICK) 	size++;

		if (size>14) size = 0;
		setfillstyle(1,7);
		bar (toolx+90,tooly+145,toolx+115,tooly+155);

		settextstyle(0,0,1);
		{
	char *sr=(char*)malloc(100);
	sprintf(sr,"%02d",size);
	outtextxy(toolx+100,tooly+145,sr);
	free(sr);
	break;
		}//case 7
	}//end of switchcase
	}//end of correct area click
	else
		quit = 1;

	show_mouse();
	}//end of left click if
}//end of while

click();
hide_mouse();
putimage(toolx,tooly,buffer,COPY_PUT);
show_mouse();
free(buffer);
StatusLine("Strike F1 for Help",__LINE__,__FILE__);
loadcur("cursor","word",0,0);
}//end of properties


int color_card()
{
click();
mouse_status mouse=click();
int toolx=mouse.x;
int tooly=mouse.y;
if (toolx+160 > getmaxx()) toolx=getmaxx()-165;
if (tooly+40 > getmaxy()) tooly=getmaxy()-45;
if (toolx <10) toolx=10;
if (tooly <10) tooly=10;

char *buffer=(char *)malloc(imagesize(0,0,137,72));
if (!buffer) error("ColorCard\nUnable to allocate enough memory for screen save",__FILE__,__LINE__);
hide_mouse();
getimage(toolx,tooly,toolx+137,tooly+71,buffer);
loadbmp("color.vsn",toolx,tooly);
/********processing ********/
show_mouse();
click();
int result=-2;

while (result==-2)
{
mouse=click();
if (mouse.button == LEFT_CLICK)
{
	result = -1;
	if (inarea(mouse.x,mouse.y,toolx,tooly,toolx+136,tooly+71))
		result = -2;
	if (inarea(mouse.x,mouse.y,toolx+131,tooly+58,toolx+4,tooly+27))
	{
	mouse.x=(mouse.x-toolx-4)/16;
	mouse.y=(mouse.y-tooly-27)/16;
	result=mouse.x+ (mouse.y*8);
	}//end of in area
}//end of LEFT_click
}//end of while

hide_mouse();
free(buffer);
putimage(toolx,tooly,buffer,COPY_PUT);
show_mouse();
if (result > 15)
	result = 15;
return result;
}//end of color card

struct quad
{
	int x1,x2,y1,y2;
};

int sreplace(char *target,char *source,int start,int end)
{
	char *buffer = (char *)calloc(1,100);
	char *s;
	if (buffer == NULL)
		return -1;
	strncpy(buffer,target,start);
	strcat(buffer,source);
	s = target+end;
	int result = strlen(buffer);
	strcat(buffer,s);
	strcpy(target,buffer);
	free(buffer);
	return result;
}//end of replacing

quad mark()
{
	click();
	hide_mouse();
	setactivepage(1);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	setcolor(color);
	int sx=0,sy=0,ex=0,ey=0;
	StatusLine("Marking a region",__LINE__,__FILE__);
	mouse_status mouse;
	show_mouse();
	mouse = click();
	mouse.button=0;
	StatusLine("Click to mark the start of selection",__LINE__,__FILE__);
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
	StatusLine("Click to mark the end of selection",__LINE__,__FILE__);
	hide_mouse();
	setcolor(color);
	setlinestyle(1,0,1);


	while (!mouse.button)
	{
		x1=mouse.x;y1=mouse.y;
		mouse=status();
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);
		if (mouse.x < 3) mouse.x =3;
		if (mouse.y < 3) mouse.y =3;
		ex=mouse.x;
		ey=mouse.y;
		setcolor(10);
		rectangle(sx,sy,ex,ey);

//		if (mouse.x!=x1 || mouse.y !=y1)
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
	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button=0;
	}//end of middle click
}//end of second while
	quad q;
	q.x1 = sx;
	q.x2 = ex;
	q.y1 = sy;
	q.y2 = ey;
	show_mouse();
	loadcur("cursor","word",0,0);
	return q;
}//end of function