# include <stdio.h>

int main(int argc,char *argv[])
{
	FILE *fp;
	fp = fopen("output.txt","wt");
	if (fp == NULL)
		return -1;
	fprintf(fp,"List of Args Passed :\n");
	for (int i = 0;i <argc;i++)
		fprintf(fp,"%3d - %s\n",i,argv[i]);
	fclose(fp);
	return 0;
}