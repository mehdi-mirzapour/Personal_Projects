int ALAST=6;
void abfirst(void)
{
if (ALAST==0) {
             ssprint(5,27,30,BRIGHT|GREEN|B_D_BLUE,FM_NAME);
             return;  }

if (ALAST==1) {
             ssprint(7,27,30,BRIGHT|GREEN|B_D_BLUE,FT_NAME);
             return;
            }

if (ALAST==2) {
             ssprint(9,27,30,BRIGHT|GREEN|B_D_BLUE,NAME);
             return;
            }

if (ALAST==3) {
             ssprint(11,27,30,BRIGHT|GREEN|B_D_BLUE,CERTIFY);
             return;
            }

if (ALAST==4) {
             ssprint(14,10,15,GREEN|BRIGHT|B_D_BLUE,AGE);
             return;
            }

if (ALAST==5) {
              ssprint(14,33,16,BRIGHT|GREEN|B_D_BLUE,SEX);
              return;
            }

if (ALAST==6) {
             ssprint(17,10,57,BRIGHT|GREEN|B_D_BLUE,DEGREE);
             return;
            }

}





void view_page1(int (*savescreen)[80])
{

     int st[40][80];
     register i;
     int x=-1,y=0,z=0;
     int cnt;
     char c;
     int temp=3;


     add=first;
     FLAG=0;
     if(SELECT_ACTIVE_PAGE)
     {
        for(i=1;i!=MANNUAL_ACTIVE_PAGE;i++)
        add=add->next;
        strcpy(FM_NAME,add->sfm_name);
        strcpy(FT_NAME,add->sft_name);
        strcpy(NAME,add->sname);
        strcpy(CERTIFY,add->scertify);
        strcpy(AGE,add->sage);
        strcpy(SEX,add->ssex);
        strcpy(DEGREE,add->sdegree);

     }

   else

     {
     strcpy(FM_NAME,this->sfm_name);
     strcpy(FT_NAME,this->sft_name);
     strcpy(NAME,this->sname);
     strcpy(CERTIFY,this->scertify);
     strcpy(AGE,this->sage);
     strcpy(SEX,this->ssex);
     strcpy(DEGREE,this->sdegree);
     }


     save_screen(4,8,23,74,savescreen);
     drawbox(4,8,21,72,B_D_BLUE|BLACK);
     if(SELECT_ACTIVE_PAGE)
     fastp(4,27,B_D_BLUE|WHITE|BRIGHT," View The Mannual Page ",1,B_D_BLUE|WHITE|BRIGHT);
     else
     fastp(4,30,B_D_BLUE|WHITE|BRIGHT," View The Last Page ",1,B_D_BLUE|WHITE|BRIGHT);
     fastp(5,9,B_D_BLUE|BLUE," ® Family Name ¯ ",1,B_D_BLUE|BLUE);
     fastp(7,9,B_D_BLUE|BLUE," ® Father Name ¯ ",1,B_D_BLUE|BLUE);
     fastp(9,9,B_D_BLUE|BLUE," ® Name ¯ ",1,B_D_BLUE|BLUE);
     fastp(11,9,B_D_BLUE|BLUE," ® Certificate ¯ ",1,B_D_BLUE|BLUE);
     fastp(13,9,B_D_BLUE|BLUE," ® Age ¯ ",1,B_D_BLUE|BLUE);
     fastp(13,32,B_D_BLUE|BLUE," ® Sex ¯           ",1,B_D_BLUE|BLUE);
     fastp(16,9,B_D_BLUE|BLUE," ® Degree ¯ ",1,B_D_BLUE|BLUE);

     for(ALAST=6;ALAST>=0;ALAST--)
     abfirst();

      FM_NAME[0]='\0';
      FT_NAME[0]='\0';
      NAME[0]='\0';
      CERTIFY[0]='\0';
      AGE[0]='\0';
      SEX[0]='\0';
      DEGREE[0]='\0';

     ok(19,18,0);
     cancel(19,33,0);
     help(19,50,0);




     FLAG=1;
     for(;;)   {
      df:

     if(FLAG==1)
     {
     ok(19,18,1);
     cancel(19,33,0);
     help(19,50,0);
     fastp(19,18,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(19,28,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=2;
     if(CHR==13) {delayok(19,18); RUNNING=1; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(19,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(19,33);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=1;
     delayhelp(19,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     ok(19,18,0);
     temp=1;
     delayhelp(19,50);
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
     ok(19,18,0);
     cancel(19,33,1);
     help(19,50,0);
     fastp(19,33,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(19,43,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=3;
     if(CHR==13) {delaycancel(19,33); RUNNING=2; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(19,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(19,33);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=2;
     delayhelp(19,50);
     RUNNING=3;
     FLAG=156;
     break;


     case 59:
     FLAG=3;
     temp=2;
     delayhelp(19,50);
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
     ok(19,18,0);
     cancel(19,33,0);
     help(19,50,1);
     fastp(19,50,B_WHITE|RED,"",1,B_WHITE|RED);
     fastp(19,60,B_WHITE|RED,"",1,B_WHITE|RED);
     getchr();
     if(CHR==9) FLAG=1;
     if(CHR==13) {delayhelp(19,50); RUNNING=3; FLAG=156;}
     if(CHR==0)
     switch(SCAN)
     {
     case 24:
     FLAG=1;
     delayok(19,18);
     RUNNING=1;
     FLAG=156;
     break;

     case 46:
     FLAG=2;
     delaycancel(19,33);
     RUNNING=2;
     FLAG=156;
     break;


     case 35:
     FLAG=3;
     temp=3;
     delayhelp(19,50);
     RUNNING=3;
     FLAG=156;
     break;

     case 59:
     FLAG=3;
     temp=3;
     delayhelp(19,50);
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
                      load_screen(4,8,23,74,savescreen);
                      FLAG=-1;
                      return;
                     }


     if(RUNNING==2) {
                      load_screen(4,8,23,74,savescreen);
                      FLAG=-1;
                      return; }

  if(RUNNING==3) {
     save_screen(8,19,18,59,st);
     drawbox(8,19,16,57,B_BROWN|BLACK);
     fastp(9,21,BLACK|B_BROWN,  "           View Page               ",2,BLACK|B_BROWN);
     fastp(10,21,BLACK|B_BROWN, "You can use other types of viewing  ",2,BLACK|B_BROWN);
     fastp(11,21,BLACK|B_BROWN, "such as Group viewing in the select ",2,BLACK|B_BROWN);
     fastp(12,21,BLACK|B_BROWN, "menu with differnt patterns.        ",2,BLACK|B_BROWN);
     oks(14,33,1,B_BROWN);
     getchr();
     delayoks(14,33,B_BROWN);
     FLAG=temp;
     load_screen(8,19,18,59,st);
     goto df;
     }
}
