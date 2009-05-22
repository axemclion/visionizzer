void selector()
{
	FILE *fp,*p;
	StatusLine("Select an object to modify",__LINE__,__FILE__);
	fp = fopen("ttt.tmp","wt");
	p = fopen("draw.tmp","rt");

	char *selected = (char *)calloc(1,100);
	char *buffer = (char *)calloc(1,100);
	int count = 0;
	do{
		strcpy(buffer,"");
		fgets(buffer,100,p);
		buffer[32] = '\n';
		buffer[33] = NULL;
		fprintf(fp,"%s",buffer);
		count++;
		if (strncmp(buffer,"polygon",7) == 0 ||strncmp(buffer,"fillpolygon",11) == 0 ||strncmp(buffer,"fillpolygonp",12) == 0)
			while(strcmp(buffer,"End of Points\n") != 0)
				fgets(buffer,100,p);
	}while (!feof(p));
	fclose(p);
	fclose(fp);
	listbox("ttt.tmp",selected,count-1);
	remove("ttt.tmp");
	if (strcmp(selected,"") == 0 || strcmp(selected," ") == 0)
	{
		free(selected);
		free(buffer);
		return;
	}

	FILE *tmp = fopen("ttt.tmp","wt");
	p = fopen("draw.tmp","rt");
	fp  = fopen("undel.tmp","at");
	if (tmp == NULL || p == NULL || fp == NULL)
		error("Cannot open file for modification",__FILE__,__LINE__);

	fgets(buffer,100,p);
	do{
		buffer[strlen(buffer) - 1] = NULL;
		if (strncmp(buffer,selected,30) == 0)
			{
		if (!(strncmp(buffer,"polygon",7) == 0 ||strncmp(buffer,"fillpolygon",11) == 0 ||strncmp(buffer,"fillpolygonp",12) == 0))
			{
			if (strcmp(buffer,"") != 0 && strncmp(buffer,"object",6) != 0)
				fprintf(fp,"%s\n",buffer);
			}
		else
			while(strcmp(buffer,"End of Points\n") != 0)
					fgets(buffer,100,p);
			}//end of writing to undelete file
		else
			{
			fprintf(tmp,"%s\n",buffer);
			if (strncmp(buffer,"polygon",7) == 0 ||strncmp(buffer,"fillpolygon",11) == 0 ||strncmp(buffer,"fillpolygonp",12) == 0)
				while(strcmp(buffer,"End of Points\n") != 0)
					{
					fgets(buffer,100,p);
					fprintf(tmp,"%s",buffer);
					}
			}//written to deleted file
	fgets(buffer,100,p);
	}while (!feof(p));
	fclose(p);
	fclose(fp);
	fclose(tmp);
	remove("draw.tmp");
	rename("ttt.tmp","draw.tmp");
//	free(buffer);
//	free(selected);

	fp = fopen("object.tmp","rt");
	p = fopen("ttt.tmp","wt");
	if (p == NULL || fp == NULL)
		error("Cannot open file for modification",__FILE__,__LINE__);
	strcat(selected,"\n");
	char *s;
	s = selected+7;

	fgets(buffer,100,fp);
	do{
		if (strcmp(buffer,s) == 0)
			{
			while (strcmp(buffer,"**********\n") != 0)
				fgets(buffer,100,fp);
			fgets(buffer,100,fp);
			}
		if (strcmp(buffer,"") != 0)
			fprintf(p,"%s",buffer);
	fgets(buffer,100,fp);
	}while(!feof(fp));
	free(buffer);
	free(selected);
	fclose(fp);
	fclose(p);
	remove("object.tmp");
	rename("ttt.tmp","object.tmp");
}//end of selecting and deleting an object*/

void undelete()
{
	FILE *fp,*p,*tmp;
	fp = fopen("draw.tmp","at");
	 p = fopen("undel.tmp","rt");
  tmp = fopen("ttt.tmp","wt");
	if (fp == NULL || tmp == NULL)
		error("Cannot allocate or open files for undelete",__FILE__,__LINE__);
	if (p == NULL)
		{
		fclose(fp);
		fclose(tmp);
		return;
		}

	char *buffer = (char *)calloc(1,100);
	char *buffer1 = (char *)calloc(1,100);

		do
		{
		strcpy(buffer1,buffer);
		fgets(buffer,100,p);
		if (!feof(p))
			fprintf(tmp,"%s",buffer1);
		}while (!feof(p));
	fprintf(fp,"%s",buffer);
	fclose(fp);
	free(buffer);
	free(buffer1);
	fclose(p);
	fclose(tmp);
	remove("undel.tmp");
	rename("ttt.tmp","undel.tmp");
	hide_mouse();
	draw_grid(resolution);
	redraw();
	show_mouse();
}//end of the undelete function