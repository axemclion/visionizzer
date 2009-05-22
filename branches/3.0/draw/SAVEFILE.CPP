# include <string.h>
# include <stdlib.h>
# include <dir.h>
# include <stdio.h>

int main()
{

struct ffblk ffblk;

int done;
done = findfirst("\\*.$$$",&ffblk,0);
FILE *fp,*sav;
sav = fopen("tmp.sav","wt");
if (sav == NULL) return -1;
char buffer[100];
while (!done)
{
	/****************start appending all available $$$ files******/
	strcpy(buffer,"\\");
	strcat(buffer,ffblk.ff_name);
	fp = fopen(buffer,"rt");
	if (!fp) return -1;
	fprintf(sav,"\nfilename :\n%s\n",ffblk.ff_name);
	while (!feof(fp))
	{
		fgets(buffer,100,fp);
		fputs(buffer,sav);
	}//end of writing the file contents
	fclose(fp);
	/****************end of appending**********/
	done = findnext(&ffblk);
}
fclose(sav);
return 0;

}//end of main