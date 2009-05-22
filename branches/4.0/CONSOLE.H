# define LX 175
# define LY 86
void error(const char*msg,char *,int);

void listbox(char *listfile,char *selected,int num = 20,char *title = "List Dialog")
{
	FILE *fp;
	char *buffer = (char *)calloc(1,70);
	fp = fopen(listfile,"rt");
	if (fp == NULL || buffer == NULL)
		return;
	hide_mouse();
	loadbmp("list.vsn",LX,LY);
	setcolor(15);
	outtextxy(LX+30,LY+10,title);
	setcolor(0);
	int quit = 0;

	while (!feof(fp) && quit < 11 && quit < num)
	{
		fgets(buffer,70,fp);
		buffer[strlen(buffer)-1] = NULL;
		outtextxy(LX+20,LY+70+quit*15,buffer);
		quit++;
	}//end of displayting all data
		show_mouse();
		quit = 0;
		int top = 1;
		int key = 0;
		int sel = 1;
		hide_mouse();
		int prevsel = 1;
		setlinestyle(1,0,1);
		rectangle(LX+10,LY+65,LX+280,LY+80);
		setlinestyle(0,0,1);
		show_mouse();
		mouse_status mouse;
		mouse = status();
		setfillstyle(SOLID_FILL,15);

		while (!quit)
		{
			prevsel = sel;
			mouse = status();
			key = 0;
			if (kbhit())
				key = getch();

			if (mouse.button != 0 || key != 0)
			if (inarea(mouse.x,mouse.y,LX+65,LY+31,LX+139,LY+53) || key == 13)
			{
				quit = 1;
				setcolor(8);
				rectangle(LX+65,LY+32,LX+139,LY+53);
				if (key == 0) xclick();
			}//end of OK button
			else if (inarea(mouse.x,mouse.y,LX+162,LY+31,LX+236,LY+53) || key == 27)
			{
				quit = -1;
				rectangle(LX+162,LY+32,LX+236,LY+53);
				sel = -1;
				if (key == 0) xclick();
			} //end of cancel button
			else if (inarea(mouse.x,mouse.y,LX+289,LY+224,LX+302,LY+237)&& top + 10 < num)
			{
				hide_mouse();
				setcolor(0);rectangle(LX+289,LY+225,LX+302,LY+238);setcolor(15);line(LX+289,LY+238,LX+302,LY+238);line(LX+302,LY+225,LX+302,LY+238);show_mouse();
				xclick();hide_mouse();
				setcolor(15);rectangle(LX+289,LY+225,LX+302,LY+238);setcolor(0);line(LX+289,LY+238,LX+302,LY+238);line(LX+302,LY+225,LX+302,LY+238);
				bar(LX+287,LY+238,LX+10,LY+65);
				rewind(fp);
				for (int i=0;i < top+11 && !feof(fp);i++)
					{
						fgets(buffer,70,fp);
						buffer[strlen(buffer)-1] = NULL;
						if (i >= top)
							outtextxy(LX+20,LY+70+(i-top)*15,buffer);
					}//end of reading
				top --;
				setcolor(7);rectangle(LX+290,LY+79+top*112/(num-11),LX+300,LY+94+top*112/(num-11));
				setcolor(15);top++;
				rectangle(LX+290,LY+79+top*112/(num-11),LX+300,LY+94+top*112/(num-11));setcolor(8);line(LX+290,LY+94+top*112/(num-11),LX+300,LY+94+top*112/(num-11));line(LX+300,LY+79+top*112/(num-11),LX+300,LY+94+top*112/(num-11));
				top ++;
				setlinestyle(1,0,1);
				if (sel >=top && sel < top+11)
					rectangle(LX+10,(sel-top)*15+LY+65,LX+280,(sel-top)*15+LY+80);
				setlinestyle(0,0,1);

				show_mouse();
			}//end if clicking up
			else if (inarea(mouse.x,mouse.y,LX+289,LY+64,LX+302,LY+77) && top > 0)
			{
				hide_mouse();
				setcolor(0);rectangle(LX+289,LY+65,LX+302,LY+78);setcolor(15);line(LX+289,LY+78,LX+302,LY+78);line(LX+302,LY+65,LX+302,LY+78);show_mouse();
				xclick();
				hide_mouse();
				setcolor(15);rectangle(LX+289,LY+65,LX+302,LY+78);setcolor(0);line(LX+289,LY+78,LX+302,LY+78);line(LX+302,LY+65,LX+302,LY+78);
				bar(LX+287,LY+238,LX+10,LY+65);
				rewind(fp);
				for (int i= 0;i < top-2 ; i++)
					fgets(buffer,70,fp);
				for (i = 0;i < 11;i++)
					{
						fgets(buffer,70,fp);
						buffer[strlen(buffer)-1] = NULL;
						outtextxy(LX+20,LY+70+i*15,buffer);
					}//end of printing
				setcolor(7);rectangle(LX+290,LY+79+top*112/(num-11),LX+300,LY+94+top*112/(num-11));
				top--;
				setcolor(15);rectangle(LX+290,LY+79+top*112/(num-11),LX+300,LY+94+top*112/(num-11));setcolor(8);line(LX+290,LY+94+top*112/(num-11),LX+300,LY+94+top*112/(num-11));line(LX+300,LY+79+top*112/(num-11),LX+300,LY+94+top*112/(num-11));
				if (top == 0) top = 1;
				setlinestyle(1,0,1);
				if (sel >=top && sel < top+11)
					rectangle(LX+10,(sel-top)*15+LY+65,LX+280,(sel-top)*15+LY+80);
				setlinestyle(0,0,1);
				show_mouse();
			}//end of down clicking
			else if (inarea(mouse.x,mouse.y,LX+6,LY+63,LX+287,LY+230))
			{
				sel = (mouse.y-LY-70) / 15;
				prevsel-=top;
				setlinestyle(1,0,1);
				hide_mouse();
				setcolor(15);
				if (prevsel >= 0 && prevsel <= 11)
					rectangle(LX+10,prevsel*15+LY+65,LX+280,prevsel*15+LY+80);
				setcolor(0);
				rectangle(LX+10,sel*15+LY+65,LX+280,sel*15+LY+80);
				show_mouse();
				setlinestyle(0,0,1);
				sel = sel+top;
			}//end of selection
		}//end of main loop
		rewind(fp);
		for (int i=0;i < sel;i++)
			fgets(buffer,70,fp);
		buffer[strlen(buffer)-1] = NULL;
		if (selected != NULL)
			strcpy(selected,buffer);
		if (quit == -1)
			strcpy(selected," ");
		fclose(fp);
		free(buffer);
}//end of filedialog*/


void edit(char *fname,int max,int x1,int y1)
{
				int key=0;
				int count =strlen(fname);
				outtextxy(x1,y1,fname);
				count = strlen(fname);
				while (key != 13 && key !=27)
				{
				key = getch();
				char a[2];
					if (key == 8 && strlen(fname) > 0)
						{
						char *b = (char *)calloc(1,strlen(fname)+3);
						strncpy(b,fname,strlen(fname)-1);
						setcolor(15);
						outtextxy(x1,y1,fname);
						strcpy(fname,b);
						setcolor(0);
						outtextxy(x1,y1,fname);
						free(b);
						count--;
						}//end of backspace
					if (key >= 32 && key < 126 && count < max)
						{
						setcolor(0);
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


void G_input_box(char *result,char *title=__DATE__,char* message1=__TIME__, char *message2="",char * message3="",int length=30)
{
	hide_mouse();
	char *sc = (char *)malloc(imagesize(0,0,295,110));
	if (sc == NULL) error("Cannot allocate enough memory for intput box",__FILE__,__LINE__);
	getimage(175,106,470,110+106,sc);
	loadbmp("input.vsn",175,106);
	int x1 =175;int y1 = 106;
	settextstyle(12,0,1);
	setcolor(15);
	outtextxy(x1+30,y1+9,title);
	setcolor(0);
	outtextxy(55+x1,30+y1,message1);
	outtextxy(55+x1,45+y1,message2);
	outtextxy(55+x1,60+y1,message3);
	edit(result,length,x1+20,y1+90);
	putimage(175,106,sc,COPY_PUT);
	free(sc);
	show_mouse();
}//end of function

void msgbox(char *message1,char *message2=" ",char *message3=" ",char *message4= " ")
{
	hide_mouse();
	char *sc = (char *)malloc(imagesize(0,0,295,115));
	if (sc == NULL) error("Cannot allocate enough memory for message box",__FILE__,__LINE__);
	getimage(175,106,175+295,106+115,sc);
	loadbmp("display.vsn",175,106);
	int x1 =175;int y1 = 106;
	setcolor(0);
	settextstyle(12,0,1);
	outtextxy(45+x1,25+y1,message1);
	outtextxy(45+x1,40+y1,message2);
	outtextxy(45+x1,55+y1,message3);
	outtextxy(45+x1,70+y1,message4);
	getch();
	putimage(175,106,sc,COPY_PUT);
	free(sc);
	show_mouse();
}// end of function

int G_YesNoDialog(char *a=" " ,char *b= " ",char *c = " ",char *bn="Visionizzer",char *b1 = "Yes",char *b2 = "No")
{
	int x1,y1;
	x1 = 175;y1= 106;
	hide_mouse();
	loadbmp("msgbox.vsn",x1,y1);
	settextstyle(12,0,1);
	setcolor(15);
	outtextxy(12+x1,8+y1,bn);
	setcolor(0);
	outtextxy(70+x1,35+y1,a);
	outtextxy(70+x1,50+y1,b);
	outtextxy(70+x1,65+y1,c);
	outtextxy(x1+88-textwidth(b1)/2,103+y1,b1);
	outtextxy(x1+188-textwidth(b2)/2,103+y1,b2);
	show_mouse();
	setlinestyle(0,0,1);
	mouse_status mouse;
	int result = 0;
	show_mouse();
	while (result != 1 && result != -1)
		{
			if (kbhit())
				result = getch();
			mouse = status();
			if (inarea(mouse.x,mouse.y,x1+51,y1+95,x1+125,y1+117) && mouse.button == LEFT_CLICK || result == 13 || result == 32)
				{
				result = 1;
				setcolor(0);
				rectangle(x1+51,y1+95,x1+125,y1+117);
				setcolor(8);
				rectangle(x1+52,y1+96,x1+124,y1+116);
				setlinestyle(1,0,1);
				rectangle(x1+55,y1+100,x1+120,y1+112);
				click();
				}//first button clicked
			else if (inarea(mouse.x,mouse.y,x1+151,y1+95,x1+225,y1+117) && mouse.button == LEFT_CLICK || result == 27)
				{
				setcolor(0);
				rectangle(x1+151,y1+95,x1+225,y1+117);
				setcolor(8);
				rectangle(x1+152,y1+96,x1+224,y1+116);
				setlinestyle(1,0,1);
				rectangle(x1+155,y1+100,x1+220,y1+112);
				click();
				result = -1;
				}//end of second button
		}//end of main loop body
	setactivepage(0);
	setvisualpage(0);
	return result;
}//end of messagebox