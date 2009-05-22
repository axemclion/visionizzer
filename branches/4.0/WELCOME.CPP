# include <stdio.h>
# include <string.h>

int main(int argc,char *argv[])
{
	printf("Type SOFT at command line to launch this software");
	if (argc <4 )
		return 1;
	if (!(strcmp(argv[1],"to") == 0
		&& strcmp(argv[2],"this") == 0
		&& strcmp(argv[3],"software") == 0))
		return 1;
	rename("d1.axe","phase1.zip");
	rename("d2.axe","phase2.zip");
	rename("d3.axe","phase3.zip");
	rename("d4.axe","phase4.zip");
	rename("d5.axe","phase5.zip");
	rename("d6.axe","phase6.zip");
	rename("d7.axe","phase0.zip");
	rename("data","starting.exe");
	return 0;
}

