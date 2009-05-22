/***********DOS Compatiable only **************/

#define RIGHT_CLICK 2
#define LEFT_CLICK 1
#define BOTH_CLICK 3
#define MIDDLE_CLICK 4
#define NO_CLICK 0

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


mouse_status down()
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
		mouse=down();
	}

	while (mouse.button)
	{
		mouse=down();
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