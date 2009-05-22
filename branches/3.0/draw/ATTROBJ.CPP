void intro();

# define PM 10

void code_write()
{
	int s;
	setactivepage(1);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	setvisualpage(0);
	xclick();
	mouse_status mouse;
	mouse = status();

	char *nme[PM],*val[PM];
	for (int i=0;i < PM;i++)
	{
	nme[i]=(char *)calloc(1,80);
	if (nme[i] == NULL) error("Not enough memory for nme[i]");
	val[i]=(char *)calloc(1,80);
	if (nme[i] == NULL) error("Not enough memory for val[i]");
	}

char *buffer = (char *)calloc(1,100);
char *name = (char *)calloc(1,100);
char *type = (char *)calloc(1,100);
if (buffer == NULL) error("Not Enough memory for buffer");
if (name == NULL) error("Not Enough memory for name");
if (type == NULL) error("Not Enough memory for type");
i=0;

FILE *fp;
if ((fp = fopen("\\cmd.$$$","rt")) !=NULL)
{
while (!feof(fp))
{
		int x1,y1,x2,y2;
		fscanf(fp,"%s",name);
		fscanf(fp,"%s",buffer);
		while (strcmp(buffer,"**********") != 0)
		{
		builtable(buffer,nme[i],val[i]);
		fscanf(fp,"%s",buffer);

		if (strcmp(nme[i],"x1") == 0) x1=atoi(val[i]);
		if (strcmp(nme[i],"x2") == 0) x2=atoi(val[i]);
		if (strcmp(nme[i],"y1") == 0) y1=atoi(val[i]);
		if (strcmp(nme[i],"y2") == 0) y2=atoi(val[i]);
		if (strcmp(nme[i],"type") == 0) strcpy(type,val[i]);
		i++;
		}//end of while
i=0;
	if (mouse.x <= max(x1,x2) && mouse.x >=min(x1,x2) && mouse.y <= max(y1,y2) && mouse.y >=min(y1,y2))
		break;
}//end of while building table
fclose(fp);
}//end of opening the file*/
free(buffer);

	for (i=0;i < 10;i++)
		{
		sprintf(nme[i],"-----",i);
		free(val[i]);
		}

	mouse =status();
	int toolx=mouse.x;
	int tooly=mouse.y;

	if (toolx+90 > getmaxx()) toolx=getmaxx()-90;
	if (tooly+160 > getmaxy()) tooly=getmaxy()-160;
	hide_mouse();
	////////*drawing part started**********************
	{
	setcolor(15);
	for (int x=toolx,y=tooly;x < toolx+90 ;x++,y++)
		{
		setcolor(7);
		rectangle(x,y,toolx,tooly);
		delay(1.5);
		}
	}
	setcolor(15);
	setlinestyle(0,0,1);
	setfillstyle(SOLID_FILL,7);
	bar(toolx,tooly,toolx+90,tooly+160);
	rectangle(toolx,tooly,toolx+90,tooly+160);
	setfillstyle(SOLID_FILL,7);
	floodfill(toolx+1,tooly+1,15);
	rectangle(toolx+5,tooly+4,toolx+85,tooly+25);
	for (i=tooly+30;i<=tooly+140;i+=20)
		{
		setcolor(15);
		line(toolx+6,i+20,toolx+84,i+20);
		setcolor(8);
		line(toolx+6,i+21,toolx+84,i+21);
		}

	setcolor(8);
	line(toolx+90,tooly,toolx+90,tooly+160);
	line(toolx,tooly+160,toolx+90,tooly+160);
	line(toolx+85,tooly+4,toolx+85,tooly+25);
	line(toolx+5,tooly+25,toolx+85,tooly+25);
	rectangle(toolx+5,tooly+30,toolx+85,tooly+150);

	settextstyle(8,0,1);
	setcolor(15);
	outtextxy(toolx+11,tooly+2,"Events");
	line(toolx+85,tooly+30,toolx+85,tooly+150);
	line(toolx+5,tooly+150,toolx+85,tooly+150);
	setcolor(8);
	outtextxy(toolx+10,tooly+1,"Events");
	show_mouse();
	////////////////////end of drawing properties
	////////////////////writing temperory events
	if (strcmp(type,"command")==0)
		fp=fopen("cmdobj.vbc","rt");
	else if (strcmp(type,"command")==0)
		fp=fopen("lblobj.vbc","rt");
	else if (strcmp(type,"command")==0)
		fp=fopen("txtobj.vbc","rt");
	else
		fp = NULL;

	buffer= (char*) calloc(1,100);
	if (fp != NULL)
	{
	while (strcmp(buffer,"[events]") != 0 && !feof(fp))
		fscanf(fp,"%s",buffer);
		fgets(buffer,100,fp);
	for (int i=0;i < PM && !feof(fp);i++)
		{
		char *buf = (char *)calloc(1,20);
		fgets(buffer,100,fp);
		if (strcmp(buffer,"[end]\n")== 0 || strcmp(buffer,"[end]")== 0 )
			{
			free(buf);
			break;
			}
		for (int k=0;*(buffer +k) != 32 && *(buffer+k) != NULL;k++);k++;
		for (int j=0;j < strlen(buffer) && *(buffer+k+j) != '(';j++)
			*(buf+j) = *(buffer+j+k);
		strcpy(nme[i],buf);
		free(buf);
		k=0;
			do
			{
			j=fgetc(fp);
			if (j== '{')	k++;
			if (j== '}')   k--;
			}while (k != 0);
			fgets(buffer,100,fp);
		}//end of for llopp
	fclose(fp);
	}//end of command evens
	free(buffer);
{
	int top=0,top1;
	s=-10;
	settextstyle(12,0,1);
	mouse_status mouse;
	position_mouse(toolx+80,tooly+45);

	while( top != -10)
	{
	int x=0;
	if (top != top1)
		{
		buffer = (char *)calloc(1,100);
		hide_mouse();
		if (top < 0) top=0;
		if (top > PM-6) top= PM-6;
		for (x=0,i=top;i < top+6 ;i++,x++)
		{
		bar(toolx+10,tooly+32+x*20,toolx+84,tooly+47+x*20);
			strcpy(buffer,nme[i]);
		while(textwidth(buffer) >=58)
			*(buffer+strlen(buffer)-1) =NULL;
		setcolor(8);
		outtextxy(toolx+11,tooly+39+x*20,buffer);
		}
		show_mouse();
		free(buffer);
		}//end of redrawing of the properties
	top1=top;

	int key;
	if (kbhit()) key = getch();
	mouse=status();

	if (mouse.button == LEFT_CLICK && (mouse.x < toolx || mouse.x >toolx+90 || mouse.y <tooly || mouse.y>tooly+160))
		s=top =-10;
	if (mouse.button == LEFT_CLICK && mouse.x >= toolx+5 && mouse.x <= toolx+90 && mouse.y >= tooly+30 && mouse.y<=tooly+150)
		{
		s =(mouse.y-tooly-30)/20+top;
		top = -10;
	if (strcmp(nme[s],"-----")==0)
			s=-10;
		}
	show_mouse();
		switch(key)
		{
			case 72://up arror
				top--;
				break;
			case 80://down arrow
				top++;
				break;
			case 27:
				s=top = -10;
				}	//end of switch case
	key=0;
	}//end of while
	if (strcmp(type,"command")==0)
		fp=fopen("cmdobj.vbc","rt");
	else if (strcmp(type,"command")==0)
		fp=fopen("lblobj.vbc","rt");
	else if (strcmp(type,"command")==0)
		fp=fopen("txtobj.vbc","rt");
	if (fp != NULL)
	{
		buffer = (char*) calloc(1,100);
		FILE *t;
		t=fopen("\\$$$.$$$","wt");
		while (strcmp(buffer,"[events]\n") != 0)
				fgets(buffer,100,fp);

			while (!feof(fp))
			{
			char *buf = (char *)calloc(1,120);
			fgets(buffer,100,fp);

			for (int k=0;*(buffer +k) != 32 && *(buffer+k) != NULL ;k++);k++;
			for (int j=0;*(buffer + k) != NULL && j < strlen(buffer) && *(buffer+k+j) != '(';j++)
				*(buf+j) = *(buffer+j+k);
				k=0;
				if (strcmp(buf,nme[s])==0)
				{
				char *buf1 = (char *)calloc(1,100);
				for (k=0;*(k+buffer) != 32;k++)
					*(buf1+k)=*(buffer+k);
				*(buf1+k++) =' ';
				for (j=0;j < strlen(name) ;j++)
					*(buf1+k+j)=*(name+j);
				int i=j+k;
				for (j=0;j < strlen(buffer)-k;j++)
					*(buf1+j+i) = *(buffer+j+k);
				strcpy(buffer,buf1);
				free(buf1);
				k=0;
				{//check if the value is already existant
				FILE *tm;
				if ((tm = fopen("\\code.$$$","rt")) != NULL)
					{
					char *read = (char *)calloc(1,100);
					FILE *four;
					if ((four = fopen ("\\ttt.$$$","wt")) == NULL)
						error("Error opening ttt.$$$");

						while (!feof(tm))
						{
							strcpy(read,NULL);
							fgets(read,100,tm);
							if (strcmp(read,buffer) == 0)
							{
								fprintf(t,"%s",buffer);
								k=0;
								do
								{
								j=fgetc(tm);
								fputc(j,t);
								if (j== '{')	k++;
								if (j== '}')   k--;
								}while (k != 0 && !feof(tm));
								fputc('\n',t);
								k=-100;
							}//end of if statements
							else
								if (strcmp(read,"\n") != 0)
									fprintf(four,"%s",read);
						}//end of while statements
					fclose(four);
					fclose(tm);
					free(read);
					remove("\\code.$$$");
					rename("\\ttt.$$$","\\code.$$$");
					}//edn ofif ((tm = fopen("\\code.$$$","rt") != NULL)
				}//end of checking if the event for the object is already available

				if (k != -100)
				{//end of Object's code not available
				k=0;
				fprintf(t,"%s",buffer);
					do
					{
					j=fgetc(fp);
					fputc(j,t);
					if (j== '{')	k++;
					if (j== '}')   k--;
					}while (k != 0);
					fputc('\n',t);
				}//end of Object's code not available
				}//end of if statement
			free(buf);
			}//end of file -== 	while (!feof(fp))
		free(buffer);
		fclose(t);
		fclose(fp);
	}//end of file opening
}//end of scrolling and editing part
///////////////////*****freeup up and house keeping
	for (i=0;i < 10;i++)
	{
	free(nme[i]);
	}
	FILE *t;
	free(name);
	free(type);

	/////////***checking if editing is really needed ******/
if (s != -10)
{
	cleardevice();
	closegraph();
		printf("GOING to EDIT >>>>>>>>>>");
		fclose(t);
		if (-1 == spawnl(P_WAIT,"edit.com"," ","\\$$$.$$$",NULL))
			printf("Error Opening a file to edit.");
	type = (char*)calloc(1,100);
	t=fopen ("\\$$$.$$$","rt");
	if (t != NULL)
		fp = fopen ("\\code.$$$","at");
	if (fp != NULL)
		{
		while (!feof(t) && t!= NULL)
			if (fgets(type,100,t) != NULL)
				fprintf(fp,"%s",type);
		fclose(fp);
		}
	free(type);
	fclose(t);
	remove("\\$$$.$$$");
	intro();
	draw_grid(resolution);
	redraw();
}
else
	{
	setvisualpage(1);
	hide_mouse();
	setactivepage(0);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setvisualpage(0);
	show_mouse();
	}
	show_mouse();
	StatusLine("Strike F1 for Help",__LINE__,__FILE__);
}//end of code_writer

void attr()
{
	setlinestyle(0,0,1);
	setactivepage(1);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	xclick();
	mouse_status mouse;
	mouse = status();

	char *nme[PM],*val[PM];
	for (int i=0;i < PM;i++)
	{
	nme[i]=(char *)calloc(1,80);
	if (nme[i] == NULL) error("Not enough memory for nme[i]");
	val[i]=(char *)calloc(1,80);
	if (nme[i] == NULL) error("Not enough memory for val[i]");
	}

char *buffer = (char *)calloc(1,100);
char *name = (char *)calloc(1,100);
if (buffer == NULL) error("Not Enough memory for buffer");
i=0;

FILE *fp;
if ((fp = fopen("\\cmd.$$$","rt")) !=NULL)
{
while (!feof(fp))
{
		int x1,y1,x2,y2;
		fscanf(fp,"%s",name);
		fscanf(fp,"%s",buffer);
		while (strcmp(buffer,"**********") != 0)
		{
		builtable(buffer,nme[i],val[i]);
		fscanf(fp,"%s",buffer);

		if (strcmp(nme[i],"x1") == 0) x1=atoi(val[i]);
		if (strcmp(nme[i],"x2") == 0) x2=atoi(val[i]);
		if (strcmp(nme[i],"y1") == 0) y1=atoi(val[i]);
		if (strcmp(nme[i],"y2") == 0) y2=atoi(val[i]);
		i++;
		}//end of while
i=0;
	if (mouse.x <= max(x1,x2) && mouse.x >=min(x1,x2) && mouse.y <= max(y1,y2) && mouse.y >=min(y1,y2))
		break;
}//end of while building table
fclose(fp);
}//end of opening the file*/
free(buffer);

	mouse = status();
	int toolx=mouse.x;
	int tooly=mouse.y;

	if (toolx+160 > getmaxx()) toolx=getmaxx()-160;
	if (tooly+160 > getmaxy()) tooly=getmaxy()-160;
	hide_mouse();
	////////*drawing part started**********************
	setcolor(15);
	setlinestyle(0,0,1);
	setfillstyle(SOLID_FILL,7);
	bar(toolx,tooly,toolx+160,tooly+160);
	rectangle(toolx,tooly,toolx+160,tooly+160);
	setfillstyle(SOLID_FILL,7);
	floodfill(toolx+1,tooly+1,15);
	rectangle(toolx+5,tooly+4,toolx+155,tooly+25);
	for (i=tooly+30;i<=tooly+140;i+=20)
		{
		setcolor(15);
		line(toolx+6,i+20,toolx+154,i+20);
		setcolor(8);
		line(toolx+6,i+21,toolx+154,i+21);
		}

	setcolor(8);
	line(toolx+160,tooly,toolx+160,tooly+160);
	line(toolx,tooly+160,toolx+160,tooly+160);
	line(toolx+155,tooly+4,toolx+155,tooly+25);
	line(toolx+5,tooly+25,toolx+155,tooly+25);
	rectangle(toolx+5,tooly+30,toolx+155,tooly+150);

	settextstyle(8,0,1);
	setcolor(15);
	outtextxy(toolx+31,tooly+2,"Attributes");
	line(toolx+155,tooly+30,toolx+155,tooly+150);
	line(toolx+5,tooly+150,toolx+155,tooly+150);
	line(toolx+90,tooly+30,toolx+90,tooly+150);
	setcolor(8);
	outtextxy(toolx+30,tooly+1,"Attributes");
	line(toolx+91,tooly+30,toolx+91,tooly+150);
	show_mouse();
	/////////////////////end of drawing part
{
	int top=0,top1,s=-10;
	settextstyle(12,0,1);
	mouse_status mouse;
	position_mouse(toolx+80,tooly+45);

	while( top != -10)
	{
	int x=0;
	if (top != top1)
		{
		buffer = (char *)calloc(1,100);
		hide_mouse();
		if (top < 0) top=0;
		if (top > PM-6) top= PM-6;
		for (x=0,i=top;i < top+6 ;i++,x++)
		{
		bar(toolx+10,tooly+32+x*20,toolx+88,tooly+47+x*20);
		bar(toolx+92,tooly+32+x*20,toolx+150,tooly+47+x*20);
			strcpy(buffer,nme[i]);
		while(textwidth(buffer) >=58)
			*(buffer+strlen(buffer)-1) =NULL;
		setcolor(8);
		outtextxy(toolx+11,tooly+39+x*20,buffer);
		setcolor(15);
		outtextxy(toolx+10,tooly+40+x*20,buffer);
		setcolor(0);

		strcpy(buffer,val[i]);
		while(textwidth(buffer) >=58)
			*(buffer+strlen(buffer)-1) =NULL;
		outtextxy(toolx+94,tooly+40+x*20,buffer);
		}
	show_mouse();
		free(buffer);
		}//end of redrawing of the properties
	top1=top;

	int key;
	if (kbhit()) key = getch();
	mouse=status();

	gotoxy(72,1);
	printf("(%03d,%03d)",mouse.x,mouse.y);

	if (mouse.button == LEFT_CLICK && (mouse.x < toolx || mouse.x >toolx+160 || mouse.y <tooly || mouse.y>tooly+160))
		top =-10;


	if (mouse.button == LEFT_CLICK && mouse.x >= toolx+5 && mouse.x <= toolx+160 && mouse.y >= tooly+30 && mouse.y<=tooly+150)
		{
		buffer = (char *)calloc(1,100);
		s =(mouse.y-tooly-30)/20+top;
		strcpy(buffer,val[s]);
		setfillstyle(SOLID_FILL,7);
		hide_mouse();
		bar(toolx+5,tooly+4,toolx+155,tooly+25);

		setcolor(8);
		rectangle(toolx+5,tooly+4,toolx+155,tooly+25);
		setcolor(15);
		line(toolx+5,tooly+25,toolx+155,tooly+25);
		line(toolx+155,tooly+4,toolx+155,tooly+25);
///////////start of precessing
		settextstyle(12,0,1);

		{
		char *p=(char *)calloc(1,18);
		strncpy(p,buffer,17);
		outtextxy(toolx+8,tooly+10,p);
		free(p);
		}
		int key = 0;
		int pos=strlen(buffer);
		while ( key != 13 && key != 27)
		{
			key = getch();

			switch (key)
			{
			case 8://backspace
				pos--;
				*(buffer+pos) = NULL;
				break;
			default :
			if (key > 0 && key < 128 && key > 32)
				{
				*(buffer+pos) = key;
				pos++;
				}
			}//end of switch casae

			if (pos < 0) pos = 0;

			setfillstyle(SOLID_FILL,7);
			bar(toolx+6,tooly+5,toolx+154,tooly+24);
			char *print=(char *)calloc(1,100);
			if (textwidth(buffer) >= 150)
				{
					for (int i=strlen(buffer)-1,j=17;i >=0 && j >= 0;i--,j--)
					*(print+j) = *(buffer+i);
				}
			else
				strcpy(print,buffer);

			outtextxy(toolx+8,tooly+10,print);
			free(print);
			}//end of while editing key
			if (buffer)
					{
					changeprop(name,nme[s],buffer);
					strncpy(val[s],buffer,79);
					}
//////////end of processing and clean up
		setfillstyle(SOLID_FILL,7);
		hide_mouse();
		bar(toolx+5,tooly+4,toolx+155,tooly+25);
		settextstyle(8,0,1);
		setcolor(15);
		outtextxy(toolx+31,tooly+2,"Attributes");
		rectangle(toolx+5,tooly+4,toolx+155,tooly+25);
		setcolor(8);
		outtextxy(toolx+30,tooly+1,"Attributes");
		line(toolx+5,tooly+25,toolx+155,tooly+25);
		line(toolx+155,tooly+4,toolx+155,tooly+25);
		settextstyle(12,0,1);
		free(buffer);
		}//end of leftclick
		show_mouse();
		switch(key)
		{
			case 72://up arror
				top--;
				break;
			case 80://down arrow
				top++;
				break;
			case 27:
				top = -10;
				}	//end of switch case

	gotoxy(10,10);
	key=0;
	if (top == -10)
		break;
	}//end of while
}//end of scrolling and editing part
	////////////////clearig part
	for (i=0;i < 10;i++)
	{
	free(nme[i]);
	}
	free(name);
	hide_mouse();
	setvisualpage(1);
	setactivepage(0);
	cleardevice();
	draw_grid(resolution);
	redraw();
	setvisualpage(0);
	setactivepage(1);
	cleardevice();
	setactivepage(0);
	show_mouse();


}//end of function