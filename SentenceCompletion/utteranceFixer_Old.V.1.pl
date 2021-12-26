:- module(utteranceFixer,
			[
			 x_scheme/3,
			 x_scheme/12,
			 y_scheme/12
			]).
						
:- chr_constraint x_scheme/3,x_scheme/12.
:- dynamic y_scheme/12.



/*========================================================================
   Initialization
                  Add lexicon entries to inputs   
========================================================================*/


%x_scheme(Lex,Order,SII) <=> lex(Lex,[Cat|[]])| x(H,Cat,A,B,SII).
%x(H,A,B,SII) <=> lex(H,[Cat|T])| x(H,[Cat|T],A,B,SII).
%
%x(_,[],_,_,_)      <=> true.
%x(H,[Cat|T],A,B,SII) <=> x(H,T,A,B,SII), x(H,Cat,A,B,SII).



/*========================================================================
   Triggering-Firing Rules Start   
========================================================================*/


%Error Detection
x_scheme((cn,0),(det,0),(pn,0),(rc,0),(v(iv),0),(v(tv),0),(np,0),(vp,0),(s,0),_,_,0) <=>
writeln('All initial categories must not be zero'),
true.


/*========================================================================
   Triggering-Firing Rules
   Type A: Creation Rules  
========================================================================*/

 
%cn,det->np
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	(A>0 ; B>0), I=0 |
	X is A-1,
	Y is B-1,
	Z is G+1,
	CountY is CountX+1,
	costUF([X,Y,C,D,E,F,Z,H,I,K],Cost),
	assert(y_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,cRule1,CountY)),
	x_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,cRule1,CountY).



%propn->np
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	C>0, I=0 |
	X is C-1,
	Y is G+1,
	CountY is CountX+1,
	costUF([A,B,X,D,E,F,Y,H,I,K],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,X),(rc,D),(v(iv),E),(v(tv),F),(np,Y),(vp,H),(s,I),Cost,cRule2,CountY)),
	x_scheme((cn,A),(det,B),(pn,X),(rc,D),(v(iv),E),(v(tv),F),(np,Y),(vp,H),(s,I),Cost,cRule2,CountY).


%v(iv)->vp
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	E>0, I=0 |
	X is E-1,
	Y is H+1,
	CountY is CountX+1,
	costUF([A,B,C,D,X,F,G,Y,I,K],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),X),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,cRule3,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),X),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,cRule3,CountY).


%v(tv),np->vp
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	(F>0; G>0), I=0|
	X is F-1,
	Y is G-1,
	Z is H+1,
	CountY is CountX+1,
	costUF([A,B,C,D,E,X,Y,Z,I,K],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),X),(np,Y),(vp,Z),(s,I),Cost,cRule4,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),X),(np,Y),(vp,Z),(s,I),Cost,cRule4,CountY).


%np,rc,vp->np
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	D>0, G>0, H>0, I=0 |
	X is D-1,
	Y is H-1,
	CountY is CountX+1,
	costUF([A,B,C,X,E,F,G,Y,I,K],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,cRule5,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,X),(v(iv),E),(v(tv),F),(np,G),(vp,Y),(s,I),Cost,cRule5,CountY).


%np,vp->s.
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	(H>0), I=0  |
	X is G-1,
	Y is H-1,
	Z is I+1,
	CountY is CountX+1,
	costUF([A,B,C,D,E,F,X,Y,Z,K],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,X),(vp,Y),(s,Z),Cost,cRule6,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,X),(vp,Y),(s,Z),Cost,cRule6,CountY).



/*========================================================================
   Triggering-Firing Rules
   Type B: Balancing Rules  
========================================================================*/


% Balancing np alone
x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
	(F<0, G<0), I=1 |
	X is F+1,
	Y is G+1,
	Z is E-1,
	CountY is CountX+1,
	costUF([A,B,C,D,Z,X,Y,H,I,K],Cost),
	assert(y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),Z),(v(tv),X),(np,Y),(vp,H),(s,I),Cost,bRule1,CountY)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),Z),(v(tv),X),(np,Y),(vp,H),(s,I),Cost,bRule1,CountY).


%% Balancing for np and (cn,det) 
%x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
%	G>0, I=1 |
%	X is A+1,
%	Y is B+1,
%	Z is G-1,
%	CountY is CountX+1,
%	costUF([A,B,C,D,Z,X,Y,H,I,K],Cost),
%	assert(y_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,bRule2,CountY)),
%	x_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,bRule2,CountY).
%
%
%% Balancing for np and (cn,det)	
%x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),_,K,CountX) ==>
%	G<0, I=1 |
%	X is A-1,
%	Y is B-1,
%	Z is G+1,
%	CountY is CountX+1,
%	costUF([A,B,C,D,Z,X,Y,H,I,K],Cost),
%	assert(y_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,bRule3,CountY)),
%	x_scheme((cn,X),(det,Y),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,Z),(vp,H),(s,I),Cost,bRule3,CountY).
	
