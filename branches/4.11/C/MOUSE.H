/***********DOS Compatiable only **************/

#define RIGHT_CLICK 2
#define LEFT_CLICK 1
#define BOTH_CLICK 3
#define MIDDLE_CLICK 4
#define NO_CLICK 0

# define max(a,b) (a>b ? a:b)
# define min(a,b) (a<b ? a:b)

struct quad
{
	int x1,x2,y1,y2;
};

int inarea(int a,int b,int x,int y,int x1,int y1)
{
if (a > min(x1,x) && a < max(x1,x) && b> min(y,y1) && b < max(y1,y))
	return 1;
else
	return 0;
}

int mouse_present()
{
	REGS mousein,mouseout;
	mousein.x.ax=0;
	int86(0x33,&mousein,&mouseout);

	if (mouseout.x.ax == 1)
		{
		# define MOUSE__ 1
		}
return 0;
}

struct mouse_status
{
	int button;
	int x;
	int y;
};

void position_mouse(int x,int y)
{
	REGS in__,out__;
	in__.x.ax=4;
	in__.x.cx=x;
	in__.x.dx=y;
	int86(0x33,&in__,&out__);
}


mouse_status status()
{
	REGS in__,out__;
	in__.x.ax=3;
	int86(0x33,&in__,&out__);
	mouse_status mouse;
	mouse.button=out__.h.bl;
	mouse.x=out__.x.cx;
	mouse.y=out__.x.dx;
	return mouse;
}

mouse_status click()
{
	REGS in__,out__;
	in__.x.ax=3;
	int86(0x33,&in__,&out__);
	mouse_status mouse;
	mouse.button=out__.h.bl;
	mouse.x=out__.x.cx;
	mouse.y=out__.x.dx;
	if (out__.h.bl)
		{
			while (out__.h.bl)
				{
						int86(0x33,&in__,&out__);
				}
		}
	return mouse;
}

void hide_mouse()
{
	REGS in__,out__;
	in__.x.ax=2;
	int86(0x33,&in__,&out__);
}
void show_mouse()
{
	REGS in__,out__;
	in__.x.ax=1;
	int86(0x33,&in__,&out__);
}

mouse_status xclick()
{

	mouse_status mouse;
	mouse.button =0;

	while (!mouse.button)
	{
		mouse=status();
	}

	while (mouse.button)
	{
		mouse=status();
	}
	return mouse;
}

void bind_mouse(int x1,int y1,int x2,int y2)
{
	REGS i;
	i.x.ax=7;
	i.x.cx=x1;
	i.x.dx=x2;
	int86(0x33,&i,&i);
	i.x.ax=8;
	i.x.cx=y1;
	i.x.dx=y2;
	int86(0x33,&i,&i);
}

void mouse_change(char cursor[],int x=8,int y=8)
{
	char b[64];
	for (int o_i=0;o_i<64;o_i++)
		b[o_i] = cursor[o_i];
	REGS _i;
	SREGS _s;
	_i.x.ax=9;
	_i.x.bx = x;
	_i.x.cx=y;
	_i.x.dx = FP_OFF(cursor);
	_s.es = FP_SEG(cursor);
	int86x(0x33,&_i,&_i,&_s);
}


void anim(char word[][64],int maxcount,int del = 5,int hotx=8,int hoty=8)
{
static int count = 0;
struct time t;
gettime(&t);
static unsigned int basetime =t.ti_sec *100+t.ti_hund+t.ti_min*6000+t.ti_hour*360000;
unsigned int times =t.ti_sec *100+t.ti_hund+t.ti_min*6000+t.ti_hour*360000;
/********time calculated*************/
if (times-basetime > del)
	{
	count++;
	if (count > maxcount-1)
		count = 0;
	mouse_change(word[count],hotx,hoty);
	hide_mouse();
	show_mouse();
	basetime =t.ti_sec *100+t.ti_hund+t.ti_min*6000+t.ti_hour*360000;
	times =t.ti_sec *100+t.ti_hund+t.ti_min*6000+t.ti_hour*360000;
	}//end of animation
}//end of animation

void revert()
{
char normal[64] = {255,63,255,31,255,15,255,7,255,3,255,1,255,0,127,0,63,0,31,0,255,1,255,16,255,48,127,248,127,248,127,252,0,0,0,64,0,96,0,112,0,120,0,124,0,126,0,127,128,127,0,124,0,108,0,70,0,6,0,3,0,3,0,0};
mouse_change(normal,0,0);
}
