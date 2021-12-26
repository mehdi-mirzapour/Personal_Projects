/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
void shell_to_dos(void)
{
    int x;
    for(x=0;x<25;x++)  {
     scrollup(0,0,24,19,0,1);
     scrolldown(0,20,24,40,0,1);
     delay(15);
			 }

     for(x=0;x<25;x++)  {
     scrollup(0,40,24,59,0,1);
     scrolldown(0,60,24,80,0,1);
     delay(15);
			}


    system("CLS");
    printf("\n\n\n        Type 'Exit' to return to DBANK v2.00 . . .");
    cursor(1);

    system("C:\COMMAND.COM ");
    cursor(0);
}

/***************************************************************************/
/***************************************************************************/
/***************************************************************************/
void show_command(int (*savescreen)[80],char *command)
{
int x,cnt;
int st[40][80];
   save_screen(7,9,16,72,savescreen);
   drawbox(7,9,14,70,B_D_BLUE|BLACK);
   fastp(8,25,MAGENTA|B_D_BLUE,"Please Enter Your DOS Command  ",2,MAGENTA|B_D_BLUE);

   if(FLAG==-1) FLAG=0;

  for(;;)   {
      df:
     if(FLAG==0)
     {
     ok(12,18,0);
     cancel(12,34,0);
     help(12,50,0);
     cnt=_gets(10,14,50,command,-2,0,0,command);
     cursor(0);
     if(cnt==TAB)   FLAG=1;
     if(cnt==S_TAB) FLAG=3;
     if(cnt==ALT_O) {delayok(12,18); FLAG=156;RUNNING=1;}
     if(cnt==ALT_C) {delaycancel(12,34); FLAG=156;RUNNING=2;}
     if(cnt==ALT_h) {delayhelp(12,50); FLAG=156;RUNNING=3;}
     if(cnt==F1)    {delayhelp(12,50); FLAG=156;RUNNING=3;}
     if(cnt==ENTER) FLAG=1;
     }

     if(FLAG==1)
     {
     ok(12,18,1);
     cancel(12,34,0);
     help(12,50,0);
     fastp(12,18,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(12,28,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=2;
     if(CHR==13) {delayok(12,18); RUNNING=1; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(12,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(12,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     delayhelp(12,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     ok(12,18,0);
     delayhelp(12,50);
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
     ok(12,18,0);
     cancel(12,34,1);
     help(12,50,0);
     fastp(12,34,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(12,44,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=3;
     if(CHR==13) {delaycancel(12,34); RUNNING=2; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(12,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(12,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     delayhelp(12,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 59:
     FLAG=3;
     delayhelp(12,50);
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
     ok(12,18,0);
     cancel(12,34,0);
     help(12,50,1);
     fastp(12,50,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(12,60,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=0;
     if(CHR==13) {delayhelp(12,50); RUNNING=3; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(12,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(12,34);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     delayhelp(12,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     delayhelp(12,50);
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
     if(command[0]=='\0')
     {
     save_screen(8,19,21,60,st);
     fastp(13,58,D_BLUE|B_D_BLUE,"   ",2,D_BLUE|B_D_BLUE);
     drawbox(8,19,18,58,B_GREEN|BLACK);
     fastp(9,21,RED|B_GREEN,  "             Error !                 ",2,RED|B_GREEN);
     fastp(10,21,BLUE|B_GREEN, "You have not type any command in the",2,BLUE|B_GREEN);
     fastp(11,21,BLUE|B_GREEN, "input line to be executed in the DOS",2,BLUE|B_GREEN);
     fastp(12,21,BLUE|B_GREEN, "enviroument please enter command and",2,BLUE|B_GREEN);
     fastp(13,21,BLUE|B_GREEN, "then click on Okey item.            ",2,BLUE|B_GREEN);
     oks(16,33,1,B_GREEN);
     getchr();
     delayoks(16,33,B_GREEN);
     FLAG=0;
     load_screen(8,19,21,60,st);
     goto df;
     }
     else {FLAG=-1; 	 for(x=0;x<25;x++)           {
			  scrollup(0,0,24,19,0,1);
			  scrolldown(0,20,24,40,0,1);
			  scrollup(0,41,24,59,0,1);
			  scrolldown(0,60,24,79,0,1);
			  delay(15);     		}
			 system("CLS");
			 cursor(1);
			 system(command);
             printf("\n\n               Now press a key to return to DBANK v2.00");
			 if(getch()==0) getch();
			 cursor(0);
             return;}
     }
     if(RUNNING==2)  load_screen(7,9,16,72,savescreen);
     if(RUNNING==2)  FLAG=-1;
     if(RUNNING==2)  return;

  if(RUNNING==3) {
     save_screen(8,19,20,59,st);
     drawbox(8,19,18,57,B_BROWN|BLACK);
     fastp(9,21,BLACK|B_BROWN,  "       Emergency Command           ",2,BLACK|B_BROWN);
     fastp(10,21,BLACK|B_BROWN, "Sometimes you want to run a command",2,BLACK|B_BROWN);
     fastp(11,21,BLACK|B_BROWN, "without exiting from program so you",2,BLACK|B_BROWN);
     fastp(12,21,BLACK|B_BROWN, "can do it by running your command  ",2,BLACK|B_BROWN);
     fastp(13,21,BLACK|B_BROWN, "in the MS-DOS Command menu so  type",2,BLACK|B_BROWN);
     fastp(14,21,BLACK|B_BROWN, "your command in input line. ",2,BLACK|B_BROWN);
     oks(16,33,1,B_BROWN);
     getchr();
     delayoks(16,33,B_BROWN);
     FLAG=0;
     load_screen(8,19,20,59,st);
     goto df;
     }
}


