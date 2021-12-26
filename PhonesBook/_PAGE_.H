int LAST=6;
void bfirst(void)
{
if (LAST==0) {
             ssprint(5,30,30,BRIGHT|GREEN|B_D_BLUE,FM_NAME);
             return;  }

if (LAST==1) {
             ssprint(7,30,30,BRIGHT|GREEN|B_D_BLUE,FT_NAME);
             return;
            }

if (LAST==2) {
             ssprint(9,30,30,BRIGHT|GREEN|B_D_BLUE,NAME);
             return;
            }

if (LAST==3) {
             ssprint(11,30,30,BRIGHT|GREEN|B_D_BLUE,CERTIFY);
             return;
            }

if (LAST==4) {
             ssprint(14,13,15,GREEN|BRIGHT|B_D_BLUE,AGE);
             return;
            }

if (LAST==5) {
              ssprint(14,37,16,BRIGHT|GREEN|B_D_BLUE,SEX);
              return;
            }

if (LAST==6) {
             ssprint(17,13,57,BRIGHT|GREEN|B_D_BLUE,DEGREE);
             return;
            }

}





void show_add(int (*savescreen)[80])
{

     int st[40][80];
     register i;
     int x=-1,y=0,z=0;
     int cnt;
     char c;
     int temp=3;



     FLAG=0;

     save_screen(4,11,23,77,savescreen);
     drawbox(4,11,21,75,B_D_BLUE|BLACK);
     fastp(4,34,B_D_BLUE|WHITE|BRIGHT," Add New Page ",1,B_D_BLUE|WHITE|BRIGHT);
     fastp(5,12,B_D_BLUE|BLUE," ® Family Name ¯ ",1,B_D_BLUE|BLUE);
     fastp(7,12,B_D_BLUE|BLUE," ® Father Name ¯ ",1,B_D_BLUE|BLUE);
     fastp(9,12,B_D_BLUE|BLUE," ® Name ¯ ",1,B_D_BLUE|BLUE);
     fastp(11,12,B_D_BLUE|BLUE," ® Certificate ¯ ",1,B_D_BLUE|BLUE);
     fastp(13,12,B_D_BLUE|BLUE," ® Age ¯ ",1,B_D_BLUE|BLUE);
     fastp(13,36,B_D_BLUE|BLUE," ® Sex ¯           ",1,B_D_BLUE|BLUE);
     fastp(16,12,B_D_BLUE|BLUE," ® Degree ¯ ",1,B_D_BLUE|BLUE);

     for(LAST=6;LAST>=0;LAST--)
     bfirst();

     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);




     for(;;)   {
      df:

     if(FLAG==0)
     {
     bfirst();
     LAST=0;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=_gets(5,30,30,FM_NAME,-2,0,0,FM_NAME);
     cursor(0);
     if(cnt==TAB)   FLAG=1;
     if(cnt==S_TAB) FLAG=9;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=0;delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=0;delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=1;
     }

     if(FLAG==1)
     {
     bfirst();
     LAST=1;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=_gets(7,30,30,FT_NAME,-2,0,0,FT_NAME);
     cursor(0);
     if(cnt==TAB)   FLAG=2;
     if(cnt==S_TAB) FLAG=0;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=1; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=1; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=2;
     }

    if(FLAG==2)
     {
     bfirst();
     LAST=2;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=_gets(9,30,30,NAME,-2,0,0,NAME);
     cursor(0);
     if(cnt==TAB)   FLAG=3;
     if(cnt==S_TAB) FLAG=1;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=2; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=2; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=3;
     }

     if(FLAG==3)
     {
     bfirst();
     LAST=3;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=_gets(11,30,30,CERTIFY,-2,0,0,CERTIFY);
     cursor(0);
     if(cnt==TAB)   FLAG=4;
     if(cnt==S_TAB) FLAG=2;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=3; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=3; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=4;
     }

     if(FLAG==4)
     {
     bfirst();
     LAST=4;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=_gets(14,13,15,AGE,-2,0,0,AGE);
     cursor(0);
     if(cnt==TAB)   FLAG=5;
     if(cnt==S_TAB) FLAG=3;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=4; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=4; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=5;
     }

     if(FLAG==5)
     {
     bfirst();
     LAST=5;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=TAB;
     ssprint(14,37,16,BLACK|B_GREEN,SEX);
     h:
     getchr();
     if(CHR==9 || (CHR==0 && SCAN==15) || (CHR==-32 && SCAN==80)) {
                     if(CHR==9) cnt=TAB;
                     if(CHR==0 && SCAN==15) cnt=S_TAB;
                     if(CHR==-32 && SCAN==80 ) x=show_sex(sex,2);}
                       else goto h;
     xy(15,38);
     write_char(' ',B_D_BLUE,16);
     xy(16,38);
     write_char(' ',B_D_BLUE,16);
       if(x==0) strcpy(SEX,"MALE");
       if(x==1) strcpy(SEX,"FEMALE");
     cursor(0);
     if(cnt==TAB)   FLAG=6;
     if(cnt==S_TAB) FLAG=4;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=5; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=5; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=6;
     }

      if(FLAG==6)
     {
     bfirst();
     LAST=6;
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,0);
     cnt=_gets(17,13,57,DEGREE,-2,0,0,DEGREE);
     cursor(0);
     if(cnt==TAB)   FLAG=7;
     if(cnt==S_TAB) FLAG=5;
     if(cnt==ALT_O) {delayok(19,21); FLAG=156;RUNNING=7;}
     if(cnt==ALT_C) {delaycancel(19,37); FLAG=156;RUNNING=8;}
     if(cnt==ALT_h) {temp=6; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==F1)    {temp=6; delayhelp(19,53); FLAG=156;RUNNING=9;}
     if(cnt==ENTER) FLAG=7;
     }


     if(FLAG==7)
     {
     bfirst();
     ok(19,21,1);
     cancel(19,37,0);
     help(19,53,0);
     fastp(19,21,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(19,31,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=8;
     if(CHR==13) {delayok(19,21); RUNNING=7; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=7;
     delayok(19,21);
     RUNNING=7;
     FLAG=156;
     break;

     case 46:
     FLAG=8;
     delaycancel(19,37);
     RUNNING=8;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=7;
     delayhelp(19,53);
     RUNNING=9;
     FLAG=156;
     break;

     case 59:
     FLAG=9;
     ok(19,21,0);
     temp=7;
     delayhelp(19,53);
     RUNNING=9;
     FLAG=156;
     break;


     case 15:
     FLAG=6;
     break;
     }

     }

     if(FLAG==8)
     {
     bfirst();
     ok(19,21,0);
     cancel(19,37,1);
     help(19,53,0);
     fastp(19,37,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(19,47,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=9;
     if(CHR==13) {delaycancel(19,37); RUNNING=8; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=7;
     delayok(19,21);
     RUNNING=7;
     FLAG=156;
     break;

     case 46:
     FLAG=8;
     delaycancel(19,37);
     RUNNING=8;
     FLAG=156;
     break;


     case 35:
     FLAG=9;
     temp=8;
     delayhelp(19,53);
     RUNNING=9;
     FLAG=156;
     break;


     case 59:
     FLAG=9;
     temp=8;
     delayhelp(19,53);
     RUNNING=9;
     FLAG=156;
     break;


     case 15:
     FLAG=7;
     break;
     }

     }



     if(FLAG==9)
     {
     bfirst();
     ok(19,21,0);
     cancel(19,37,0);
     help(19,53,1);
     fastp(19,53,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(19,63,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=0;
     if(CHR==13) {delayhelp(19,53); RUNNING=9; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=7;
     delayok(19,21);
     RUNNING=7;
     FLAG=156;
     break;

     case 46:
     FLAG=8;
     delaycancel(19,37);
     RUNNING=8;
     FLAG=156;
     break;


     case 35:
     FLAG=9;
     temp=9;
     delayhelp(19,53);
     RUNNING=9;
     FLAG=156;
     break;

     case 59:
     FLAG=9;
     temp=9;
     delayhelp(19,53);
     RUNNING=9;
     FLAG=156;
     break;

     case 15:
     FLAG=8;
     break;
     }

     }


     if(FLAG==156) break;

     }



     if(RUNNING==7) {
                    ok(19,21,0);
                    FLAG=-1;
                    if(  FM_NAME[0]=='\0' || FT_NAME=='\0' || NAME[0]=='\0'
                         ||  CERTIFY[0]=='\0' || AGE[0]=='\0'
                           || DEGREE[0]=='\0' || SEX[0]=='\0'         )
                    {
                    save_screen(7,19,18,59,st);
                    drawbox(7,19,16,57,B_GREEN|BLACK);
                    cancel(19,37,0);
                    help(19,53,0);
                    fastp(8,21,MAGENTA|B_GREEN,  "          Warrning !              ",2,MAGENTA|B_GREEN);
                    fastp(10,21,BLACK|B_GREEN, " Some of your enterty is not yet   ",2,BLACK|B_GREEN);
                    fastp(11,21,BLACK|B_GREEN," completed and it means you will   ",2,BLACK|B_GREEN);
                    fastp(12,21,BLACK|B_GREEN," have some empty fields.           ",2,BLACK|B_GREEN);
                    oks(14,33,1,B_GREEN);
                    getchr();
                    delayoks(14,33,B_GREEN);
                    FLAG=temp;
                    load_screen(7,19,18,59,st);
                    }
                    load_screen(4,11,23,77,savescreen);
                    for(i=0;i<7;i++)
                    selectmenu[i].select=1;
                    for(i=0;i<2;i++)
                    {
                     showmenu[i].select=1;
                     printmenu[i].select=1;
                    }
                    pagemenu[1].select=1;
                    pagemenu[2].select=1;
                    pagemenu[3].select=1;

                    ACCEPT_ID_ENTERY=1;
                    return;
                            }


     if(RUNNING==8) { FM_NAME[0]='\0';
                      FT_NAME[0]='\0';
                      NAME[0]='\0';
                      CERTIFY[0]='\0';
                      AGE[0]='\0';
                      SEX[0]='\0';
                      DEGREE[0]='\0';
                      load_screen(4,11,23,77,savescreen);
                      FLAG=-1;
                      ACCEPT_ID_ENTERY=0;
                      return; }

  if(RUNNING==9) {
     save_screen(7,19,18,59,st);
     drawbox(7,19,16,57,B_BROWN|BLACK);
     cancel(19,37,0);
     help(19,53,0);
     fastp(8,21,BLACK|B_BROWN,  "         Add New Page             ",2,BLACK|B_BROWN);
     fastp(10,21,BLACK|B_BROWN, " Enter you certifications and jump ",2,BLACK|B_BROWN);
     fastp(11,21,BLACK|B_BROWN," over with Tab & Shift Tab keys so ",2,BLACK|B_BROWN);
     fastp(12,21,BLACK|B_BROWN," when it is finished click Okey.   ",2,BLACK|B_BROWN);
     oks(14,33,1,B_BROWN);
     getchr();
     delayoks(14,33,B_BROWN);
     FLAG=temp;
     load_screen(7,19,18,59,st);
     goto df;
     }



}

get_manual_page()
{
static char c[20];;
for(;;) {
_gets(9,31,5,c,-2,0,0,c);
MANNUAL_ACTIVE_PAGE=atoi(c);
if (!(MANNUAL_ACTIVE_PAGE>PAGE_NUMBER)
                    && MANNUAL_ACTIVE_PAGE!=0) break; }
cursor(0);
}



