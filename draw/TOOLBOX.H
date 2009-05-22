void easter_egg();
void mode1(int,int);
void mode2(int,int);

int toolbox()
{
/******housekeeping********/
int mode = 1;
StatusLine("Select the action to be taken",__LINE__,__FILE__);
setlinestyle(0,0,1);
{
char word[64] = {255,31,255,7,255,1,127,128,31,128,15,192,63,192,127,224,15,224,51,241,89,243,109,251,182,255,154,255,205,255,242,255,0,224,0,216,0,166,128,81,96,72,48,36,192,34,128,17,240,19,204,10,166,12,146,4,73,0,101,0,50,0,13,0};
mouse_change(word,0,0);
}
mouse_status mouse=status();
int toolx=mouse.x;
int tooly=mouse.y;
if (toolx+120 > getmaxx()) toolx=getmaxx()-120;
if (tooly+160 > getmaxy()) tooly=getmaxy()-160;

char *buffer=(char *)malloc(imagesize(0,0,122,162));
if (!buffer) error("Toolbox\nUnable to allocate memory for screen save");

hide_mouse();
getimage(toolx,tooly,toolx+120,tooly+160,buffer);
position_mouse(toolx,tooly);
	setcolor(15);
	for (int x=toolx,y=tooly;x < toolx+120 ;x++,y++)
		{
		setcolor(7);
		rectangle(x,y,toolx,tooly);
		delay(1.5);
		}

setlinestyle(SOLID_LINE,1,1);
setcolor(15);
setfillstyle(SOLID_FILL,7);
bar(toolx,tooly,toolx+120,tooly+160);

rectangle(toolx,tooly,toolx+120,tooly+160);
setcolor(8);
line(toolx+120,tooly,toolx+120,tooly+160);
line(toolx,tooly+160,toolx+120,tooly+160);

{
for (int x=toolx;x < toolx+120;x+=40)
for (int y=tooly;y < tooly+160;y+=40)
	{
	setcolor(15);
	rectangle(x,y,x+39,y+39);
	setcolor(8);
	line(x+39,y,x+39,y+39);
	line(x,y+39,x+39,y+39);
	}
//arrows
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	bar(toolx+15,tooly+15,toolx+30,tooly+25);
	line(toolx+15,tooly+10,toolx+15,tooly+30);
	line(toolx+5,tooly+20,toolx+15,tooly+10);
	line(toolx+5,tooly+20,toolx+15,tooly+30);
	floodfill(toolx+6,tooly+20,15);

//right arrow
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	bar(toolx+120-15,tooly+15,toolx+120-30,tooly+25);
	line(toolx+120-15,tooly+10,toolx+120-15,tooly+30);
	line(toolx+120-5,tooly+20,toolx+120-15,tooly+10);
	line(toolx+120-5,tooly+20,toolx+120-15,tooly+30);
	floodfill(toolx+120-6,tooly+20,15);

}//end of drawing buttons

mode1(toolx,tooly);
show_mouse();

int result=0;
click();
/**********processing**********/
while (!result)
{
	mouse=status();
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mode);
	show_mouse();


if (mouse.button)
{
	result = -1;
	if (LEFT_CLICK==mouse.button && mouse.x >toolx && mouse.y > tooly && mouse.y < tooly+160 && mouse.x < toolx+120)
	{
{//start of animation of buttonas
	int x=mouse.x;
	int y=mouse.y;
	x = ((x-toolx)/40)*40+toolx;
	y = ((y-tooly)/40)*40+tooly;
	hide_mouse();
	setcolor(8);
	rectangle(x,y,x+39,y+39);
	setcolor(15);
	line(x+39,y,x+39,y+39);
	line(x,y+39,x+39,y+39);
	show_mouse();
	mouse_status xmouse;
		xmouse = status();
		while (xmouse.button !=0)
		{
		  xmouse = status();
		}

}//end of animation
if (mode == 2)
{
	switch (((mouse.x-toolx)/40)+(((mouse.y-tooly)/40)*3))
	{
	case 0:
		result=0;
		mode =1;
		break;
	case 1:
		result=9;break;
	case 2:
		result=0;
		mode = 1;
		break;
	case 3:
		result = '1';break;
	case 4:
		result = '2';break;
	case 5:
		result = '3';break;
	case 6:
		result = '4';break;
	case 7:
		result = ' ';break;
	case 8:
		result = ' ';break;
	case 9:
		result = ' ';break;
	case 10:
		result = ' ';break;
	case 11:
		result = ' ';break;
	}
}//end of switch case for mode2

else if (mode == 1)
	switch(((mouse.x-toolx)/40)+(((mouse.y-tooly)/40)*3))
	{
	case 0:
		result=0;
		mode =2;
		break;
	case 1://line
		result=111;break;
	case 2://circle
		result=0;
		mode = 2;
		break;
	case 3://obj
		result = 'r';break;
	case 4://properties
		result = 'l';break;
	case 5://edit
		result = 'c';break;
	case 6://text
		result= 't';break;
	case 7://pieslice
		result ='p' ;break;
	case 8://
		result ='f';break;
	case 9://thickness
		result ='w';break;
	case 10://setting
		result ='`';break;
	case 11://code
		result = '[';break;
	};//end of switch case
}//end of left click*/

	if (mouse.button != 0 && inarea(mouse.x,mouse.y,toolx,tooly,toolx+120,tooly+160))
	{
		hide_mouse();
		setcolor(15);
	for (int x=toolx,y=tooly;x < toolx+120 ;x++,y++)
		{
		setcolor(15);
		rectangle(x,y,toolx,tooly);
		delay(1.5);
		}

setlinestyle(SOLID_LINE,1,1);
setcolor(15);
setfillstyle(SOLID_FILL,7);
bar(toolx,tooly,toolx+120,tooly+160);

rectangle(toolx,tooly,toolx+120,tooly+160);
setcolor(8);
line(toolx+120,tooly,toolx+120,tooly+160);
line(toolx,tooly+160,toolx+120,tooly+160);

{
for (int x=toolx;x < toolx+120;x+=40)
for (int y=tooly;y < tooly+160;y+=40)
	{
	setcolor(15);
	rectangle(x,y,x+39,y+39);
	setcolor(8);
	line(x+39,y,x+39,y+39);
	line(x,y+39,x+39,y+39);
	}
		//arrows
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	bar(toolx+15,tooly+15,toolx+30,tooly+25);
	line(toolx+15,tooly+10,toolx+15,tooly+30);
	line(toolx+5,tooly+20,toolx+15,tooly+10);
	line(toolx+5,tooly+20,toolx+15,tooly+30);
	floodfill(toolx+6,tooly+20,15);

//right arrow
	setcolor(15);
	setfillstyle(SOLID_FILL,15);
	bar(toolx+120-15,tooly+15,toolx+120-30,tooly+25);
	line(toolx+120-15,tooly+10,toolx+120-15,tooly+30);
	line(toolx+120-5,tooly+20,toolx+120-15,tooly+10);
	line(toolx+120-5,tooly+20,toolx+120-15,tooly+30);
	floodfill(toolx+120-6,tooly+20,15);

}//end of drawing buttons
		if (mode == 1) mode1(toolx,tooly);
		else if (mode == 2) mode2(toolx,tooly);
		show_mouse();
	}//end of this click
}//end of mouse click

}//end of main loop body
	hide_mouse();
	putimage(toolx,tooly,buffer,COPY_PUT);
	free(buffer);
	show_mouse();
mouse_change(_TARGET_CUR);
show_mouse();
return result;

}//end of toolbox

void mode1(int toolx,int tooly)
{
// draw icons
setlinestyle(0,0,3);
setcolor(8);

rectangle(toolx+10,tooly+50,toolx+30,tooly+70);
line (toolx+45,tooly+45,toolx+75,tooly+75);
circle(toolx+100,tooly+60,10);

settextstyle(5,0,2);outtextxy(toolx+3,tooly+80,"AB");
setfillstyle(7,8);setlinestyle(0,0,1);sector(toolx+65,tooly+100,45,296,17,8);

//paint
setcolor(15);
setlinestyle(0,0,3);
line(toolx+110,tooly+90,toolx+90,tooly+110);
line(toolx+112,tooly+90,toolx+90,tooly+110);
setlinestyle(0,0,1);
setcolor(8);
bar(toolx+90,tooly+100,toolx+110,tooly+110);
fillellipse(toolx+100,tooly+110,10,5);
setfillstyle(0,7);
sector(toolx+100,tooly+100,0,360,10,5);
setfillstyle(6,7);
fillellipse(toolx+100,tooly+110,10,5);
setcolor(15);
ellipse(toolx+100,tooly+100,0,360,10,5);
line(toolx+90,tooly+100,toolx+90,tooly+110);
line(toolx+110,tooly+100,toolx+110,tooly+110);
ellipse(toolx+100,tooly+110,180,360,10,5);

//deleting paint
setcolor(15);
setlinestyle(0,0,3);
line(toolx+110,tooly+130,toolx+90,tooly+150);
line(toolx+112,tooly+130,toolx+90,tooly+150);
setlinestyle(0,0,1);
setcolor(8);
bar(toolx+90,tooly+140,toolx+110,tooly+150);
fillellipse(toolx+100,tooly+150,10,5);
setfillstyle(0,7);
sector(toolx+100,tooly+140,0,360,10,5);
setfillstyle(6,7);
fillellipse(toolx+100,tooly+150,10,5);
setcolor(15);
ellipse(toolx+100,tooly+140,0,360,10,5);
line(toolx+90,tooly+140,toolx+90,tooly+150);
line(toolx+110,tooly+140,toolx+110,tooly+150);
ellipse(toolx+100,tooly+150,180,360,10,5);

//exit
setfillstyle(SOLID_FILL,0);setcolor(15);
bar(toolx+50,tooly+10,toolx+70,tooly+30);
settextstyle(0,0,2);outtextxy(toolx+64,tooly+15,"<");
settextstyle(0,0,2);outtextxy(toolx+70,tooly+15,"-");
int poly[8]={toolx+65,tooly+15,toolx+65,tooly+35,toolx+50,tooly+30,toolx+50,tooly+10};
setfillstyle(INTERLEAVE_FILL,7);fillpoly(4,poly);

//properties
setfillstyle(2,7);
bar(toolx+50,tooly+130,toolx+70,tooly+150);
rectangle(toolx+50,tooly+130,toolx+70,tooly+150);

//writing code
setcolor(15);
settextstyle(10,0,2);outtextxy(toolx+3,tooly+110,"C");
setcolor(15);settextstyle(12,0,1);outtextxy(toolx+15,tooly+140,"ode");

//write shortcut keys
setcolor(8);
settextstyle(2,0,5);
outtextxy(toolx+30,tooly+25,"<");
outtextxy(toolx+61,tooly+25,"|ð)");
outtextxy(toolx+110,tooly+25,">");

outtextxy(toolx+30,tooly+65,"R");
outtextxy(toolx+70,tooly+65,"L");
outtextxy(toolx+110,tooly+65,"C");

outtextxy(toolx+30,tooly+105,"T");
outtextxy(toolx+70,tooly+105,"P");
outtextxy(toolx+110,tooly+105,"F");

outtextxy(toolx+30,tooly+145,"W");
outtextxy(toolx+61,tooly+145,"~");
outtextxy(toolx+110,tooly+145,"[");

setcolor(15);
settextstyle(2,0,5);
outtextxy(toolx+29,tooly+24,"<");
outtextxy(toolx+60,tooly+24,"|ð)");
outtextxy(toolx+109,tooly+24,">");

outtextxy(toolx+29,tooly+64,"R");
outtextxy(toolx+69,tooly+64,"L");
outtextxy(toolx+109,tooly+64,"C");

outtextxy(toolx+29,tooly+104,"T");
outtextxy(toolx+69,tooly+104,"P");
outtextxy(toolx+109,tooly+104,"F");

outtextxy(toolx+29,tooly+144,"W");
outtextxy(toolx+60,tooly+144,"~");
outtextxy(toolx+109,tooly+144,"[");

}//end of drawing mode1

void mode2(int toolx,int tooly)
{

//command button
setcolor(15);
rectangle(toolx+5,tooly+50,toolx+35,tooly+70);
setcolor(8);
line(toolx+5,tooly+70,toolx+35,tooly+70);
line(toolx+35,tooly+50,toolx+35,tooly+70);
settextstyle(2,0,2);
outtextxy(toolx+7,tooly+55,"Command");

//textbox
setcolor(8);
rectangle(toolx+45,tooly+50,toolx+75,tooly+70);
setcolor(15);
line(toolx+45,tooly+70,toolx+75,tooly+70);
line(toolx+75,tooly+50,toolx+75,tooly+70);
settextstyle(2,0,2);
outtextxy(toolx+47,tooly+55,"TextBox");

//radio buttons
setcolor(15);
ellipse(toolx+100,tooly+60,0,360,6,6);
setcolor(8);
ellipse(toolx+100,tooly+60,45,225,6,6);
setfillstyle(SOLID_FILL,8);
fillellipse(toolx+100,tooly+60,4,4);

//properties
setcolor(15);
setfillstyle(SOLID_FILL,7);
bar3d(toolx+50,tooly+130,toolx+70,tooly+150,7,1);
rectangle(toolx+57,tooly+125,toolx+77,tooly+145);
setcolor(15);

//editor;
setfillstyle(EMPTY_FILL,0);
bar(toolx+85,tooly+125,toolx+115,tooly+155);
settextstyle(2,0,1);
setcolor(15);
rectangle(toolx+85,tooly+125,toolx+115,tooly+155);
setfillstyle(SOLID_FILL,8);
bar(toolx+86,tooly+129,toolx+114,tooly+127);
outtextxy(toolx+87,tooly+130,"Smaple cg");
outtextxy(toolx+87,tooly+136,"dfg dfgr");
outtextxy(toolx+87,tooly+142,"dfgh d f");
outtextxy(toolx+87,tooly+148,"0 018  0");


//grid hider
setcolor(15);
setfillstyle(SOLID_FILL,8);
bar(toolx+45,tooly+5,toolx+65,tooly+25);
rectangle(toolx+45,tooly+5,toolx+65,tooly+25);
setfillstyle(HATCH_FILL,7);
bar(toolx+55,tooly+15,toolx+75,tooly+35);
rectangle(toolx+55,tooly+15,toolx+75,tooly+35);


setcolor(8);
settextstyle(2,0,5);
outtextxy(toolx+30,tooly+25,"<");
outtextxy(toolx+61,tooly+25," ");
outtextxy(toolx+110,tooly+25,">");

outtextxy(toolx+30,tooly+65,"1");
outtextxy(toolx+70,tooly+65,"2");
outtextxy(toolx+110,tooly+65,"3");

outtextxy(toolx+30,tooly+105,"4");
outtextxy(toolx+70,tooly+105,"5");
outtextxy(toolx+110,tooly+105,"6");

outtextxy(toolx+30,tooly+145," ");
outtextxy(toolx+61,tooly+145," ");
outtextxy(toolx+110,tooly+145," ");

setcolor(15);
settextstyle(2,0,5);
outtextxy(toolx+29,tooly+24,"<");
outtextxy(toolx+51,tooly+24," ");
outtextxy(toolx+109,tooly+24,">");

outtextxy(toolx+29,tooly+64,"1");
outtextxy(toolx+69,tooly+64,"2");
outtextxy(toolx+109,tooly+64,"3");

outtextxy(toolx+29,tooly+104,"4");
outtextxy(toolx+69,tooly+104,"5");
outtextxy(toolx+109,tooly+104,"6");

outtextxy(toolx+29,tooly+144," ");
outtextxy(toolx+60,tooly+144," ");
outtextxy(toolx+109,tooly+144," ");

}//end of drawing mode2


