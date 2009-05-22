class button
{
	int x2,y2,x1,y1;

	public:

	char text[100];
	button();
	void init(int a,int b,int c,int d,char *text1);
	button(int a,int b,int c,int d,char *text1);
	int in(int,int);
	void draw();
	void depress();
	void up();
	int lclick(int,int);
};

	int button::in(int ax,int ay)
	{
		return inarea(ax,ay,x1,y1,x2,y2);
	}

	void button::draw()
	{
		setlinestyle(0,0,1);
		setcolor(15);
		rectangle(x2,y2,x1,y1);
		setfillstyle(1,7);
		int x3,y3;
		x3 = min(x1,x2)+abs(x2-x1)/2-textwidth(text)/2;
		y3 = min(y1,y2)+abs(y2-y1)/2-textheight(text)/2;
		floodfill(x3,y3,15);
		setcolor(8);
		line(x1,y1,x1,y2);
		line(x1,y1,x2,y1);
		settextstyle(12,0,1);
		setcolor(0);
		outtextxy(x3,y3,text);
	}//end of drawing button

	void button::up()
	{
	hide_mouse();
	setcolor(15);
	rectangle(x1,y1,x2,y2);
	setcolor(8);
	line(x1,y1,x1,y2);
	line(x1,y1,x2,y1);
	show_mouse();
	}//end of depressoing button

	void button::depress()
	{
	hide_mouse();
	setcolor(8);
	rectangle(x1,y1,x2,y2);
	setcolor(15);
	line(x1,y1,x1,y2);
	line(x1,y1,x2,y1);
	show_mouse();

	}//end of button uping
	button::button()
	{
		x1 = x2=y1=y2=0;
	}

	void button::init(int a,int b,int c,int d,char *text1)
	{
		x1=max(a,c);
		x2=min(a,c);
		y1=max(b,d);
		y2=min(d,b);
		strcpy(text,text1);
	 }


	button::button(int a,int b,int c,int d,char *text1)
	{
		x1=max(a,c);
		x2=min(a,c);
		y1=max(b,d);
		y2=min(d,b);
		strcpy(text,text1);
	 }

	int button::lclick(int ax,int ay)
	{
		if (in(ax,ay))
		{
			mouse_status mouse = status();
			if (mouse.button != 0)
				{
				setfillstyle(SOLID_FILL,7);
				bar(x1,y1,x2,y2);
				setcolor(8);
		int x3,y3;
		x3 = min(x1,x2)+abs(x2-x1)/2-textwidth(text)/2;
		y3 = min(y1,y2)+abs(y2-y1)/2-textheight(text)/2;
				outtextxy(x3+1,y3+1,text);
				depress();
				}
			while (mouse.button != 0)
				mouse=status();
				setfillstyle(SOLID_FILL,7);
				bar(x1,y1,x2,y2);
				setcolor(8);
		int x3,y3;
		x3 = min(x1,x2)+abs(x2-x1)/2-textwidth(text)/2;
		y3 = min(y1,y2)+abs(y2-y1)/2-textheight(text)/2;
				outtextxy(x3,y3,text);

				up();
		if (inarea(mouse.x,mouse.y,x1,y1,x2,y2))
			return 1;
		else
			return 0;
		}//end of inside area
		else
			return 0;

	}//end of clickig
