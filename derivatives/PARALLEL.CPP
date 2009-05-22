#include <math.h>
#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <dos.h>
#include <string.h>
#include <mouse.h>
#include <button.cls>

# define READ_MASK 0x04
# define MAX 11

char word[6][64] = {
 {255,63,255,95,255,167,255,192,127,207,191,239,223,239,239,239,247,247,251,251,241,253,226,254,70,255,141,255,219,255,231,255,0,192,0,160,0,88,0,63,128,48,64,16,32,16,16,16,8,8,4,4,14,2,29,1,185,0,114,0,36,0,24,0},
 {255,63,255,95,255,167,255,192,127,207,191,239,223,239,239,239,231,247,195,251,137,253,30,254,62,255,189,255,219,255,231,255,0,192,0,160,0,88,0,63,128,48,64,16,32,16,16,16,24,8,60,4,118,2,225,1,193,0,66,0,36,0,24,0},
 {255,63,255,95,255,167,255,192,127,207,191,239,223,239,143,239,23,247,59,250,125,252,254,254,126,255,189,255,219,255,231,255,0,192,0,160,0,88,0,63,128,48,64,16,32,16,112,16,232,8,196,5,130,3,1,1,129,0,66,0,36,0,24,0},
 {255,63,255,95,255,167,255,192,127,207,63,232,223,232,239,233,247,243,251,251,253,253,254,254,126,255,189,255,219,255,231,255,0,192,0,160,0,88,0,63,128,48,192,23,32,23,16,22,8,12,4,4,2,2,1,1,129,0,66,0,36,0,24,0},
 {255,63,255,95,255,167,255,192,127,207,191,239,223,239,143,239,23,247,59,250,125,252,254,254,126,255,189,255,219,255,231,255,0,192,0,160,0,88,0,63,128,48,64,16,32,16,112,16,232,8,196,5,130,3,1,1,129,0,66,0,36,0,24,0},
 {255,63,255,95,255,167,255,192,127,207,191,239,223,239,239,239,231,247,195,251,137,253,30,254,62,255,189,255,219,255,231,255,0,192,0,160,0,88,0,63,128,48,64,16,32,16,16,16,24,8,60,4,118,2,225,1,193,0,66,0,36,0,24,0}};

	static int txd=0;
	static int tx[9];
	static int rx[9];
	int port  =0x378;
	char bp1;

void intro();
void drawport(int,int);


int main(void)
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
	intro();
	button quit(20,450,300,470,"Quit");
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
	anim(word,6,6,0,0);

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

		if (readport.lclick(mouse.x,mouse.y))
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
				bar(203,120+y*25+2,249,120+y*25+20);
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
					bar(203,120+i*25+2,249,120+i*25+20);
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
					bar(203,120+i*25+2,249,120+i*25+20);
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
void intro()
{
	setfillstyle(SOLID_FILL,7);
	floodfill(0,0,1);
	settextstyle(8,0,3);
	settextjustify(0,1);
	outtextxy(31,40,"Parallel Port Tester");
	setcolor(8);
	outtextxy(30,39,"Parallel Port Tester");
	settextstyle(12,0,1);
	settextjustify(LEFT_TEXT,TOP_TEXT);
	button t(20,80,300,400,"");
	t.draw();t.depress();
	t = button(320,80,620,400,"");
	t.draw();t.depress();
	char temp[70];
	setcolor(0);
	settextjustify(LEFT_TEXT,CENTER_TEXT);
	for (int i=0;i < 8;i++)
		{
			setcolor(15);
			line(370,120+i*20,570,120+i*20);
			setcolor(0);
			line(370,122+i*20,570,122+i*20);
			sprintf(temp,"Bit %1d   Pin %2d        ",i,i+2);
			outtextxy(75,135+25*i,temp);
			button  a(70,121+25*i,250,121+25*i+22,"");
			a.draw();
		}

	settextjustify(LEFT_TEXT,TOP_TEXT);
	t = button(23,83,297,100,"Output to Port");
	t.draw();
	t = button(323,83,617,100,"Input from Port");
	t.draw();
	t = button(70,120,250,120+8*25,"");
	t.draw();t.depress();
	t = button(370,120,620-50,120+8*20,"");
	t.draw();t.depress();
	t = button(369,289,571,291+64," ");
	t.draw();t.depress();
	setfillstyle(SOLID_FILL,0);
	bar(370,290,570,290 + 64);
	line (130,121,130,320);
	line (200,121,200,320);
	line (463,121,463,280);
	line (488,121,488,280);
	line (513,121,513,280);
	line (540,121,540,280);
	setcolor(0);
	line (374,126+20*4,374 + textwidth("Busy"),126+20*4);
	line(374,126+20*5,374+textwidth("Auto Feed"),126+20*5);
	line(374,126+20*7,374+textwidth("Select i/p"),126+20*7);


	line (131,121,131,320);
	line (201,121,201,320);
	line (464,121,464,280);
	line (489,121,489,280);
	line (514,121,514,280);
	line (541,121,541,280);

	outtextxy(374,128+20*0,"Error       15 +1 B3");
	outtextxy(374,128+20*1,"Select      13 +1 B4 ");
	outtextxy(374,128+20*2,"Paper End   12 +1 B5");
	outtextxy(374,128+20*3,"Ackno       10 +1 B6 ");
	outtextxy(374,128+20*4,"Busy        11 +1 B7");
	outtextxy(374,128+20*5,"Auto Feed   14 +2 B1");
	outtextxy(374,128+20*6,"Initilaise  16 +2 B2");
	outtextxy(374,128+20*7,"Select i/p  17 +2 B3");

	setfillstyle(SOLID_FILL,0);
	bar(320,405,620,478);


	button b(350,420,570,475," ");
	b.draw();
	b= button(353,423,567,472," ");
	b.draw();b.depress();
	setcolor(8);
	setfillstyle(XHATCH_FILL,8);
	line (131,121,131,320);
	line (201,121,201,320);
	line(400,465,520,465);
	line(520,465,530,430);
	setcolor(15);

	line (390,410,530,410);
	line (390,410,350,420);
	line (570,420,530,410);
	setfillstyle(SOLID_FILL,8);
	floodfill(500,411,15);

	line(390,430,530,430);
	line(390,430,400,465);

	for (i=0;i < 13;i++)
		fillellipse(400+i*10,440,3,3);
	for (i=0;i < 12;i++)
		fillellipse(405+i*10,455,3,3);
	line (407,434,483,434);
	setfillstyle(SOLID_FILL,7);
	fillellipse(370,445,6,6);
	fillellipse(550,445,6,6);
	line(366,445,374,445);
	line(546,445,554,445);
	setcolor(8);
	line(366,444,374,444);
	line(546,444,554,444);
	arc(370,445,225,45,6);
	arc(550,445,225,45,6);
}//end of intro

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
