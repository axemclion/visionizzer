void msgbox(char *message1,char *message2=" ",char *message3=" ",char *message4= " ")
{
	int x,y,y1,x1;

	x = max(max(textwidth(message1),textwidth(message2)),textwidth(message3));
	x = max(x,textwidth("Press any key to continue "));
	x1 = getmaxx()/2+x/2;
	x = getmaxx()/2-x;

	y=getmaxy()/2;
	y1 = getmaxy()/2+63;
  if (strcmp(message2," ") != 0)
		y1 = y1 + 20;
  if (strcmp(message3," ") != 0)
		y1 = y1 + 20;
  if (strcmp(message4," ") != 0)
		y1 = y1 + 20;
	hide_mouse();
	char far *scr;
	scr = (char far *)farmalloc(imagesize(x,y,x1,y1));
	if (scr == NULL)
		perror("Cannont Allocate Memory for Messagebox");
	getimage(x,y,x1,y1,scr);

	setfillstyle(SOLID_FILL,7);
	setlinestyle(0,0,1);
	setcolor(15);
	for (int a=(x1-x)/2,b=(y1-y)/2;a < x1-x || b < y1-y;)
	{
		bar(x+a,y+b,x1-a,y1-b);
		rectangle(x+a,y+b,x1-a,y1-b);
		if (a < x1-x) a++;
		if (b < y1-y) b++;
		delay(.4);
	}//end of animation
	setcolor(8);
	setfillstyle(SOLID_FILL,7);
	bar(x,y,x1,y1);
	rectangle(x+1,y+1,x1-1,y1-1);
	setcolor(15);
	line(x+1,y+1,x1-1,y+1);
	line(x+1,y+1,x+1,y1-2);
	settextstyle(7,0,1);
	setlinestyle(0,0,1);
	setcolor(8);
	outtextxy(x+15,y+8,message1);
	outtextxy(x+15,y+28,message2);
	outtextxy(x+15,y+48,message3);
	setcolor(15);
	rectangle(x+10,y+10,x1-10,y1-30);
	outtextxy(x+14,y+7,message1);
	outtextxy(x+14,y+27,message2);
	outtextxy(x+14,y+47,message3);


	setcolor(8);
	line(x+10,y+10,x + 10,y1-30);
	line(x+10,y+10,x1-10,y+10);

	rectangle(x+10,y1-22,x1-10,y1-9);

	setcolor(15);
	line(x+10,y1-22,x1-10,y1-22);
	line(x+10,y1-22,x+10,y1-9);
	settextstyle(12,0,1);

	setcolor(8);
	outtextxy((x+x1)/2-textwidth("Press a key to continue")/2,y1-20,"Press a key to continue");
	show_mouse();
	getch();
	hide_mouse();
	putimage(x,y,scr,COPY_PUT);
	show_mouse();
	farfree(scr);
}
int G_YesNoDialog(char *title=__DATE__,char *message1=__TIME__,char *message2=" ", char *message3="",char *button1="Yes",char *button2="No")
{
	fflush(stdin);
	int x=160;
	int y=160;
	int x1=480;
	int y1=320;

	/************start drawing **************/
	setlinestyle(0,0,3);
	setfillstyle(SOLID_FILL,0);
	bar(x,y,x1,y1);
	setfillstyle(INTERLEAVE_FILL,8);
	bar(x,y,x1,y1);

	setcolor(15);
	rectangle(x,y,x1-1,y1-1);
	setcolor(7);
	rectangle(x+1,y+1,x1,y1);
	setcolor(15);
	settextstyle(7,0,3);

	int a=x+(x1-x)/2 - textwidth(title)/2;
	setfillstyle(CLOSE_DOT_FILL,7);
	bar(x+3,y+3,x1-3,y+30);
	setcolor(15);
	outtextxy(a,y+1,title);
	line(x,y+30,x1,y+30);
	setcolor(7);
	settextstyle(8,0,1);
	outtextxy(x+10,y+30,message1);
	outtextxy(x+10,y+55,message2);
	outtextxy(x+10,y+80,message3);

	/*********** draw buttons *******/
	setfillstyle(SOLID_FILL,7);
	bar(x+40,y1-40,x+150,y1-10);
	bar(x1-40,y1-40,x1-150,y1-10);

	setcolor(15);
	//top kline
	line(x1-40,y1-40,x1-150,y1-40);
	line(x+40,y1-40,x+150,y1-40);
	//left line
	line(x+40,y1-40,x+40,y1-10);
	line(x1-150,y1-40,x1-150,y1-10);

	setcolor(8);
	//right line
	line(x+150,y1-40,x+150,y1-10);
	line(x1-40,y1-40,x1-40,y1-10);
	//bottom line
	line(x1-40,y1-10,x1-150,y1-10);
	line(x+40,y1-10,x+150,y1-10);


	settextstyle(TRIPLEX_FONT,0,2);
	setcolor(0);
	outtextxy(x+42,y1-40,button1);
	outtextxy(x1-148,y1-40,button2);
/****************processing       ************/
	int result=0,active_result=1;
	int key=0;
	mouse_status but={0};
	mouse_present();
	{
	char word[64] ={0x3f,0xfc,0xdf,0xfb,0xef,0xf7,0xf7,0xef,0xfb,0xdf,0xa1,0xb9,0xc0,0x79,0xcc,0x7f,0xfc,0x7f,0x78,0x7e,0xf1,0xbf,0xe3,0xdb,0xa7,0xed,0x67,0xf6,0xdf,0xfb,0x27,0xfc,0xc0,0x3,0x20,0x4,0x10,0x8,0x8,0x10,0x4,0x20,0x5e,0x46,0x3f,0x86,0x33,0x80,0x3,0x80,0x87,0x81,0xe,0x40,0x1c,0x24,0x58,0x12,0x98,0x9,0x20,0x4,0xd8,0x3};
	mouse_change(word);
	}

# ifdef MOUSE__
	show_mouse();
	position_mouse(x+95,y1-20);
#endif

	while (!result)
	{
		#ifdef MOUSE__
			but=status();
		#endif
		if (kbhit())
			key=getch();

		/*************** mouse check **********************/

		if (1==but.button && but.y < y1-10 && but.y > y1-40)
		{
			if (but.x > x+40 && but.x < x+150)
				result= 1;
			if (but.x < x1-40 && but.x > x1-150)
				result= -1;
		}//end of mouse check
		/****************keyboardf check   ******************/
		if (kbhit())
			key=getch();
		switch (key)
			{
			case 27: //ESCAPE
				result= -1;
				break;
			case 13: // ENTER
				result=1;
				break;
			case 9: //TAB
			case 72://arrow keys
			case 80:
			case 75:
			case 77:
				{
/****** change buttons by keyboard *****/

	setlinestyle(2,0,2);
	if (1==active_result)
		{setcolor(5);rectangle(x+50,y1-15,x+140,y1-35);
		setcolor(7);rectangle(x1-50,y1-15,x1-140,y1-35);
		}
	if (-1==active_result)
		{setcolor(5);rectangle(x1-50,y1-15,x1-140,y1-35);
		setcolor(7); rectangle(x+50,y1-15,x+140,y1-35);
		}
	setlinestyle(0,0,1);
				if (1==active_result)
					{
					active_result=-1;
					gotoxy(1,1);
					}
				else if (-1==active_result)
					{
					active_result=1;
					gotoxy(1,1);
					}

			key=0;
			break;
				}//end of tab case
			default:
				if (0!=key)
					result=active_result;
			}//end of switch case

	}//end of while

// animation effect

	if (-1==result)
		{
		setcolor(8);
		line(x1-40,y1-40,x1-150,y1-40);
		line(x1-150,y1-40,x1-150,y1-10);
		setcolor(15);
		line(x1-40,y1-40,x1-40,y1-10);
		line(x1-40,y1-10,x1-150,y1-10);
		}
	if (1==result)
		{
		setcolor(8);
		line(x+40,y1-40,x+150,y1-40);
		line(x+40,y1-40,x+40,y1-10);
		setcolor(15);
		line(x+150,y1-40,x+150,y1-10);
		line(x+40,y1-10,x+150,y1-10);
		}
but.button=1;
while (but.button !=0)
{
but = status();
}

hide_mouse();
fflush(stdin);
return result;

}// end of function

void G_input_box(char *result,char *title=__DATE__,char* message1=__TIME__, char *message2="",char * message3="",int length=30)
{
	hide_mouse();
	fflush(stdin);
	int x,y,x1,y1;
	x=160;y=160;x1=480;y1=320;

	/************start drawing **************/
	setfillstyle(SOLID_FILL,0);
	bar(x,y,x1,y1);
	setfillstyle(INTERLEAVE_FILL,8);
	bar(x,y,x1,y1);

	setcolor(15);
	rectangle(x,y,x1-1,y1-1);
	setcolor(7);
	rectangle(x+1,y+1,x1,y1);
	setcolor(15);
	settextstyle(7,0,3);

	int a=(x+((x1-x)/2))-16*strlen(title)/2;
	outtextxy(a,y+1,title);
	line(x,y+30,x1,y+30);
	setcolor(7);
	settextstyle(6,0,1);
	outtextxy(x+10,y+30,message1);
	outtextxy(x+10,y+55,message2);
	outtextxy(x+10,y+80,message3);
	/*draw input box */
	setfillstyle(SOLID_FILL,7);
	bar(x+10,y1-10,x1-10,y1-50);
	setcolor(15);
	line(x1-10,y1-10,x1-10,y1-50);
	line(x+10,y1-10,x1-10,y1-10);
	setcolor(8);
	line(x+10,y1-50,x1-10,y1-50);
	line(x+10,y1-10,x+10,y1-50);
	/*******processing starts **********/
	int keyhit=0,key=0;
	settextstyle(SANS_SERIF_FONT,0,3);
	show_mouse();
	mouse_change(_TEXT_CUR);
	show_mouse();
	while (keyhit <=length && textwidth(result) < x1-x-30)
	{
	 key=getch();
	  /***testing keys********/
	 switch(key)
	 {
	case 8: //backspace
		{
		hide_mouse();
		*(result+keyhit-1)=NULL;
		setfillstyle(SOLID_FILL,7);
		bar(x+12,y1-12,x1-12,y1-48);
		outtextxy(x+20,y1-40,result);
		show_mouse();
		keyhit--;
		break;
		}

	case 27:
		*result =NULL;
	case 13:
		keyhit =length+1;
		break;
	default:
		{
		char *ans;
		keyhit++;
		setcolor(15);
		settextstyle(SANS_SERIF_FONT,0,2);
		ans=(char*)&key;
		strcat(result,ans);
		}
	hide_mouse();
	outtextxy(x+20,y1-40,result);
	show_mouse();
	}//end of switch case
	position_mouse(textwidth(result) + x+12,y1-40);
	}//end of while
	mouse_change(_TARGET_CUR,8,8);
	hide_mouse();
}//end of function

void filedialog(char *title,char *values[10],char *selected,int num)
{
num--;
int x,y,x1,y1;
x=160;y=80;
x1=420;y1=320;
setlinestyle(0,0,1);

setcolor(15);

setfillstyle(SOLID_FILL,7);
bar(x,y,x1,y1);
rectangle(x,y,x1,y1);
rectangle(x+10,y+40,x1-10,y1-10);
rectangle(x1-15,y+45,x1-35,y1-15);
rectangle(x1-17,y+47,x1-33,y+67);

settextstyle(4,0,1);
outtextxy(x+11,y+1,title);

settextstyle(0,1,1);
outtextxy(x1-20,y+50,"¯");
outtextxy(x1-20,y1-35,"®");
rectangle(x+10,y+25,x1-10,y+37);

setcolor(8);
rectangle(x1-20,y+5,x1-5,y+20);
rectangle(x1-37,y+5,x1-22,y+20);

line(x+10,y+25,x1-10,y+25);
line(x+10,y+25,x+10,y+37);
outtextxy(x1-21,y+51,"¯");
outtextxy(x1-21,y1-36,"®");
settextstyle(4,0,1);
rectangle(x1-17,y1-17,x1-33,y1-37);
line(x1-17,y+47,x1-17,y+67);
line(x1-17,y+67,x1-33,y+67);


line(x,y1,x1,y1);
line(x1,y,x1,y1);
line(x+10,y+40,x+10,y1-10);
line(x+10,y+40,x1-10,y+40);
outtextxy(x+10,y,title);
line(x1-15,y+45,x1-15,y1-15);
line(x1-15,y+45,x1-35,y+45);
settextstyle(12,0,1);
outtextxy(x+14,y+29,values[0]);
setcolor(15);
line(x1-33,y1-17,x1-33,y1-37);
line(x1-17,y1-37,x1-33,y1-37);
outtextxy(x+13,y+28,values[0]);

line(x1-20,y+5,x1-5,y+5);
line(x1-20,y+5,x1-20,y+20);
line(x1-37,y+5,x1-22,y+5);
line(x1-37,y+5,x1-37,y+20);
setcolor(0);
int start = 9;
int sel = 0;
/////////////////start of processing
for (int i=0;i < 9;i++)
outtextxy(x+13,y+54+i*20,values[i]);
outtextxy(405,90,"X");
outtextxy(387,90,"~");
mouse_status mouse={0,0,0};
mouse_present();
show_mouse();
start = 0;
int start1=0;
while (sel != -1)
{
//	bind_mouse(x,y,x1,y1);
	if (mouse.button)
	{
	bar(x+11,y+26,x1-11,y+36);
	setcolor(8);
	outtextxy(x+14,y+29,values[sel]);
	setcolor(15);
	outtextxy(x+13,y+28,values[sel]);
	for (int i=0;i < 9;i++)
		{
		setcolor(7);
		outtextxy(x+13,y+54+i*20,values[i+start1]);
		setcolor(0);
		outtextxy(x+13,y+54+i*20,values[i+start]);
		}

	start1=start;
		if (inarea(mouse.x,mouse.y,x1-17,y+68,x1-33,y1-38))
		{
			start = (mouse.y -y-68)*(num-9)/(y1-37-y-77);
			hide_mouse();
			bar(x1-17,y+68,x1-33,y1-38);
			setcolor(15);
			rectangle(x1-20,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+76);
			setcolor(8);
			line(x1-20,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+68);
			line(x1-30,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+76);
			show_mouse();
		}//scrolling area

		if (inarea(mouse.x,mouse.y,x1-37,y+5,x1-5,y+20))
		{
			if (mouse.x < x1-22)
				{
				setcolor(15);
				rectangle(x1-37,y+5,x1-22,y+20);
				setcolor(8);
				line(x1-37,y+5,x1-22,y+5);
				line(x1-37,y+5,x1-37,y+20);
				strcpy(selected,values[sel]);
				}
			else
				{
				setcolor(15);
				rectangle(x1-20,y+5,x1-5,y+20);
				setcolor(8);
				line(x1-20,y+5,x1-5,y+5);
				line(x1-20,y+5,x1-20,y+20);
				strcpy(selected,NULL);
				}
				xclick();
				sel = -1;
		}//end of the procedures

		if (mouse.x < x1-17 && mouse.x > x1-33 && mouse.y > y+47 && mouse.y < y+67)
		{
			start --;
			if (start < 0) start = 0;
			hide_mouse();
			setcolor(8);
			rectangle(x1-17,y+47,x1-33,y+67);
			setcolor (15);
			line(x1-17,y+47,x1-17,y+67);
			line(x1-17,y+67,x1-33,y+67);
			show_mouse();
			xclick();
			hide_mouse();
			setcolor(15);
			rectangle(x1-17,y+47,x1-33,y+67);
			setcolor (8);
			line(x1-17,y+47,x1-17,y+67);
			line(x1-17,y+67,x1-33,y+67);

			bar(x1-17,y+68,x1-33,y1-38);
			setcolor(15);
			rectangle(x1-20,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+76);
			setcolor(8);
			line(x1-20,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+68);
			line(x1-30,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+76);
			show_mouse();
		}//end of up nutton cklick

		else if (mouse.x < x1-17 && mouse.x > x1-33 && mouse.y > y1-37 && mouse.y < y1-17)
			{
			start ++;
			if (start +9 > num)
				start=num-9;
			hide_mouse();
			setcolor(15);
			rectangle(x1-17,y1-17,x1-33,y1-37);
			setcolor (8);
			line(x1-33,y1-17,x1-33,y1-37);
			line(x1-17,y1-37,x1-33,y1-37);
			show_mouse();
			xclick();
			hide_mouse();
			setcolor(8);
			rectangle(x1-17,y1-17,x1-33,y1-37);
			setcolor (15);
			line(x1-33,y1-17,x1-33,y1-37);
			line(x1-17,y1-37,x1-33,y1-37);
			bar(x1-17,y+68,x1-33,y1-38);
			rectangle(x1-20,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+76);
			setcolor(8);
			line(x1-20,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+68);
			line(x1-30,(y1-37-y-77)/(num-9)*start + y+68,x1-30,(y1-37-y-77)/(num-9)*start + y+76);
			show_mouse();

		}//end of up nutton cklick

		else if (mouse.x >x+10 && mouse.x <x1-40 && mouse.y > y+54 && mouse.y < y1-15)
		{
		sel = start + (mouse.y-40)/20 -4;
		}//clicked inside the area
	}//mouse button has been clicked
	mouse = status();
}///end of while loop

}//end of opening dialogbox
