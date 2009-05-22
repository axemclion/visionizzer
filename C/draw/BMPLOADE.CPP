# define NOERROR 0
# define ARGSERR 1
# define FILENOTFOUND 2
# define FORMATERR 3
# define COMPRESSIONERR 4
# define COLORERR 5


int loadbmp(char *fname,int sx=1,int sy=1,int ex=-1,int ey=-1)
{
	FILE *fp;
	fp = fopen(fname,"rb");
	int width,height;

	if (fp == NULL)
		return FILENOTFOUND;
	width = char(fgetc(fp));
	height = char(fgetc(fp));

	if (!((width == 'B' || width == 'A') && (height== 'M' || height == 'X')))
		return FORMATERR;

	fseek(fp,0xE,SEEK_SET);
	if (fgetc(fp) != 0x28)
		return FORMATERR;
	fseek(fp,0x1C,SEEK_SET);
	if (fgetc(fp) != 4)
		return COLORERR;
	fseek(fp,0x1E,SEEK_SET);
	if (fgetc(fp) != 0)
		return COMPRESSIONERR;


	/*getting the x and y coordinates*/
	fseek(fp,0x12,SEEK_SET);
	width = (unsigned char)fgetc(fp) + (unsigned char)fgetc(fp)*256;
	fseek(fp,0x16,SEEK_SET);
	height = (unsigned char)fgetc(fp) + (unsigned char)fgetc(fp)*256;

	int realwidth = width;
	if (width % 8 != 0)
		width =(ceil(((width *4)/32))+1)*32/4;

	if (ex > width || ex == -1)
		ex = width;
	if (ey > height || ey == -1)
		ey = height;

int val;
fseek(fp,118,SEEK_SET);
	for (int y = height;y > 0;y--)
		{
			int color;
			for (int x = 0;x < width;x++)
			{

				val = fgetc(fp);
				color = (val & 0xf0) >>4;
				if (color == 1) color =4 ;else if (color == 9 ) color = 12;else if (color == 12) color = 9;else if (color == 4) color =1 ;else if (color == 14) color =11 ;else if (color == 11) color =14 ;else if (color == 3) color = 6 ;else if (color == 6) color =3 ;
				if (x < ex && y < ey)
					if (x <= realwidth)
						putpixel(x+sx,y+sy,color);
				x++;
				color = (val & 0x0F);
				if (color == 1) color =4 ;else if (color == 9 ) color = 12;else if (color == 12) color = 9;else if (color == 4) color =1 ;else if (color == 14) color =11 ;else if (color == 11) color =14 ;else if (color == 3) color = 6 ;else if (color == 6) color =3 ;
				if (x < ex && y < ey)
					if (x <= realwidth)
						putpixel(x+sx,y+sy,color);
			}//emnd of drawing the image
		}
	fclose(fp);
	return NOERROR;
}

int loadcur(char *file,char *cur,int x,int y)
{
	FILE *fp;
	char word[64];
	char *buffer = (char*)malloc(100);
	fp = fopen(file,"rt");
	if (fp == NULL)
		return FILENOTFOUND;
	fscanf(fp,"%s",buffer);
	fgetc(fp);
	word[0] = fgetc(fp);
	do{
		if (strcmp(buffer,cur) == 0)
			break;
		word[0] = 0;
		while (word[0] !=';')
			word[0] = fgetc(fp);
			fscanf(fp,"%s",buffer);
			fgetc(fp);fgetc(fp);
	}while (!feof(fp));
	if (strcmp(buffer,cur) !=0)
		return FORMATERR;


	for (int i= 0;i < 63;i++)
		fscanf(fp,"%3d,",&word[i]);
	fscanf(fp,"%3d",&word[63]);
	fclose(fp);
	free(buffer);
	mouse_change(word,x,y);
	hide_mouse();
	show_mouse();
	return NOERROR;
}//end of loading cursor