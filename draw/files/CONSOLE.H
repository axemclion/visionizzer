char *G_listbox(DLLIST *list,const char *title=__DATE__,const int b=300)
{
	const int y=getmaxy()/2-150;
	const int x=(getmaxx()-b)/2;
	const int y1=getmaxy()/2+150;
	const int x1=(getmaxx()+b)/2;;
	/************draw the box ***********/
	setfillstyle(SOLID_FILL,8);
	bar(x,y,x1,y1);
	setcolor(0);
	rectangle(x,y,x1,y1);
	settextstyle(GOTHIC_FONT,0,1);
	outtextxy(getmaxx()/2-textwidth(title)/2,y,title);
	line (x,y+40,x1,y+40);
	setfillstyle(WIDE_DOT_FILL,8);
	bar(x+20,y+50,x1-20,y1-40);
	setfillstyle(XHATCH_FILL,8);
	bar(x1-40,y+50,x1-20,y1-40);
	setfillstyle(INTERLEAVE_FILL,7);
	bar(x1-40,y+50,x1-20,y+70);
	bar(x1-40,y1-60,x1-20,y1-40);
	/*** buttons ********/

	setfillstyle(SOLID_FILL,7);
	bar(x+30,y1-30,x+120,y1-10);
	bar(x1-30,y1-30,x1-120,y1-10);


	setcolor(15);
	//top kline
	line(x1-30,y1-30,x1-120,y1-30);
	line(x+30,y1-30,x+120,y1-30);
	//left line
	line(x+30,y1-30,x+30,y1-10);
	line(x1-120,y1-30,x1-120,y1-10);

	setcolor(8);
	//right line
	line(x+120,y1-30,x+120,y1-10);
	line(x1-30,y1-30,x1-30,y1-10);
	//bottom line
	line(x1-30,y1-10,x1-120,y1-10);
	line(x+30,y1-10,x+120,y1-10);


	settextstyle(DEFAULT_FONT,0,1);
	setcolor(0);
	outtextxy(x+42,y1-25,"OK");
	outtextxy(x1-108,y1-25,"Cancel");
  /*******write the list *******/
	setcolor(15);
	settextstyle(SANS_SERIF_FONT,0,3);
	int count=0;
	list=DLGetFirst(list);
	while (NULL !=DLGetData(list) && count < 8)
	{
		outtextxy(x+30,y+50+count*25,(char far*)DLGetData(list,NULL,NULL));
		if (NULL ==DLGetNext(list))
			{break;}
		list=DLGetNext(list);
		count++;
	}//end of while
	/*******finished writing**********/
	/*******begin processing**********/
	DLLIST *current;
	current=DLGetFirst(list);
	char *result=(char *)calloc(1,sizeof result);
	mouse_status but;
	mouse_present();
	#ifdef MOUSE__
		show_mouse();
	#endif

	int key;
	current=DLGetFirst(list);
	while (1)
	{
		#ifdef MOUSE__
			but=click();
		#endif
		key=0;
		if (kbhit())
			key=getch();
		switch (key)
		{
			case 13://enter
				return result;
			case 27://escape
				*result=NULL;
				return result;
			case 72://up arrow
			{
			if (DLGetData(DLGetFirst(current)) !=DLGetData(current))
			{
				hide_mouse();
				current=DLGetPrev(current);
				list=current;
				count=0;
				setfillstyle(WIDE_DOT_FILL,8);
				bar(x+20,y+50,x1-41,y1-40);
				while (NULL !=DLGetData(list) && count < 8)
				{
					outtextxy(x+30,y+50+count*25,(char far*)DLGetData(list,NULL,NULL));
					list=DLGetNext(list);
					count++;
					}//end of while
				show_mouse();
				}///end of conditional if
			break;
			}//end of uparrow
			case 80://down arrow
			{
			if (DLGetData(DLGetLast(current)) !=DLGetData(current))
			{
				hide_mouse();
				current=DLGetNext(current);
				list=current;
				count=0;
				setfillstyle(WIDE_DOT_FILL,8);
				bar(x+20,y+50,x1-41,y1-40);
				while (NULL !=DLGetData(list) && count < 8)
				{
					outtextxy(x+30,y+50+count*25,(char far*)DLGetData(list,NULL,NULL));
					list=DLGetNext(list);
					count++;
				}//end of while
			}//end of conditional if
			show_mouse();
			break;
			}//end of down button
			default:
				{
				if ((key >'a' && key <'z') || (key >='1' && key <'9') || (key >'a' && key <'z'))
				{
				list=DLGetFirst(current);
				while (DLGetData(list) !=NULL)
				{
					char *kb;
					kb=(char*)DLGetData(list);
					if (key==*kb || key-32==*kb)
						{
						result=(char *)DLGetData(list,NULL,NULL);
						current=list;
						list=DLGetLast(list);
						/******writing selected **********/
						char *buffer=(char *)calloc(1,sizeof buffer);
						strcpy(buffer,"Selected : ");
						strcat(buffer,result);
						setfillstyle(SOLID_FILL,0);
						bar(x+10,y+25,x1-10,y+38);
						settextstyle(DEFAULT_FONT,0,1);
						outtextxy(x+15,y+30,buffer);
						settextstyle(SANS_SERIF_FONT,0,3);
						key=0;
						break;
						}
					else
						list=DLGetNext(list);
				}
				list=DLGetFirst(list);
				}//end of alphanumeric keys
				else if (key)
				{
				result=(char *)DLGetData(current,NULL,NULL);
				char *buffer=(char *)calloc(1,sizeof buffer);
				strcpy(buffer,"Selected : ");
				strcat(buffer,result);
				setfillstyle(SOLID_FILL,0);
				bar(x+10,y+25,x1-10,y+38);
				settextstyle(DEFAULT_FONT,0,1);
				outtextxy(x+15,y+30,buffer);
				settextstyle(SANS_SERIF_FONT,0,3);
				}//only if key present
				key=0;
				}//end of default case
			}//end of switch case
		/*****mouse click*********/
		if (1==but.button)
		{
			if (but.y < y1-10 && but.y >y1-30)
			{
			  if (but.x <x+120 &&but.x >x+30)
			  {
				return result;
			  }
			  if (but.x >x1-120 && but.x<x1-30)
			  {
				return NULL;
			  }
			}//end of button id
			if (but.x <x1-20 && but.x >x1-40)
			{
				if (but.y>y+50 && but.y <y+70 && DLGetData(DLGetFirst(current)) !=DLGetData(current))
				{
					current=DLGetPrev(current);
					list=current;
					count=0;
					setfillstyle(WIDE_DOT_FILL,8);
					bar(x+20,y+50,x1-41,y1-40);
					while (NULL !=DLGetData(list) && count < 8)
					{
						outtextxy(x+30,y+50+count*25,(char far*)DLGetData(list,NULL,NULL));
						list=DLGetNext(list);
						count++;
					}//end of while
				}//end of second scroll
				if (but.y>y1-60 && but.y <y1-40 && DLGetData(DLGetLast(current)) != DLGetData(current))
				{
					current=DLGetNext(current);
					list=current;
					count=0;
					setfillstyle(WIDE_DOT_FILL,8);
					bar(x+20,y+50,x1-41,y1-40);
					while (NULL !=DLGetData(list) && count < 8)
					{
						outtextxy(x+30,y+50+count*25,(char far*)DLGetData(list,NULL,NULL));
						list=DLGetNext(list);
						count++;
					}//end of while
				}//end of one scroll
			}// end of scroll buttons

			if(but.x>x+20 &&but.x <x1-40&& but.y >y+50 &&but.y <y1-40)
			{
				list=current;
				switch((but.y-y-50)/25)
					{case 8:
					list =DLGetNext(list);
					case 7:
					list =DLGetNext(list);
					case 6:
					list =DLGetNext(list);
					case 5:
					list =DLGetNext(list);
					case 4:
					list =DLGetNext(list);
					case 3:
					list =DLGetNext(list);
					case 2:
					list =DLGetNext(list);
					case 1:
					list =DLGetNext(list);
					break;
				}//end of switch case
			result=(char *)DLGetData(list,NULL,NULL);
			char *buffer=(char *)calloc(1,sizeof buffer);
			strcpy(buffer,"Selected : ");
			strcat(buffer,result);
			setfillstyle(SOLID_FILL,0);
			bar(x+10,y+25,x1-10,y+38);
			settextstyle(DEFAULT_FONT,0,1);
			outtextxy(x+15,y+30,buffer);
			settextstyle(SANS_SERIF_FONT,0,3);
			} //end of list if
		}//end of mouse check
	 }//end of I button



}//end of function

int G_YesNoDialog(char *title=__DATE__,char *message1=__TIME__,char *message2=" ", char *message3="",char *button1="Yes",char *button2="No")
{
	fflush(stdin);
	const int x=160;
	const int y=160;
	const int x1=480;
	const int y1=320;

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
# ifdef MOUSE__
	show_mouse();
	position_mouse(x+95,y1-20);
#endif
	while (!result)
	{
		#ifdef MOUSE__
			but=down();
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
but = down();
}
hide_mouse();
fflush(stdin);
return result;

}// end of function

void G_input_box(char *result,char *title=__DATE__,char* message1=__TIME__, char *message2="",char * message3="",int length=30)
{
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
	while (keyhit <=length && textwidth(result) < x1-x-30)
	{
	 key=getch();
	  /***testing keys********/
	 switch(key)
	 {
	case 8: //backspace
		{
		*(result+keyhit-1)=NULL;
		setfillstyle(SOLID_FILL,7);
		bar(x+12,y1-12,x1-12,y1-48);
		outtextxy(x+20,y1-40,result);
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
	outtextxy(x+20,y1-40,result);
	}//end of switch case

	}//end of while
}//end of function

