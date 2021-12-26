
void show_exit(void)
{
int x=0;
char x1,y1,xb,yb;
int savescreen[40][80];
int st[40][80];
union REGS in;

   EXIT_HOT_KEY=0;
   cursor_status(&xb,&yb,&x1,&y1);
   save_screen(8,9,16,72,savescreen);
   cursor(0);
   drawbox(8,9,14,70,B_D_BLUE|BLACK);
   fastp(10,21,BLUE|B_D_BLUE,"Are You Sure To Exit From Data Bank",2,BLUE|B_D_BLUE);
   xy(10,57);
   write_char('?',BLUE|B_D_BLUE|BLINK,1);
  FLAG=1;

  for(;;)   {
      df:
  
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
     FLAG=3;
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
     if(CHR==9) FLAG=1;
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
     load_screen(8,9,16,72,savescreen);
     cursor(0);
     border(BLACK);
     for(x=0;x<25;x++)  {
     scrolldown(x,0,24,79,0,1);
     load_screen(0,0,x,79,EXT);
     delay(35);
             }
     cursor(1);
     xy(YA,0);
     exit(0);
     }

     if(RUNNING==2)  {
                     load_screen(8,9,16,72,savescreen);
                     xy(x1,y1);
                     in.h.ah=1;
                     in.h.ch=xb;
                     in.h.cl=yb;
                     int86(0x10,&in,&in);
                     FLAG=-1;
                     EXIT_HOT_KEY=1;
                     return;
                     }


  if(RUNNING==3) {
     save_screen(8,19,20,59,st);
     drawbox(8,19,18,57,B_BROWN|BLACK);
     fastp(9,21,BLACK|B_BROWN,  "       Exit From Data Bank         ",2,BLACK|B_BROWN);
     fastp(10,21,BLACK|B_BROWN, "While you want to exit from program",2,BLACK|B_BROWN);
     fastp(11,21,BLACK|B_BROWN, "you may forget to save current file",2,BLACK|B_BROWN);
     fastp(12,21,BLACK|B_BROWN, "and this may cause your information",2,BLACK|B_BROWN);
     fastp(13,21,BLACK|B_BROWN, "to be lost. Answer 'Cancel' if you ",2,BLACK|B_BROWN);
     fastp(14,21,BLACK|B_BROWN, "want to remain in DBANK.           ",2,BLACK|B_BROWN);
     oks(16,33,1,B_BROWN);
     getchr();
     delayoks(16,33,B_BROWN);
     FLAG=1;
     load_screen(8,19,20,59,st);
     goto df;
     }


}


void tsr_help(void)
{
int x=0;
char x1,y1,xb,yb;
char *buf;
int st[40][80];
union REGS in;
buf=(char *)malloc(24*80*2);
   HELP_HOT_KEY=0;
   cursor_status(&xb,&yb,&x1,&y1);
   gettext(1,2,80,25,buf);
   cursor(0);
   set_color_regs(GREEN,40,105,47);
   xy(1,0);
   write_char(' ',B_WHITE|BRIGHT,80);
   xy(2,0);
   write_char(177,B_WHITE|BRIGHT|BLUE,22*80);
   fastp(1,29,BRIGHT|B_WHITE|RED," Help Service",3,BRIGHT|B_WHITE|RED);
   fastp(24,0,BRIGHT|B_WHITE|BLACK,"   Data Bank Help Service (DBHS)                                       ",3,BRIGHT|B_WHITE|BLACK);
   drawbox(4,10,20,70,B_GREEN);
   getchr();
   HELP_HOT_KEY=1;
   set_color_regs(GREEN,40,-105,47);
   xy(x1,y1);
   in.h.ah=1;
   in.h.ch=xb;
   in.h.cl=yb;
   int86(0x10,&in,&in);
   FLAG=-1;
   puttext(1,2,80,25,buf);
   free(buf);
}

