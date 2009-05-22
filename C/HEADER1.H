# define ONO 100

struct object
{
	char name[100];
	int x1,y1,x2,y2;
	int type;
};

extern int __obj;
extern struct object _ob[ONO];

void getlist()
{
	FILE *fp;
	fp = fopen("object.tmp","rt");
	if (fp == NULL) return;
	char *buffer = (char *)calloc(1,100);
	__obj = 0;
	do{
			fgets(buffer,100,fp);strcpy(_ob[__obj].name,buffer);
			fgets(buffer,100,fp);_ob[__obj].type = atoi(buffer);
			fgets(buffer,100,fp);_ob[__obj].x1 = atoi(buffer);
			fgets(buffer,100,fp);_ob[__obj].y1 = atoi(buffer);
			fgets(buffer,100,fp);_ob[__obj].x2 = atoi(buffer);
			fgets(buffer,100,fp);_ob[__obj].y2 = atoi(buffer);
		while (strcmp(buffer,"**********") != 0);
		fgets(buffer,100,fp);
		__obj++;
	}while(!feof(fp));
	free(buffer);
	fclose(fp);
}//end of function

int sreplace(char *target,char *source,int start,int end)
{
	char *buffer = (char *)calloc(1,100);
	char *s;
	if (buffer == NULL)
		return -1;
	strncpy(buffer,target,start);
	strcat(buffer,source);
	s = target+end;
	int result = strlen(buffer);
	strcat(buffer,s);
	strcpy(target,buffer);
	free(buffer);
	return result;
}//end of replacing


void error(const char *msg,char *file,int line)
{
	closegraph();
	fprintf(stderr,"ERROR in module:\n %s\n\n",msg);
	fprintf(stderr,"Filename    : %s\n",file);
	fprintf(stderr,"Line Number : %d\n",line);
	getch();
	exit(1);
}

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
	remove("object.tmp");
	rename("$$$.$$$","object.tmp");
	free(buffer);
}//end of change property
