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

	if (fp == NULL)
		return FILENOTFOUND;
	if (fgetc(fp) != 'B' && fgetc(fp)!= 'M')
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

	int width,height;

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