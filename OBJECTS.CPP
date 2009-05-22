# define GRID_COLOR 8
# define POINTS 30

extern char filetmp[15];
extern unsigned int upattern;
extern unsigned int color;
extern unsigned int line_style;
extern unsigned int thickness;
extern int resolution;
extern unsigned int fillpattern;
extern unsigned int fillcolor;
extern unsigned int font,direction,size;
extern char cuspattern[8];

void StatusLine(const char *msg,int line,char *file);
void drawobj(char *);

void redraw()
{
	FILE *fp;
	fp = fopen(filetmp,"rt");
	if (fp == NULL)
		error("Error opening file for redrawing",__FILE__,__LINE__);
	char object[100];
	while (!feof(fp))
	{
	fscanf(fp,"%s ",&object);
	int sx,sy,ex,ey,thk,ls,col,fs,fc,fonts,fontn,fontdir;
	char cp[8];
	sx=sy=ex=ey=thk=ls=col=fs=fc=fonts=fontn=fontdir=0;
		if (strcmp(object,"object") == 0)
			{
			fgets(object,100,fp);
			*(object + strlen(object) -1 ) = NULL;
			drawobj(object);
			}//end of drawing objects
		else if (strcmp(object,"line") == 0 || strcmp(object,"rectangle") == 0)
			{
			fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%07d\n",
						&sx,&sy,&ex,&ey,&col,&thk,&ls,&fontdir);
			setcolor(col);setlinestyle(ls,fontdir,thk);
			if (strcmp(object,"rectangle") == 0)
				rectangle(sx,sy,ex,ey);
			else
				line(sx,sy,ex,ey);
			}//end of drawing a line

		else if (strcmp(object,"bar") == 0)
			{
			fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d\n",
					&sx,&sy,&ex,&ey,&fc,&fs);
			setfillstyle(fs,fc);
			bar(sx,sy,ex,ey);
			}//end of drawing a rectangle

		else if (strcmp(object,"barp") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
				&sx,&sy,&ex,&ey,&fc,
				&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				setfillpattern(cp,fc);
				bar(sx,sy,ex,ey);
			}//end of bar with user defined pattern
		else if (strcmp(object,"print") == 0)
		{
			fscanf(fp,"%03d,%03d,",
							&sx,&sy);
			fgets(object,100,fp);
			*(object + strlen(object) -1 ) = NULL;
			gotoxy(sx,sy);
			printf("%s",object);
		}//end of text

		else if (strcmp(object,"text") == 0)
		{
			fscanf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,",
							&col,&sx,&sy,
							&fontn,&fontdir,&fonts);
			fgets(object,100,fp);
			*(object + strlen(object) -1 ) = NULL;
			setcolor(col);
			settextstyle(fontn,fontdir,fonts);
			outtextxy(sx,sy,object);
		}//end of text

		else if (strcmp(object,"ellipse") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
						&sx,&sy,&ex,&ey,&fonts,&fontn,&col,&thk);
				setcolor(col);
				setlinestyle(0,0,thk);
				ellipse(sx,sy,ex,ey,fonts,fontn);
			}//end of ellipse
		else if (strcmp(object,"pie") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&ex,&ey,&fonts,&fontn,
							&col,&thk,&fc,&fs);
				setcolor(col);
				setlinestyle(0,0,thk);
				setfillstyle(fs,fc);
				sector(sx,sy,ex,ey,fonts,fontn);
			}//end of drawing simple piechart

		else if (strcmp(object,"piepattern") == 0)
			{
				int xradius,yradius;
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
					&sx,&sy,
					&ex,&ey,
					&xradius,&yradius,
					&col,&thk,&fc,
					&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				setcolor(col);
				setlinestyle(0,0,thk);
				setfillpattern(cp,fc);
				sector(sx,sy,ex,ey,xradius,yradius);
			}//end of complex pie chart

		else if (strcmp(object,"fillellipse") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&ex,&ey,
							&col,&thk,&fc,&fs);
				setcolor(col);
				setfillstyle(fs,fc);
				setlinestyle(0,0,thk);
				fillellipse(sx,sy,ex,ey);
			}//end of fillellipse simple

			else if (strcmp(object,"fillellipsep") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&ex,&ey,
							&col,&thk,&fc,
							&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
							setcolor(col);
							setfillpattern(cp,fc);
							setlinestyle(0,0,thk);
							fillellipse(sx,sy,ex,ey);
			}//end of complex ellipse filler
			else if (strcmp(object,"fillstyle") == 0)
			{
				fscanf(fp,"%03d,%03d,%02d,%02d,%02d\n",
								&sx,&sy,&col,&fc,&fs);

				if (fc == GRID_COLOR)
					{
					setfillstyle(SOLID_FILL,7);
					floodfill(sx,sy,col);
					}
				setfillstyle(fs,fc);
				floodfill(sx,sy,col);
			}//end of floodfilling
			else if (strcmp(object,"fillpattern") == 0)
			{
			fscanf(fp,"%03d,%03d,%02d,%02d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&col,&fc,
							&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
					if (fc == GRID_COLOR)
					{
					setfillstyle(SOLID_FILL,7);
					floodfill(sx,sy,col);
					}

			setfillpattern(cp,fc);
			floodfill(sx,sy,col);
			}//end of fill pattern
			else if (strcmp(object,"polygon") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%07d\n",
								&fontdir,&col,&ls,&thk,&fontn);
				int points[30];
				for (int i = 0; i < fontdir*2 && i < 30;i+=2)
					fscanf(fp,"%03d,%03d",&points[i],&points[i+1]);
				setcolor(col);
				setlinestyle(ls,fontn,thk);
				drawpoly(fontdir,points);
			}//end of simple polygon

			else if (strcmp(object,"fillpolygon") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%07d\n",
								&fontdir,&col,&ls,&thk,&fc,&fs,&fontn);
				int points[30];
				for (int i = 0; i < fontdir*2 && i < 30;i+=2)
					fscanf(fp,"%03d,%03d",&points[i],&points[i+1]);
				setcolor(col);
				setfillstyle(fs,fc);
				setlinestyle(ls,fontn,thk);
				fillpoly(fontdir,points);
			}//end of simple polygon filling simple

			else if (strcmp(object,"fillpolygonp") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%07d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
								&fonts,&col,&ls,&thk,&fc,&fontn,
								&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				int points[30];
				for (int i = 0; i < fonts*2 && i < 30;i+=2)
					fscanf(fp,"%03d,%03d",&points[i],&points[i+1]);
				setcolor(col);
				setfillpattern(cp,fc);
				setlinestyle(ls,fontn,thk);
				fillpoly(fonts,points);
			}//end of simple polygon filling simple
			else if (strcmp(object,"bmp") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%s\n",
							&sx,&sy,&ex,&ey,&object);
				loadbmp(object,sx,sy,ex,ey);
			}//end of loading bitmaps
	}//end of parsing all values
	fclose(fp);
	StatusLine(" ",__LINE__,__FILE__);
}//end of function

void paint()
{
loadcur("cursor","paint",0,0);
mouse_status mouse;
mouse.button = 0;
int colx=0;
colx=color_card();

StatusLine("Select the Outline Color",__LINE__,__FILE__);

while (mouse.button == 0)
	mouse=status();

if (colx !=-1 && mouse.button == LEFT_CLICK)
	{
	hide_mouse();

	if (fillcolor == GRID_COLOR)
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
	fp=fopen(filetmp,"at");
	if (fillpattern == 12)
		fprintf(fp,"fillpattern %03d,%03d,%02d,%02d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
		mouse.x,mouse.y,colx,fillcolor,
		cuspattern[0],cuspattern[1],cuspattern[2],cuspattern[3],cuspattern[4],cuspattern[5],cuspattern[6],cuspattern[7]);
	else
		fprintf(fp,"fillstyle %03d,%03d,%02d,%02d,%02d\n",
		mouse.x,mouse.y,colx,fillcolor,fillpattern);
	fclose(fp);
	}//end of fillstyle
	redraw();
	loadcur("cursor","word",0,0);
}//end of paint

void text(void)
{
loadcur("cursor","text",0,0);
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
strcpy(result,"");
int x1,y1;
x1=x;y1=y;
while (key != 27 )
{
	show_mouse();
	position_mouse(x,y);
	key = 0;
	key=getch();
	if (key >=32 && key < 127 && x1 + textwidth(result) < getmaxx())
		{
		char buffer[2];
		if (!buffer) error("TEXT\nError allacating memory for buffer",__FILE__,__LINE__);
		sprintf(buffer,"%c",key);
		hide_mouse();
		outtextxy(x,y,buffer);
		strcat(result,buffer);
		show_mouse();
		x+=textwidth(buffer);
		}//inside the required range and end of printabe characters

	if (key == 8 && strlen(result) > 0)//backspace
	{
		hide_mouse();
		char *buffer=(char*)calloc(1,strlen(result)+1);
		if (!buffer) error("TEXT\nUnable to allocate memory for text screen save",__FILE__,__LINE__);
		char *sr=(char *)calloc(1,2);
		if (!sr) error("TEXT\nUnable to allocate memory for text screen save",__FILE__,__LINE__);
		*sr=*(result+strlen(result)-1);
		for (int i=0;i <strlen(result)-1;i++)
			*(buffer+i)=*(result + i);

		x=x-textwidth(sr) ;
		bar(x,y,x+textwidth(sr),y+textheight(sr)+10);
		char *scr=(char *) malloc(imagesize(x,y,x+textwidth(sr),10+y+textheight(sr)));
		if (!scr) error("TEXT\nUnable to allocate memory for text screen save",__FILE__,__LINE__);
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
	loadcur("cursor","word",0,0);
	FILE* fp;
	fp=fopen(filetmp,"at");
	if (fp ==NULL)
		 error("Text : ERROR OPENMING FILE",__FILE__,__LINE__);

	if (strlen(result) != 0)
		fprintf(fp,"text %02d,%03d,%03d,%02d,%02d,%02d,%s\n",
			color,x1,y1,
			font,direction,size,
			result);

	fclose(fp);
	free(result);
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
}//end of text function

void o_poly(int type = 0)
{
	loadcur("cursor","polygon",0,0);
	int key;
	StatusLine("Polygon Mode - press Enter to finish,Esc to clear",__LINE__,__FILE__);
	mouse_status mouse;
	int sx,sy,ex,ey;
	xclick();
	mouse = click();
	sx=mouse.x;sy= mouse.y;
	int poly[POINTS],c=0;
	poly[c++]=sx;poly[c++]=sy;
	while (mouse.button != RIGHT_CLICK)
	{
	ex = sx;ey = sy;
	mouse = click();
	setcolor(color);
	setlinestyle(line_style,upattern,thickness);
	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button=0;
	}//end of middle click

	if (mouse.button == LEFT_CLICK && c < POINTS)
	  {
	  sx = mouse.x;sy=mouse.y;
	  poly[c++] = sx;poly[c++] = sy;
	  hide_mouse();
	  line(sx,sy,ex,ey);
	  show_mouse();
	  }//end of clicking on the screen
	}//end of drawing loop
	c=c/2;
	if (fillcolor == GRID_COLOR && type == 1)
		{
		setfillstyle(SOLID_FILL,7);
		fillpoly(c,poly);
		}
	hide_mouse();
	if (fillpattern == 12)
		setfillpattern(cuspattern,fillcolor);
	else
		setfillstyle(fillpattern,fillcolor);
	if (type == 0)
		drawpoly(c,poly);
	else if (type == 1)
		fillpoly(c,poly);
	show_mouse();
	FILE *fp;
	fp = fopen(filetmp,"at");
	if (fp == NULL)
		error ("Error Drawing for ploygon",__FILE__,__LINE__);
	if (type == 1)
		if (fillpattern == 12)
			fprintf(fp,"fillpolygonp %03d,%03d,%03d,%03d,%03d,%07d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
			c,color,line_style,thickness,fillcolor,upattern,
			cuspattern[0],cuspattern[1],cuspattern[2],cuspattern[3],cuspattern[4],cuspattern[5],cuspattern[6],cuspattern[7]);
		else
			fprintf(fp,"fillpolygon %03d,%03d,%03d,%03d,%03d,%03d,%7d\n",
			c,color,line_style,thickness,fillcolor,fillpattern,upattern);
	else
		fprintf(fp,"polygon %03d,%03d,%03d,%03d,%07d\n",
		c,color,line_style,thickness,upattern);
	c--;
	while (c >= 0)
		{
		fprintf(fp,"%03d,%03d\n",poly[c*2],poly[c*2+1]);
		c--;
		}

	fprintf(fp,"End of Points\n");
	fclose(fp);
	loadcur("cursor","word",0,0);
}//end of drawing polygon

void o_bmp()
{
	char *buffer = (char *)calloc(1,40);
	if (buffer == NULL)
		error("Cannot allocate memory for bitmap loading",__FILE__,__LINE__);
	G_input_box(buffer,"Load BitMap",
							"Please enter the name of",
							"file to load. (The .bmp ",
							"must be in 16 color format)");
	quad q = mark();
	if (loadbmp(buffer,q.x1,q.y1,q.x2-q.x1,q.y2-q.y1) != 0)
		return;
	FILE *fp;
	fp = fopen(filetmp,"at");
	if (fp == NULL)
		error ("Unable to open file for bitmap loading",__FILE__,__LINE__);
	fprintf(fp,"bmp %03d,%03d,%03d,%03d,%s\n",q.x1,q.y1,q.x2-q.x1,q.y2-q.y1,buffer);
	fclose(fp);
	free(buffer);

}//end of loading bitmap


void o_circle(int type=0)
{
	loadcur("cursor","circpoint",8,8);
	click();
	hide_mouse();
	setactivepage(1);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	StatusLine("Click to mark the centre of CIRCLE",__LINE__,__FILE__);
	int x=0,y=0,stangle=0,endangle=360,xradius=10,yradius=10;
	mouse_status mouse;
	mouse.button=0;
	show_mouse();
	while (!mouse.button)
	{
		mouse=status();
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);
		x=mouse.x;y=mouse.y;
		if (mouse.button ==MIDDLE_CLICK)
		{
			position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
			mouse.button =0;
		}//end of middle click
	}//end of first click
	click();
	loadcur("cursor","circle",10,10);
	StatusLine("Move mouse to increase/decrease radius, arrow keys for arcs",__LINE__,__FILE__);
	setcolor(color);
	setfillstyle(fillpattern,fillcolor);
	if (fillpattern ==12)
		setfillpattern(cuspattern,fillcolor);
	setlinestyle(line_style,0,thickness);
	int x1,y1,key=0;
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
		setlinestyle(line_style,0,thickness);
		if (fillpattern == 12)
			setfillpattern(cuspattern,fillcolor);
		else
			setfillstyle(fillpattern,fillcolor);

		if (type == 0)
			ellipse(x,y,stangle,endangle,xradius,yradius);

		else if (type == 1)
			if (fillcolor == GRID_COLOR)
				{
				setfillstyle(SOLID_FILL,7);
				sector(x,y,stangle,endangle,xradius,yradius);
				if (fillcolor != 12)
					setfillstyle(fillpattern,fillcolor);
				else
					setfillpattern(cuspattern,fillcolor);
				sector(x,y,stangle,endangle,xradius,yradius);
				}
			else
				sector(x,y,stangle,endangle,xradius,yradius);

		else if (type == 2)
			if (fillcolor == GRID_COLOR)
				{
				setfillstyle(SOLID_FILL,7);
				fillellipse(x,y,xradius,yradius);
				if (fillcolor != 12)
					setfillstyle(fillpattern,fillcolor);
				else
					setfillpattern(cuspattern,fillcolor);;
				fillellipse(x,y,xradius,yradius);
				}
			else fillellipse(x,y,xradius,yradius);

		show_mouse();

	}//end of second while
	redraw();
	FILE* fp;
	fp = fopen(filetmp,"at");
	if (fp == NULL) error("Unable to open file for circle",__FILE__,__LINE__);

	if (!type)
		fprintf(fp,"ellipse %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
					x,y,
					stangle,endangle,
					xradius,yradius,
					color,thickness);
	else if (type == 1)
	{
		if (fillpattern != 12)
	fprintf(fp,"pie %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
					x,y,
					stangle,endangle,
					xradius,yradius,
					color,thickness,fillcolor,fillpattern);
		else
	fprintf(fp,"piepattern %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
					x,y,
					stangle,endangle,
					xradius,yradius,
					color,thickness,fillcolor,
					cuspattern[0],cuspattern[1],cuspattern[2],cuspattern[3],cuspattern[4],cuspattern[5],cuspattern[6],cuspattern[7]);
	}// end of drawing a piechart
	else if (type == 2)
	{
		if (fillpattern != 12)
			fprintf(fp,"fillellipse %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							x,y,xradius,yradius,
							color,thickness,fillcolor,fillpattern);
		else
			fprintf(fp,"fillellipsep %03d,%03d,%03d,%03d,%03d,%03d,%03d,%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d\n",
							x,y,xradius,yradius,
							color,thickness,fillcolor,
							cuspattern[0],cuspattern[1],cuspattern[2],cuspattern[3],cuspattern[4],cuspattern[5],cuspattern[6],cuspattern[7]);
	}//end of drawing fillellipse
	fclose(fp);
	redraw();
	click();
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
	loadcur("cursor","word",0,0);
}//end of function

void o_line(int type)
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
	setlinestyle(line_style,upattern,thickness);
	if (fillpattern == 12)
		setfillpattern(cuspattern,fillcolor);
	else
		setfillstyle(fillpattern,fillcolor);
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
			if (type == 1)
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

		else
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

		if (type == 0)
			line(sx,sy,ex,ey);
		else if (type == 1)
			rectangle(sx,sy,ex,ey);
		else if (type == 2)
			if (fillcolor == GRID_COLOR)
				{
					setfillstyle(SOLID_FILL,7);
					bar(sx,sy,ex,ey);
					if (fillpattern == 12)
						setfillpattern(cuspattern,fillcolor);
					else
						setfillstyle(fillpattern,fillcolor);
					bar(sx,sy,ex,ey);
				}
			else
					bar(sx,sy,ex,ey);

	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button=0;
	}//end of middle click

	}//end of second while
	FILE* fp;
	fp = fopen(filetmp,"at");
	if (fp ==NULL) error("Unable to open Line program",__FILE__,__LINE__);

	if (!type)
		fprintf(fp,"line %03d,%03d,%03d,%03d,%03d,%03d,%03d,%07d\n",
		sx,sy,ex,ey,
		color,thickness,line_style,upattern);
	else if (type == 1 )
		fprintf(fp,"rectangle %03d,%03d,%03d,%03d,%03d,%03d,%03d,%07d\n",
		sx,sy,ex,ey,
		color,thickness,line_style,upattern);
	else if (type == 2)
		if (fillpattern != 12)
				fprintf(fp,"bar %03d,%03d,%03d,%03d,%03d,%03d\n",
				sx,sy,ex,ey,
				fillcolor,fillpattern);
		else
				fprintf(fp,"barp %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
				sx,sy,ex,ey,
				fillcolor,
				cuspattern[0],cuspattern[1],cuspattern[2],cuspattern[3],cuspattern[4],cuspattern[5],cuspattern[6],cuspattern[7]);
	fclose(fp);
	click();
	show_mouse();
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
}

void cus_pattern()
{
	hide_mouse();
	loadcur("cursor","fillstyle",8,8);
	char pattern[8][8];
	char *scr= (char *)malloc(imagesize(100,100,260,400));
	if (scr== NULL) error("In Creating Customer Pattern\nCustomer Pattern Creation Module",__FILE__,__LINE__);
	getimage(100,100,260,400,scr);
	loadbmp("pattern.vsn",100,100);


		for (int x=0;x<8;x++)
		for (int y=0;y<8;y++)
		{
			pattern[x][y]=(cuspattern[x] & (int)pow(2,y)) >> y;
			putpixel(105+x,265+y,pattern[x][y] * 10+1);
			putpixel(105+8+x,265+y,pattern[x][y] * 10+1);
			putpixel(105+x,265+y+8,pattern[x][y] * 10+1);
			putpixel(105+8+x,265+8+y,pattern[x][y] * 10+1);
			setfillstyle(SOLID_FILL,pattern[x][y] *8+1);
			bar(100+x*20+2,100+y*20+2,100+x*20+18,100+y*20+18);
		}//end of initialisation

	mouse_status mouse;
	mouse = status();
	show_mouse();
	char quit = 0;
	while (!quit)
	{
		mouse = status();
		if (mouse.button && inarea(mouse.x,mouse.y,139,268,248,290))
		{
			quit = 1;
			setcolor(8);
			rectangle(140,270,249,291);
			xclick();
		}//quitting
		else if (inarea(mouse.x,mouse.y,100,100,260,260) && mouse.button)
		{
			int x = (mouse.x - 100) / 20;
			int y = (mouse.y - 100) / 20;

			if (mouse.button == LEFT_CLICK)
				pattern[x][y] = 1;
			else if (mouse.button == RIGHT_CLICK)
				pattern[x][y] = 0;
			setfillstyle(SOLID_FILL,pattern[x][y] *8+1);
			hide_mouse();
			bar(100+x*20+2,100+y*20+2,100+x*20+18,100+y*20+18);
			putpixel(105+x,265+y,pattern[x][y] * 10+1);
			putpixel(105+8+x,265+y,pattern[x][y] * 10+1);
			putpixel(105+x,265+y+8,pattern[x][y] * 10+1);
			putpixel(105+8+x,265+8+y,pattern[x][y] * 10+1);
			show_mouse();
		}//doing work
	}//end of main quit

	StatusLine("Press F1 for help",__LINE__,__FILE__);
	for (x=0;x < 8;x++)
			cuspattern[x] =0;
	for (x=0;x<8;x++)
	for (y=0;y<8;y=y+1)
		cuspattern[x] =cuspattern[x] + pattern[y][x] * pow(2,7-y);
	hide_mouse();
	putimage(100,100,scr,COPY_PUT);
	free(scr);
	show_mouse();
	loadcur("cursor","word",0,0);
}//end of pattern

void lines()
{
loadcur("cursor","fillstyle",8,8);
int x = 200,y = 200;
int quit = 0;
char *sc = (char *)malloc(imagesize(0,0,264,70));
if (sc == NULL)
	error("Cannot allocate memory for sc",__FILE__,__LINE__);
mouse_status mouse;
hide_mouse();
getimage(x,y,x+264,y+70,sc);
loadbmp("lines.vsn",x,y);
for (int i =0 ;i < 16;i++)
	{
	setfillstyle(SOLID_FILL,((unsigned int)pow(2,i) & upattern) >> i);
	bar(x+15+i*15,y+40,x+15+i*15+10,y+30);
	}//end of drawing current pattern
show_mouse();
position_mouse(x +15,y+35);
setcolor(color);
while (!quit)
{
	mouse = status();
	gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);

	if (inarea(mouse.x,mouse.y,x+15,y+30,x+15+15*16,y+40) && mouse.button != 0)
		{
			hide_mouse();
			mouse.x = (mouse.x-x-15)/15;
			if (mouse.button == LEFT_CLICK)
				upattern = upattern | (unsigned int)pow(2,mouse.x);
			else if (mouse.button == RIGHT_CLICK)
				upattern = upattern & ~((unsigned int)pow(2,mouse.x));


			setfillstyle(SOLID_FILL,((unsigned int)pow(2,mouse.x) & upattern) >> mouse.x);
			bar(15*mouse.x+x+15,y+30,10+x+15+mouse.x*15,y+40);

			setcolor(7);
			setlinestyle(0,0,3);line(x+20,y+55,x+16*15-5,y+55);
			setcolor(color);setlinestyle(4,upattern,thickness);
			line(x+20,y+55,x+16*15-5,y+55);
			show_mouse();
		}//end of inarea
		else if (!inarea(mouse.x,mouse.y,x,y,x+264,y+70) && mouse.button != 0)
			quit = 1;
		else if (inarea(mouse.x,mouse.y,248+x,6+y,258+x,16+y) && mouse.button == LEFT_CLICK)
			quit = 1;
}//end of main quit loop
line_style = 4;
hide_mouse();
putimage(x,y,sc,COPY_PUT);
free(sc);
show_mouse();
loadcur("cursor","word",0,0);
}

void print()
{
	xclick();
	StatusLine("Click to start typing text",__LINE__,__FILE__);
	mouse_status mouse;
	setactivepage(1);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	mouse = click();
	char *result = (char *)calloc(1,100);
	StatusLine("Press 'ESC' to quit this mode",__LINE__,__FILE__);
	int quit = 0;
	int x = mouse.x*80/getmaxx()+1;
	int y = mouse.y*25/getmaxy()+1;
	int key = 0;
	int sx = x;
	while (!quit)
	{
		key = 0;
		if (kbhit())
			key = getch();
		if (key == 27)
			quit = 1;
		else if (key >=32 && key < 255 && x < 80)
				{
				hide_mouse();
				gotoxy(x++,y);printf("%c",key);
				char t[2];
				t[0] = key;t[1] = NULL;
				strcat(result,t);
				show_mouse();
				}
		else if (key == 8 && strlen(result) > 0)
		{
		x-=2;
		y--;
		hide_mouse();
		result[strlen(result) -1] = NULL;
		char *sc = (char *)malloc(imagesize(0,0,20,20));
		setactivepage(1);
		getimage(x*((float)getmaxx()/(float)80),y*((float)getmaxy()/(float)25),
		(x+1)*((float)getmaxx()/(float)80),(y+1)*((float)getmaxy()/(float)25),sc);
		setactivepage(0);
		putimage(x*((float)getmaxx()/(float)80),y*((float)getmaxy()/(float)25),sc,COPY_PUT);
		show_mouse();
		free(sc);
		y++;x++;
		}//end of backspace
	}
	FILE* fp;
	fp=fopen(filetmp,"at");
	if (fp ==NULL)
		 error("Text : ERROR OPENMING FILE",__FILE__,__LINE__);
	if (strlen(result) != 0)
		fprintf(fp,"print %03d,%03d,%s\n",sx,y,result);
	fclose(fp);
	free(result);
	StatusLine("Strike F1 for help",__LINE__,__FILE__);
}


