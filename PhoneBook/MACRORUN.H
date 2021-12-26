#define BLACK    0
#define BLUE     1
#define GREEN    2
#define D_BLUE   3
#define RED      4
#define MAGENTA  5
#define BROWN    6
#define WHITE    7

#define B_BLACK    0*16
#define B_BLUE     1*16
#define B_GREEN    2*16
#define B_D_BLUE   3*16
#define B_RED      4*16
#define B_MAGENTA  5*16
#define B_BROWN    6*16
#define B_WHITE    7*16



#define BRIGHT     8
#define BLINK    128



#define ENTER    -10
#define TAB      -11
#define S_TAB    -12
#define F1       -13
#define ALT_C    -14
#define ALT_O    -15
#define ALT_h    -23

#define ALT_F    -16
#define ALT_E    -17
#define ALT_L    -18
#define ALT_S    -19
#define ALT_P    -20
#define ALT_X    -21
#define ALT_H    -22

#define NIL (struct member *)NULL



char CHR;
char SCAN;
char ALARM=1;
int  FLAG=-1;
char RUNNING;
int ss[40][80];
int nz[40][80];
char CHECK=1;
int F=0;
char *SAVE;
char XA,YA;
int EXT[40][80];
int EXT_HELP[40][80];

int ACCEPT_FILE_PATH=0;
int ACCEPT_ID_ENTERY=0;
int SELECT_ACTIVE_PAGE=0;
int PAGE_NUMBER=0;
int MANNUAL_ACTIVE_PAGE=0;
int HELP_HOT_KEY=0;
int EXIT_HOT_KEY=0;
