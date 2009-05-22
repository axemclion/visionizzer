int plug(char *argval,char *argv2)
{
char *argv1 = (char *)calloc(1,100);
strcpy(argv1,"plugins\\");
strcat(argv1,argval);


char *buffer = (char *)calloc(1,100);
char *buffer1 = (char *)calloc(1,100);
char *buffer2 = (char *)calloc(1,100);
clrscr();
strcpy(buffer,argv1);
strcat(buffer,".zip");
strcpy(buffer1,argv1);
strcat(buffer1,"\\");

int base = 0;
if (strcmp(argv2,"2") == 0)
	base = 2010;
else if (strcmp(argv2,"3") == 0)
	base = 2019;
else if (strcmp(argv2,"1") == 0)
	base = 2001;

strcpy(buffer,argv1);
strcat(buffer,"\\config.ini");
FILE *fp = fopen(buffer,"rt");
FILE *draw = fopen("draw.ttt","wt");
if (fp == NULL)
	{printf("Please check for the configuration file in the plugin");return 2;}

printf("\nReading configuration file %s........",buffer);
printf("\nRegistering the components........");

for (int i = base;i < base + 9 && !feof(fp);i++)
{
	fgets(buffer,100,fp);
	sscanf(buffer,"%s %s\n",buffer1,buffer2);
	fprintf(draw,"%d %s %s\\%s\n",i,buffer1,argv1,buffer2);
	strcpy(buffer,NULL);
}
fclose(fp);

fp = fopen("draw.ini","rt");
while (!feof(fp))
{
	fgets(buffer,100,fp);
	if (feof(fp))
		break;

	sscanf(buffer,"%d %s %s",&i,buffer1,buffer2);
	if (i < base || i > base+8)
		fprintf(draw,"%d %s %s\n",i,buffer1,buffer2);
}//end of restoring other components
fclose(fp);
fclose(draw);
remove("draw.ini");
rename("draw.ttt","draw.ini");

sprintf(buffer,"res\\obj%s.vsn",argv2);
remove(buffer);
sprintf(buffer,"copy %s\\menu.vsn res\\obj%s.vsn",argv1,argv2);
system(buffer);
free(argv1);
free(buffer);
free(buffer1);
free(buffer2);
printf("\nThe required plugin is loaded");
return 0;
}

