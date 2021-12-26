:- module(utteranceFixer,
			[
			 x_scheme/3,
			 x_scheme/12,
			 y_scheme/12
			]).
						
:- chr_constraint x_scheme/3,x_scheme/12,ex_scheme/12.
:- dynamic y_scheme/12.


x_scheme((cn,0),(det,0),(pn,0),(rc,0),(v(iv),0),(v(tv),0),(np,0),(vp,0),(s,0),_,_,0) <=>
writeln('All initial categories must not be zero'),
true.

/*========================================================================
   Triggering-Firing Rules
   Type B: Descedning Rules  
========================================================================*/

x_scheme((cn,A1),(det,B1),(pn,C1),(rc,D1),(v(iv),E1),(v(tv),F1),(np,G1),(vp,H1),(s,I1),_,_,CountX1), 
ex_scheme((cn,A2),(det,B2),(pn,C2),(rc,D2),(v(iv),E2),(v(tv),F2),(np,G2),(vp,H2),(s,_),_,_,_) <=>
(I1=1) |
	X1 is A1+A2,
	X2 is B1+B2,
	X3 is C1+C2,
	X4 is D1+D2,
	X5 is E1+E2,
	X6 is F1+F2,
	X7 is G1+G2,
	X8 is H1+H2,
	X9 is 1,
	CountY is CountX1+1,
	costUF([A1,B1,C1,X1,E1,F1,G1,H1,I1],Cost),
	assert(y_scheme((cn,X1),(det,X2),(pn,X3),(rc,X4),(v(iv),X5),(v(tv),X6),(np,X7),(vp,X8),(s,X9),Cost,collector,CountY)),
	x_scheme((cn,X1),(det,X2),(pn,X3),(rc,X4),(v(iv),X5),(v(tv),X6),(np,X7),(vp,X8),(s,X9),Cost,collector,CountY).	


% rc>0 ; vp>0 | rc--,vp--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	(I=1, (D>0 ; H>0)) |
	X is D-1,
	Y is H-1,
	CountY is CountX+1,
	costUF([A,B,C,X,E,F,G,Y,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,descedningRule1,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,descedningRule1,CountY).	


% rc<0, vp<0 | rc++,vp++.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	(I=1 ,(D<0 , H<0)) |
	X is D+1,
	Y is H+1,
	CountY is CountX+1,
	costUF([A,B,C,X,E,F,G,Y,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,descedningRule2,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,descedningRule2,CountY).




% np>0 ; rc>0 ; v(tv)>0 | np--,rc--,v(tv)--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	(I=1, (D>0 ; G>0 ; F>0)) |
	X is D-1,
	Y is G-1,
	Z is F-1,
	CountY is CountX+1,
	costUF([A,B,C,X,E,Z,Y,H,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),Z),(np,Y),(vp,H),(s,I),Cost,descedningRule3,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),Z),(np,Y),(vp,H),(s,I),Cost,descedningRule3,CountY).
	
	
% np<0 , rc<0 , v(tv)<0 | np++,rc++,v(tv)++.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	(I=1, (D<0 , G<0 , F<0)) |
	X is D+1,
	Y is G+1,
	Z is F+1,
	CountY is CountX+1,
	costUF([A,B,C,X,E,Z,Y,H,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),Z),(np,Y),(vp,H),(s,I),Cost,descedningRule4,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),Z),(np,Y),(vp,H),(s,I),Cost,descedningRule4,CountY).


/*========================================================================
   Triggering-Firing Rules
   Type A: Ascending Rules  
========================================================================*/

 
% pn>0 | np++,pn--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	C>0 |
	X is C-1,
	Y is G+1,
	CountY is CountX+1,
	costUF([A,B,X,D,E,F,Y,H,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,X),(rc,D),(v(iv),E),(v(tv),F),(np,Y),(vp,H),(s,I),Cost,ascendingRule1,CountY)),
	x_scheme((cn,A),(det,B),(pn,X),(rc,D),(v(iv),E),(v(tv),F),(np,Y),(vp,H),(s,I),Cost,ascendingRule1,CountY).


% det>0 | np++,cn--,det--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	A>0 |
	X is A-1,
	Y is B-1,
	Z is G+1,
	CountY is CountX+1,
	costUF([X,Y,C,D,E,F,Z,H,I],Cost),
	assert(y_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,ascendingRule2,CountY)),
	x_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,ascendingRule2,CountY).


% cn>0 | np++,cn--,det--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	B>0 |
	X is A-1,
	Y is B-1,
	Z is G+1,
	CountY is CountX+1,
	costUF([X,Y,C,D,E,F,Z,H,I],Cost),
	assert(y_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,ascendingRule3,CountY)),
	x_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,ascendingRule3,CountY).


% v(iv)>0 | vp++, v(iv)--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	E>0 |
	X is E-1,
	Y is H+1,
	CountY is CountX+1,
	costUF([A,B,C,D,X,F,G,Y,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),X),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,ascendingRule4,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),X),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,ascendingRule4,CountY).


% v(tv)>0 | vp++, np--, v(tv)--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	F>0 |
	X is F-1,
	Y is G-1,
	Z is H+1,
	CountY is CountX+1,
	costUF([A,B,C,D,E,X,Y,Z,I],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),X),(np,Y),(vp,Z),(s,I),Cost,ascendingRule5,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),X),(np,Y),(vp,Z),(s,I),Cost,ascendingRule5,CountY).


% np>0 | s++,np--,vp--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	G>0 |
	X is G-1,
	Y is H-1,
	Z is I+1,
	CountY is CountX+1,
    costUF([A,B,C,D,E,F,X,Y,Z],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,X),(vp,Y),(s,Z),Cost,ascendingRule7,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,X),(vp,Y),(s,Z),Cost,ascendingRule7,CountY).


% vp>0 | s++,np--,vp--.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	H>0 |
	X is G-1,
	Y is H-1,
	Z is I+1,
	CountY is CountX+1,
    costUF([A,B,C,D,E,F,X,Y,Z],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,X),(vp,Y),(s,Z),Cost,ascendingRule7,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,X),(vp,Y),(s,Z),Cost,ascendingRule7,CountY).	


% Trial Test for Checking
% rc>0 | rc--,np++. 
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,_,CountX) <=>
	(I=0 ,(D>0)) |
	X is D-1,
	Y is G+1,
	CountY is CountX+1,
	costUF([A,B,C,X,E,F,Y,H,I],Cost),
    assert(y_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,Y),(vp,H),(s,I),Cost,descedningRuleStar,CountY)),	
    assert(y_scheme((cn,0),(det,0),(pn,0),(rc,0),(v(iv),0),(v(tv),0),(np,-1),(vp,-1),(s,0),Cost,descedningRuleStar,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,Y),(vp,H),(s,I),Cost,descedningRuleStar,CountY),
	ex_scheme((cn,0),(det,0),(pn,0),(rc,0),(v(iv),0),(v(tv),0),(np,-1),(vp,-1),(s,0),Cost,descedningRuleStar,CountY).
	