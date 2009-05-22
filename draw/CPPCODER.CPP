# include <process.h>
# include <graphics.h>
# include <dos.h>
# include <stdio.h>
# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include <dir.h>
# include <conio.h>
# include <mouse.h>

int fc(char *file1,char *file2,char *dest);
void ccoder(char *);

int main(int argc,char *argv[])
{
if (argc < 1)
	return 1;
ccoder(argv[1]);
char path[100],path1[100];
strcpy(path,argv[1]);
strcpy(path1,path);
strcat(path1,"prog.java");
fc("code.cpp",NULL,path1);
strcpy(path1,path);

strcat(path1,"code.h");
remove(path1);
remove("head");
fc("head","code.tmp",path1);
remove("head");
FILE *fp = fopen("end.bat","wt");
fprintf(fp,"cls");
fclose(fp);
strcpy(path1,path);
return 0;
}

void ccoder(char *path)
{
	char object[100];
	remove("code.cpp");
	strcat(path,"\\");
	char *path1 =(char *)calloc(1,100);
#ifdef AXE
	printf("%s",path);
	getch();getch();
	click();
# endif

	char *name;
	if (!path1)
		return;
	strcpy(path1,path);

	FILE *fp,*prog,*draw;

	strcat(path1,"code.cpp");
	prog=fopen("code.cpp","wt");
	if (prog == NULL)
		return ;

	strcpy(path1,path);
	/**********writing to file ***********/
	fprintf(prog,"import java.awt.*;\n");
	fprintf(prog,"import javax.swing.*;\n");
	fprintf(prog,"import java.applet.*;\n");

	fp = fopen ("object.tmp","rt");
if (fp != NULL)
{
	fprintf(prog,"\n\nvoid redraw();\n\n");

	draw = fopen("draw.ini","rt");
	int type=0,c=0;
	fgets(object,100,fp);
	if (object[strlen(object)-1] == '\n')
		object[strlen(object)-1] = NULL;
	fgets(path1,100,fp);
	do
	{
		rewind(draw);
		while (path1[c] != '=' && path1[c]!= NULL)
			c++;
		type = atoi(path1+c+1);

		c = 0;
		fscanf(draw,"%d %s",&c,path1);
		do{
		char ss[100];
		fscanf(draw,"%s\n",ss);
		if (type == c)
			break;
		fscanf(draw,"%d %s",&c,path1);
		}while(!feof(draw));

		fprintf(prog,"%s %s(",path1,object);

		{
		FILE *head;
		head = fopen("head","at");
		fprintf(head,"extern %s %s;\n",path1,object);
		fclose(head);
		}

		//fist arguement
		fgets(path1,100,fp);
		c=0;
		while (path1[c] != '=' && path1[c]!= NULL)
			c++;
		name = path1+c+1;
		if (name[strlen(name)-1] == '\n')
			name[strlen(name)-1] = NULL;
		if (isdigit(name[0]))	fprintf(prog,"%d",atoi(name));
		else 	fprintf(prog,"\"%s\"",name);

		fgets(path1,100,fp);c=0;

			do{
			while (path1[c] != '=' && path1[c]!= NULL)
				c++;
			name = path1+c+1;
		if (name[strlen(name)-1] == '\n')
			name[strlen(name)-1] = NULL;
			if (isdigit(name[0]))
				fprintf(prog,",%d",atoi(name));
			else
				fprintf(prog,",\"%s\"",name);
			fgets(path1,100,fp);c=0;
			}while (strcmp(path1,"**********\n") != 0 && !(feof(fp)));
		fprintf(prog,");\n");
		fgets(object,100,fp);fgets(path1,100,fp);
		object[strlen(object)-1] = NULL;
	}while (!feof(fp));
fclose(draw);
fclose(fp);
}
	fprintf(prog,"\n\nint main()\n{\n");
	fprintf(prog,"\tint gdriver = VGA, gmode=VGAMED, errorcode;\n");fprintf(prog,"\tinitgraph(&gdriver, &gmode,\"\");\n");
	fprintf(prog,"\terrorcode = graphresult();");fprintf(prog,"\n\tif (errorcode != grOk)  // an error occurred \n");fprintf(prog,"\t\t{\n");
	fprintf(prog,"\t\tprintf(\"Graphics error:\");\n");fprintf(prog,"\t\tprintf(\"Press any key to halt:\");\n");fprintf(prog,"\t\tgetch();\n");fprintf(prog,"\t\texit(1);\n\t\t}\n");

	fprintf(prog,"\nredraw();");
	fprintf(prog,"\nmouse_present();\nshow_mouse();");
	fprintf(prog,"\nwhile(1)\n{\nfocus = -1;key = 0;\n");
	fprintf(prog,"\tmouse1 = mouse;\n\tmouse = status();");
	fprintf(prog,"\tif (kbhit()) \n\t\tkey = getch();\n");
	//start of events
	fp = fopen("object.tmp","rt");
	draw = fopen("code.tmp","rt");
if (fp != NULL && draw != NULL)
{
	fgets(object,100,fp);
	do{
	object[strlen(object)-1] = NULL;
	fprintf(prog,"\tif (inarea(mouse.x,mouse.y,%s.x1,%s.y1,%s.x2,%s.y2))\n\t{\n\t\tfocus = %s.action();\n",
	object,object,object,object,object);
	//events are writen here
	rewind(draw);
	fgets(path1,100,draw);
	do{
		int op = 0;
		while (path1[op++] != ' ');
		name=path1+op;
		if (path1[strlen(path1) -1] == '\n')
			path1[strlen(path1) -1] = NULL;
		if (strncmp(object,name,strlen(object)) == 0)
			fprintf(prog,"\t\t%s;\n",name);
			op = 1;fgetc(draw);
			while (op != 0)
			{
				if (path1[0] == '\"')
					while (fgetc(draw) == '\"');
				else if (path1[0] == '\'')
					while (fgetc(draw) == '\'');
				else if (path1[0] =='{')	op++;
				else if (path1[0] =='}')	op--;
				path1[0] = fgetc(draw);
			}//read till end of function
	fgets(path1,100,draw);
	}while (!feof(draw));
	//events are completed here
	fprintf(prog,"\t}//end of %s\n\n",object);
	while (strcmp(object,"**********\n") != 0)
		fgets(object,100,fp);
	fgets(object,100,fp);
	fgets(path1,100,fp);
	}while(!feof(fp));
fclose(fp);
}
	fclose(draw);
	//end of events

	fprintf(prog,"\n}//end of main program execution loop");
	fprintf(prog,"\n}//end of function main");

	fprintf(prog,"\n\nvoid redraw()\n\t{\n");
	fprintf(prog,"char pattern[8];\n");
	fp = fopen("draw.tmp","rt");


	while (!feof(fp) && fp != NULL)
	{
	fscanf(fp,"%s ",&object);
	int sx,sy,ex,ey,thk,ls,col,fs,fc;
	unsigned int fonts,fontn,fontdir;
	char cp[8];
	sx=sy=ex=ey=thk=ls=col=fs=fc=fonts=fontn=fontdir=0;
		if (strcmp(object,"object") == 0)
			{
			fgets(object,100,fp);
			*(object + strlen(object) -1 ) = NULL;
			fprintf(prog,"%s.draw();\n",object);
			}//end of drawing objects
		else if (strcmp(object,"print") == 0)
		{
			fscanf(fp,"%03d,%03d,",
							&sx,&sy);
			fgets(object,100,fp);
			*(object + strlen(object) -1 ) = NULL;
			fprintf(prog,"gotoxy(%d,%d);\n",sx,sy);
			fprintf(prog,"printf(\"%s\");\n",object);
		}//end of text

		else if (strcmp(object,"line") == 0 || strcmp(object,"rectangle") == 0)
			{
			fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%07d\n",
						&sx,&sy,&ex,&ey,&col,&thk,&ls,&fontn);
			fprintf(prog,"setcolor(%d);setlinestyle(%d,%d,%d);\n",col,ls,fontn,thk);
			if (strcmp(object,"rectangle") == 0)
				fprintf(prog,"rectangle(%d,%d,%d,%d);\n",sx,sy,ex,ey);
			else
				fprintf(prog,"line(%d,%d,%d,%d);\n",sx,sy,ex,ey);
			}//end of drawing a line

		else if (strcmp(object,"bar") == 0)
			{
			fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d\n",
					&sx,&sy,&ex,&ey,&fc,&fs);
			fprintf(prog,"setfillstyle(%d,%d);\n",fs,fc);
			fprintf(prog,"bar(%d,%d,%d,%d);\n",sx,sy,ex,ey);
			}//end of drawing a rectangle

		else if (strcmp(object,"barp") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
				&sx,&sy,&ex,&ey,&fc,
				&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				fprintf(prog,"\npattern[0] = %d;",cp[0]);fprintf(prog,"\npattern[1] = %d;",cp[1]);fprintf(prog,"\npattern[2] = %d;",cp[2]);fprintf(prog,"\npattern[3] = %d;",cp[3]);
				fprintf(prog,"\npattern[4] = %d;",cp[4]);fprintf(prog,"\npattern[5] = %d;",cp[5]);fprintf(prog,"\npattern[6] = %d;",cp[6]);fprintf(prog,"\npattern[7] = %d;",cp[7]);
				fprintf(prog,"\nsetfillpattern(pattern,%d);\n",fc);
				fprintf(prog,"bar(%d,%d,%d,%d);\n",sx,sy,ex,ey);
			}
		else if (strcmp(object,"text") == 0)
		{
			fscanf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,",
							&col,&sx,&sy,
							&fontn,&fontdir,&fonts);
			fgets(object,100,fp);
			*(object + strlen(object) -1 ) = NULL;
			fprintf(prog,"setcolor(%d);\n",col);
			fprintf(prog,"settextstyle(%d,%d,%d);\n",fontn,fontdir,fonts);
			fprintf(prog,"outtextxy(%d,%d,\"%s\");\n",sx,sy,object);
		}//end of text
		else if (strcmp(object,"ellipse") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
						&sx,&sy,&ex,&ey,&fonts,&fontn,&col,&thk);
				fprintf(prog,"setcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(0,0,%d);\n",thk);
				fprintf(prog,"ellipse(%d,%d,%d,%d,%d,%d);\n",sx,sy,ex,ey,fonts,fontn);
			}//end of ellipse
		else if (strcmp(object,"pie") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&ex,&ey,&fonts,&fontn,
							&col,&thk,&fc,&fs);
				fprintf(prog,"setcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(0,0,%d);\n",thk);
				fprintf(prog,"setfillstyle(%d,%d);\n",fs,fc);
				fprintf(prog,"sector(%d,%d,%d,%d,%d,%d);\n",sx,sy,ex,ey,fonts,fontn);
			}//end of drawing simple piechart

		else if (strcmp(object,"piepattern") == 0)
			{
				int xradius,yradius;
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
					&sx,&sy,
					&ex,&ey,
					&xradius,&yradius,
					&col,&thk,&fc,
					&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				fprintf(prog,"setcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(0,0,%d);\n",thk);
				fprintf(prog,"\npattern[0] = %d;",cp[0]);fprintf(prog,"\npattern[1] = %d;",cp[1]);fprintf(prog,"\npattern[2] = %d;",cp[2]);fprintf(prog,"\npattern[3] = %d;",cp[3]);
				fprintf(prog,"\npattern[4] = %d;",cp[4]);fprintf(prog,"\npattern[5] = %d;",cp[5]);fprintf(prog,"\npattern[6] = %d;",cp[6]);fprintf(prog,"\npattern[7] = %d;",cp[7]);
				fprintf(prog,"setfillpattern(pattern,%d);\n",fc);
				fprintf(prog,"sector(%d,%d,%d,%d,%d,%d);\n",sx,sy,ex,ey,fonts,fontn);
			}//end of complex pie chart

		else if (strcmp(object,"fillellipse") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&ex,&ey,
							&col,&thk,&fc,&fs);
				fprintf(prog,"setcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(0,0,%d);\n",thk);
				fprintf(prog,"setfillstyle(%d,%d);\n",fs,fc);
				fprintf(prog,"fillellipse(%d,%d,%d,%d);\n",sx,sy,ex,ey);
			}//end of fillellipse simple

			else if (strcmp(object,"fillellipsep") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&ex,&ey,
							&col,&thk,&fc,
							&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				fprintf(prog,"setcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(0,0,%d);\n",thk);
				fprintf(prog,"\npattern[0] = %d;",cp[0]);fprintf(prog,"\npattern[1] = %d;",cp[1]);fprintf(prog,"\npattern[2] = %d;",cp[2]);fprintf(prog,"\npattern[3] = %d;",cp[3]);
				fprintf(prog,"\npattern[4] = %d;",cp[4]);fprintf(prog,"\npattern[5] = %d;",cp[5]);fprintf(prog,"\npattern[6] = %d;",cp[6]);fprintf(prog,"\npattern[7] = %d;",cp[7]);
				fprintf(prog,"setfillpattern(pattern,%d);\n",fc);
				fprintf(prog,"fillellipse(%d,%d,%d,%d);\n",sx,sy,ex,ey);
			}//end of complex ellipse filler

			else if (strcmp(object,"fillstyle") == 0)
			{
				fscanf(fp,"%03d,%03d,%02d,%02d,%02d\n",
								&sx,&sy,&col,&fc,&fs);
				fprintf(prog,"setfillstyle(%d,%d);\n",fs,fc);
				fprintf(prog,"floodfill(%d,%d,%d);\n",sx,sy,col);
			}//end of floodfilling
			else if (strcmp(object,"fillpattern") == 0)
			{
			fscanf(fp,"%03d,%03d,%02d,%02d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
							&sx,&sy,&col,&fc,
							&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
			fprintf(prog,"\npattern[0] = %d;",cp[0]);fprintf(prog,"\npattern[1] = %d;",cp[1]);fprintf(prog,"\npattern[2] = %d;",cp[2]);fprintf(prog,"\npattern[3] = %d;",cp[3]);
			fprintf(prog,"\npattern[4] = %d;",cp[4]);fprintf(prog,"\npattern[5] = %d;",cp[5]);fprintf(prog,"\npattern[6] = %d;",cp[6]);fprintf(prog,"\npattern[7] = %d;",cp[7]);
			fprintf(prog,"setfillpattern(pattern,%d);\n",fc);
			fprintf(prog,"floodfill(%d,%d,%d);\n",sx,sy,col);
			}//end of fill pattern
			else if (strcmp(object,"polygon") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%07d\n",
								&fontdir,&col,&ls,&thk,&fontn);
				int points[30];
				fprintf(prog,"{\nint poly[] = {");

				for (int i = 0; i < fontdir*2 && i < 30;i+=2)
					{
					fscanf(fp,"%03d,%03d",&points[i],&points[i+1]);
					fprintf(prog,"%3d,%3d,",points[i],points[i+1]);
					}//end of for next loop
				fprintf(prog,"0};\nsetcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(%d,%d,%d);\n",ls,fontn,thk);
				fprintf(prog,"drawpoly(%d,poly);}\n",fontdir);
			}//end of simple polygon

			else if (strcmp(object,"fillpolygon") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%07d\n",
								&fontdir,&col,&ls,&thk,&fc,&fs,&fontn);
				int points[30];
				fprintf(prog,"{\nint poly[] = {");
				for (int i = 0; i < fontdir*2 && i < 30;i+=2)
					{
					fscanf(fp,"%03d,%03d",&points[i],&points[i+1]);
					fprintf(prog,"%3d,%3d,",points[i],points[i+1]);
					}//end of for next loop
				fprintf(prog,"0};\nsetcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(%d,0,%d);\n",ls,fontn,thk);
				fprintf(prog,"setfillstyle(%d,%d);\n",fs,fc);
				fprintf(prog,"fillpoly(%d,poly);}\n",fontdir);
			}//end of simple polygon filling simple

			else if (strcmp(object,"fillpolygonp") == 0)
			{
				fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%07d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",
								&fontdir,&col,&ls,&thk,&fc,&fontn,
								&cp[0],&cp[1],&cp[2],&cp[3],&cp[4],&cp[5],&cp[6],&cp[7]);
				int points[30];
				fprintf(prog,"{\nint poly[] = {");
				for (int i = 0; i < fonts*2 && i < 30;i+=2)
					{
					fscanf(fp,"%03d,%03d",&points[i],&points[i+1]);
					fprintf(prog,"%3d,%3d,",points[i],points[i+1]);
					}//end of for next loop
				fprintf(prog,"0};\nsetcolor(%d);\n",col);
				fprintf(prog,"setlinestyle(%d,%d,%d);\n",ls,fontn,thk);
				fprintf(prog,"\npattern[0] = %d;",cp[0]);fprintf(prog,"\npattern[1] = %d;",cp[1]);fprintf(prog,"\npattern[2] = %d;",cp[2]);fprintf(prog,"\npattern[3] = %d;",cp[3]);
				fprintf(prog,"\npattern[4] = %d;",cp[4]);fprintf(prog,"\npattern[5] = %d;",cp[5]);fprintf(prog,"\npattern[6] = %d;",cp[6]);fprintf(prog,"\npattern[7] = %d;",cp[7]);
				fprintf(prog,"setfillpattern(pattern,%d);\n",fc);
				fprintf(prog,"fillpoly(%d,poly);}\n",fontdir);
			}//end of simple polygon filling simple
			else if (strcmp(object,"bmp") == 0)
			{
				int sx,sy,ex,ey;
				fscanf(fp,"%03d,%03d,%03d,%03d,%s\n",
							&sx,&sy,&ex,&ey,&object);
				fprintf(prog,"loadbmp(\"%s\",%d,%d,%d,%d);\n",object,sx,sy,ex,ey);
			}//end of loading bitmaps
	}//end of parsing all values

	fclose(fp);
	fprintf(prog,"\n\t}//end of redrawing all objects\n\n");

fclose(prog);
free(path);
free(path1);
}//end of function



int fc(char *file1,char *file2,char *dest)
{
	FILE *src,*dst;
	src = fopen(file1,"rt");
	dst = fopen(dest,"at");
	if (dst == NULL)
		return 1;
	char *buffer = (char *)calloc(1,100);
	if (src != NULL)
	{
		fgets(buffer,100,src);
		do{
			fprintf(dst,"%s",buffer);
			fgets(buffer,100,src);
		}while (!feof(src));
		fclose(src);
	}

	src = fopen(file2,"rt");
	if (src != NULL)
	{
		fgets(buffer,100,src);
		do{
			fprintf(dst,"%s",buffer);
			fgets(buffer,100,src);
		}while (!feof(src));
		fclose(src);
	}
free(buffer);
fclose(dst);

return 0;
}

