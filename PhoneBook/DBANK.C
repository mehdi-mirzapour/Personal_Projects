
#include "main.h"

#define IGNORE  0
#define RETRY   1
#define ABORT   2



/*
define the error messages for trapping disk problems
*/
static char *err_msg[] = {
    "write protect",
    "unknown unit",
    "drive not ready",
    "unknown command",
    "data error (CRC)",
    "bad request",
    "seek error",
    "unknown media type",
    "sector not found",
    "printer out of paper",
    "write fault",
    "read fault",
    "general failure",
    "reserved",
    "reserved",
    "invalid disk change"
};

error_win(char *msg)
{
   int retval;

   cputs(msg);

/*
prompt for user to press a key to abort, retry, ignore
*/
   while(1)
   {
       retval= getch();
       if (retval == 'a' || retval == 'A')
       {
           retval = ABORT;
           break;
       }
       if (retval == 'r' || retval == 'R')
       {
           retval = RETRY;
           break;
       }
       if (retval == 'i' || retval == 'I')
       {
           retval = IGNORE;
           break;
       }
   }

   return(retval);
}

/*
pragma warn -par reduces warnings which occur
due to the non use of the parameters errval,
bp and si to the handler.
*/
#pragma warn -par

int handler(int errval,int ax,int bp,int si)
{
   static char msg[80];
   unsigned di;
   int drive;
   int errorno;

   di= _DI;
/*
if this is not a disk error then it was
another device having trouble
*/

   if (ax < 0)
   {
      /* report the error */
      error_win("Device error");
      /* and return to the program directly requesting abort */
      hardretn(ABORT);
   }
/* otherwise it was a disk error */
   drive = ax & 0x00FF;
   errorno = di & 0x00FF;
/* report which error it was */
   sprintf(msg, "Error: %s on drive %c\r\nA)bort, R)etry, I)gnore: ",
           err_msg[errorno], 'A' + drive);
/*
return to the program via dos interrupt 0x23 with abort, retry,
or ignore as input by the user.
*/
   hardresume(error_win(msg));
   return ABORT;
}
#pragma warn +par


main()
{
int savescreen[40][80];
int save1[40][80];
int back[40][80];
int cnt=0;
char x1,y1;
static command[100];
static char path[100];
static char shell='n';
static char switches[50];
char m[100];
int x;







harderr(handler);
first=NIL;
save_screen(0,0,24,79,EXT);
findc(&x1,&y1);
XA=x1;
YA=y1;
getcwd(path,100);

if(path[strlen(path)-1] !='\\') strcat(path,"\\");
    border(BLUE|BRIGHT);
    bef(mainmenu);
     _about();
     set_color_regs(RED,68,68,59);
     set_color_regs(GREEN,40,-105,47);
     set_color_regs(20,154,217,121);

    HELP_HOT_KEY=1;
    EXIT_HOT_KEY=1;
    password(back,y1);
    best:
    if (shell=='y') {
		    write_to_buffer('t');
		    adv_write_to_buffer(-32,80);
		    shell='n'; }
    bef(mainmenu);     /*****    Okey . . . ******/








    for(;;)
    {
      here:
      x=show_horizental(mainmenu,7);

     switch(x)
     {
     case 0:



	       save_screen(2,1,13,21,savescreen);
	       drawbox(2,1,11,19,B_WHITE|BLACK);
	       drawseperateline(6,1,6,19,B_WHITE|BLACK);
	       drawseperateline(9,1,9,19,B_WHITE|BLACK);
	       x=show_file(filemenu,6);
	       if(ifif(savescreen,x,2,1,13,21,'p','h')) goto here;

		switch(x)
		{
		 case 0:
		 show_new(cnt,path,save1);
		 break;

		 case 4:
		 show_close(save1);
		 break;

		 case 5:
		 show_exit();
		 break;
		}

		load_screen(2,1,13,21,savescreen);
		cursor(0);
		break;


     case 1:

		save_screen(2,9,9,32,savescreen);
		drawbox(2,9,7,30,B_WHITE|BLACK);
		x=show_edit(pagemenu,4);
		if(ifif(savescreen,x,2,9,9,32,'l','f')) goto here;

		 switch(x)
		 {
		 case 0:
		 show_add(save1);
		 if(ACCEPT_ID_ENTERY==1) if(!(add_to_link_list())) printf("Not Enough Memory");
		 break;

		 case 1:
		 break;

		 case 2:
		 break;

		 case 3:
		 save_screen(7,12,12,41,save1);
		 drawbox(7,12,10,39,B_WHITE|BLACK);
		 if(SELECT_ACTIVE_PAGE==0)  x=show_sub(submenu1,2);
		 if(SELECT_ACTIVE_PAGE==1)  x=show_sub(submenu2,2);
		 if(x==0) SELECT_ACTIVE_PAGE=0;
		      if(x==1) {
			SELECT_ACTIVE_PAGE=1;
			get_manual_page();
				 }
	       load_screen(7,12,12,41,save1);

	       break;
	       }

	     load_screen(2,9,9,32,savescreen);
	     break;



     case 2:

	     save_screen(2,17,14,47,savescreen);
	     drawbox(2,17,12,45,B_WHITE|BLACK);
	     drawseperateline(10,17,10,45,B_WHITE|BLACK);
	     drawseperateline(6,17,6,45,B_WHITE|BLACK);
	     x=show_select(selectmenu,7);
	     if(ifif(savescreen,x,2,17,14,47,'s','p')) goto here;


	     switch (x)
	       {
		 case 3:

		 break;

		 case 4:

		 break;

		case 5:

		break;
	       }

	      load_screen(2,17,14,47,savescreen);

	       break;


     case 3:


	   save_screen(2,27,7,51,savescreen);
	   drawbox(2,27,5,49,B_WHITE|BLACK);
	   x=show_show(showmenu,2);
	   if(ifif(savescreen,x,2,27,7,51,'r','l')) goto here;
	   load_screen(2,27,7,51,savescreen);
	    switch(x)
	     {
	      case 0:
	      view_page1(save1);
	      break;

	      case 1:
	      break;
	     }
	      break;

     case 4:

	  save_screen(2,35,7,60,savescreen);
	  drawbox(2,35,5,58,B_WHITE|BLACK);
	  x=show_print(printmenu,2);
	  if(ifif(savescreen,x,2,35,7,60,'t','s')) goto here;
	  load_screen(2,35,7,60,savescreen);
	  break;



     case 6:


	  save_screen(2,59,7,79,savescreen);
	  drawbox(2,59,6,77,B_WHITE|BLACK);
	  drawseperateline(4,59,4,77,B_WHITE|BLACK);
	  x=show_help(helpmenu,2);
	  if(ifif(savescreen,x,2,59,7,79,'f','t')) goto here;
	  load_screen(2,59,7,79,savescreen);
	   switch(x)
	   {
	   case 0:
	   tsr_help();
	   break;

	   case 1:
	   about();
	   break;
	   }
	   break;





     case 5:

	     save_screen(2,44,9,64,savescreen);
	     drawbox(2,44,7,61,B_WHITE|BLACK);
	     drawseperateline(5,44,7,61,B_WHITE|BLACK);
	     x=show_tools(toolsmenu,3);
	     if(ifif(savescreen,x,2,44,9,64,'h','r')) goto here;


	      switch (x)
	      {
	      case 0:
	      break;

	      case 1:
	      show_command(savescreen,command);
	      goto best;


	     case 2:
	     shell_to_dos();
	     shell='y';
	     goto best;
	     }
	     jmp0:
	     load_screen(2,44,9,64,savescreen);

    }
}


}
