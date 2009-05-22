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
void error(const char*msg);

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
}}

void draw_grid(int grid,int color=8,int linestyle=0)
{
	mouse_change(_TARGET_CUR);
	bind_mouse(0,12,getmaxx(),getmaxy());
	setcolor(15);
	rectangle(0,0,getmaxx(),getmaxy());
	if (__grid == 0) return;
	if (grid < 0) grid = 1;
	setcolor(color);
	setlinestyle(linestyle,1,1);
	hide_mouse();
	for (int i=0;i< getmaxx();i+=grid)
	{
		line (i,0,i,getmaxy());
		line (0,i,getmaxx(),i);
	}
	setlinestyle(1,0,3);
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
	setfillstyle(SOLID_FILL,7);
	bar(1,1,566,10);
	setcolor(8);
	rectangle(1,1,566,10);
	setcolor(15);
	rectangle(1,10,566,10);
	rectangle(566,1,566,10);
	settextstyle(0,0,1);
	setcolor(8);outtextxy(10,3,msg);
	setcolor(15);outtextxy(9,2,msg);
	# ifdef AXE
		gotoxy(1,1);printf("%d in %s",line,file);
	# endif
}

void error(const char *msg)
{
	fprintf(stderr,"ERROR in module: %s",msg);
  //	fprintf(stderr,"Line Number : %d",line);
  //	fprintf(stderr,"File Name   : %s",file);
	getch();
	closegraph();
	exit(1);
}
void properties()
{
click();
char word[64] = {255,31,255,39,255,89,127,174,159,183,239,219,7,220,255,236,127,237,135,245,155,245,173,249,182,253,218,255,236,255,240,255,0,224,0,216,0,166,128,81,96,72,16,36,248,35,0,19,128,18,120,10,100,10,82,6,73,2,37,0,19,0,15,0};
mouse_change(word);
StatusLine("Click on properties to change them, outside to exit properties box.",__LINE__,__FILE__);
mouse_status mouse=click();
int toolx=mouse.x;
int tooly=mouse.y;
if (toolx+120 > getmaxx()) toolx=getmaxx()-125;
if (tooly+160 > getmaxy()) tooly=getmaxy()-165;
if (toolx <10) toolx=10;
if (tooly <10) tooly=10;

char *buffer=(char *)malloc(imagesize(0,0,120,160));
if (!buffer) error("Properties\nUnable to allocate memory for screen save");
hide_mouse();
getimage(toolx,tooly,toolx+120,tooly+160,buffer);


/*******draw buttons **********/
setfillstyle(SOLID_FILL,8);
setlinestyle(0,0,1);
bar(toolx,tooly,toolx+120,tooly+160);

setcolor(14);
setcolor(11);
for (int iy=1;iy < 160;iy=iy+20)
line (toolx,tooly+iy,toolx+120,tooly+iy);
line (toolx+85,tooly,toolx+85,tooly+160);
setcolor(8);
line (toolx+85,tooly+101,toolx+85,tooly+119);

setcolor(15);
rectangle(toolx,tooly,toolx+120,tooly+160);

settextstyle(0,0,1);
setcolor(14);
outtextxy(toolx+5,tooly+6,"Color");
outtextxy(toolx+5,tooly+6+20,"Thickness");
outtextxy(toolx+5,tooly+6+40,"Linestyle");
outtextxy(toolx+5,tooly+6+60,"BackColor");
outtextxy(toolx+5,tooly+6+80,"Pattern");
outtextxy(toolx+5,tooly+6+100,"Change pattern");
outtextxy(toolx+5,tooly+6+120,"FontName");
outtextxy(toolx+5,tooly+6+140,"Size");

click();
position_mouse(toolx+30,tooly+30);
show_mouse();
mouse =status();
setcolor(color);

/*******drawing properties ********/
/*color*/
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
settextstyle(0,HORIZ_DIR,1);
char *sr=(char*)malloc(sizeof sr);
sprintf(sr,"%02d",font);
outtextxy(toolx+100,tooly+125,sr);
sprintf(sr,"%02d",size);
outtextxy(toolx+100,tooly+145,sr);
free(sr);
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
		setcolor(8);
		line (toolx+95,tooly+25,toolx+110,tooly+35);
		setcolor(15);
		setlinestyle(0,0,thickness);
		line (toolx+95,tooly+25,toolx+110,tooly+35);
		break;

		case 2://linestyle
		if (mouse.button == LEFT_CLICK) 	line_style++;
		if (mouse.button == RIGHT_CLICK) line_style--;

		if (line_style > 3) line_style = 0;

		setcolor(8);setlinestyle(0,0,1);
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
				setfillpattern(cuspattern ,7);
				bar (toolx+95,tooly+85,toolx+110,tooly+95);
		}
		break; //end of fillpattern
		case 6://font
		if (mouse.button == LEFT_CLICK) 	font++;
		if (mouse.button == RIGHT_CLICK) 	font--;

		if (font>12) font = 0;
		setfillstyle(1,8);
		bar (toolx+86,tooly+122,toolx+119,tooly+139);
		settextstyle(0,0,1);
		{
	char *sr=(char*)malloc(sizeof sr);
	sprintf(sr,"%02d",font);
	outtextxy(toolx+100,tooly+125,sr);
	free(sr);
		}//case 6
		break;

		case 7 ://size
		if (mouse.button == RIGHT_CLICK) 	size--;
		if (mouse.button == LEFT_CLICK) 	size++;

		if (size>14) size = 0;
		setfillstyle(1,8);
		bar (toolx+86,tooly+142,toolx+119,tooly+159);

		settextstyle(0,0,1);
		{
	char *sr=(char*)malloc(sizeof sr);
	sprintf(sr,"%02d",size);
	outtextxy(toolx+100,tooly+145,sr);
	free(sr);
	break;
		}//case 7
		case 5:
		cus_pattern();
		break;//end of custoemr pattern
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
mouse_change(_TARGET_CUR);
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

char *buffer=(char *)malloc(imagesize(0,0,160,40));
if (!buffer) error("ColorCard\nUnable to allocate enough memory for screen save");
hide_mouse();
getimage(toolx,tooly,toolx+160,tooly+40,buffer);

/****** draw buttons *******/
setlinestyle(SOLID_LINE,0,1);
setcolor(15);
int c=0;
for (int y=0;y<2;y++){
for (int x=0;x<8;x++){
setfillstyle(SOLID_FILL,c++);
bar(toolx+x*20,tooly+y*20,toolx+x*20+20,tooly+y*20+20);
}}
rectangle(toolx,tooly,toolx+160,tooly+40);

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
	if (mouse.x>toolx && mouse.y > tooly && mouse.x <toolx+160 && mouse.y <tooly+40)
	{
	mouse.x=(mouse.x-toolx)/20;
	mouse.y=(mouse.y-tooly)/20;
	result=mouse.x+ (mouse.y*8);
	}//end of LEFT_click
}//end of LEFT_click
}//end of while

hide_mouse();
free(buffer);
putimage(toolx,tooly,buffer,COPY_PUT);
show_mouse();
return result;
}//end of color card

