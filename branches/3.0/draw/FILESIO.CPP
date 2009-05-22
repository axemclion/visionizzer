int openfile(char *arg)
{
	FILE *fp,*opn;
	char buffer[100];

	opn = fopen(arg,"rt");
	if (!opn) return -1;
	fp = NULL;
	while (!feof(opn))
	{
		fgets(buffer,100,opn);
		if (strcmp(buffer,"filename :\n") == 0)
			{
				if (fp != NULL)
					fclose(fp);
				fscanf(opn,"%s",buffer);
				char buffer1[100];
				strcpy(buffer1,"\\");
				strcat(buffer1,buffer);
				fp = fopen(buffer1,"wt");
			}//end of opening a new file
		else if (fp != NULL)
			fputs(buffer,fp);

	}//end of opening file
	fclose(opn);
	return 0;
}//end of opening file