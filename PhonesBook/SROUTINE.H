

void drawbox(int x1,int y1,int x2,int y2,char attr)
{
int i,j;
int numx,numy;
int x;
numx=x2-x1+1;
numy=y2-y1+1;

xy(x1,y1);
write_char('Ú',attr,1);
xy(x1,y1+1);
write_char('Ä',attr,numy-1);
xy(x1,y1+numy-1);
write_char('¿',attr,1);





  for(i=1;i<(numx-1);i++)
   {
   xy(x1+i,y1);
   write_char('³',attr,1);
   xy(x1+i,y1+1);
   write_char(' ',attr,numy-1);
   xy(x1+i,y1+numy-1);
   write_char('³',attr,1);
   }

xy(x1+numx-1,y1);
write_char('À',attr,1);
xy(x1+numx-1,y1+1);
write_char('Ä',attr,numy-1);
xy(x1+numx-1,y1+numy-1);
write_char('Ù',attr,1);

for(i=1;i<(numx+1);i++)
  for(j=1;j<3;j++)
  {
  xy(x1+i,y2+j);
  x=save_char(x1+i,y2+j);
  x=0xff&x;
  write_char(x,B_BLACK|WHITE,1);
  }

for(i=1;i<(numy+1);i++)
  {
  xy(x2+1,y1+i+1);
  x=save_char(x2+1,y1+i+1);
  x=0xff&x;
  write_char(x,B_BLACK|WHITE,1);
  }





}



void drawseperateline(int x1,int y1,int x2,int y2,char attr)
{

x2=x2*100;
   xy(x1,y1);
   write_char('Ã',attr,1);
   xy(x1,y1+1);
   write_char('Ä',attr,y2-y1);
   xy(x1,y2);
   write_char('´',attr,1);



}


void save_line(char row,int i,int j)
{
char count=0;
int  attr;


 while( (i+count) <= j)
 {
  attr=save_char(row,i+count);
  SAVE[count]=attr&0x00ff;
  count++;
 }

 SAVE[count]='\0';

}



void backspace(char row,int i,int j,char attr)
{
char count=0;
save_line(row,i,j);
i--;
   while(*(SAVE+count) !='\0')
   {
    xy(row,i+count);
    write_char(SAVE[count],attr,1);
    count++;
   }
   xy(row,i+count-1);
   write_char('.',36,1);
   xy(row,i+count);
   write_char('.',36,1);
   xy(row,i);
}

void del(char row,int i,int j,char attr)
{
backspace(row,i+1,j,attr);
}

void insert(char row,int i,int j,char attr)
{
char count=0;
save_line(row,i,j-1);
i++;
   while(*(SAVE+count) !='\0')
   {
    xy(row,i+count);
    write_char(SAVE[count],attr,1);
    count++;
   }
   xy(row,i+count);
   write_char('.',36,1);
   xy(row,i-1);
}

void before(char x,char y,int max,char attr)
{
xy(x,y);
write_char('[',attr,1);
xy(x,y+1);
write_char('.',attr,max);
xy(x,y+max+1);
write_char(']',attr,1);
}

int print(char x,char y,int max,char attr,char technic)
{
if (technic==1) before(x,y,max,attr);
xy(x,y+1);
return(y+1);
}

void ssprint(char x,char y,int max,char attr,char *arr)
{
register i;
before(x,y,max,attr);
for(i=0;i<strlen(arr);i++) {
xy(x,y+1+i);
write_char(arr[i],attr,1); }
}


char status(void)
{
char s;
s=peekb(0x0000,0x0417);
s=(s&0x80)/128;
return(s);
}


int get_string(char x,char y,char max,char technic,char i,char j ,char *a)
{
int flagx;
char is,ff=0;
char g;
int z=10;
i=j=strlen(a);
is=print(x,y,max,36,1);
if (technic==-2) for(g=0;*(a+g)!='\0';g++) {xy(x,is+g); write_char(a[g],32,1);}
strt:
if (technic!=-2 || ff==1) {i=0; j=0;}


if (status()==1) cursor(2);
	   else cursor(1);

     for(;;)
      {
	xy(x,is+i);
	   getchr();

    if (CHR==-32 || CHR==0)
	 switch(SCAN)
	  {
	   case 77:
	   if (i==j) break;
	   else if (i==max)  break;
	   else if (i<j) ++i;
	   break;

	   case 75:
	   if (i==0) break;
	   else i--;
	   break;


	   case 71:
	   i=0;
	   break;

	   case 79:
	   i=j;
	   break;

	   case 83:
	   if(i==j) break;
	   del(x,is+i,is+j,32);
	   j--;
	   break;

	   case 82:
	   if (status()==1) cursor(2);
	   else cursor(1);
	   break;


	   case 15:
	   return (S_TAB);

	   case 59:
	   return (F1);

	   case 46:
	   return(ALT_C);

	   case 24:
	   return(ALT_O);

	   case 35:
	   return(ALT_h);
	 }

      else
	  {
	   switch(CHR)
	   {
	   case 8:
	    if (i==0) goto e1;
	    backspace(x,is+i,is+j,32);
	       i--;
	      j--;
	   goto e1;


	   case 13:
	   return (ENTER);

	   case 27:
       is=print(x,y,max,36,1);
	   ff=1;
	   goto strt;


	   case 9:
	   return (TAB);
	   }

	  flagx=0;


	  if (status()==1) if (i<max-1 && j<max-1 )  { insert(x,is+i,is+j,32);
					   write_char(toupper(CHR),32,1);
					   j++;
					   flagx=1;
					   }
	  if (status()==1 && flagx==0) i=max-1;
	  if (status()==0 && i<max-1)  write_char(toupper(CHR),32,1);
	  if (i>=max-1)  goto e1;
	  if (i==j) { ++j; ++i; }
	    else ++i;
	  }

 e1:
z=z*100;
}

}



int  _gets(char x,char y,char max,char *a,char technic,char m,char n,char *z)
{
char ch;
char test,ret;
int i,j,x1;
ret=get_string(x,y,max,technic,m,n,z);

for(i=1;i<=max;++i)
{
x1=save_char(x,y+i);
ch=x1&0x00ff;
test=x1>>8;
if (test==32) a[i-1]=ch;  else break;
}
a[i-1]='\0';
return(ret);
}

void ok(char x,char y,char mode)
{

if(mode==1)
{
fastp(x,y,B_D_BLUE|B_WHITE, "   Okey    ",3,RED|B_WHITE);
xy(x,y+11); write_char(220,BLACK|B_D_BLUE,1);
fastp(x+1,y,BLACK|B_D_BLUE,  " ßßßßßßßßßßß",3,BLACK|B_D_BLUE);
}
else
{
fastp(x,y,B_WHITE|BRIGHT|BLACK, "   Okey    ",3,B_WHITE|BRIGHT|BLACK);
xy(x,y+11); write_char(220,BLACK|B_D_BLUE,1);
fastp(x+1,y,BLACK|B_D_BLUE,  " ßßßßßßßßßßß",3,BLACK|B_D_BLUE);
}
}




void cancel(char x,char y,char mode)
{
if (mode==1)
{
fastp(x,y,B_WHITE|B_D_BLUE,"   Cancel  ",3,RED|B_WHITE);
xy(x,y+11); write_char(220,BLACK|B_D_BLUE,1);
fastp(x+1,y,BLACK|B_D_BLUE,  " ßßßßßßßßßßß",3,BLACK|B_D_BLUE);
}
else
{
fastp(x,y,B_WHITE|BRIGHT|BLACK,"   Cancel  ",3,B_WHITE|BRIGHT|BLACK);
xy(x,y+11); write_char(220,BLACK|B_D_BLUE,1);
fastp(x+1,y,BLACK|B_D_BLUE,  " ßßßßßßßßßßß",3,BLACK|B_D_BLUE);
}
}


void help(char x,char y,char mode)
{

if(mode==1)
{
fastp(x,y,B_D_BLUE|B_WHITE, "   Help    ",3,RED|B_WHITE);
xy(x,y+11); write_char(220,BLACK|B_D_BLUE,1);
fastp(x+1,y,BLACK|B_D_BLUE,  " ßßßßßßßßßßß",3,BLACK|B_D_BLUE);
}
else
{
fastp(x,y,B_WHITE|BRIGHT|BLACK, "   Help    ",3,B_WHITE|BRIGHT|BLACK);
xy(x,y+11); write_char(220,BLACK|B_D_BLUE,1);
fastp(x+1,y,BLACK|B_D_BLUE,  " ßßßßßßßßßßß",3,BLACK|B_D_BLUE);
}
}

void delayok(char x,char y)
{
xy(x,y); write_char(' ',0x3c,1);
fastp(x,y+1,B_D_BLUE|B_WHITE, "   Okey    ",3,RED|B_WHITE);
fastp(x+1,y,0x3c,  "            ",3,0x3c);
delay(70);
}


void delaycancel(char x,char y)
{
xy(x,y); write_char(' ',0x3c,1);
fastp(x,y+1,B_D_BLUE|B_WHITE, "   Cancel  ",3,RED|B_WHITE);
fastp(x+1,y,0x3c,  "            ",3,0x3c);
delay(70);
}

void delayhelp(char x,char y)
{
xy(x,y); write_char(' ',0x3c,1);
fastp(x,y+1,B_D_BLUE|B_WHITE, "   Help    ",3,RED|B_WHITE);
fastp(x+1,y,0x3c,  "            ",3,0x3c);
delay(70);
}

void oks(char x,char y,char mode,char color)
{
if(mode==1)
{
fastp(x,y,B_D_BLUE|B_WHITE, "   Okey    ",3,RED|B_WHITE);
xy(x,y+11); write_char(220,BLACK|color,1);
fastp(x+1,y,BLACK|color,  " ßßßßßßßßßßß",3,BLACK|color);}
}

void delayoks(char x,char y,char color)
{
xy(x,y); write_char(' ',color,1);
fastp(x,y+1,B_D_BLUE|B_WHITE, "   Okey    ",3,RED|B_WHITE);
fastp(x+1,y,color,  "            ",3,color);
delay(70);
}



void _about(void)
{
int x;
register i;
int s[40][80];
void set_color_regs(int,char,char,char);

cursor(0);
xy(0,0);
save_screen(3,9,22,72,s);
drawbox(3,9,20,70,B_D_BLUE|BLACK);
fastp(4,17,BLUE|B_D_BLUE, "       Paradise Software Presents            ",2,MAGENTA|B_D_BLUE);
drawseperateline(5,9,5,70,B_D_BLUE|BLACK);
xy(4,24);
write_char('P',B_D_BLUE|BROWN|BRIGHT,1);
xy(4,33);
write_char('S',B_D_BLUE|BROWN|BRIGHT,1);
xy(4,42);
write_char('P',B_D_BLUE|BROWN|BRIGHT,1);
fastp(7,13,BLUE|B_D_BLUE, " This is Beta Version of DBANK for testing my ability  ",2,BLUE|B_D_BLUE);
fastp(8,13,BLUE|B_D_BLUE," in an real program .                                  ",2,BLUE|B_D_BLUE);
fastp(9,13,BLUE|B_D_BLUE," Please NOTICE the programmer with the faults that you ",2,BLUE|B_D_BLUE); fastp(10,13,BLUE|B_D_BLUE," may have seen in Data Bank Beta Version .         ",2,BLUE|B_D_BLUE);
fastp(19,45,BLUE|B_D_BLUE," Mehdi Mirzapour 1996  ",2,BLUE|B_D_BLUE);
oks(13,33,1,B_D_BLUE);
fastp(24,1,B_WHITE|BLACK,"  Use Arrow Key Up/Down To Select Items ",1,GREEN|B_WHITE);
x=show_present(present,5);
switch(x)
{
case 3:
for(i=3;i<24;i++)
{
xy(i,9);
write_char(177,B_WHITE|BRIGHT|BLUE,70);
delay(20);
}
return;


case 4:
other_exit();
break;

}

load_screen(3,9,22,72,s);
}


void write_black(int x)
{
register i;
for(i=1;i<24;i++)
{
xy(i,x);
write_char(' ',0x0000,1);}
}


void password(int (*back)[80],int y1)
{
char pass[100];
int cnt;
char mehdi[40];
int st[40][80];
drawbox(7,9,14,70,B_D_BLUE|BLACK);
fastp(9,19,MAGENTA|B_D_BLUE," Enter Password  ",2,MAGENTA|B_D_BLUE);
fastp(24,1,BLACK|B_WHITE,"   With The Best Wishes For You !                 ",1,RED|B_WHITE);
cursor(1);
pass[0]='\0';
 FLAG=0;

  for(;;)   {
      df:
     if(FLAG==0)
     {
     ok(12,18,0);
     cancel(12,34,0);
     help(12,50,0);
     cnt=_gets(9,37,15,pass,-2,0,0,pass);
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
     if(strcmpi(pass,"PARADISE")!=0 && strcmpi(pass,"MIRZAPOUR")!=0)
     {
     save_screen(8,19,21,59,st);
     fastp(13,58,D_BLUE|B_D_BLUE,"  ",2,D_BLUE|B_D_BLUE);
     drawbox(8,19,19,57,B_GREEN|BLACK);
     fastp(9,21,BLUE|B_GREEN,  "In this part of program seems that ",2,BLUE|B_GREEN);
     fastp(10,21,BLUE|B_GREEN, "you have a type mismatch entery or ",2,BLUE|B_GREEN);
     fastp(11,21,BLUE|B_GREEN, "you haven't enter serial number.   ",2,BLUE|B_GREEN);
     fastp(13,21,BLUE|B_GREEN, "If you don't know the serial number",2,BLUE|B_GREEN);
     fastp(14,21,BLUE|B_GREEN, "surely you have a copy of  program  ",2,BLUE|B_GREEN);
     fastp(15,21,BLUE|B_GREEN, "without licence.                    ",2,BLUE|B_GREEN);
     oks(17,33,1,B_GREEN);
     getchr();
     delayoks(17,33,B_GREEN);
     FLAG=0;
     load_screen(8,19,21,59,st);
     goto df;
     }
     else {FLAG=-1; return;}
     }
     if(RUNNING==2) other_exit();
          

  if(RUNNING==3) {
     save_screen(8,19,22,59,st);
     drawbox(8,19,20,57,B_BROWN|BLACK);
     fastp(9,21,BLACK|B_BROWN,  "In this part of program you should ",2,BLACK|B_BROWN);
     fastp(10,21,BLACK|B_BROWN, "use your  serial number  to enter  ",2,BLACK|B_BROWN);
     fastp(11,21,BLACK|B_BROWN, "program so type your serial number ",2,BLACK|B_BROWN);
     fastp(12,21,BLACK|B_BROWN, "and click on Okey item to pass.    ",2,BLACK|B_BROWN);
     fastp(14,21,BLACK|B_BROWN, "Else if you don't know the program ",2,BLACK|B_BROWN);
     fastp(15,21,BLACK|B_BROWN, "password you should escape from it ",2,BLACK|B_BROWN);
     fastp(16,21,BLACK|B_BROWN, "by clicking on Cancel item.        ",2,BLACK|B_BROWN);
     oks(18,33,1,B_BROWN);
     getchr();
     delayoks(18,33,B_BROWN);
     FLAG=0;
     load_screen(8,19,22,59,st);
     goto df;
     }



}

void set_color_regs(int color,char green,char blue, char red)
{
union REGS in;
in.x.ax=0x1010;
in.x.bx=color;
in.h.ch=green;
in.h.cl=blue;
in.h.dh=red;
int86(0x10,&in,&in);
}


void seprate_array(char *c,char *s)
{
int i,j=0;
int max;
max=strlen(c);
for(i=0;i<=max;i++)
{
if (c[i]==' ') break;
}
c[i]='\0';
i++;
for(;i<=max;i++,j++)
s[j]=c[i];
s[j]='\0';
}

void findc(char *x,char *y)
{
union REGS in,out;
in.h.ah=3;
in.h.bh=0;
int86(0x10,&in,&out);
*x=out.h.dl;
*y=out.h.dh;
}


int ifif(int (*savescreen)[80],int x,char n1,char n2,char n3,char n4,char n,char p)
{
char flag=0;

     if(x==-3) { load_screen(n1,n2,n3,n4,savescreen);
	 write_to_buffer(n);
	 flag=1;
	}

     if(x==-2) {  load_screen(n1,n2,n3,n4,savescreen);
	 write_to_buffer(p);
	 flag=1;
	 }

     if(x==-1) {  load_screen(n1,n2,n3,n4,savescreen);
	  flag=1;
	  }

     if(x==ALT_F) { load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,33);
	flag=1;
	}

     if(x==ALT_E) {  load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,25);
	 flag=1;
	 }

     if(x==ALT_L) { load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,38);
	 flag=1;
	 }

     if(x==ALT_P) {  load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,19);
	 flag=1;
	 }

     if(x==ALT_X) { load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,20);
	 flag=1;
	 }

     if(x==ALT_H) {  load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,35);
	 flag=1;
	 }

     if(x==ALT_S) {  load_screen(n1,n2,n3,n4,savescreen);
		 adv_write_to_buffer(0,31);
	 flag=1;
	 }
return(flag);
}


