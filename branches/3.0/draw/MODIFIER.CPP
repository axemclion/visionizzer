void select_color()
{
FILE *fp;
int x,y,sr,er,c;
int sx,sy,ser,ssr,ssc;

x=y=sr=er=c=0;
int selected = 0,key=0;

{
char word[64] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xff,0xff,0xc7,0x83,0x4f,0x82,0x5d,0x82,0xf9,0x83,0x71,0x82,0xe1,0x82,0xc1,0x83,0xe1,0x87,0xf1,0x8e,0xf1,0x8d,0xf1,0xbb,0xf1,0xbf,0x51,0xf5,0x51,0xe5,0xff,0xff,};
mouse_change(word);
}

char c1[8]={0,0,0,0,0,0,0,0};
fp = fopen("\\fill.$$$","rt");

if (fp != NULL)
{
	while (selected == 0)
	{
		key=getch();
		switch(key)
		{
			case 80://up
			case 72://down
				if (feof(fp))
					fseek(fp,0l,SEEK_SET);
				else
					fscanf(fp,"%03d,%03d,%02d,%02d,%02d, p %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&c,&sr,&er,&c1[0],&c1[1],&c1[2],&c1[3],&c1[4],&c1[5],&c1[6],&c1[7]);
				break;

			case	27:
				selected =-1;
				break;
			case 13:
				ssc = c;sx=x;sy =y ;ssr = sr;ser = er;
				selected =1;
				break;
		}//end of swithcase
	position_mouse(x,y);

	setcolor(c);
	if (sr==12)
		setfillpattern(c1,er);
	else
		setfillstyle(sr,er);
	bar(500,1,600,10);
	}//end of while selected
fclose(fp);
}//end of file open
if (selected ==1)
{
	FILE *t;
	t=fopen("\\tmp.$$$","wt");
	fp=fopen("\\fill.$$$","rt");

if (t==NULL) error ("Error opening tempory file for removing color");
if (fp==NULL) error ("Error opening tempory file for removing color");

while (!feof(fp))
	{
		fscanf(fp,"%03d,%03d,%02d,%02d,%02d, p %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&c,&sr,&er,&c1[0],&c1[1],&c1[2],&c1[3],&c1[4],&c1[5],&c1[6],&c1[7]);
	if (!(sx == x && sy ==y && ser ==er && ssr == sr && ssc ==c))
		 fprintf(t,"%03d,%03d,%02d,%02d,%02d, p %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",x,y,c,sr,er,c1[0],c1[1],c1[2],c1[3],c1[4],c1[5],c1[6],c1[7]);
	}//end of file
	fclose(fp);
	fclose(t);
}//end of deletion if
remove("\\fill.$$$");
rename("\\tmp.$$$","\\fill.$$$");
mouse_change(_TARGET_CUR);
}//end of color select


/*int matherr (struct exception *a)
{
  if (a->type == DOMAIN)
	 if (!strcmp(a->name,"sqrt")) {
		a->retval = sqrt (-(a->arg1));
	 return 1;
	 }
  return 0;
} */

extern int err;

void select()
{
int selected=0;
mouse_status mouse= {0,0,0};
StatusLine("Select an object by clicking it",__LINE__,__FILE__);
setactivepage(1);
cleardevice();
draw_grid(resolution);
	click();
	int sx2,sy2,sx1,sy1,col,t,ls,sr,er,ts;
	int x1,y1,x2,y2;
	char *res;
	res=(char * )malloc(100);
	if (res == NULL) error("Error allocating memory for text\nSelection Mdoule");

while (selected == 0)
{
	mouse=status();
	int _key_;
	if (kbhit()) _key_ = getch();
	if (_key_ == 27) selected =-1;
	_key_ =0;

	gotoxy(72,1);printf("%03d,%03d",mouse.x,mouse.y);

	if (mouse.button ==MIDDLE_CLICK)
	{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
	}//end of middle click

if (mouse.button == LEFT_CLICK)
{
	setactivepage(1);
	selected =-1;
	/************line selection***************/
	FILE *fp,*temp;
	if ((temp = fopen("\\$$$.$$$","wt")) == NULL) 	error("ERROR opening Teporary file for line");
	if ((fp = fopen("\\line.$$$","rt")) != NULL)
{
		while (!feof(fp))
		{
		fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&sx2,&sy2,&sx1,&sy1,&col,&t,&ls);

	int a,b,c;
	a=sy2-sy1;
	b=sx1-sx2;
	c=sx1*(sy1-sy2) + sy1*(sx2-sx1);
	float r;
	r=a*mouse.x + b*mouse.y+c;
	r=abs(r *r / (a*a + b*b));

	if (r < (err*err)  && min(sx1,sx2) <= mouse.x && max(sx1,sx2) >= mouse.x && min(sy1,sy2) <= mouse.y && max(sy2,sy1) >= mouse.y)
	{
		selected=1;
		x1=sx1;y1=sy1;x2=sx2;y2=sy2;
		setactivepage(0);
		StatusLine("Line has been selected",__LINE__,__FILE__);
	}//end of if
		else
			{
			  setactivepage(1);
			  setcolor(col);
			  setlinestyle(ls,0,t);
			  line(sx2,sy2,sx1,sy1);
			  fprintf(temp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",sx2,sy2,sx1,sy1,col,t,ls);
			}//end of else
		}//end of while feof
		fclose(fp);
}//end of line
		fclose(temp);
	setactivepage(0);

		/******start circle selection*****/
	if ((temp = fopen("\\c$$$.$$$","wt")) == NULL) error("ERROR opening Teporary file for circle");
	if ((fp = fopen("\\circ.$$$","rt")) != NULL)
{
		while (!feof(fp))
		{
		sx1=sy1=sx2=sy2=0;
		fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&sx1,&sy1,&sr,&er,&sx2,&sy2,&col,&t,&ls,&ls);
		int bx,by;
		float r;
		bx=abs(sx1-mouse.x);
		by=abs(sy1-mouse.y);
		r=sqrt(bx*bx+by*by);
		r=r*(float)(1-sx2*sy2/sqrt((float)bx*bx*sy2*sy2 + (float)by*by*sx2*sx2));

		if (abs(r) < err*err)
		{
			x1=sx1-sx2;y1=sy1-sy2;x2=sx1+sx2;y2=sy1+sy2;
			setactivepage(0);
			StatusLine("CIRCLE SELECTED",__LINE__,__FILE__);
			selected =3;
		}
		else
		{
			setactivepage(1);
			setlinestyle(0,0,t);
			setcolor(col);
			ellipse(sx1,sy1,sr,er,sx2,sy2);
			fprintf(temp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",sx1,sy1,sr,er,sx2,sy2,col,t,x1,ls);
		}//end of else
		}//end of file read operation
		fclose(fp);
}//end of circle selection
		fclose(temp);
		/******start pie selection*****/
	if ((temp = fopen("\\p$$$.$$$","wt")) == NULL) error("ERROR opening Teporary file for piee");
	if ((fp = fopen("\\pie.$$$","rt")) != NULL )
{
		while (!feof(fp))
		{
		sx1=sy1=sx2=sy2=0;
		fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&sx1,&sy1,&sr,&er,&sx2,&sy2,&col,&t,&ls,&ts);
		int bx,by;
		float r;
		bx=abs(sx1-mouse.x);
		by=abs(sy1-mouse.y);
		r=sqrt(bx*bx+by*by);
		r=r*(float)(1-sx2*sy2/sqrt((float)bx*bx*sy2*sy2 + (float)by*by*sx2*sx2));

		if (abs(r) < err*err)
		{
			x1=sx1-sx2;y1=sy1-sy2;x2=sx1+sx2;y2=sy1+sy2;
			setactivepage(0);
			StatusLine("PIESLICE SELECTED",__LINE__,__FILE__);
			selected =4;
		}
		else
		{
			setactivepage(1);
			setlinestyle(0,0,t);
			setcolor(col);
			setfillstyle(ls,ts);
			sector(sx1,sy1,sr,er,sx2,sy2);
			fprintf(temp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",sx1,sy1,sr,er,sx2,sy2,col,t,ls,ts);
		}//end of else
		}//end of file read operation
		fclose(fp);
}//end of circle selection
		fclose(temp);
/********start of rectangle selection************/
	setactivepage(0);
		/******start rectangle selection*****/
	if ((temp = fopen("\\r$$$.$$$","wt")) == NULL) error("ERROR opening Teporary file for Rectanglee");
	if ((fp = fopen("\\rect.$$$","rt")) != NULL )
{
		while (!feof(fp))
		{
		sx1=sy1=sx2=sy2=0;
		fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&sx2,&sy2,&sx1,&sy1,&col,&t,&ls);

	int r1,r2,r3,r4;
	r1=abs(mouse.x - sx1);
	r2=abs(mouse.x - sx2);
	r3=abs(mouse.y - sy1);
	r4=abs(mouse.y - sy2);

	float r = min(min(r1,r2),min(r3,r4));

	if (abs(r) < err*err && mouse.x <= max(sx1,sx2) && mouse.x >= min(sx1,sx2) && mouse.y <= max(sy1,sy2) && mouse.y >= min(sy1,sy2))
		{
			setactivepage(0);
			x1=sx1;y1=sy1;x2=sx2;y2=sy2;
			StatusLine("RECTANGLE SELECTED",__LINE__,__FILE__);
			selected =2;
		}
		else
		{
			setactivepage(1);
			setlinestyle(ls,0,t);
			setcolor(col);
			rectangle(sx1,sy1,sx2,sy2);
			fprintf(temp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",sx2,sy2,sx1,sy1,col,t,ls);
		}//end of else
		}//end of file read operation
		fclose(fp);
}//end of rectangle selection
		fclose(temp);
	setactivepage(0);
			/******start rectangle selection*****/
	if ((temp = fopen("\\t$$$.$$$","wt")) == NULL) error("ERROR opening Teporary file for text");
	if ((fp = fopen("\\text.$$$","rt")) != NULL)
{
		sx1=sy1=sx2=sy2=0;
		while (!feof(fp))
		{
		strcpy(res,NULL);
		fscanf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,%s\n",&col,&sx2,&sy2,&sx1,&sy1,&sr,res);
		settextstyle(sx1,sy1,sr);
		int ax1,ax2,ay1,ay2;

		ax1 = sx2;
		ay1 = sy2;
		ax2 = sx2+textwidth(res);
		ay2 = sy2+textheight(res);


	if (mouse.x > ax1 && mouse.x < ax2 && mouse.y < ay2 && mouse.y > ay1)
		{
			x1=ax1;y1=ay1;x2=ax2;y2=ay2;
			setactivepage(0);
			StatusLine("TEXT HAS BEEN SELECTED",__LINE__,__FILE__);
			selected =5;
		}
		else
		{
		setactivepage(1);
		char *buf;
		int ac=0;
		buf = (char *)calloc(1,100);
		if (!buf) error("ERROR Allocating buffer memory in Text module\n\nSection Selection");
		*buf = *res;
		while (*(res+ac) != NULL)
		{
			if (*(res+ac) ==253)
				*(buf+ac)=' ';
			else
				*(buf+ac)=*(res+ac);
		  ac++;
		}

		setcolor(col);
		settextstyle(sx1,sy1,sr);
		outtextxy(sx2,sy2,buf);
		free(buf);
		fprintf(temp,"%02d,%03d,%03d,%02d,%02d,%02d,%s\n",col,sx2,sy2,sx1,sy1,sr,res);
		}//end of else
		}//end of file read operation
		fclose(fp);
}//end of rectangle selection
		fclose(temp);
	}//end of button clicked selection wif
}//end of selection while

setactivepage(0);
int key=0;
			while (key != 27)
			{
			if (selected < 0) key =27;
			if (kbhit())	key = getch();
			if (key== 83) //delete
				{
				hide_mouse();
				if (selected == 1 || selected == 3 || selected == 2 || selected == 4 || selected == 5)
				{
				StatusLine("Object deleted",__LINE__,__FILE__);

				char *fer=(char*)malloc(imagesize(42,42,0,0));
				if (fer == NULL) error("\nerror modifying line\nCannot create a temp memory for Buffer");

				for (int a=min(x2,x1);a<=max(x2,x1);a=a+40){
				for (int b=min(y2,y1);b<=max(y2,y1);b=b+40)
				{
				if (a+41 > getmaxx())
				{
				setactivepage(1);
				getimage(getmaxx()-42,b-1,getmaxx()-1,b+41,fer);
				setactivepage(0);
				putimage(getmaxx()-42,b-1,fer,COPY_PUT);
				}//end of x out of bounds
			setactivepage(1);
			getimage(a-1,b-1,a+41,b+41,fer);
			setactivepage(0);
			putimage(a-1,b-1,fer,COPY_PUT);
//			rectangle(a-1,b-1,a+41,b+41);
				}}//end of fornext
				free(fer);
				if (selected == 1)
					{remove("\\line.$$$");rename("\\$$$.$$$","\\line.$$$");}
				if (selected == 3)
					{remove("\\circ.$$$");rename("\\c$$$.$$$","\\circ.$$$");}
				if (selected == 2)
					{remove("\\rect.$$$");rename("\\r$$$.$$$","\\rect.$$$");}
				if (selected == 4)
					{remove("\\pie.$$$");rename("\\p$$$.$$$","\\pie.$$$");}
				if (selected == 5)
					{remove("\\text.$$$");rename("\\t$$$.$$$","\\text.$$$");}
				}//end of line delete
				show_mouse();
				key=27;
				}//end of delete key
		}//end of while
setactivepage(1);
cleardevice();
setactivepage(0);
StatusLine("Strike F1 for Help",__LINE__,__FILE__);
free(res);
remove("\\$$$.$$$");
remove("\\c$$$.$$$");
remove("\\r$$$.$$$");
remove("\\p$$$.$$$");
remove("\\t$$$.$$$");
show_mouse();
}//end of select
