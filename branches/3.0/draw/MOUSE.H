/***********DOS Compatiable only **************/

#define RIGHT_CLICK 2
#define LEFT_CLICK 1
#define BOTH_CLICK 3
#define MIDDLE_CLICK 4
#define NO_CLICK 0

# define max(a,b) (a>b ? a:b)
# define min(a,b) (a<b ? a:b)

int inarea(int a,int b,int x,int y,int x1,int y1)
{
if (a > min(x1,x) && a < max(x1,x) && b> min(y,y1) && b < max(y1,y))
	return 1;
else
	return 0;
}

char _TEXT_CUR[64] = {0x0,0x0,0xfd,0xbf,0xfb,0xdf,0x7,0xe0,0xdf,0xfb,0xdf,0xfb,0xdf,0xfb,0x5f,0xfa,0x5f,0xfa,0xdf,0xfb,0xdf,0xfb,0xdf,0xfb,0x9f,0xf9,0x3f,0xfc,0x7f,0xfe,0x7f,0xfe,0xff,0xff,0x2,0x40,0x4,0x20,0xf8,0x1f,0x20,0x4,0x20,0x4,0x20,0x4,0xa0,0x5,0xa0,0x5,0x20,0x4,0x20,0x4,0x20,0x4,0x60,0x6,0xc0,0x3,0x80,0x1,0x80,0x1};
char _TARGET_CUR[64] = {127,254,63,252,15,240,71,226,115,206,243,207,249,159,224,7,224,7,249,159,243,207,115,206,71,226,15,240,63,252,127,254,128,1,192,3,176,13,136,17,4,32,4,32,2,64,143,241,143,241,2,64,4,32,4,32,136,17,176,13,192,3,128,1};

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
