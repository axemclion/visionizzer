# include <graphics.h>
# include <dos.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dir.h>
# include <conio.h>
# include <mouse.h>

void ccoder(char *);
void copy_files();

int main(int argc,char *argv[])
{
ccoder(argv[1]);
copy_files();
return 0;
}

void ccoder(char *path)
{
	char *path1 =(char *)calloc(1,15);
	if (!path1)
		{
		printf("ERROR");
		getch();
		}
	strcat(path,"\\");
	strcpy(path1,path);

	FILE *fp,*prog;

	int ccol=0,ct,cpat,cstyle,cls;
	int x,y,x1,y1,sr,er,c,t,fpattern,fstyle,ls;
	x=y=x1=y1=sr=er=c=ls=0;

	strcat(path1,"prog.cpp");
	printf("%s",path);
if ((prog=fopen(path1,"wt")) != NULL)
{

	strcpy(path1,path);
	/**********writing to file ***********/
	fprintf(prog,"#include <conio.h>\n");
	fprintf(prog,"#include <stdio.h>\n");
	fprintf(prog,"#include <graphics.h>\n");
	fprintf(prog,"#include <stdlib.h>\n");
	fprintf(prog,"#include <string.h>\n");
	fprintf(prog,"#include <dos.h>\n");
	fprintf(prog,"#include \"%smouse.h\"\n",path1);

	fp = fopen ("\\code.$$$","rt");
if (fp != NULL)
{
	fprintf(prog,"#include \"%svobj.h\"\n",path1);
	fprintf(prog,"#include \"%sredraw.h\"\n",path1);
	fprintf(prog,"#include \"%scode.h\"\n",path1);
	fprintf(prog,"\n#define PNO 10\n");
	fprintf(prog,"\nchar *_nme[PNO],*_val[PNO];\n");
}
fclose(fp);

	fprintf(prog,"\n\nvoid redraw()\n\t{\n");

		if ((fp=fopen("\\circ.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	x=y=x1=y1=sr=er=c=ls=0;
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&sr,&er,&x1,&y1,&c,&t,&fpattern,&fstyle);
	if (ccol != c)
		{
				fprintf(prog,"setcolor(%2d);\n",c);
				ccol=c;
		}
	if (ct != t)
		{
				fprintf(prog,"setlinestyle(%d,0,%d);\n",ls,t);
				ct=t;
		}
	fprintf(prog,"ellipse(%d,%d,%d,%d,%d,%d);\n",x,y,sr,er,x1,y1);
	}
	fclose(fp);
	fprintf(prog,"//////////////////\n\n");
}///////////////////end ofcircle


	if ((fp=fopen("\\rect.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	x=y=x1=y1=sr=er=c=ls=0;
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&x1,&y1,&c,&t,&ls);
	if (ccol != c)
		{
				fprintf(prog,"setcolor(%2d);\n",c);
				ccol=c;
		}
		if (ct != t || cls != ls)
		{
				fprintf(prog,"setlinestyle(%d,0,%d);\n",ls,t);
				ct=t;
				cls=ls;
		}
	fprintf(prog,"rectangle(%d,%d,%d,%d);\n",x,y,x1,y1);
	}
	fclose(fp);
	fprintf(prog,"//////////////////\n\n");
}////////////end of recetangl//////////////////////////


	if ((fp=fopen("\\line.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	x=y=x1=y1=sr=er=c=ls=0;
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&x1,&y1,&c,&t,&ls);
	if (ccol != c)
		{
				fprintf(prog,"setcolor(%2d);\n",c);
				ccol=c;
		}
		if (ct != t || cls != ls)
		{
				fprintf(prog,"setlinestyle(%d,0,%d);\n",t);
				ct=t;
				cls=ls;
		}
	fprintf(prog,"line(%d,%d,%d,%d);\n",x,y,x1,y1);
	}
	fclose(fp);
	fprintf(prog,"//////////////////\n\n");


}//end of line/////////////////////
	if ((fp=fopen("\\pie.$$$","r+t"))!=NULL)
{
	while (!feof(fp))
	{
	x=y=x1=y1=sr=er=c=ls=0;
	fscanf(fp,"%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&sr,&er,&x1,&y1,&c,&t,&fpattern,&fstyle);
	if (cpat != fpattern || cstyle != fstyle)
		{
		fprintf(prog,"setfillstyle(%d,%d);\n",fpattern,fstyle);
		cpat= fpattern;
		cstyle = fstyle;
		}
	if (ccol != c)
		{
				fprintf(prog,"setcolor(%2d);\n",c);
				ccol=c;
		}
	if (ct != t)
		{
				fprintf(prog,"setlinestyle(%d,0,%d);\n",t);
				ct=t;
		}
	fprintf(prog,"sector(%d,%d,%d,%d,%d,%d);\n",x,y,sr,er,x1,y1);
	}
	fclose(fp);
	fprintf(prog,"//////////////////\n\n");
}///////////////////////////end of sector/////

	if ((fp=fopen("\\text.$$$","r+t"))!=NULL)
{
	char *res;
	res = (char *)calloc(1,100);
	while (!feof(fp))
	{
	x=y=x1=y1=sr=er=c=ls=0;
	strcpy(res,NULL);
	fscanf(fp,"%02d,%03d,%03d,%02d,%02d,%02d,%s\n",&c,&x,&y,&x1,&y1,&sr,res);
	for (int i=0;i < strlen(res)-1;i++)
		if (*(res+i) == 253)
			*(res+i) = 32;

	if (ccol != c)
		{
				fprintf(prog,"setcolor(%2d);\n",c);
				ccol=c;
		}
	fprintf(prog,"settextstyle(%d,%d,%d);\n",x1,y1,sr);
	fprintf(prog,"outtextxy(%d,%d,\"%s\");\n",x,y,res);
	}//end of while
	fclose(fp);
	free(res);
	fprintf(prog,"//////////////////\n\n");
}////////////////////end of text

	if ((fp=fopen("\\fill.$$$","rt"))!=NULL)
{
	while (!feof(fp))
	{
	char c1[8]={0,0,0,0,0,0,0,0};
	fscanf(fp,"%03d,%03d,%02d,%02d,%02d, p %03d,%03d,%03d,%03d,%03d,%03d,%03d,%03d\n",&x,&y,&c,&sr,&er,&c1[0],&c1[1],&c1[2],&c1[3],&c1[4],&c1[5],&c1[6],&c1[7]);
	if (sr == 12)
			{
			fprintf(prog,"{\n\tchar pat[8] ={%d,%d,%d,%d,%d,%d,%d,%d};\n",c1[0],c1[1],c1[2],c1[3],c1[4],c1[5],c1[6],c1[7]);
			fprintf(prog,"\tsetfillpattern(pat,%d);\n}\n",er);
			}
	else
			fprintf(prog,"setfillstyle(%d,%d);\n",sr,er);
		fprintf(prog,"floodfill(%d,%d,%d);\n",x,y,c);
	}//end of while
	fclose(fp);
}//end of floodfill
	fprintf(prog,"\n\t}//end of redrawing of the 2-D objects\n\n");
	fprintf(prog,"int main()\n{\n");
	fprintf(prog,"\tint gdriver = VGA, gmode=VGAMED, errorcode;\n");
	fprintf(prog,"\tint x, y, ht;\n");
	fprintf(prog,"\tinitgraph(&gdriver, &gmode,\"\");\n");
	fprintf(prog,"\terrorcode = graphresult();");
	fprintf(prog,"\tif (errorcode != grOk)  // an error occurred \n");
	fprintf(prog,"\t\t{\n");
	fprintf(prog,"\t\tprintf(\"Graphics error:\");\n");
	fprintf(prog,"\t\tprintf(\"Press any key to halt:\");\n");
	fprintf(prog,"\t\tgetch();\n");
	fprintf(prog,"\t\texit(1);\n\t\t}\n");
	fprintf(prog,"//////////////////\n\n");
	fp = fopen ("\\code.$$$","rt");
if (fp != NULL)
{
	fprintf(prog,"\ndraw_all();");
	fprintf(prog,"\nmouse_present();\nshow_mouse();");
}
fclose(fp);

	fprintf(prog,"\nredraw();");
	fprintf(prog,"//////////////////\n");
	fprintf(prog,"// End of Drawing part\n");
fp = fopen ("\\code.$$$","rt");
if (fp != NULL)
{
	fprintf(prog,"\tfor (int i=0;i <PNO ;i++)\n");
	fprintf(prog,"\t\t{ \n\t\t_nme[i] = (char *)calloc(1,50);\n");
	fprintf(prog,"\t\t_val[i] = (char *)calloc(1,50);\n\t\t}\n");
	fprintf(prog,"\tchar *focus = (char *)calloc(1,30);\n");
	fprintf(prog,"\tmouse_status mouse={0,0,0},mouse1;\n");
	fprintf(prog,"\tint key=0;\n");

	fprintf(prog,"\n\nwhile(1)\n\t{\n");
	fprintf(prog,"\tmouse1 = mouse;\n\tif (kbhit())\n\tkey = getch();\n");
	fprintf(prog,"\tmouse = down();\n");
	fprintf(prog,"\tif (mouse1.x != mouse.x && mouse1.y != mouse.y)\n");
	fprintf(prog,"\t\t{\nFILE *fp;\n");
	fprintf(prog,"\nif ((fp = fopen(\"cmd.$$$\",\"rt\")) != NULL)\n{\n");
	fprintf(prog,"int x1,y1,x2,y2;\nx1=x2=y1=y2=0;\n");
	fprintf(prog,"char *buffer = (char *)calloc(1,50);\n");
	fprintf(prog,"char *name = (char *)calloc(1,50);\n");
	fprintf(prog,"int _i=0;\nwhile (!feof(fp))\n");
	strcpy(path1,"%s");
	fprintf(prog,"\n{\nint x1,y1,x2,y2;\nfscanf(fp,\"\%s\",name);\n",path1);
	fprintf(prog,"fscanf(fp,\"\%s\",buffer);\n",path1);
	fprintf(prog,"while (strcmp(buffer,\"**********\") != 0 && !feof(fp))\n{\n");
	fprintf(prog,"builtable(buffer,_nme[_i],_val[_i]);\n");
	fprintf(prog,"fscanf(fp,\"%s\",buffer);\n",path1);
	strcpy(path1,path);
	fprintf(prog,"if (strcmp(_nme[_i],\"x1\") == 0) x1=atoi(_val[_i]);\n");
	fprintf(prog,"if (strcmp(_nme[_i],\"x2\") == 0) x2=atoi(_val[_i]);\n");
	fprintf(prog,"if (strcmp(_nme[_i],\"y1\") == 0) y1=atoi(_val[_i]);\n");
	fprintf(prog,"if (strcmp(_nme[_i],\"y2\") == 0) y2=atoi(_val[_i]);\n");
	fprintf(prog,"		_i++;\n}//end of while\n_i=0;\n");
	fprintf(prog,"if (mouse.x <= max(x1,x2) && mouse.x >=min(x1,x2) && mouse.y <= max(y1,y2) && mouse.y >=min(y1,y2))\n");
	fprintf(prog,"{\nstrcpy(focus,name);\nbreak;\n}");
	fprintf(prog,"else \n\tstrcpy(focus,NULL);\n}//end of file\n");
	fprintf(prog,"free(name);\nfree(buffer);\nfclose(fp);\n");
	fprintf(prog,"}//end of file opening\n}//end of mouse has been moved\n");

while (!feof(fp))
	{
		char *buffer,*buf;
		buf = (char *)calloc(1,100);
		buffer = (char *) calloc(1,100);

		fgets(buffer,100,fp);
if (strcmp(buffer,"\n") != 0)
	{
		int j=0,k=0;
		while (*(buffer+k) != ' '&& *(buffer+k) != NULL) k++;
		k++;
		while (*(buffer+k+j) != '_' && *(buffer+k+j) !=NULL)
			*(buf+j++) = *(buffer+j+k);
			*(buf+j++) = *(buffer+j+k);
		while (*(buffer+k+j) >='0' && *(buffer+k+j) <='9'&& *(buffer+k+j) != NULL && *(buffer+k+j) != '\n')
			*(buf+j++) = *(buffer+j+k);
		fprintf(prog,"if (strcmp(focus,\"%s\") == 0)\n",buf);
		while (*(buffer+k+j) != NULL && *(buffer+k+j) != '\n')
			*(buf+j++) = *(buffer+j+k);
		fprintf(prog,"\t\t%s;\n",buf);
			k=0;
			do
			{
			j=fgetc(fp);
			if (j== '{')	k++;
			if (j== '}')   k--;
			}while (k != 0);
			j=fgetc(fp);
}//end of not /n

	free(buf);
	free(buffer);
		}//end of file
	fclose(fp);
	fprintf(prog,"}//\\\\\\\\\\End of calling events\n");
	}//end of if*/
	fprintf(prog,"getch();\nclosegraph();\nreturn 0;\n\n}");
	fclose(prog);
}
free(path);
free(path1);
}//end of function

void copy_files()
{
	char *buffer= (char*)calloc(1,100);
	FILE *fp,*p;
	fp = fopen("\\code.$$$","rt");
	p = fopen("files\\code.h","wt");
	if (fp != NULL)
	{
			do
			{
			strcpy(buffer,NULL);
			fgets(buffer,100,fp);
			if (strcmp(buffer,NULL) != 0)
				fprintf(p,"%s",buffer);
			}while (!feof(fp));
		fclose(fp);
	}
	if (p!= NULL) 	fclose(p);

	fp = fopen("\\cmd.$$$","rt");
	p = fopen("files\\cmd.$$$","wt");
	if (fp != NULL)
	{
		while (!feof(fp))
			{
			fgets(buffer,100,fp);
			fprintf(p,"%s",buffer);
			}
		fclose(fp);
	}
	if (p!= NULL) 	fclose(p);
	free(buffer);
}

