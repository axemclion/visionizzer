# include <stdio.h>

int main()
{
	FILE * fp, *temp;
	fp = fopen("e:\\table.txt","rt");
	temp = fopen("e:\\sample.txt","wt");
	int c = 0;
	while (!feof(fp))
	{
		c = fgetc(fp);
		if (c == 32)
			fputc('\t',temp);
		else
			fputc(c,temp);
	}//end of main file
}