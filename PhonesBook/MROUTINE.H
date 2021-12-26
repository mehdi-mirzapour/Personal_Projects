char flag(void)
{
union REGS i,j;
i.h.ah=0x12;
int86(0x16,&i,&j);
return(j.h.al);
}


void cursor(int flag)
{
union REGS in;
in.h.ah=1;
if (flag==0) {  in.h.ch=22;
		 in.h.cl=19; }

if (flag==1) { in.h.ch=0x0b;
		in.h.cl=0x0c; }

if (flag==2) { in.h.ch=17;
		 in.h.cl=23;}
int86(0x10,&in,&in);
}


void border(char color)
{
union REGS in;
in.h.ah=0xb;
in.h.bh=0;
in.h.bl=color;
int86(0x10,&in,&in);
}






void xy(char row,char coloum)
{
union REGS in,out;
in.h.ah=2;
in.h.bh=0;
in.h.dh=row;
in.h.dl=coloum;
int86(0x10,&in,&out);
}



void write_char(char ch,char attr,int times)
{
union REGS in,out;
in.h.ah=9;
in.h.al=ch;
in.h.bh=0;
in.h.bl=attr;
in.x.cx=times;
int86(0x10,&in,&out);
}




int save_char(char x,char y)
{
int far *ptr;
ptr=(int far *)0xb8000000;
return(*(ptr+80*x+y));
}




void load_char(char x,char y,int ch)
{
int far *ptr;
ptr=(int far *)0xb8000000;
*(ptr+80*x+y)=ch;
}





void save_screen(char x1,char y1,char x2, char y2,int (*int_ptr)[80])
{
int i,j;

for(i=0;i<(x2-x1+1);i++)
   for(j=0;j<(y2-y1+1);j++)
      int_ptr[i][j]=save_char(x1+i,y1+j);

}


void load_screen(char x1,char y1,char x2, char y2,int (*int_ptr)[80])
{
int i,j;

for(i=0;i<(x2-x1+1);i++)
   for(j=0;j<(y2-y1+1);j++)
      load_char(x1+i,y1+j,int_ptr[i][j]);

}


void edit(char x1,char y1,char x2, char y2,int (*int_ptr)[80])
{
int i,j;
int tt[80][80];

for(i=0;i<(x2-x1+1);i++)
   for(j=0;j<(y2-y1+1);j++)
      tt[i][j]=int_ptr[i][j+1];

for(i=0;i<(x2-x1+1);i++)
   for(j=0;j<(y2-y1+1);j++)
      int_ptr[i][j]=tt[i][j];


}


void write_to_buffer(char c)
{
union REGS in;
in.h.ah=5;
in.h.ch=0;
in.h.cl=c;
int86(0x16,&in,&in);
}

void adv_write_to_buffer(char c,char scan)
{
union REGS in;
in.h.ah=5;
in.h.ch=scan;
in.h.cl=c;
int86(0x16,&in,&in);
}

void fastp(char x,char y,char color,char *print,char xrow,char xcolor)
{
int i=0;

for(i=0;*(print+i)!='\0';++i)
  {
  xy(x,y+i);
  if (i==xrow) write_char(*(print+i),xcolor,1);
   else write_char(*(print+i),color,1);
  }

}


void getchr(void)
{
union REGS in,out;
int far *ptr;
int far *h;
int far *key;
int flag=0,sflag=0;
struct tm *tim;
long int x=0;
time_t lt;
char *st;
char i;
char verify=1;
h=(int far *)0xb8000000;
ptr=(int far *)0xb8000000;
key=(int far *)0x00400017;

k:
x=0;
while (verify==1) {

  if (bioskey(1)==0){  x++;

			  if  (flag==1 ) {  *(ptr+2)='S'|0x1c00;
					    *(ptr+3)='c'|0x1c00;
					    *(ptr+4)='r'|0x1c00;
					    *(ptr+5)='e'|0x1c00;
					    *(ptr+6)='e'|0x1c00;
					    *(ptr+7)='n'|0x1c00;
					    *(ptr+9)='B'|0x1c00;
					    *(ptr+10)='l'|0x1c00;
					    *(ptr+11)='a'|0x1c00;
					    *(ptr+12)='n'|0x1c00;
					    *(ptr+13)='k'|0x1c00;
								  }

				  else	 {  *(ptr+2)=' '|0x1c00;
					    *(ptr+3)=' '|0x1c00;
					    *(ptr+4)=' '|0x1c00;
					    *(ptr+5)=' '|0x1c00;
					    *(ptr+6)=' '|0x1c00;
					    *(ptr+7)=' '|0x1c00;
					    *(ptr+9)=' '|0x1c00;
					    *(ptr+10)=' '|0x1c00;
					    *(ptr+11)=' '|0x1c00;
					    *(ptr+12)=' '|0x1c00;
					    *(ptr+13)=' '|0x1c00;    }

			  if  (*key&64 && flag==0 ) {*(ptr+80*24+58)=' '|0x3c00;
				      *(ptr+80*24+59)='C'|0x3c00;
				      *(ptr+80*24+60)='a'|0x3c00;
				      *(ptr+80*24+61)='p'|0x3c00;
				      *(ptr+80*24+62)='s'|0x3c00;
				      *(ptr+80*24+63)=' '|0x3c00;}

			   else if(flag==0){     *(ptr+80*24+58)=' '|0x7700;
				      *(ptr+80*24+59)=' '|0x7700;
				      *(ptr+80*24+60)=' '|0x7700;
				      *(ptr+80*24+61)=' '|0x7700;
				      *(ptr+80*24+62)=' '|0x7700;
				      *(ptr+80*24+63)=' '|0x7700;}


		     if  (*key&32 && flag==0) {  *(ptr+80*24+65)=' '|0x3c00;
				      *(ptr+80*24+66)='N'|0x3c00;
				      *(ptr+80*24+67)='u'|0x3c00;
				      *(ptr+80*24+68)='m'|0x3c00;
				      *(ptr+80*24+69)=' '|0x3c00;}

			   else if(flag==0) {     *(ptr+80*24+65)=' '|0x7700;
				      *(ptr+80*24+66)=' '|0x7700;
				      *(ptr+80*24+67)=' '|0x7700;
				      *(ptr+80*24+68)=' '|0x7700;
				      *(ptr+80*24+69)=' '|0x7700;}


		     if  (*key&16 && flag==0) {  *(ptr+80*24+71)=' '|0x3c00;
				      *(ptr+80*24+72)='S'|0x3c00;
				      *(ptr+80*24+73)='c'|0x3c00;
				      *(ptr+80*24+74)='r'|0x3c00;
				      *(ptr+80*24+75)='o'|0x3c00;
				      *(ptr+80*24+76)='l'|0x3c00;
				      *(ptr+80*24+77)='l'|0x3c00;
				      *(ptr+80*24+78)=' '|0x3c00;}

			   else if(flag==0){     *(ptr+80*24+71)=' '|0x7700;
				      *(ptr+80*24+72)=' '|0x7700;
				      *(ptr+80*24+73)=' '|0x7700;
				      *(ptr+80*24+74)=' '|0x7700;
				      *(ptr+80*24+75)=' '|0x7700;
				      *(ptr+80*24+76)=' '|0x7700;
				      *(ptr+80*24+77)=' '|0x7700;
				      *(ptr+80*24+78)=' '|0x7700; }

   if(x>=100000l)     {
	if(bioskey(1)==0) {
	    if(sflag==0) {save_screen(1,0,24,79,ss); sflag=1;}
	    flag=1;
	    h=(ptr+((rand()%23)+1)*80+rand()%81);
	    h=h+rand()%80;
        *h=''|0x3000|(rand()%16)*256;
	    }else {   load_screen(1,0,24,79,ss);
		      CHR=0;
		      SCAN=0;
		      if(getch()==0) getch();
		      return;
		      }
		      }
if(ALARM)
 { lt=time(NULL);
     tim=localtime(&lt);
	     st=asctime(tim);
		for(i=0;i<strlen(st)-1;i++)
		      *(ptr+0+53+i)=st[i]|0x1c00;  }
			      else   for(i=0;i<26;i++)
						*(ptr+0+53+i)=' '|0x1c00;
				      }




  if (bioskey(1)!=0) {if (sflag==1) load_screen(1,0,24,79,ss);
		      if (sflag==1) {     if(getch()==0) getch();
					   CHR=0;
					   SCAN=0;
					   return;   }

              in.h.ah=16;
		      int86(0x16,&in,&out);
		      SCAN=out.h.ah;
		      CHR=out.h.al;
/*                    Now Defination Of Hot Keys
              if(CHR==0 && SCAN==45 && EXIT_HOT_KEY)
              { show_exit(); goto k; }
              if(CHR==0 && SCAN==104 && HELP_HOT_KEY)
              { tsr_help();  goto k; }                            */
              break;
              		      }

}

}

void scrollup(char x1,char y1,char x2,char y2,char attr,char num)
{
union REGS in;
in.h.ah=6;
in.h.al=num;
in.h.bh=attr;
in.h.ch=x1;
in.h.cl=y1;
in.h.dh=x2;
in.h.dl=y2;
int86(0x10,&in,&in);
}



void scrolldown(char x1,char y1,char x2,char y2,char attr,char num)
{
union REGS in;
in.h.ah=7;
in.h.al=num;
in.h.bh=attr;
in.h.ch=x1;
in.h.cl=y1;
in.h.dh=x2;
in.h.dl=y2;
int86(0x10,&in,&in);
}


int search(int x,struct menu *p,int i)
{
int j;
for(j=0;j<i;j++)
  if(p[j].alt==1)
    if(p[j].scankey==x) return(j);

return(-1);
}


int find(int x,struct menu *p,int i)
{
int j;
for(j=0;j<i;j++)
   if(p[j].key==x) return(j);

return(-1);
}

void bef(struct menu *m)
{
int a;
cursor(0);
xy(0,0);
write_char(178,B_WHITE|BRIGHT|BLUE,25*80);
xy(0,0);
write_char(' ',B_BLUE,80);
xy(1,0);
write_char(' ',B_WHITE,80);
xy(24,0);
write_char(' ',B_WHITE,80);
fastp(0,26,BRIGHT|WHITE|B_BLUE,"DataBank Version 2.00",3,BRIGHT|WHITE|B_BLUE);

for (a=0;a<7;++a)
      fastp(m[a].x,m[a].y,B_WHITE|BLACK,
      m[a].name,m[a].xrow,B_WHITE|RED);

}



int show_horizental(struct menu *m,int i)
{
int temp,a;

 for (a=0;a<i;++a)
   m[a].chrkey=0;

if(F==1) temp=0; else temp=1;
 for(;;)  {

  fastp(m[F].x,m[F].y,B_GREEN|BLACK,
      m[F].name,m[F].xrow,B_GREEN|RED);
     fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
     m[temp].name,m[temp].xrow,B_WHITE|RED);

  fastp(24,2,BLACK|B_WHITE,
      m[F].remark,m[F].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[F].chrkey==2) return(F);

getchr();
  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 77:
      if (F==(i-1))  {
		       temp=F;
			 F=0;
		      }
      else { temp=F;
	     F++;  }
      break;

      case 75:
      if (F==0)       {
			temp=F;
			 F=(i-1);
		      }
      else { temp=F;
	     F--; }
      break;

      case 33:
      temp=F;
      F=search(33,m,i);
      m[F].chrkey=2;
      break;

      case 25:
      temp=F;
      F=search(25,m,i);
      m[F].chrkey=2;
      break;


      case 38:
      temp=F;
      F=search(38,m,i);
      m[F].chrkey=2;
      break;



      case 31:
      temp=F;
      F=search(31,m,i);
      m[F].chrkey=2;
      break;


      case 19:
      temp=F;
      F=search(19,m,i);
      m[F].chrkey=2;
      break;


      case 20:
      temp=F;
      F=search(20,m,i);
      m[F].chrkey=2;
      break;


      case 35:
      temp=F;
      F=search(35,m,i);
      m[F].chrkey=2;
      break;



      case 80:
      return (F);
    default:
      sound(2000);
      delay(5);
      sound(1900);
      delay(5);
      nosound();
     }
    else
      switch(CHR)
      {
      case 13:
      return (F);

      case 'F':
      case 'f':
      temp=F;
      F=find('f',m,i);
      m[F].chrkey=2;
      break;

      case 'p':
      case 'P':
      temp=F;
      F=find('p',m,i);
      m[F].chrkey=2;
      break;

      case 'L':
      case 'l':
      temp=F;
      F=find('l',m,i);
      m[F].chrkey=2;
      break;

      case 'S':
      case 's':
      temp=F;
      F=find('s',m,i);
      m[F].chrkey=2;
      break;

      case 'r':
      case 'R':
      temp=F;
      F=find('r',m,i);
      m[F].chrkey=2;
      break;

      case 'T':
      case 't':
      temp=F;
      F=find('t',m,i);
      m[F].chrkey=2;
      break;

      case 'H':
      case 'h':
      temp=F;
      F=find('h',m,i);
      m[F].chrkey=2;
      break;

      default:
      sound(2000);
      delay(5);
      sound(1900);
      delay(5);
      nosound();
     }
    fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
     m[temp].name,m[temp].xrow,B_WHITE|RED);
}

}

int show_file(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

if (m[i].select==1)    fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
			 else
	  fastp(m[i].x,m[i].y,B_GREEN|BRIGHT|BLACK,
	    m[i].name,m[i].xrow,B_GREEN|BRIGHT|BLACK);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2 && m[i].select==1) return(i);

    q:
  getchr();

 if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;

      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);


      default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();

     }
   else
      switch(CHR)
      {
      case 'n':
      case 'N':
      temp=i;
      i=find('n',m,num);
      m[i].chrkey=2;
      break;


      case 's':
      case 'S':
      temp=i;
      i=find('s',m,num);
      m[i].chrkey=2;
      break;


      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;


      case 'o':
      case 'O':
      temp=i;
      i=find('o',m,num);
      m[i].chrkey=2;
      break;



      case 'c':
      case 'C':
      temp=i;
      i=find('c',m,num);
      m[i].chrkey=2;
      break;

      case 'x':
      case 'X':
      temp=i;
      i=find('x',m,num);
      m[i].chrkey=2;
      break;


      case 27:
      return(-1);

      case 13:
      if (m[i].select==1) return (i);
      break;


      default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

 if (m[temp].select==1)
      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
   else    fastp(m[temp].x,m[temp].y,B_WHITE|BRIGHT|BLACK,
	   m[temp].name,m[temp].xrow,B_WHITE|BRIGHT|BLACK);

}

}


int show_edit(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

if (m[i].select==1)    fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
			 else
	  fastp(m[i].x,m[i].y,B_GREEN|BRIGHT|BLACK,
	    m[i].name,m[i].xrow,B_GREEN|BRIGHT|BLACK);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2 && m[i].select==1) return(i);


  getchr();
  if (CHR==-32 ||CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;

      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
      default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {
      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;


      case 'e':
      case 'E':
      temp=i;
      i=find('e',m,num);
      m[i].chrkey=2;
      break;


      case 's':
      case 'S':
      temp=i;
      i=find('s',m,num);
      m[i].chrkey=2;
      break;

      case 'r':
      case 'R':
      temp=i;
      i=find('r',m,num);
      m[i].chrkey=2;
      break;



      case 27:
      return(-1);

      case 13:
      if (m[i].select==1) return (i);

	    default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

 if (m[temp].select==1)
      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
   else    fastp(m[temp].x,m[temp].y,B_WHITE|BRIGHT|BLACK,
	   m[temp].name,m[temp].xrow,B_WHITE|BRIGHT|BLACK);
}

}

int show_select(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

if (m[i].select==1)    fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
			 else
	  fastp(m[i].x,m[i].y,B_GREEN|BRIGHT|BLACK,
	    m[i].name,m[i].xrow,B_GREEN|BRIGHT|BLACK);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2 && m[i].select==1) return(i);

getchr();
  if (CHR==-32 ||CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);

	   default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {

      case 'f':
      case 'F':
      temp=i;
      i=find('f',m,num);
      m[i].chrkey=2;
      break;


      case 't':
      case 'T':
      temp=i;
      i=find('t',m,num);
      m[i].chrkey=2;
      break;


      case 'n':
      case 'N':
      temp=i;
      i=find('n',m,num);
      m[i].chrkey=2;
      break;



      case 'c':
      case 'C':
      temp=i;
      i=find('c',m,num);
      m[i].chrkey=2;
      break;

      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;


      case 's':
      case 'S':
      temp=i;
      i=find('b',m,num);
      m[i].chrkey=2;
      break;



      case 'd':
      case 'D':
      temp=i;
      i=find('d',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      if(m[i].select==1) return (i);
      break;
	    default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

 if (m[temp].select==1)
      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
   else    fastp(m[temp].x,m[temp].y,B_WHITE|BRIGHT|BLACK,
	   m[temp].name,m[temp].xrow,B_WHITE|BRIGHT|BLACK);
}

}

int show_show(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

if (m[i].select==1)    fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
			 else
	  fastp(m[i].x,m[i].y,B_GREEN|BRIGHT|BLACK,
	    m[i].name,m[i].xrow,B_GREEN|BRIGHT|BLACK);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2 && m[i].select==1) return(i);

getchr();
  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;

      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
	   default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {

      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;


      case 's':
      case 'S':
      temp=i;
      i=find('s',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      if(m[i].select==1) return (i);

	    default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

 if (m[temp].select==1)
      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
   else    fastp(m[temp].x,m[temp].y,B_WHITE|BRIGHT|BLACK,
	   m[temp].name,m[temp].xrow,B_WHITE|BRIGHT|BLACK);
}

}



int show_print(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

if (m[i].select==1)    fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
			 else
	  fastp(m[i].x,m[i].y,B_GREEN|BRIGHT|BLACK,
	    m[i].name,m[i].xrow,B_GREEN|BRIGHT|BLACK);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2 && m[i].select==1) return(i);



 getchr();
  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
	   default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {

      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;


      case 's':
      case 'S':
      temp=i;
      i=find('s',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      if (m[i].select==1) return (i);
	    default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

 if (m[temp].select==1)
      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
   else    fastp(m[temp].x,m[temp].y,B_WHITE|BRIGHT|BLACK,
	   m[temp].name,m[temp].xrow,B_WHITE|BRIGHT|BLACK);
}

}

int show_help(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

  fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2) return(i);

  getchr();

  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
      default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {

      case 'h':
      case 'H':
      temp=i;
      i=find('h',m,num);
      m[i].chrkey=2;
      break;


      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      return (i);

      default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

       fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
}

}

int show_tools(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;



for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);

if(m[0].alt==1) fastp(m[0].x,m[0].y+8,B_WHITE|BLUE,
		"ON",m[0].xrow,B_WHITE|BLUE);
	       else
	       fastp(m[0].x,m[0].y+8,B_WHITE|BLUE,
		"OFF",m[0].xrow,B_WHITE|BLUE);
i=1;
temp=1;
   for(;;) {

 if(m[i].chrkey==2 && m[i].select==1 && i==0 && m[0].alt==1) {m[0].alt=0;
							      ALARM=0;
								  i=0;
								  temp=1;}
	  else if(m[i].chrkey==2 && m[i].select==1 && i==0) {m[0].alt=1;
							     ALARM=1;
							     i=0;
							     temp=1;
							     }
m[0].chrkey=0;
if (m[i].select==1)    {fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
      if(m[0].alt==1 && i==0) fastp(m[0].x,m[0].y+8,B_GREEN|BLUE,
		"ON",m[0].xrow,B_GREEN|BLUE);
      if(m[0].alt==0 && i==0)
	       fastp(m[0].x,m[0].y+8,B_GREEN|BLUE,
		"OFF",m[0].xrow,B_GREEN|BLUE);    }
			 else
	  {
	  fastp(m[i].x,m[i].y,B_GREEN|BRIGHT|BLACK,
	    m[i].name,m[i].xrow,B_GREEN|BRIGHT|BLACK);
	    if(m[0].alt==1) fastp(m[0].x,m[0].y+7,B_WHITE|BLUE,
		"ON",m[0].xrow,B_WHITE|BLUE);
	       else
	       fastp(m[0].x,m[0].y+7,B_WHITE|BLUE,
		"OFF",m[0].xrow,B_WHITE|BLUE);   }
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2 && m[i].select==1 && i!=0) return(i);
getchr();

  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
     }
   else
      switch(CHR)
      {
      case 'a':
      case 'A':
      temp=i;
      i=find('a',m,num);
      m[i].chrkey=2;
      break;


      case 'c':
      case 'C':
      temp=i;
      i=find('c',m,num);
      m[i].chrkey=2;
      break;


      case 's':
      case 'S':
      temp=i;
      i=find('s',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      if (m[i].select==1 && i!=0) return (i);
      if (m[i].select==1 && i==0 && m[0].alt==1) {m[0].alt=0; ALARM=0;}
	  else if( m[i].select==1 && i==0 ) {m[0].alt=1; ALARM=1;}

      }


 if (m[temp].select==1)
      {
      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
      if(m[0].alt==1) fastp(m[0].x,m[0].y+8,B_WHITE|BLUE,
		"ON",m[0].xrow,B_WHITE|BLUE);
	       else
	       fastp(m[0].x,m[0].y+8,B_WHITE|BLUE,
		"OFF",m[0].xrow,B_WHITE|BLUE);}
   else    fastp(m[temp].x,m[temp].y,B_WHITE|BRIGHT|BLACK,
	   m[temp].name,m[temp].xrow,B_WHITE|BRIGHT|BLACK);
}

}

int show_sex(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

  fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2) return(i);

  getchr();

  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
      default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {

      case 'm':
      case 'M':
      temp=i;
      i=find('m',m,num);
      m[i].chrkey=2;
      break;


      case 'f':
      case 'F':
      temp=i;
      i=find('f',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      return (i);

      default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

       fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
}

}

int show_sub(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;


for (i=0;i<num;++i)
 if (m[i].select==1)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);
   else    fastp(m[i].x,m[i].y,B_WHITE|BRIGHT|BLACK,
	   m[i].name,m[i].xrow,B_WHITE|BRIGHT|BLACK);
i=0;
temp=1;
   for(;;) {

  fastp(m[i].x,m[i].y,B_GREEN|BLACK,
      m[i].name,m[i].xrow,B_GREEN|RED);
   fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);
	  if(m[i].chrkey==2) return(i);

  getchr();

  if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


      case 33:
      return(ALT_F);

      case 25:
      return(ALT_E);

      case 38:
      return(ALT_L);

      case 19:
      return(ALT_P);

      case 20:
      return(ALT_X);

      case 35:
      return(ALT_H);

      case 31:
      return(ALT_S);

      case 77:
      return(-3);

      case 75:
      return(-2);
      default:
      sound(2000);
      delay(5);
      sound(1000);
      delay(5);
      nosound();
     }
   else
      switch(CHR)
      {

      case 'l':
      case 'L':
      temp=i;
      i=find('l',m,num);
      m[i].chrkey=2;
      break;


      case 'M':
      case 'm':
      temp=i;
      i=find('m',m,num);
      m[i].chrkey=2;
      break;

      case 27:
      return(-1);

      case 13:
      return (i);

      default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }

       fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);
}

}




int show_present(struct menu *m,int num)
{
int i,temp;

    for (i=0;i<num;++i)
	m[i].chrkey=0;

for (i=0;i<num;++i)
      fastp(m[i].x,m[i].y,B_WHITE|BLACK,
      m[i].name,m[i].xrow,B_WHITE|RED);

      i=0;
      temp=1;


   for(;;)  {

    fastp(m[i].x,m[i].y,B_GREEN|BLACK|BLINK,
      m[i].name,m[i].xrow,B_GREEN|RED|BLINK);

    fastp(24,2,BLACK|B_WHITE,
      m[i].remark,m[i].xrow,B_WHITE|
      RED|BRIGHT);

      if(m[i].chrkey==2 && m[i].select==1) return(i);

    q:
  getchr();

 if (CHR==-32 || CHR==0)
    switch (SCAN)
    {
      case 80:
      if (i==(num-1))  {
		       temp=i;
			 i=0;
		      }
      else { temp=i;
	     i++;  }
      break;

      case 72:
      if (i==0)       {
			temp=i;
			 i=(num-1);
		      }
      else { temp=i;
	     i--; }
      break;


     }
   else
      switch(CHR)
      {
      case 'm':
      case 'M':
      temp=i;
      i=find('m',m,num);
      m[i].chrkey=2;
      break;


      case 'n':
      case 'N':
      temp=i;
      i=find('n',m,num);
      m[i].chrkey=2;
      break;


      case 'B':
      case 'b':
      temp=i;
      i=find('b',m,num);
      m[i].chrkey=2;
      break;


      case 'r':
      case 'R':
      temp=i;
      i=find('r',m,num);
      m[i].chrkey=2;
      break;

    
      case 'd':
      case 'D':
      temp=i;
      i=find('d',m,num);
      m[i].chrkey=2;
      break;


      case 27:
      return(-1);

      case 13:
      if (m[i].select==1) return (i);
      break;


      default:
      sound(2000);
      delay(5);
      sound(800);
      delay(5);
      nosound();
      }


      fastp(m[temp].x,m[temp].y,B_WHITE|BLACK,
      m[temp].name,m[temp].xrow,B_WHITE|RED);

}

}

void cursor_status(char *start,char *end,char *row,char *coloum)
{
union REGS in,out;
in.h.ah=3;
in.h.bh=0;
int86(0x10,&in,&out);
*start=out.h.ch;
*end=out.h.cl;
*row=out.h.dh;
*coloum=out.h.dl;
}



void other_exit(void)
{
int x;
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


