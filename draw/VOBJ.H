extern int __obj;

void changeprop(const char *name,const char *prop,const char *val)
{
	FILE *fp,*prog;
	prog=fopen("$$$.$$$","at");
	fp=fopen("object.tmp","rt");
	if (fp == NULL) error("FP not available",__FILE__,__LINE__);
	if (prog==NULL) error("prog",__FILE__,__LINE__);
	char *buffer;
	int modify=0;
	buffer=(char *)calloc(1,100);
	if (buffer == NULL) error("buffer",__FILE__,__LINE__);
	while (!feof(fp))
	{
		strcpy(buffer,NULL);
		fscanf(fp,"%s",buffer);

		if (strcmp(buffer,name) == 0)
			modify  = 1;
				if (strncmp(buffer,prop,strlen(prop)) ==0 && modify == 1 && buffer[strlen(prop)] == '=')
				{
				fprintf(prog,"%s=%s\n",prop,val);
				modify=0;
				}
		else
			fprintf(prog,"%s\n",buffer);
	}//end of while
	fclose(fp);
	fclose(prog);
	remove("object.tmp");
	rename("$$$.$$$","object.tmp");
	free(buffer);
}//end of change property


int addobj(int type,char *fname = NULL)
{
	revert();
	show_mouse();
	bind_mouse(5,10,getmaxx()-5,getmaxy()-5);
	FILE *fp,*prog;
	setactivepage(1);
	draw_grid(resolution);
	redraw();
	setactivepage(0);
	char *buffer = (char *)calloc(1,180);
	char *name = (char *)calloc(1,180);
	char *buf = (char *)calloc(1,180);
	prog = fopen("draw.ini","rt");
	int sx,sy,ex,ey;
	while (!feof(prog))
	{
		fgets(buf,180,prog);
		sscanf(buf,"%d %s %s",&sx,name,buffer);
		if (type == sx)
			break;
	}//end of opening the required object
	free(buf);
	if (type != sx)
		{
			free(buffer);
			free(name);
			return -1;
		}
	fclose(prog);
	fp = fopen(buffer,"rt");
	if (strcmp(name,"exe") == 0)
		{
			strcpy(fname,buffer);
			free(buffer);
			free(name);
			return 10;
		}//end of plug in execution

	if (fp == NULL)
		{
		free(name);
		free(buffer);
		return -1;
		}
	quad q = mark();
	prog=fopen("object.tmp","at");
	if (prog == NULL)
		error("Error opening temporary file",__FILE__,__LINE__);
	fprintf(prog,"%s%d\n",name,__obj);
	fprintf(prog,"type=%d\n",sx);
	sprintf(buffer,"%s%d",name,__obj++);
	strcpy(name,buffer);

	while (!feof(fp))
	{
		fscanf(fp,"%s",buffer);
		if (strcmp(buffer,"[properties]") == 0)
		{
			fscanf(fp,"%s",buffer);
			while (strcmp(buffer,"[end]") != 0)
			{
				fprintf(prog,"%s\n",buffer);
				fscanf(fp,"%s",buffer);
			}//end of properties while
			break;
		}//end of if
	}//end of while
	free(buffer);
	fclose(fp);
	fclose(prog);

	sx = q.x1;
	sy = q.y1;
	ex = q.x2;
	ey = q.y2;

	buffer =(char *)calloc(1,80);

	if (sx >ex)  {int t=sx;sx=ex;ex=t;}
	if (sy >ey)  {int t=sy;sy=ey;ey=t;}

	sprintf(buffer,"%d",sx);changeprop(name,"x2",buffer);
	sprintf(buffer,"%d",sy);changeprop(name,"y2",buffer);
	sprintf(buffer,"%d",ex);changeprop(name,"x1",buffer);
	sprintf(buffer,"%d",ey);changeprop(name,"y1",buffer);

	drawobj(name);
	fp = fopen(filetmp,"at");
	fprintf(fp,"object %s\n",name);
	fclose(fp);
	free(buffer);
	free(name);
	setlinestyle(0,0,1);

	show_mouse();
	return 0;
}//end of add
