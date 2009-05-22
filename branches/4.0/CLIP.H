void errorclip(const char *msg,int line,char *file)
{
	REGS regs;
	SREGS sregs;
	 regs.x.ax = 0x1700; //get WINOLDP version
	 int86x(0x2F, &regs, &regs, &sregs);
	if (regs.x.ax == 0x1700)
		msgbox("VisioniZZer is not running on",
				 "enhanced WINDOWS mode. So error",
				 "report cannot be copied to the ",
				 "the clipboard.");
	 regs.x.ax = 0x1701; //open clipboard
	 int86x(0x2F, &regs, &regs, &sregs);

	if (regs.x.ax == 0)
		msgbox("Clipboard is in use by some",
				 "other application. Try closing",
				 "that application and then run",
				 "this");
	char *error =(char *)calloc(1,400);
	sprintf(error,"Error :\r\nLinker Filename : %s (OFFSET : 0032:%04d)",file,line);
	regs.x.ax = 0x1703; //set clipboard data
	regs.x.dx = 1; //text format
	sregs.es=FP_SEG(error);
	regs.x.bx=FP_OFF(error);
	regs.x.si=0;
	regs.x.cx=strlen(error);
	int86x(0x2f,&regs,&regs,&sregs);

	regs.x.ax = 0x1708; // close clipboard
	int86x(0x2f,&regs,&regs,&sregs);
	free(error);
}

