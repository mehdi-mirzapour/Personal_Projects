/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
void show_new(int cnt,char *path,int (*savescreen)[80])
{
     static char temp[100];
     int st[40][80];
     register i;
     int x=0,y=0,z=0;
     char c;
     char temppath[100];

     getcwd(path,100);
     if(path[strlen(path)-1] !='\\') strcat(path,"\\");
     strcpy(temppath,path);
     if(FLAG==-1) FLAG=0;
     save_screen(4,3,12,76,savescreen);
     drawbox(4,3,11,74,B_D_BLUE|RED);
     fastp(5,27,BLUE|B_D_BLUE,"Enter Your File Position ",3,BLUE|B_D_BLUE);

     FLAG=0;

     for(;;)   {
      df:
     if(FLAG==0)
     {
     ok(9,18,0);
     cancel(9,34,0);
     help(9,50,0);
     cnt=_gets(7,9,58,path,-2,0,0,path);
     cursor(0);
     if(cnt==TAB)   FLAG=1;
     if(cnt==S_TAB) FLAG=3;
     if(cnt==ALT_O) {delayok(9,18); FLAG=156;RUNNING=1;}
     if(cnt==ALT_C) {delaycancel(9,34); FLAG=156;RUNNING=2;}
     if(cnt==ALT_h) {delayhelp(9,50); FLAG=156;RUNNING=3;}
     if(cnt==F1)    {delayhelp(9,50); FLAG=156;RUNNING=3;}
     if(cnt==ENTER) FLAG=1;
     }

     if(FLAG==1)
     {
     ok(9,18,1);
     cancel(9,34,0);
     help(9,50,0);
     fastp(9,18,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(9,28,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=2;
     if(CHR==13) {delayok(9,18); RUNNING=1; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(9,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(9,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     delayhelp(9,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     ok(9,18,0);
     delayhelp(9,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 15:
     FLAG=0;
     break;
     }

     }

     if(FLAG==2)
     {
     ok(9,18,0);
     cancel(9,34,1);
     help(9,50,0);
     fastp(9,34,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(9,44,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=3;
     if(CHR==13) {delaycancel(9,34); RUNNING=2; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(9,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(9,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     delayhelp(9,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 59:
     FLAG=3;
     delayhelp(9,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 15:
     FLAG=1;
     break;
     }

     }



     if(FLAG==3)
     {
     ok(9,18,0);
     cancel(9,34,0);
     help(9,50,1);
     fastp(9,50,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(9,60,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=0;
     if(CHR==13) {delayhelp(9,50); RUNNING=3; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(9,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(9,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     delayhelp(9,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     delayhelp(9,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 15:
     FLAG=2;
     break;
     }

     }


     if(FLAG==156) break;

     }



     if(RUNNING==1) {
     if(fopen(path,"w")==NULL)
     {
     save_screen(14,19,23,60,st);
     drawbox(14,19,21,58,B_GREEN|BLACK);
     fastp(15,21,RED|B_GREEN,  "      Entery Position Error !       ",2,RED|B_GREEN);
     fastp(16,21,BLUE|B_GREEN, "You haven't type a correct file path",2,BLUE|B_GREEN);
     fastp(17,21,BLUE|B_GREEN, "or maybe your disk is protected.    ",2,BLUE|B_GREEN);
     oks(19,33,1,B_GREEN);
     getchr();
     delayoks(19,33,B_GREEN);
     FLAG=0;
     load_screen(14,19,23,60,st);
     goto df;
     }
     else { FLAG=-1;
	    for(i=1;i<5;i++) filemenu[i].select=1;
        pagemenu[0].select=1;
	    load_screen(4,3,12,76,savescreen);
	    filemenu[0].select=0;
	    filemenu[3].select=0;
	    fcloseall();
	    strcpy(temp,"del ");
	    strcat(temp,path);
	    strcat(temp," >nul");
	    system(temp);
	    return;}
     }

     if(RUNNING==2) { load_screen(4,3,12,76,savescreen);
		      FLAG=-1;
		      strcpy(path,temppath);
		      return; }

  if(RUNNING==3) {
     save_screen(8,19,18,59,st);
     drawbox(8,19,16,57,B_BROWN|BLACK);
     fastp(9,21,BLACK|B_BROWN,  "              New                  ",2,BLACK|B_BROWN);
     fastp(10,21,BLACK|B_BROWN, " Before starting with DBASE V2.00  ",2,BLACK|B_BROWN);
     fastp(11,21,BLACK|B_BROWN, " you should use  NEW  command to   ",2,BLACK|B_BROWN);
     fastp(12,21,BLACK|B_BROWN, " enter a new file for processing.  ",2,BLACK|B_BROWN);
     oks(14,33,1,B_BROWN);
     getchr();
     delayoks(14,33,B_BROWN);
     FLAG=0;
     load_screen(8,19,18,59,st);
     goto df;
     }



}

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/

void show_close(int (*savescreen)[80])
{

     int st[40][80];
     register i;
     int x=0,y=0,z=0;
     char c;
     int temp=3;


     if(FLAG==-1) FLAG=0;
     save_screen(9,3,17,76,savescreen);
     drawbox(9,3,16,74,B_D_BLUE|RED);
     fastp(10,5,BLACK|B_D_BLUE|BLINK," þ Warninig ",1,RED|B_D_BLUE);
     fastp(11,5,BLUE|B_D_BLUE,"Remember your file should be saved before , else it will be erased. ",3,BLUE|B_D_BLUE);
     fastp(12,5,BLUE|B_D_BLUE,"Are you sure to close the file ?",3,BLUE|B_D_BLUE);
     ok(14,18,0);
     cancel(14,34,0);
     help(14,50,0);



     FLAG=2;
     for(;;)   {
      df:

     if(FLAG==1)
     {
     ok(14,18,1);
     cancel(14,34,0);
     help(14,50,0);
     fastp(14,18,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(14,28,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=2;
     if(CHR==13) {delayok(14,18); RUNNING=1; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(14,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(14,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=1;
     delayhelp(14,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     ok(14,18,0);
     temp=1;
     delayhelp(14,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 15:
     FLAG=3;
     break;
     }

     }

     if(FLAG==2)
     {
     ok(14,18,0);
     cancel(14,34,1);
     help(14,50,0);
     fastp(14,34,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(14,44,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=3;
     if(CHR==13) {delaycancel(14,34); RUNNING=2; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(14,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(14,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=2;
     delayhelp(14,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 59:
     FLAG=3;
     temp=2;
     delayhelp(14,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 15:
     FLAG=1;
     break;
     }

     }



     if(FLAG==3)
     {
     ok(14,18,0);
     cancel(14,34,0);
     help(14,50,1);
     fastp(14,50,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(14,60,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=1;
     if(CHR==13) {delayhelp(14,50); RUNNING=3; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(14,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(14,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=3;
     delayhelp(14,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     temp=3;
     delayhelp(14,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 15:
     FLAG=2;
     break;
     }

     }


     if(FLAG==156) break;

     }



     if(RUNNING==1) { filemenu[0].select=1;
		      filemenu[1].select=0;
		      filemenu[2].select=0;
		      filemenu[3].select=1;
		      filemenu[4].select=0;
              for(x=0;x<4;x++)
		      pagemenu[x].select=0;
              for(x=0;x<7;x++)
              selectmenu[x].select=0;
              for(x=0;x<2;x++)
              {
              showmenu[x].select=0;
              printmenu[x].select=0;
              }
              load_screen(9,3,17,76,savescreen);
		      FLAG=-1;
		      return;
		      }


     if(RUNNING==2) {
		      load_screen(9,3,17,76,savescreen);
                      FLAG=-1;
                      return; }

  if(RUNNING==3) {
     save_screen(13,19,23,59,st);
     drawbox(13,19,21,57,B_BROWN|BLACK);
     fastp(14,21,BLACK|B_BROWN,  "             Close                 ",2,BLACK|B_BROWN);
     fastp(15,21,BLACK|B_BROWN, "If you want to use a new file you  ",2,BLACK|B_BROWN);
     fastp(16,21,BLACK|B_BROWN, "should first colse it and then use ",2,BLACK|B_BROWN);
     fastp(17,21,BLACK|B_BROWN, "that file with Open/New command.  ",2,BLACK|B_BROWN);
     oks(19,33,1,B_BROWN);
     getchr();
     delayoks(19,33,B_BROWN);
     FLAG=temp;
     load_screen(13,19,23,59,st);
     goto df;
     }



}



