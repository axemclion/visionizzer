# define PROP_NUM 15

int parse(char*);
void drawobj(char *name);

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

void drawobj(char *oname)
{
	StatusLine("Redrawing",__LINE__,__FILE__);
	int pctr=0;
	char *nme[PROP_NUM],*val[PROP_NUM];
	char *buffer,*name;

	buffer = (char *)calloc(1,300);
	name = (char *)calloc(1,100);

	for (int i=0;i < PROP_NUM;i++)
	{
	nme[i]=(char *)calloc(1,80);
		if (nme[i] == NULL) error("Not enough memory for nme[i]",__FILE__,__LINE__);
	val[i]=(char *)calloc(1,80);
		if (nme[i] == NULL) error("Not enough memory for val[i]",__FILE__,__LINE__);
	}
	FILE *fp;
	fp = fopen("object.tmp","rt");
		if (fp == NULL) error("Error opening file in draw object",__FILE__,__LINE__);

while (!feof(fp))
{
	fgets(buffer,300,fp);
	buffer[strlen(buffer) -1] = NULL;
	if	(strcmpi(buffer,oname) == 0)
	{
	fgets(buffer,300,fp);
	buffer[strlen(buffer) -1] = NULL;
		while (strcmp(buffer,"**********") != 0)
		{
		builtable(buffer,nme[pctr],val[pctr]);
		fgets(buffer,300,fp);
		pctr++;
		buffer[strlen(buffer) -1] = NULL;
		}//end of inside pprop - wehile
	break;
	}//end of if
}//end of building table
fclose (fp);

		int type;
		type = 0;
		for (i=0;i < PROP_NUM;i++)
			if (strcmp(nme[i],"type") == 0)
				{
				type = atoi(val[i]);
				break;
				}
fp = fopen("draw.ini","rt");
if (fp == NULL)	error("Cannot open draw.ini for redrawing the objects",__FILE__,__LINE__);
while (!feof(fp))
{
	fscanf(fp,"%d %s %s",&i,name,buffer);
	if (i == type)
		break;
}//end end of parsing all the things
fclose(fp);
fp = fopen(buffer,"rt");
if (fp == NULL)	error("Error opening the file for an object",__FILE__,__LINE__);
i=pctr = 0;
strcpy(buffer,NULL);

//start of parsing the file
int args[10];
while (strcmpi(buffer,"[appearence]\n") != 0 && !feof(fp))
	fgets(buffer,300,fp);
type = 0;
	fgets(buffer,300,fp);
while (strcmpi(buffer,"[end]\n") != 0 && !feof(fp))
{
	int ctr = 0;type = 0;
	while (buffer[ctr++] != '(');
	while (buffer[ctr] != ')' && buffer[ctr] != '\n')
	{
		args[0] = ctr;
if (isalpha(buffer[ctr]))
	{
			for (int i=ctr;buffer[ctr] != ']' && buffer[ctr] !=',' && buffer[ctr] != ')' && buffer[ctr] != '+' && buffer[ctr] != '-' && buffer[ctr] != '*' && buffer[ctr] != '/' ;ctr++)
				name[ctr-i] = buffer[ctr];
			name[ctr-i] = NULL;
		if (!isdigit(name[0]))
		{
			for (int i = 0;i < PROP_NUM;i++)
				if (strcmpi(nme[i],name) == 0)
					strcpy(name,val[i]);
			ctr = sreplace(buffer,name,args[0],ctr);
			args[0] = 0;
		}//go and look in the lookup table
}//is this is an arguement
	ctr++;
	}//end of changing all arguements

 //finished changinging the actual values*****
	type = 0;
	ctr = 0;
	while (buffer[ctr++] != '(');
	while (buffer[ctr] != ')' && buffer[ctr] != '\n')
	{
		for (int i=ctr;(buffer[ctr] !=',' && buffer[ctr] != ')');ctr++)
			name[ctr-i] = buffer[ctr];
		name[ctr-i] = NULL;
		ctr++;
		args[type++] = parse(name);
	}//end of reading all arguements
	ctr = 0;
	while (buffer[ctr] != '(')
		name[ctr++] = buffer[ctr];
	name[ctr] = NULL;
	hide_mouse();
				if (strncmp(name,"setcolor",8) == 0)
					setcolor(args[0]);
				else if (strncmp(name,"settextjustify",14) == 0)
					settextjustify(args[0],args[1]);
				else if (strncmp(name,"setfillstyle",12) == 0)
					setfillstyle(args[0],args[1]);
				else if (strncmp(name,"settextstyle",12) == 0)
					settextstyle(args[0],args[1],args[2]);
				else if (strncmp(name,"setlinestyle",12) == 0)
					setlinestyle(args[0],args[1],args[3]);
				else if (strncmp(name,"floodfill",9) == 0)
					floodfill(args[0],args[1],args[2]);
				else if (strncmp(name,"line",4) == 0)
					line(args[0],args[1],args[2],args[3]);
				else if (strncmp(name,"bar",3) == 0)
					bar(args[0],args[1],args[2],args[3]);
				else if (strncmp(name,"rectangle",9) == 0)
					rectangle(args[0],args[1],args[2],args[3]);
				else if (strncmp(name,"ellipse",7) == 0)
					ellipse(args[0],args[1],args[2],args[3],args[4],args[5]);
				else if (strncmp(name,"sector",6) == 0)
					sector(args[0],args[1],args[2],args[3],args[4],args[5]);
				else if (strncmp(name,"outtextxy",9) == 0)
					{
					ctr = strlen(buffer);
					while (buffer[ctr--] != ',');
					char *s;
					s = buffer+ctr+2;
					strcpy(name,s);
					name[strlen(name) - 2] = NULL;
					outtextxy(args[0],args[1],name);
					}//end of outtext
				else if (strncmp(name,"loadbmp",7) == 0)
					{
					ctr = strlen(buffer);
					while (buffer[ctr--] != ',');
					char *s;
					s = buffer+ctr+2;
					strcpy(name,s);
					name[strlen(name) - 2] = NULL;
					drawbmp(name,args[0],args[1]);
					}//end of loading BMP
	show_mouse();
	fgets(buffer,300,fp);
}//end of reading all available instructions

//end of parsing********

fclose(fp);
free(buffer);free(name);
	for (i=0;i < PROP_NUM;i++)
	{
	free(nme[i]);
	free(val[i]);
	}
settextjustify(LEFT_TEXT,TOP_TEXT);
StatusLine("Done",__LINE__,__FILE__);
}//end of function

int parse(char *str)
{
	int start=0,end = 0;
	int count = 0;
	float var1 = 0,var2 = 0;
	char op = 0;
	//check if this is a plain number
	while (str[count] != NULL)
		if (!isdigit(str[count++]))
			op = 1;
	if (op == 0)
		return atoi(str);
	count = op = 0;
	//check for brackets
do{
	if (str[count] == '[')
	{
		char *b1 = (char *)calloc(1,100);
		char *b2 = (char *)calloc(1,100);
		start = count++;
		op = 1;
		while (op != 0 && str[count] != NULL)
			{
			if (str[count] == '[')
				op++;
			if (str[count] == ']')
				op--;
			b1[count-start-1] = str[count++];
			}//end of parsing b1
		end = count;
		b1[strlen(b1)-1] = NULL;
		var1=parse(b1);
		sprintf(b1,"%d",(int)var1);
		strncpy(b2,str,start);
		strcat(b2,b1);
		free(b1);
		b1 = str+end;
		strcat(b2,b1);
		strcpy(str,b2);
		free(b2);
		count = 0;
	}//end of brackets
}while (str[count] != '[' && str[count++] != NULL);
	count = start= end=0;
	var1=var2=0;
	while (str[count] != NULL && op != 1)
	{
		var1 = 0;
		var2 = 0;
		start = count;
		while (isdigit(str[count]))
			var1 = (str[count++]-'0') + var1*10;
		if (str[count] == NULL)
			break;
		op = str[count++];
		int flag = 0;
		while (op == '*' || op == '/')
		{
			flag = 0;
			var2 = 0;
			while (isdigit(str[count]))
				{
				var2 = (str[count++]-'0') + var2*10;
				flag = 1;
				}
			if (op == '*')
				var1 *=var2;
			else
				var1 /=var2;
			if (str[count] == NULL)
				op = 1;
			else
				op = str[count++];
		}//do fo all multiplications
		if (flag != 0)
			{
			end = count -2;
			char *b1 = (char *)calloc(1,100);
			char *b2 = (char *)calloc(1,100);
			sprintf(b1,"%d",(int)var1);
			strncpy(b2,str,start);
			strcat(b2,b1);
			count = strlen(b2) + 1;
			free(b1);
			b1 = str+end+1;
			if (op != 1)
				strcat(b2,b1);
			strcpy(str,b2);
			free(b2);
		}//end of replacing the string
	}//end of parsing once for multiplication
		count = 0;
		var1 = var2=0;
		while (isdigit(str[count]))
			var1 = (str[count++]-'0') + var1*10;
		op = str[count++];

		for (count=count -1;str[count] != NULL;count++)
			{
			var2 = 0;
			op = str[count++];
			while (isdigit(str[count]))
				var2 = (str[count++]-'0') + var2*10;
			if (op == '+')
				var1+=var2;
			else
				var1-=var2;
			count--;
			}//end of addition
	return var1;
}//end of the parsing module
