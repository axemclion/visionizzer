#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include "d:\prog\c\mouse.h"
#include "d:\prog\c\button.cls"
#include "d:\prog\c\bmploade.cpp"

# define B 9
# define F 15
# define P 10
# define M 56/2

# define READ_MASK 0x04
# define MAX 11

char word[5][64] = {
 {255,127,255,191,255,207,255,199,15,224,240,240,254,240,255,240,255,247,255,247,255,247,255,247,255,251,255,251,255,251,255,249,0,128,0,64,0,48,0,56,240,31,15,15,1,15,1,15,1,8,7,8,8,8,8,8,248,4,136,5,0,5,0,6},
 {255,127,255,191,255,207,255,199,15,224,240,240,254,240,255,240,255,247,255,247,255,247,255,247,255,251,255,251,255,251,255,249,0,128,0,64,0,48,0,56,240,31,15,15,1,15,1,15,1,8,1,8,14,8,120,8,64,4,64,4,64,4,192,7},
 {255,127,255,191,255,207,255,199,15,224,240,240,254,240,255,240,255,247,255,247,255,247,255,247,255,251,255,251,255,251,255,249,0,128,0,64,0,48,0,56,240,31,15,15,1,15,1,15,1,8,15,8,8,8,56,8,224,5,0,5,0,5,0,6},
 {255,127,255,191,255,207,255,199,15,224,240,240,254,240,255,240,255,247,255,247,255,247,255,247,255,251,255,251,255,251,255,249,0,128,0,64,0,48,0,56,240,31,15,15,1,15,2,15,2,8,2,8,2,8,30,8,48,4,224,4,0,5,0,6},
 {255,127,255,191,255,207,255,199,15,224,240,240,254,240,255,240,255,247,255,247,255,247,255,247,255,251,255,251,255,251,255,249,0,128,0,64,0,48,0,56,240,31,15,15,1,15,1,15,1,8,231,8,184,8,128,8,128,4,128,5,0,5,0,6}};

	static int txd=0;
	static int tx[9];
	static int rx[9];
	int port  =0x378;
	char bp1;

void intro();
void drawport(int,int);


int main(int argc,char *argv[])
{
	int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
   {
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}
	mouse_present();
	if (argc < 2)
		loadbmp("parallel.bmp");
	else if (0 != loadbmp(argv[1]))
		loadbmp("parallel.bmp");

	button quit(20,450,130,470,"Quit");
	button bstop(20,420,300,440,"Stop the Receptions");
	button reset(320,20,420,40,"Reset");
	button portno(430,20,530,40,"For LPT1");
	button read(320,50,530,70,"Set Read Mask");
	button graphclear(540,20,620,70,"Clear");

	button selport(480,390,570,370,"Port+1 Log");
	button readport(370,390,460,370,"Poll Port");
	button p1(575,200,610,220," ");
	button p2(575,280,610,260," ");

	button send(70,370,250,390, "Send the data");
	button txdata(70,335,100,355,"000");
	button inctx(120,335,170,355,"+");
	button dectx(180,335,230,355,"-");

	read.draw();send.draw();txdata.draw();txdata.depress();selport.draw();
	inctx.draw();dectx.draw();bstop.draw();reset.draw();
	p1.draw();p1.depress();p2.draw();p2.depress();portno.draw();
	readport.draw();graphclear.draw();
	quit.draw();
	show_mouse();
	int exit = 0;
	int stop = 0;
	mouse_status mouse = {0,0,0};
	static char rec[MAX];
	int offport = 1;
while (!exit)
{
	if (!stop)
	{
	char b0,b1,b2;
	b0 = inportb(port);
	b1 = inportb(port+1);
	b2 = inportb(port+2);

	drawport(1,b2 & 1);

	drawport(2,b0 & 1);
	drawport(3,b0 & 2);
	drawport(4,b0 & 4);
	drawport(5,b0 & 8);
	drawport(6,b0 & 16);
	drawport(7,b0 & 32);
	drawport(8,b0 & 64);
	drawport(9,b0 & 128);

	drawport(10,b1 & 64);
	drawport(11,b1 & 128);
	drawport(12,b1 & 32);
	drawport(13,b1 & 16);
	drawport(14,b2 & 2);
	drawport(15,b1 & 8);
	drawport(16,b2 & 4);
	drawport(17,b2 & 8);

	setfillstyle(SOLID_FILL,7);

	unsigned char op=	inport(port+offport);
	if (op != rec[MAX-1])
		{
			/***drawing the various grid lines */
			setcolor(10);
			setlinestyle(1,0,1);
			line(370,322,570,322);
			line(370,306,570,306);
			line(370,338,570,338);
			/*end of drawing horiz lines*/
			rec[MAX] = op;
			moveto(370,322);
			for (int i=0;i < MAX;i++)
				{
				setcolor(0);
				lineto(370+i*20,rec[i]/4+290);
				rec[i] = rec[i+1];
				setcolor(10);
				setlinestyle(1,0,1);
				line(370+i*20,290,370+i*20,355);
				setlinestyle(0,0,1);
				}
			setcolor(14);
			moveto(370,322);
			for (i=0;i < MAX;i++)
				lineto(370+i*20,290+rec[i]/4);
			setcolor(10);
	}//end of drawing graph
}// end of receptions
	mouse = status();
	gotoxy(74,1);printf("%03d,%03d",mouse.x,mouse.y);
	anim(word,5,10,0,0);

	if (mouse.button == LEFT_CLICK || mouse.button == RIGHT_CLICK)
	{

		if (selport.lclick(mouse.x,mouse.y))
			{
			if (offport == 1)
				{
					offport = 2;
					selport = button(480,390,570,370,"Port+2 Log");
					selport.draw();
				}//end of offport == 1
			else if (offport == 2)
				{
					offport = 1;
					selport = button(480,390,570,370,"Port+1 Log");
					selport.draw();
				}//end of ofport == 2
			}//end of selecting ports
		if (portno.lclick(mouse.x,mouse.y))
			{
				if (strcmp(portno.text,"For LPT1")==0)
					{
						strcpy(portno.text,"For LPT2");
						port = 0x278;
					}
				else if (strcmp(portno.text,"For LPT2")==0)
					{
						strcpy(portno.text,"For LPT1");
						port = 0x378;
					}
			hide_mouse();
			portno.draw();
			show_mouse();
			}//end of changing the port

		else if (readport.lclick(mouse.x,mouse.y))
			{
				setfillstyle(SOLID_FILL,7);
				unsigned char c=0;
				int temp[8];
				c = inportb(port+1);
				sprintf(p1.text,"%03d",c);
				p1.draw();p1.depress();

				for (int i=0;i <8;i++)
					{
					temp[i] = c %2;
					c/=2;
					}//end of conversion
				rx[0] = temp[3];
				rx[1] = temp[4];
				rx[2] = temp[5];
				rx[3] = temp[6];
				rx[4] = temp[7];
				c = 0;
				c = inport(port+2);
				sprintf(p2.text,"%03d",c);
				p2.draw();p2.depress();

				for (i=0;i <8;i++)
					{
					temp[i] = c %2;
					c/=2;
					}//end of conversion
				rx[5] = temp[1];
				rx[6] = temp[2];
				rx[7] = temp[3];

				char t[10];
				for (i=0;i < 8;i++)
					{
					bar(553,127+20*i,568,127+20*i+10);
					sprintf(t,"%1d",rx[i]);
					outtextxy(555,128+20*i,t);
					}//end of polling
			}//read the port
		if (reset.lclick(mouse.x,mouse.y))
			{
			for (int i=0;i <8;i++)
				tx[i] = 0;
			txd = 0;
			}//end of reseting all data
		if (read.lclick(mouse.x,mouse.y))
			outportb(port+2,READ_MASK);

		if(bstop.lclick(mouse.x,mouse.y))
			{
				hide_mouse();
				if (stop == 1)
					{
					stop = 0;
					bstop = button (20,420,300,440,"Stop the Receptions");

					bstop.draw();
					}//stop = true
				else if (stop == 0)
					{
					stop = 1;
					bstop = button(20,420,300,440,"Continue the Receptions");
					bstop.draw();
					}//stop == false
				show_mouse();
			}//end of stoppage

		if(quit.lclick(mouse.x,mouse.y))
			exit = 1;

		if (inarea(mouse.x,mouse.y,540,120,570,220))
			{
				int y = mouse.y-120;
				y = y/20;
				bp1 = bp1 | (int)pow(2,y);
				outportb(port+1,bp1);
			}//end of sending to port1
		if (inarea(mouse.x,mouse.y,70,120,250,120+8*25))
			{
				int y= mouse.y-120;
				y = y/25;
				if (mouse.button == RIGHT_CLICK)
					tx[y] =0;
				if (mouse.button == LEFT_CLICK)
					 tx[y] =1;
				txd = 0;
				hide_mouse();
				for (int i=0;i<8;i++)
					txd += pow(2,i) * tx[i];
				bar(203,120+y*25+5,249,120+y*25+20);
				setcolor(0);
				char t[10];
				sprintf(t,"%1d",tx[y]);	outtextxy(240,130+y*25,t);
				sprintf(txdata.text,"%03d",txd);
				txdata.draw();txdata.depress();
				show_mouse();
			}//end of direct changng

		if (graphclear.lclick(mouse.x,mouse.y))
			{
				setfillstyle(SOLID_FILL,0);
				bar(370,290,570,290 + 64);
				for (int i=0;i < MAX;i++)
					rec[i] =0;
			}///end of clearing the graph
		if (send.lclick(mouse.x,mouse.y))
			outportb(port,txd);

		if(inctx.lclick(mouse.x,mouse.y))
			{
				txd++;
				if (txd > 255)
					txd = 0;
				int temp= txd;
				setfillstyle(SOLID_FILL,7);
				char t[10];
				for (int i=0;i<8;i++)
				{
					tx[i] = temp %2;
					temp =temp/2;
					bar(203,120+i*25+5,249,120+i*25+20);
					sprintf(t,"%1d",tx[i]);
					outtextxy(240,130+i*25,t);
				}//end of conversion

				sprintf(txdata.text,"%3d",txd);
				txdata.draw();txdata.depress();
			}//end of increasing the loop
		if(dectx.lclick(mouse.x,mouse.y))
			{
				txd--;
				if (txd < 0)
					txd = 255;
				int temp= txd;
				setfillstyle(SOLID_FILL,7);
				char t[10];
				for (int i=0;i<8;i++)
				{
					tx[i] = temp %2;
					temp =temp/2;
					bar(203,120+i*25+5,249,120+i*25+20);
					sprintf(t,"%1d",tx[i]);
					outtextxy(240,130+i*25,t);
				}//end of conversion

				sprintf(txdata.text,"%3d",txd);
				txdata.draw();txdata.depress();
			}//end of decreasing
	}//left button is clicked
}//end of main lop body

	closegraph();
	return 0;
}

void drawport(int pin,int data)
{
	pin--;
	setcolor(15);
	if (data == 0)
		setfillstyle(SOLID_FILL,12);
	else
		setfillstyle(SOLID_FILL,10);

	if (pin > 12)
		fillellipse(405+(pin-13)*10,455,3,3);
	else
		fillellipse(400+pin*10,440,3,3);

}//end of drawing the details of the port

