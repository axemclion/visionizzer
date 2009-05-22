#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <process.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <dos.h>
#include <mouse.h>
#include "d:\prog\c\bmploade.cpp"
#include "d:\prog\c\draw\console.h"
#include "d:\prog\c\objects.cls"

# define PORT 0x378
# define BAUD 1

button exitthis,send,plug,recv;
progbar psend;
chkbox scanner,firewall,encrypt;
slider errorper;

void redraw();
void init();
int fc(char *file1,char *file2,char *dest);
void errorclip(const char *msg,int line,char *file){}
int main(void)
{
	char *baud = (char *)calloc(1,20);
	char *key = (char *)calloc(1,20);
	char *src = (char *)calloc(1,20);
	char *file = (char *)calloc(1,20);

	char word[6][64] = {
 {255,255,255,255,255,255,255,255,127,254,255,255,255,255,111,246,111,246,255,255,255,255,127,254,255,255,255,255,255,255,255,255,0,0,0,0,0,0,0,0,128,1,0,0,0,0,144,9,144,9,0,0,0,0,128,1,0,0,0,0,0,0,0,0},
 {255,255,255,255,255,255,127,254,191,253,255,255,239,247,119,238,119,238,239,247,255,255,191,253,127,254,255,255,255,255,255,255,0,0,0,0,0,0,128,1,64,2,0,0,16,8,136,17,136,17,16,8,0,0,64,2,128,1,0,0,0,0,0,0},
 {255,255,255,255,63,252,223,251,255,255,247,239,251,223,123,222,123,222,251,223,247,239,255,255,223,251,63,252,255,255,255,255,0,0,0,0,192,3,32,4,0,0,8,16,4,32,132,33,132,33,4,32,8,16,0,0,32,4,192,3,0,0,0,0},
 {255,255,63,252,207,243,255,255,251,223,251,223,253,191,125,190,125,190,253,191,251,223,251,223,255,255,207,243,63,252,255,255,0,0,192,3,48,12,0,0,4,32,4,32,2,64,130,65,130,65,2,64,4,32,4,32,0,0,48,12,192,3,0,0},
 {63,252,207,243,255,255,255,255,253,191,125,190,254,127,94,122,94,122,254,127,125,190,253,191,255,255,255,255,207,243,63,252,192,3,48,12,0,0,0,0,2,64,130,65,1,128,161,133,161,133,1,128,130,65,2,64,0,0,0,0,48,12,192,3}};

	init();
	redraw();
	show_mouse();
	int quit = 0;
	mouse_status mouse = {0,0,0};

	while(!quit)
	{
		mouse = status();
//		anim(word,5,10,8,8);
		gotoxy(72,1);printf("(%03d,%03d)",mouse.x,mouse.y);

		if (mouse.button != 0)
		{
			hide_mouse();
			if (exitthis.lclick(mouse.x,mouse.y))
				quit = 1;
			if (inarea(mouse.x,mouse.y,scanner.x1,scanner.y1,scanner.x2,scanner.y2))
					scanner.action();
			if (inarea(mouse.x,mouse.y,encrypt.x1,encrypt.y1,encrypt.x2,encrypt.y2))
					encrypt.action();
			if (inarea(mouse.x,mouse.y,firewall.x1,firewall.y1,firewall.x2,firewall.y2))
					firewall.action();
			if (inarea(mouse.x,mouse.y,errorper.x1,errorper.y1,errorper.x2,errorper.y2))
					errorper.action();
			if (inarea(mouse.x,mouse.y,528,376,574,395))
				edit(baud,5,532,385,0,15);
			if (inarea(mouse.x,mouse.y,472,216,592,234))
				edit(key,10,476,225,0,15);
			if (inarea(mouse.x,mouse.y,46,197,205,214))
				edit(file,15,50,202,0,15);
			if (inarea(mouse.x,mouse.y,46,147,205,166))
				edit(src,15,50,156,0,15);
			if (inarea(mouse.x,mouse.y,242,152,398,169))
				edit(file,15,246,158,0,15);
			if (recv.lclick(mouse.x,mouse.y))
				{
					int key = getch();
					switch (key)
					{
						case '1':
							fc("sample1.txt",NULL,file);break;
						case '2':
							fc("sample2.txt",NULL,file);break;
						case '3':
							fc("sample3.txt",NULL,file);break;
						case '4':
							fc("sample4.bmp",NULL,file);break;
						case '5':
							fc("sample5.bmp",NULL,file);break;
						case '6':
							fc("sample6.txt",NULL,file);break;
						case '7':
							fc("sample7.txt",NULL,file);break;
						case '8':
							fc("sample8.txt",NULL,file);break;
						case '9':
							fc("sample9.txt",NULL,file);break;
						default :
							fc("sample.txt",NULL,file);break;
					}//end of switch case
				}//end of reception

			if (send.lclick(mouse.x,mouse.y))
				{
				if (strcmp(src,"1.1.1.2") == 0)
				{
/*				cleardevice();
				closegraph();
				if (strcmp(scanner.file,"check.xyz") == 0)
					spawnl(P_WAIT,"d:\\smartdog\\smartdog.exe",file,file,NULL);
				if (strcmp(firewall.file,"check.xyz") == 0)
					spawnl(P_WAIT,"fire.exe",file,file,NULL);
				init();
				redraw();
*/				FILE *fp;
				fp = fopen(file,"rt");
				struct find_t ffblk;
				_dos_findfirst(file,_A_NORMAL,&ffblk);
				if (fp != NULL)
				{
				int key= 0;
				psend.val = 0;
				psend.min = 0;
				psend.max = 100;
				ffblk.size;
				long c = 0;
				while (!feof(fp))
				{
					key = fgetc(fp);
					outportb(PORT,(key & 128) >>7 );delay(BAUD);
					outportb(PORT,(key & 64 ) >>6 );delay(BAUD);
					outportb(PORT,(key & 32 ) >>5 );delay(BAUD);
					outportb(PORT,(key & 16 ) >>4 );delay(BAUD);
					outportb(PORT,(key & 8  ) >>3 );delay(BAUD);
					outportb(PORT,(key & 4  ) >>2 );delay(BAUD);
					outportb(PORT,(key & 2  ) >>1 );delay(BAUD);
					outportb(PORT,(key & 1  ) >>0 );delay(BAUD);
					c++;
					psend.val = (long)(psend.max*c)/ffblk.size;
					psend.draw();
				}
				fclose(fp);
				psend.val = psend.max;
				psend.draw();
				outport(PORT,0);
				}
				else
					msgbox("The File is not in","the path. Please check","the filename");
				}
				else
					msgbox("The destination address","is invalid. Please re-enter ","the destination");
				}//end of sending data

			if (plug.lclick(mouse.x,mouse.y))
			{
				char *file = (char *)calloc(1,100);
				G_input_box(file,"Plug-Ins","Enter the file name","of your plug in.","",30);
				if (strcmp(file,"") != 0)
				{
					closegraph();
					spawnl(P_WAIT,file,NULL);
					init();
					redraw();
				}
				free(file);
			}//end of plugins
			show_mouse();
		}//end of left clicking

	}//end of actual procedure
	free(baud);
	free(file);
	free(src);
	free(key);
	closegraph();
	return 0;
}


void redraw()
{
	hide_mouse();
	exitthis = button(46,385,206,415,"Exit");
	send =button(75,242,175,267,"Send");
	psend = progbar(50,310,200,330,100,0,1);
	plug = button(238,385,399,415,"Plug-ins ... ");
	scanner=chkbox(435,110,450,125,1,1,"nocheck.xyz");
	firewall=chkbox(435,150,450,165,1,1,"nocheck.xyz");
	encrypt=chkbox(435,190,450,215,1,1,"nocheck.xyz");
	errorper=slider(435,310,580,330,100,0,50);
	recv=button(247,242,359,267,"Recieve");

	loadbmp("trans");

	//drawing part
	psend.draw();
	recv.draw();
	send.draw();
	exitthis.draw();
	encrypt.draw();
	firewall.draw();
	scanner.draw();
	plug.draw();
	errorper.draw();
	//processing part
	show_mouse();
}//end of redrawing

void init()
{
int gdriver = DETECT, gmode, errorcode;
	initgraph(&gdriver, &gmode, "");
	errorcode = graphresult();
	if (errorcode != grOk)  /* an error occurred */
	{
		printf("Graphics error: %s\n", grapherrormsg(errorcode));
		printf("Press any key to halt:");
		getch();
		exit(1);             /* return with error code */
	}
	mouse_present();
}//end of initialisation

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