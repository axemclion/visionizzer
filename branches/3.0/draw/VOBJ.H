void changeprop(const char *name,const char *prop,const char *val)
{
	FILE *fp,*prog;

	prog=fopen("\\$$$.$$$","at");
	fp=fopen("\\cmd.$$$","rt");

	if (fp == NULL) error("FP not available");
	if (prog==NULL) error("prog");

	char *buffer;
	int modify=0;

	buffer=(char *)calloc(1,100);
	if (buffer == NULL) error("buffer");

	while (!feof(fp))
	{
		strcpy(buffer,NULL);
		fscanf(fp,"%s",buffer);

		if (strcmp(buffer,name) == 0)
			modify  = 1;
				if (strncmp(buffer,prop,strlen(prop)) ==0 && modify == 1)
				{
				fprintf(prog,"%s=%s\n",prop,val);
				modify=0;
				}
		else
			fprintf(prog,"%s\n",buffer);
	}//end of while
	fclose(fp);
	fclose(prog);

	remove("\\cmd.$$$");
	rename("\\$$$.$$$","\\cmd.$$$");
	free(buffer);
}//end of change property


int add(char *type,char *name)
{
	bind_mouse(3,10,getmaxx(),getmaxy());
	FILE *fp,*prog;

	setactivepage(1);
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	switch(*type)
	{
	case 'c':
		fp=fopen("cmdobj.vbc","rt");break;
	case 'l':
		fp=fopen("lblobj.vbc","rt");break;
	case 't':
		fp=fopen("txtobj.vbc","rt");break;
	default:
		return 0;
	}

	prog=fopen("\\cmd.$$$","at");

	if (prog == NULL)
		error("Error opening temporary file");
	if (fp == NULL)
		error("Error opening object file\nMake sure that the object file exists");

	char *buffer = (char *)calloc(1,80);
	while (!feof(fp))
	{
		fscanf(fp,"%s",buffer);
		if (strcmp(buffer,"[properties]") == 0)
		{
				fscanf(fp,"%s",buffer);
			while (strcmp(buffer,"[end]") != 0)
			{
				if (strcmp(buffer,type)==0)
					fprintf(prog,"%s\n",name);
				else
					fprintf(prog,"%s\n",buffer);
				fscanf(fp,"%s",buffer);
			}//end of properties while
			break;
		}//end of if
	}//end of while
	free(buffer);
	fclose(fp);
	fclose(prog);

	int sx,sy,ex,ey,x1,y1;
	mouse_status mouse;
	sx=sy=ex=ey=0;
	mouse.button =0 ;
	while (mouse.button == 0)
	{
		mouse=click();
		if (mouse.button==LEFT_CLICK)
		{sx=mouse.x;sy=mouse.y;}
		if (mouse.button == MIDDLE_CLICK)
		{
		position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
		mouse.button=0;
		}
		if (mouse.button == RIGHT_CLICK || mouse.button == BOTH_CLICK) mouse.button =0;
	}//end of while
	sx=mouse.x;
	sy=mouse.y;

	mouse.button = 0;
	hide_mouse();

	setcolor(15);
	setlinestyle(1,0,1);

	while (!mouse.button)
	{
		x1=mouse.x;y1=mouse.y;
		mouse=status();
		if (mouse.button == MIDDLE_CLICK)
			{
			position_mouse(mouse.x-(mouse.x % resolution),mouse.y - (mouse.y%resolution));
			mouse.button = 0;
			}

		if (mouse.x < 3) mouse.x =3;
		if (mouse.y < 3) mouse.y =3;
		ex=mouse.x;
		ey=mouse.y;
		rectangle(sx,sy,ex,ey);
//		if (mouse.x!=x1 || mouse.y !=y1)
		{

			char *_uffer = (char *)malloc(imagesize(0,0,10,60));
			char *_buffer = (char *)malloc(imagesize(0,0,10,60));
			setfillstyle(SOLID_FILL,3);
			for (int a=min(sx,x1);a<=max(sx,x1);a=a+60)
				{
					if (a+58 > getmaxx())
					{
						setactivepage(1);
						getimage(getmaxx()-58,sy-1,getmaxx()-1,sy+1,_buffer);
						getimage(getmaxx()-58,y1-1,getmaxx()-1,y1+1,_uffer);
						setactivepage(0);
						putimage(getmaxx()-58,sy-1,_buffer,COPY_PUT);
						putimage(getmaxx()-58,y1-1,_uffer,COPY_PUT);
					}//end of x out of bounds
				setcolor(color);
				setactivepage(1);
				getimage(a-1,sy-1,a+58,sy+1,_buffer);
				getimage(a-1,y1-1,a+58,y1+1,_uffer);
				setactivepage(0);
				putimage(a-1,sy-1,_buffer,COPY_PUT);
				putimage(a-1,y1-1,_uffer,COPY_PUT);
				}
			for (a=min(sy,y1);a<=max(sy,y1);a=a+60)
				{
				setactivepage(1);
				getimage(sx-1,a-1,sx+1,a+58,_buffer);
				getimage(x1-1,a-1,x1+1,a+58,_uffer);
				setactivepage(0);
				putimage(sx-1,a-1,_buffer,COPY_PUT);
				putimage(x1-1,a-1,_uffer,COPY_PUT);
				}
			free(_uffer);
			free(_buffer);

		}//end of rectangle selection

	}//end of while

	char *uffer =(char *)calloc(1,80);

	if (sx >ex)  {int t=sx;sx=ex;ex=t;}
	if (sy >ey)  {int t=sy;sy=ey;ey=t;}

	sprintf(uffer,"%d",sx);
	changeprop(name,"x2",uffer);
	sprintf(uffer,"%d",sy);
	changeprop(name,"y2",uffer);
	sprintf(uffer,"%d",ex);
	changeprop(name,"x1",uffer);
	sprintf(uffer,"%d",ey);
	changeprop(name,"y1",uffer);

int x3= (sx+ex)/2;
int y3=(sy+ey)/2;

	sprintf(uffer,"%d",y3);
	changeprop(name,"y3",uffer);
	sprintf(uffer,"%d",x3);
	changeprop(name,"x3",uffer);
	free(uffer);
	setlinestyle(0,0,1);

	drawobj(name);
	show_mouse();
	return 0;
}//end of add
