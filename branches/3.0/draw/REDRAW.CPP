# include <ctype.h>
# define PROP_NUM 10

void drawobj(const char *name);

void draw_all()
{
hide_mouse();
	FILE *fp;
	if ((fp = fopen("\\cmd.$$$","rt")) != NULL)
	{
	char *buffer = (char *)calloc(1,100);
	while (!feof(fp))
		{
		fscanf(fp,"%s",buffer);
		if (strcmp(buffer,"**********") != 0 && strcmp(buffer,"") != 0)
			drawobj(buffer);
			while (strcmp(buffer,"**********")!=0 && !feof(fp))
				fscanf(fp,"%s",buffer);
		}//end of file
	free(buffer);
	fclose (fp);
	}//end of opening file
show_mouse();
}//end of function


void builtable(const char *buffer,char *nme,char *val)
{
	int togg=0,j=0;
	strcpy(nme,NULL);
	strcpy(val,NULL);
	for (int i=0;i < strlen(buffer);i++)
	{
	if (*(buffer+i) == '=')
		{togg=1;continue;}
	if (!togg)
		*(nme+i) = *(buffer+i);
	else
		{
		*(val+j) = *(buffer+i);
		j++;
		}
	}//end of for
*(val+j)=NULL;
*(nme+i-j-1)=NULL;
}//end of table building

void drawobj(const char *name)
{
	int pctr=0;
	char *nme[PROP_NUM],*val[PROP_NUM];
	char *buffer;
	buffer = (char *)calloc(1,100);
	for (int i=0;i < PROP_NUM;i++)
	{
	nme[i]=(char *)calloc(1,20);
	if (nme[i] == NULL) error("Not enough memory for nme[i]");
	val[i]=(char *)calloc(1,20);
	if (nme[i] == NULL) error("Not enough memory for val[i]");
	}
	FILE *fp;
	fp = fopen("\\cmd.$$$","rt");
	if (fp == NULL) error("Error opening file in draw object");

while (!feof(fp))
{
	fscanf(fp,"%s",buffer);
	if	(strcmp(buffer,name) == 0)
	{
		fscanf(fp,"%s",buffer);
		while (strcmp(buffer,"**********") != 0)
		{
		builtable(buffer,nme[pctr],val[pctr]);
		pctr++;
		fscanf(fp,"%s",buffer);
		}//end of inside pprop - wehile
	break;
	}//end of if
}//end of building table
fclose (fp);

		char *type=(char *)calloc(1,20);
		if (type == NULL) error("Cannot allocate memory for type");
		for (i=0;i < PROP_NUM;i++)
			if (strcmp(nme[i],"type") == 0)
				{
				strcpy(type,val[i]);
				break;
				}

switch (*type)
	{
	case 'l':
		fp=fopen("lblobj.vbc","rt");break;
	case 'c':
		fp=fopen("cmdobj.vbc","rt");break;
	case 't':
		fp=fopen("txtobj.vbc","rt");break;
	default :
		fp = NULL;
	}//end of switch case
free(type);
i=pctr = 0;
strcpy(buffer,NULL);

		while (!feof(fp) && fp != NULL)
		{
			fscanf(fp,"%s",buffer);
			int loop=0;
			if (strcmp(buffer,"[appearence]") == 0)
				pctr = 1;
			if (strcmp(buffer,"[end]") == 0)
				{pctr = 0;break;}
			if (pctr)
				{
				if (strncmp(buffer,"setcolor",8) == 0)
					{loop = 1;i=10;}
				else if (strncmp(buffer,"setfillstyle",12) == 0)
					{loop = 2;i=14;}
				else if (strncmp(buffer,"outtextxy",9) == 0)
					{loop = 2;i=11;}
				else if (strncmp(buffer,"settextstyle",12) == 0)
					{loop = 3;i=14;}
				else if (strncmp(buffer,"setlinestyle",12) == 0)
					{loop = 3;i=14;}
				else if (strncmp(buffer,"floodfill",9) == 0)
					{loop = 3;i=11;}
				else if (strncmp(buffer,"line",4) == 0)
					{loop = 4;i=6;}
				else if (strncmp(buffer,"rectangle",9) == 0)
					{loop = 4;i=11;}
				else if (strncmp(buffer,"ellipse",7) == 0)
					{loop = 6;i=9;}
				else if (strncmp(buffer,"sector",6) == 0)
					{loop = 6;i=8;}
				else if (strncmp(buffer,"settextjustify",14) == 0)
					{loop = 2;i=16;}
				i--;
				int prop[7];
				for (int c=0;c < loop;c++)
				{
					char *nn;
					nn=(char*)calloc(1,50);
					int pctr = 0;
					int flag = 0;
					while (*(buffer+i) != ',' && *(buffer+i) != NULL && *(buffer+i) !='\n' && *(buffer+i) !=')')
					{
						*(nn+pctr)=(*(buffer+i));
						if (!isdigit(*(buffer+i)))
							flag=1;
						i++;
						pctr++;
					}
				*(nn+pctr)=NULL;
				if (!flag)
					prop[c] =atoi(nn);
				else
					{
					for (int i=0;i < PROP_NUM;i++)
						if (strcmp(nme[i],nn) == 0)
							prop[c]=atoi(val[i]);
					}//end of else*/
				i++;
				free(nn);
				}//end of propertiess for (int c= =..)

				if (strncmp(buffer,"setcolor",8) == 0)
					setcolor(prop[0]);
				else if (strncmp(buffer,"settextjustify",14) == 0)
					settextjustify(prop[0],prop[1]);
				else if (strncmp(buffer,"setfillstyle",12) == 0)
					setfillstyle(prop[0],prop[1]);
				else if (strncmp(buffer,"settextstyle",12) == 0)
					settextstyle(prop[0],prop[1],prop[2]);
				else if (strncmp(buffer,"setlinestyle",12) == 0)
					setlinestyle(prop[0],prop[1],prop[3]);
				else if (strncmp(buffer,"floodfill",9) == 0)
					floodfill(prop[0],prop[1],prop[2]);
				else if (strncmp(buffer,"line",4) == 0)
					line(prop[0],prop[1],prop[2],prop[3]);
				else if (strncmp(buffer,"rectangle",9) == 0)
					rectangle(prop[0],prop[1],prop[2],prop[3]);
				else if (strncmp(buffer,"ellipse",7) == 0)
					ellipse(prop[0],prop[1],prop[2],prop[3],prop[4],prop[5]);
				else if (strncmp(buffer,"sector",6) == 0)
					sector(prop[0],prop[1],prop[2],prop[3],prop[4],prop[5]);
				else if (strncmp(buffer,"outtextxy",9) == 0)
					{
					char *b = (char *)calloc(1,100);
					for (int x=0;*(buffer+i) != NULL && *(buffer +i) !=')'; i++,x++)
						*(b+x) = *(buffer+i);

					if (strncmp(b,"\"",1) != 0)
						for (int i=0;i < PROP_NUM;i++)
							if (strcmp(nme[i],"text") == 0)
								strcpy(b,val[i]);
					outtextxy(prop[0],prop[1],b);
					free(b);
					}//end of writin text
				}//end of if pctr;
		}//end of !feof(fp)....
	settextjustify(LEFT_TEXT,TOP_TEXT);
if (fp != NULL) fclose(fp);
free(buffer);
	for (i=0;i < 10;i++)
	{
	free(nme[i]);
	free(val[i]);
	}

}//end of function
