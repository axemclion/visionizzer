class electronics
{
public :
	int x2,y2,x1,y1,x3,y3;
	char file[20];

	electronics();
	electronics(int,int,int,int,int,int,char[]);
	void draw();
	int action();
};

void electronics::draw()
{
	loadbmp(file,x1,y1-11);
}

int electronics::action()
{
	mouse_status mouse;
	mouse = status();
	if (mouse.button == 0)
		return 2;
	//sample statements for label
	return 1;
}

electronics::electronics(int ax1,int ay1,int ax2,int ay2,int ax3,int ay3,char atext[100])
{
	x1 = ax1;
	x2 = ax2;
	x3 = ax3;
	y1 = ay1;
	y2 = ay2;
	y3 = ay3;
	strcpy(file,atext);
}//end of parameterised constructor

typedef electronics capacitor ;
typedef electronics resistor;
typedef electronics battery;
typedef electronics inductor;
typedef electronics ekey;
typedef electronics diode;
typedef electronics not;
typedef electronics and;
typedef electronics or;
typedef electronics delivery;

class progbar
{
public:
	int x1,y1,x2,y2,max,min,val;

	progbar();
	progbar(int,int,int,int,int,int,int);
	void draw();
	int action();
};


void progbar::draw()
{
setcolor(8);
rectangle(x1,y1,x2,y2);
setcolor(15);
line(x2,y2,x2,y1);
line(x2,y2,x1,y2);
setcolor(0);
rectangle(x2-1,y2-1,x1+1,y1+1);
setcolor(7);
line(x2-1,y2-1,x2-1,y1+1);
line(x2-1,y2-1,x1+1,y2-1);
setfillstyle(1,1);
bar(x1+3,y1+3,x1+val*(x2-x1-3)/(max-min),(y2-2));
setfillstyle(1,15);
bar(x2-3,y1+3,x1+val*(x2-x1-3)/(max-min),(y2-2));
}

progbar::progbar()
{
x2=100;
y2=100;
x1=200;
y1=200;
max=100;
min=0;
val=40;
}

progbar::progbar(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int aval)
{
	x2 =ax2;
	y2 =ay2;
	x1 =ax1;
	y1 =ay1;
	max=amax;
	min=amin;
	val=aval;
}//end of parameterised constructor

int progbar::action()
{
//sample statements for label
return 1;
}
void edit(char *fname,int max,int x1,int y1,int fore=15,int back=0)
{
				int key=0;
				int count =strlen(fname);
				while (key != 13 && key !=27)
				{
					position_mouse(x1+10+textwidth(fname),y1);
					key = -1;
					if (kbhit())
						key = getch();

					char a[2];
					if (key == 8 && strlen(fname) > 0)
						{
						hide_mouse();
						char *b = (char *)calloc(1,strlen(fname)+3);
						strncpy(b,fname,strlen(fname)-1);
						setcolor(back);
						outtextxy(x1,y1,fname);
						strcpy(fname,b);
						setcolor(fore);
						outtextxy(x1,y1,fname);
						free(b);
						count--;
						show_mouse();
						}//end of backspace
					if (key >= 32 && key < 126 && count < max)
						{
						setcolor(fore);
						count++;
						sprintf(a,"%c",key);
						strcat(fname,a);
						hide_mouse();
						outtextxy(x1,y1,fname);
						position_mouse(x1+10+textwidth(fname),y1);
						show_mouse();
						}
				}//end of word typed
}//end of tex editing
class label
{
public :
	int x2,y2;
	int x1,y1;
	int x3,y3;
	char text[100];

	label();
	label(int,int,int,int,int,int,char[]);
	void draw();
	int action();
};

label::label(int ax1,int ay1,int ax2,int ay2,int ax3,int ay3,char atext[100])
{
	x1 = ax1;
	x2 = ax2;
	x3 = ax3;
	y1 = ay1;
	y2 = ay2;
	y3 = ay3;
	strcpy(text,atext);
}//end of parameterised constructor

void label::draw()
{
	setcolor(8);
	rectangle(x2-1,y2-1,x1,y1);
	setcolor(15);
	rectangle(x2,y2,x1+1,y1+1);
	outtextxy((x1+x2)/2,(y1+y2)/2,text);
}

label::label()
{
x2=100;
y2=100;
x1=200;
y1=200;
x3=150;
y3=150 ;
}

int label::action()
{
return 2;
}




class textbox
{
public :
	int x2,y2;
	int x1,y1;
	int x3,y3;
	char text[100];

	textbox();
	textbox(int,int,int,int,int,int,char[]);
	void draw();
	int action();
};

textbox::textbox(int ax1,int ay1,int ax2,int ay2,int ax3,int ay3,char atext[100])
{
	x1 = ax1;
	x2 = ax2;
	x3 = ax3;
	y1 = ay1;
	y2 = ay2;
	y3 = ay3;
	strcpy(text,atext);
}//end of parameterised constructor

void textbox::draw()
{
setcolor(15);
setfillstyle(1,15);
settextjustify(LEFT_TEXT,TOP_TEXT);
bar(x1,y1,x2,y2);
setlinestyle(0,0,1);
rectangle(x2,y2,x1,y1);
settextstyle(12,0,1);
setcolor(8);
line(x2,y2,x1,y2);
line(x2,y2,x2,y1);
setcolor(0);
rectangle(x2-2,y2-2,x1,y1);
outtextxy(x1+4,(y1+y2)/2,text);
}

textbox::textbox()
{
x2=100;
y2=100;
x1=200;
y1=200;
x3=150;
y3=150;
}

int textbox::action()
{
	extern mouse_status mouse;
	extern int key;
	extern int focus;

	if (mouse.button != LEFT_CLICK)
		return 2;

	char *ed__ = (char *)calloc(1,100);
	strcpy(ed__,text);
	edit(ed__,(x2-x1)/textwidth("_"),x1+4,(y1+y2)/2,0,15);
	free(ed__);
	strcpy(text,ed__);
	return 1;
}



class slider
{
public :

	int x2,y1,x1,y2,max,min,val;

	void draw();
	slider();
	int action();
	slider(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int aval);
};

slider::slider(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int aval)
{
	x2 =ax2;
	y2 =ay2;
	x1 =ax1;
	y1 =ay1;
	max=amax;
	min=amin;
	val=aval;
}//end of parameterised constructor

void slider::draw()
	{
	setlinestyle(1,0,1);
	setlinestyle(0,0,1);
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
	setcolor(8);
	line(x2,y1+2,x1,y1+2);
	setcolor(15);
	line(x2,y1+3,x1,y1+3);
	setcolor(8);
	line(x1+val*(x2-x1)/(max-min),y1+3,x1+5+val*(x2-x1)/(max-min),y1+8);
	line(x1+5+val*(x2-x1)/(max-min),y1+8,x1+5+val*(x2-x1)/(max-min),y1+15);
	line(x1+5+val*(x2-x1)/(max-min),y1+15,x1-5+val*(x2-x1)/(max-min),y1+15);
	setcolor(15);
	line(x1+val*(x2-x1)/(max-min),y1+3,x1-5+val*(x2-x1)/(max-min),y1+8);
	line(x1-5+val*(x2-x1)/(max-min),y1+8,x1-5+val*(x2-x1)/(max-min),y1+15);
	line(x1,y1+3,x2,y1+3);
	}

slider::slider()
{
	x2=100;
	y2=100;
	x1=200;
	y1=200;
	max=100;
	min=0;
	val=40;
}

int slider::action()
{
	extern mouse_status mouse;
	extern int key;
	extern int focus;
	mouse = status();
	if (mouse.button != LEFT_CLICK)
		return 2;
	{char word[64] = {255,254,255,253,255,251,255,247,255,239,255,239,255,239,255,239,255,239,255,239,255,239,255,239,255,255,255,255,255,255,255,255,128,1,64,2,32,4,16,8,8,16,8,16,8,16,8,16,8,16,8,16,8,16,248,31,0,0,0,0,0,0,0,0};
	mouse_change(word,8,8);}
	hide_mouse();
	setfillstyle(SOLID_FILL,7);
	bar(x1-5,y1+4,x2+5,y2);
	show_mouse();
	bind_mouse(x1,y1+12,
			x2,y1+12);
	mouse = status();
	while(mouse.button != 0)
		mouse = status();
	hide_mouse();
	mouse = status();
	mouse_present();position_mouse(mouse.x,mouse.y);
	float t = (float)(mouse.x-x1)/(float)(x2-x1)*100;
	val = t;
	draw();
	show_mouse();
	return 1;
}



class command
{

public :
	int x2,y2;
	int x1,y1;
	int x3,y3;
	char text[100];

	command();
	command(int,int,int,int,int,int,char[]);
	void draw();
	int action();
};

command::command()
{
	x1=y1=100;
	x2=y2=200;
	x3=y3=150;
	strcpy(text,"Command");
}//end of constructor

command::command(int ax1,int ay1,int ax2,int ay2,int ax3,int ay3,char atext[100])
{
	x1 = ax1;
	x2 = ax2;
	x3 = ax3;
	y1 = ay1;
	y2 = ay2;
	y3 = ay3;
	strcpy(text,atext);
}//end of parameterised constructor

void command::draw()
{
	setlinestyle(0,0,1);
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
	setcolor(8);
	rectangle(x2,y2,x1,y1);
	setcolor(15);
	line(x1,y1,x1,y2);
	line(x1,y1,x2,y1);
	settextstyle(12,0,1);
	settextjustify(1,1);
	setcolor(15);
	outtextxy((x1+x2)/2,(y1+y2)/2,text);
}//end of drawing

int command::action()
{
	extern mouse_status mouse;
	extern int key;
	extern int focus;
	mouse = status();
	if (mouse.button == 0)
		return 2;
	hide_mouse();
	setcolor(8);
	rectangle(x1,y1,x2,y2);
	setcolor(15);
	line(x1,y2,x2,y2);
	line( x2, y1, x2, y2);
	show_mouse();
	xclick();
	hide_mouse();
	setcolor(15);
	rectangle( x1, y1, x2, y2);
	setcolor(8);
	line( x1, y2, x2, y2);
	line( x2, y1, x2, y2);
	show_mouse();
	return 1;
}


class hsb
{
public:
	int x1,y1,x2,y2,max,min,val;

	hsb();
	hsb(int,int,int,int,int,int,int);
	void draw();
	int action();
};

void hsb::draw()
{
	setfillstyle(1,7);
	bar(x1,y1,x2,y2);
	setcolor(15);
	rectangle(x1,y1,x2,y2);
	sector(x1+(y2-y1),(y1+y2)/2,270,90,(y2-y1)-4,(y2-y1)/2-4);
	ellipse(x2-(y2-y1),(y1+y2)/2,0,90,(y2-y1)-4,(y2-y1)/2-4);
	line(x2-(y2-y1),y1+4,x2-(y2-y1),y2-4);
	ellipse(x1+(y2-y1)+12+val*(x2-x1-24-2*(y2-y1))/(max-min),(y2+y1)/2,0,360,10,(y2-y1)/2-4);
	setcolor(8);
	ellipse(x1+(y2-y1)+12+val*(x2-x1-24-2*(y2-y1))/(max-min),(y1+y2)/2,225,45,10,(y2-y1)/2-4);
	ellipse(x1+(y2-y1),(y2+y1)/2,180,270,(y2-y1)-4,(y2-y1)/2-4);
	ellipse(x2-(y2-y1),(y2+y1)/2,270,0,(y2-y1)-4,(y2-y1)/2-4);
	line(x2,y1,x1,y1);
	line(x1,y2,x1,y1);
}

hsb::hsb()
{
	x2=100;
	y2=100;
	x1=200;
	y1=200;
	max=100;
	min=0;
	val=40;
}//end of default constructor

hsb::hsb(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int aval)
{
	x2 =ax2;
	y2 =ay2;
	x1 =ax1;
	y1 =ay1;
	max=amax;
	min=amin;
	val=aval;
}//end of parameterised constructor

int hsb::action()
{
	extern mouse_status mouse;
	extern int focus;
	mouse = status();
	if (mouse.button != LEFT_CLICK)
		return 2;
	if (inarea(mouse.x,mouse.y,
				 x1, y1,
				 x1+ y2- y1, y2) && val > min)
			val--;
	else if (inarea(mouse.x,mouse.y,
				 x2, y1,
				 x2-( y2- y1), y2) && val < max)
			val++;
	else if (inarea(mouse.x,mouse.y,
	 x1+( y2- y1)+11, y1,
	 x2-( y2- y1)-11, y2))
		{
		char word[64] = {63,252,207,243,247,239,255,223,255,191,255,191,255,127
		,255,127,255,127,255,127,255,191,255,191,255,223,255,255,255,255,255
		,255,192,3,48,12,8,16,4,32,2,64,2,64,1,128,1,128,1,128,1,128,2,64,2,64,
		4,32,8,16,48,12,192,3};
		mouse_change(word,8,8);
		setfillstyle(1,7);
		hide_mouse();
		bar( x1 - y1 +  y2+2, y1+3,
		 x2 +  y1 -  y2-2, y2-3);
		show_mouse();
		bind_mouse(
		 x2-( y2- y1)-11,
		( y2+ y1)/2,
		 x1+( y2- y1)+11,
		( y2+ y1)/2);
		while (mouse.button != 0)
			{
			mouse = status();
			}//end of drawgging
		val = (float)(mouse.x- x1-( y2- y1)-12)/
			(float)( x2- x1-24-2*( y2- y1))
			*(float)(max-min);
		mouse = status();
		mouse_present();
		position_mouse(mouse.x,mouse.y);
		show_mouse();
		}//end of dragging*/
	hide_mouse();
	setfillstyle(1,7);
	bar( x1 - y1 +  y2+2, y1+3,
	 x2 +  y1 -  y2-2, y2-3);

	setcolor(15);
	ellipse( x1+( y2- y1)+12+val*(float)( x2-
	 x1-24-2*( y2- y1))/(float)(max-min),(
	 y1+ y2)/2
	,0,360,
	10,( y2- y1)/2-4);
	setcolor(8);
	ellipse( x1+( y2- y1)+12+val*(float)( x2-
	 x1-24-2*( y2- y1))/(float)(max-min),(
	 y1+ y2)/2
	,225,45,
	10,( y2- y1)/2-4);
	show_mouse();
	return 1;
}

class vsb
{
public:

	int x1,y1,x2,y2,max,min,val;
	vsb();
	void draw();
	int action();
	vsb(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int aval);
};

vsb::vsb(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int aval)
{
	x2 =ax2;
	y2 =ay2;
	x1 =ax1;
	y1 =ay1;
	max=amax;
	min=amin;
	val=aval;
}//end of parameterised constructor


void vsb::draw()
{
	setfillstyle(1,7);
	bar(x2,y2,x1,y1);
	setcolor(15);
	rectangle(x2,y2,x1,y1);
	sector((x1+x2)/2,y1+(x2-x1),0,180,(x2-x1)/2-4,(x2-x1)-4);
	sector((x1+x2)/2,y2-(x2-x1),180,360,(x2-x1)/2-4,(x2-x1)-4);
	ellipse((x1+x2)/2,y1+(x2-x1)+12+val*(y2-y1-24-2*(x2-x1))/(max-min),45,225,(x2-x1)/2-4,10);
	setcolor(8);
	ellipse((x1+x2)/2,y1+(x2-x1)+12+val*(y2-y1-24-2*(x2-x1))/(max-min),225,45,(x2-x1)/2-4,10);
	ellipse((x1+x2)/2,y1+(x2-x1),0,90,(x2-x1)/2-4,(x2-x1)-4);
	ellipse((x1+x2)/2,y2-(x2-x1),270,360,(x2-x1)/2-4,(x2-x1)-4);
	line(x2,y1,x1,y1);
	line(x1,y2,x1,y1);
}//end of drawing events

vsb::vsb()
{
	x2=100;
	y2=100;
	x1=200;
	y1=200;
	max=100;
	min=0;
	val=40;
}

int vsb::action()
{
	extern mouse_status mouse;
	extern int focus;
	mouse = status();
	if (mouse.button != LEFT_CLICK)
		return 2;
	if (inarea(mouse.x,mouse.y,
				x1,y1,
				x2,y1+x2-x1) && val > min)
		val--;
	else if (inarea(mouse.x,mouse.y,
				x1,y2,
				x2,y2-(x2-x1)) && val < max)
		val++;

	else if (inarea(mouse.x,mouse.y,
	x1,y1+(x2-x1)+11,
	x2,y2-(x2-x1)-11))
		{
		char word[64] = {63,252,207,243,247,239,255,223,255,191,255,191,255,127
		,255,127,255,127,255,127,255,191,255,191,255,223,255,255,255,255,255
		,255,192,3,48,12,8,16,4,32,2,64,2,64,1,128,1,128,1,128,1,128,2,64,2,64,
		4,32,8,16,48,12,192,3};
		mouse_change(word,8,8);
		setfillstyle(1,7);
		hide_mouse();
		bar(x1+3,y1 -x1 + x2+2,
		x2-3,y2 + x1 - x2-2);
		show_mouse();
		bind_mouse((x2+x1)/2,y2-(x2-x1)-11,
		(x2+x1)/2,y1+(x2-x1)+11);
		while (mouse.button != 0)
			mouse = status();
		val = (float)(mouse.y-y1-(x2-x1)-12)/
			(float)(y2-y1-24-2*(x2-x1))
			*(float)(max-min);
		mouse = status();
		mouse_present();
		position_mouse(mouse.x,mouse.y);
		show_mouse();
		}//end of dragging
	hide_mouse();
	setfillstyle(1,7);
	bar(x1+3,y1 -x1 + x2+2,
	x2-3,y2 + x1 - x2-2);
	setcolor(8);
	ellipse((x1+x2)/2,
	y1+(x2-x1)+12+val*(float)(y2-
	y1-24-2*(x2-x1))/(float)(max-min)
	,0,360,
	(x2-x1)/2-4,10);
	setcolor(15);
	ellipse((x1+x2)/2,
	y1+(x2-x1)+12+val*(float)(y2-
	y1-24-2*(x2-x1))/(float)(max-min)
	,45,225,
	(x2-x1)/2-4,10);
	show_mouse();
	return 1;
}

class chkbox
{
public :
	int x2,y2;
	int x1,y1;
	int x3,y3;
	char file[100];

	chkbox();
	chkbox(int ax1,int ay1,int ax2,int ay2,int ax3,int ay3,char atext[100]);
	void draw();
	int action();
};

chkbox::chkbox(int ax1,int ay1,int ax2,int ay2,int ax3,int ay3,char atext[100])
{
	x1 = ax1;
	x2 = ax2;
	x3 = ax3;
	y1 = ay1;
	y2 = ay2;
	y3 = ay3;
	strcpy(file,atext);
}//end of parameterised constructor


void chkbox::draw()
{
	loadbmp(file,x1,y1);
}

chkbox::chkbox()
{
x2=100;
y2=100;
x1=200;
y1=200;
strcpy(file,"check.xyz");
}

int chkbox::action()
{
	extern mouse_status mouse;
	extern int key;
	extern int focus;

	if (mouse.button == 0)
		return 2;
	if (mouse.button == LEFT_CLICK)
		strcpy(file,"nocheck.xyz");
	else if (mouse.button == RIGHT_CLICK)
		strcpy(file,"check.xyz");
	draw();
	xclick();
	return 1;
}

class cirbar
{
public:
	int x1,y1,x2,y2,max,min,val,style;

	void draw();
	cirbar();
	int action();
	cirbar(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int ava,int astyle);
};
cirbar::cirbar(int ax1,int ay1,int ax2,int ay2,int amax,int amin,int ava,int astyle)
{
	x2 =ax2;
	y2 =ay2;
	x1 =ax1;
	y1 =ay1;
	max=amax;
	min=amin;
	val=ava;
	style = astyle;
}//end of parameterised constructor


void cirbar::draw()
{
setlinestyle(1,0,1);
setfillstyle(1,7);
bar(x2-1,y2-1,x1+1,y1+1);
setfillstyle(9,7);
sector((x1+x2)/2,(y1+y2)/2,0,360,(x2-x1)/2,(y2-y1)/2);
setfillstyle(style,1);
sector((x1+x2)/2,(y1+y2)/2,0,val*360/(max-min),(x2-x1)/2,(y2-y1)/2);
setcolor(8);
ellipse((x1+x2)/2,(y1+y2)/2,45,225,(x2-x1)/2,(y2-y1)/2);
}

cirbar::cirbar()
{
x2=100;
y2=100;
x1=200;
y1=200;
max=100;
min=0;
val=40;
style=1;
}

int cirbar::action()
{
	return 2;
}

