void about(void)
{
register i;
int s[40][80];
void set_color_regs(int,char,char,char);
save_screen(8,16,17,60,s);
set_color_regs(GREEN,40,105,47);
drawbox(8,16,16,58,B_GREEN|BLUE);
fastp(10,18,BLACK|B_GREEN,"     A Program By Mehdi Mirzapour  ",2,BLACK|B_GREEN);
fastp(11,18,BLACK|B_GREEN,"        Data Bank Version 2.00",2,BLACK|B_GREEN);
fastp(12,18,BLACK|B_GREEN,"          All Right Reserved",2,BLACK|B_GREEN);
oks(14,30,1,B_GREEN);
for(i=0;i<6;i++)
{
sound(400);
delay(50);
sound(600);
delay(50);
sound(800);
delay(50);
}
nosound();
for(;;)
{
getchr();
if(CHR!=0 || SCAN!=0)  break;
}
delayoks(14,30,B_GREEN);
load_screen(8,16,17,60,s);
set_color_regs(GREEN,40,-105,47);
}

