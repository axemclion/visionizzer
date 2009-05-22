void intro();

void attr()
{
	StatusLine("Click on an object to change its properties",__LINE__,__FILE__);
	mouse_status mouse;
	xclick();int count = 0;
	mouse = click();
	FILE *fp,*prog;
	fp = fopen("object.tmp","rt");
	prog = fopen("objtmp.tmp","wt");
	StatusLine("Object not found or selected",__LINE__,__FILE__);
	char *sc = (char *)calloc(1,100);char *name =(char *)calloc(1,100);
	if (sc == NULL)	error("Cannot allcate memory for sc in attribures box",__FILE__,__LINE__);
	int no;quad q;
	if (fp == NULL)
		return;
	char *object = (char*)calloc(1,100);
	while (!feof(fp))
	{
		no = 0;
		fgets(object,100,fp);
		fgets(name,100,fp);
		fgets(sc,100,fp);
		if (feof(fp))
			break;
		while (sc[no] != '=') sc[no++] = ' ';sc[no] = ' ';q.x1 = atoi(sc);no = 0;
		fgets(sc,100,fp);	while (sc[no] != '=')sc[no++] = ' ';sc[no] = ' ';q.y1 = atoi(sc);no = 0;
		fgets(sc,100,fp);	while (sc[no] != '=')sc[no++] = ' ';sc[no] = ' ';q.x2 = atoi(sc);no = 0;
		fgets(sc,100,fp);	while (sc[no] != '=')sc[no++] = ' ';sc[no] = ' ';q.y2 = atoi(sc);no = 0;
		if (!inarea(mouse.x,mouse.y,q.x1,q.y1,q.x2,q.y2))
			while (strnicmp(name,"**********",10) != 0 && !feof(fp))
				fgets(name,100,fp);
		else
			{
			fprintf(prog,"x2=%d\n",q.x1);	fprintf(prog,"y2=%d\n",q.y1);	fprintf(prog,"x1=%d\n",q.x2);fprintf(prog,"y1=%d\n",q.y2);
			count= 3;
				do{
				count++;
				fgets(sc,100,fp);
				if (strnicmp(sc,"**********",10) != 0)
					fprintf(prog,"%s",sc);
				}while (strnicmp(sc,"**********",10) != 0);
			break;
			}//this is witten to the file
	}//do till the emd of this file
	fclose(fp);fclose(prog);
	free(sc);free(name);
	StatusLine("No objects available",__LINE__,__FILE__);
	if (count == 0)
		{
		if (object != NULL)
			free(object);
		return;
		}
	do
	{
		char * buffer = (char *)calloc(1,100);
		sc = (char *)calloc(1,100);
		listbox("objtmp.tmp",sc,count);
		if (strcmp(sc," ") == 0)
		{
			free(buffer);
			free(sc);
			break;
		}
		no = 0;
		while (sc[no++] != '=');
		name = sc+no;
		strcpy(buffer,name);
		G_input_box(buffer,"New Property","Enter a new value for ",sc);
		no = 0;
		while (sc[no++] != '=');
		sreplace(sc,buffer,no,strlen(sc));
		FILE *fp1,*fp2;
		fp1 = fopen("objtmp.tmp","rt");fp2 = fopen("ttt.tmp","wt");
		if (fp1 == NULL || fp2 == NULL) error("Cannot open fp1 and fp22",__FILE__,__LINE__);
		while (!feof(fp1))
		{
			fgets(buffer,100,fp1);
			if (strnicmp(sc,buffer,no) == 0)
				fprintf(fp2,"%s\n",sc);
			else
				fprintf(fp2,"%s",buffer);
		}//end of reading
		fclose(fp1);fclose(fp2);remove("objtmp.tmp");rename("ttt.tmp","objtmp.tmp");
		no = 0;free(buffer);
		while (sc[no++] != '=');
		name = sc+no;sc[no-1] = NULL;
		object[strlen(object)-1] = NULL;
		changeprop(object,sc,name);
		free(sc);
	}while (1 == G_YesNoDialog("Continue to change ","other properties of ","this object","Change Property"));
	hide_mouse();
	cleardevice();
	draw_grid(resolution);
	redraw();
	show_mouse();
	free(object);
}//end of attributes

void codegen()
{
	StatusLine("Select a function to edit",__LINE__,__FILE__);
	xclick();
	mouse_status mouse;
	mouse = click();
	FILE *fp = fopen("object.tmp","rt");
	if (fp == NULL)
		return;
	quad q;
	int ot = 0;
	char *buffer = (char *)calloc(1,50);
	char *name = (char *)calloc(1,50);
	char *type = (char *)calloc(1,50);
	char *object = (char *)calloc(1,50);
	while (!feof(fp))
	{
		fgets(object,100,fp);
		object[strlen(object)-1] = NULL;
			fgets(type,100,fp);
			if (feof(fp))
				break;
			builtable(type,buffer,name);	ot  =atoi(name);

			fgets(type,100,fp);builtable(type,buffer,name);q.x1=atoi(name);
			fgets(type,100,fp);builtable(type,buffer,name);q.y1=atoi(name);
			fgets(type,100,fp);builtable(type,buffer,name);q.x2=atoi(name);
			fgets(type,100,fp);builtable(type,buffer,name);q.y2=atoi(name);

			while (!feof(fp) && strncmp(buffer,"**********",10) != 0)
				fgets(buffer,100,fp);
			if (inarea(mouse.x,mouse.y,q.x1,q.y1,q.x2,q.y2))
				{
				ot = ot + 10000;
				break;
				}
	}//end of reading the file
	free(buffer);
	free(type);
	free(name);
	fclose(fp);
	if (ot < 10000)
		{
		free(object);
		return;
		}
	buffer = (char *)calloc(1,200);
	name = (char *)calloc(1,200);
	ot-=10000;
	fp = fopen("draw.ini","rt");
	int sx,sy,ex,ey;
	while (!feof(fp))
	{
		fscanf(fp,"%d %s %s",&q.x1,name,buffer);
		if (ot == q.x1)
			break;
	}//end of this while loop
	fclose(fp);

	fp = fopen(buffer,"rt");
	FILE *p;ot = 0;
	p = fopen("ttt.tmp","wt");
		while (strcmp(buffer,"[events]\n") != 0)
			fgets(buffer,200,fp);
		fgets(buffer,200,fp);
		if (strcmp(buffer,"\n") == 0)
			fgets(buffer,200,fp);
		q.x1 = 0;
		while (strcmp(buffer,"[end]\n") != 0 && !feof(fp))
			{
				fprintf(p,"%s",buffer);
				q.x1++;
				name[0]= fgetc(fp);
				ot = 1;
				while (ot != 0)
					{
					name[0]= fgetc(fp);
					if (name[0] == '\"')
						while (fgetc(fp) != '\"');
					else if (name[0] == '\'')
						while (fgetc(fp) != '\'');
					else if (name[0] =='{')	ot++;
					else if (name[0] =='}')	ot--;
					}//gone to the end of funcion
					fgets(name,100,fp);
					fgets(buffer,100,fp);
					if (strcmp(buffer,"\n") == 0)
						fgets(buffer,200,fp);
					buffer[34] = NULL;
			}//finished listing all function names
	fclose(p);
	listbox("ttt.tmp",name,q.x1);
	remove("ttt.tmp");
	if (strcmp(name," ") == 0)
	{
	fclose(fp);
	free(object);
	free(buffer);
	free(name);
	return;
	}
	remove("ttt.tmp");

	//creating the function name//
	sscanf(name,"%s",buffer);
	strcat(buffer," ");
	strcat(buffer,object);
	ot = 0;
	while (name[ot++] != ' ');
	type = name+ot;
	strcat(buffer,"_");
	strcat(buffer,type);
	strcpy(object,buffer);
	rewind (fp);
	//Checking if the code has already been modified
	p = fopen("code.tmp","rt");
	FILE *tmp = fopen("ttt.tmp","wt");
	int found = 0;
	strcpy(buffer,"");
	if (p != NULL && !feof(p))
	do
	{  strcpy(buffer,"");
		fgets(buffer,100,p);
		if (strlen(buffer) > 0)
			buffer[strlen(buffer)-1] = NULL;
		if (strcmp(buffer,object) == 0)
			found =1;
		if (strcmp(buffer,"") != 0 && strcmp(buffer,"\n") != 0 && found == 0)
			fprintf(tmp,"%s\n",buffer);
	}while (found!= 1 && !feof(p));
	//parsed p till object is found

	if (!found)
	{
	while (strcmp(buffer,"[events]\n") != 0)
		fgets(buffer,100,fp);
		do{
			fgets(buffer,100,fp);
			buffer[strlen(buffer)-1] = NULL;
			if (strcmp(buffer,name) == 0)
				break;
		}while (!feof(fp));
	}//end of not finding the current value

	FILE *t = fopen("codehere.tmp","wt");
	fprintf(t,"%s\n",object);
	ot = 0;
	do{
		name[0] = 0;
		if (found) name[0]= fgetc(p);
		else name[0]= fgetc(fp);
		fputc(name[0],t);
		if (found == 0)
			{
			if (name[0] == '\"')
				{
				while ((name[0] = fgetc(fp)) != '\"')
					fputc(name[0],t);
				fputc(name[0],t);
				}
			else if (name[0] == '\'')
				{
				while ((name[0] = fgetc(fp)) != '\'')
					fputc(name[0],t);
				fputc(name[0],t);
				}

			else if (name[0] =='{')	ot++;
			else if (name[0] =='}')	ot--;
			}//end of found = 0 else
		else
			{
			if (name[0] == '\"')
				{
				while ((name[0] = fgetc(p)) != '\"')
					fputc(name[0],t);
				fputc(name[0],t);
				}
			else if (name[0] == '\'')
				{
				while ((name[0] = fgetc(p)) != '\'')
					fputc(name[0],t);
				fputc(name[0],t);
				}

			else if (name[0] =='{')	ot++;
			else if (name[0] =='}')	ot--;
			}//end of found = 1 else
	}while (ot != 0);
	fprintf(t,"\n");
	fclose(t);
	strcmp(buffer,"");
	if (found)
	{
		fgets(buffer,100,p);
		do{
			if (strcmp(buffer,"\n") != 0)
				fprintf(tmp,"%s",buffer);
			fgets(buffer,100,p);
		}while(!feof(p));
		fclose(tmp);
		remove("code.tmp");
		rename("ttt.tmp","code.tmp");
	}
	if (tmp != NULL)
		fclose(tmp);
	fclose(p);
	fclose(fp);
	free(buffer);free(name);
	free(object);
	StatusLine("Finished Successfully",__LINE__,__FILE__);
}
