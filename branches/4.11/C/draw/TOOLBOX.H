int toolbox(int type = 0)
{
loadcur("cursor","proper",0,0);
int objectreturn = -2;
char mode = 1;
StatusLine("Select the action to be taken",__LINE__,__FILE__);
if (type == 1)
	StatusLine("Select the object to be drawn",__LINE__,__FILE__);
setlinestyle(0,0,1);
mouse_status mouse=status();
int toolx=mouse.x;
int tooly=mouse.y-160;
if (toolx+120 > getmaxx()) toolx=getmaxx()-120;
if (tooly < 0) tooly=10;

char *buffer=(char *)malloc(imagesize(0,0,122,162));
if (!buffer) error("Toolbox\nUnable to allocate memory for screen save",__FILE__,__LINE__);

hide_mouse();
getimage(toolx,tooly,toolx+120,tooly+160,buffer);
if (type == 1) loadbmp("obj1.vsn",toolx,tooly);
else loadbmp("menu1.vsn",toolx,tooly);

show_mouse();
int result=0;
click();
/**********processing**********/
mode = 1;
while (result==0)
{
	mouse=status();
	if (!inarea(mouse.x,mouse.y,toolx,tooly,toolx+120,tooly+160) && mouse.button != 0)
		result = -1;
	else if (mouse.button == LEFT_CLICK)
		{
		int x = (mouse.x-toolx)/40;int y =(mouse.y-tooly)/40;
			//depressing the buttons
				char *sc = (char *)malloc(imagesize(0,0,38,38));
				hide_mouse();
				getimage(toolx+x*40+2,tooly+y*40+2,toolx+x*40+38,tooly+y*40+38,sc);
				putimage(toolx+x*40+3,tooly+y*40+3,sc,COPY_PUT);

				setcolor(8);
				rectangle(toolx+x*40,tooly+y*40+1,toolx+x*40+39,tooly+y*40+40);
				setcolor(15);
				line(toolx+x*40,tooly+y*40+40,toolx+x*40+39,tooly+y*40+40);
				line(toolx+x*40+39,tooly+y*40+1,toolx+x*40+39,tooly+y*40+40);
				show_mouse();
				click();
				hide_mouse();
				putimage(toolx+x*40+2,tooly+y*40+2,sc,COPY_PUT);
				free(sc);
			//end of animation
		setfillstyle(4,6);
		if (type == 1)
			if (y == 0)
				objectreturn = -1;
			else
				objectreturn = x+(y-1)*3+(mode-1)*9;
		if (mode == 1)
			switch(x+y*3)
			{
				case 0:
					mode = 3;
					if (type == 1) loadbmp("obj3.vsn",toolx,tooly);
					else loadbmp("menu3.vsn",toolx,tooly);
					result = 0;
					break;
				case 1:
					result = 'i' ; break;
				case 2:
					mode = 2;
					if (type == 1) loadbmp("obj2.vsn",toolx,tooly);
					else loadbmp("menu2.vsn",toolx,tooly);
					result = 0;
					break;
				case 3 :
					result = 'l';break;
				case 4:
					result = 'r';break;
				case 5:
					result = 18;break;
				case 6:
					result = 'c' ;break;
				case 7:
					result = 3;break;
				case 8:
					result = 'p';break;
				case 9:
					result =16;break;
				case 10:
					result = 12;break;
				case 11:
					result = 't';break;
			}//end of switch case for mode 1

		else if (mode ==2)
			switch(x+y*3)
			{
				case 0:
					mode = 1;
					if (type == 1) loadbmp("obj1.vsn",toolx,tooly);
					else loadbmp("menu1.vsn",toolx,tooly);
					result = 0;
					break;
				case 1:
					result = '`';break;
				case 2:
					mode = 3;
					if (type == 1) loadbmp("obj3.vsn",toolx,tooly);
					else loadbmp("menu3.vsn",toolx,tooly);
					result = 0;break;
				case 3:
					result = 'f';break;
				case 4:
					result = 9998;break;
				case 5:
					result = 9999; break;
				case 6 :
					result = 27; break;
				case 7:
					result = 15; break;
				case 8:
					result = 1060;break;
				case 9:
					result = 9;break;
				case 10:
					result = '?';break;
				case 11:
					result = 1004;break;
			}//end of switch case
		else if (mode == 3)
			switch(x+y*3)
			{
				case 0:
					mode = 2;
					if (type == 1) loadbmp("obj2.vsn",toolx,tooly);
					else loadbmp("menu2.vsn",toolx,tooly);
					result = 0;
					break;
				case 1:
					result = 111;break;
				case 2:
					mode = 1;
					if (type == 1) loadbmp("obj1.vsn",toolx,tooly);
					else loadbmp("menu1.vsn",toolx,tooly);
					result = 0;break;
				case 3:
					result = 1059;break;
				case 4:
					result = 5000;break;
				case 5:
					result = 12020;break;
				case 6:
					result = 19;break;
				case 7:
					result = 2000;break;
				case 8:
					result = 'e';break;
				case 9:
					result = 21;break;
				case 10:
					result = 22;break;
				case 11:
					result = 23;break;
			}//end of third menu
		show_mouse();
		}//end of left click
}//end of main loop body
hide_mouse();
putimage(toolx,tooly,buffer,COPY_PUT);
free(buffer);
show_mouse();
show_mouse();
loadcur("cursor","word",0,0);
if (type == 1)
	return objectreturn+2000;
else
	return result;
}//end of toolbox

