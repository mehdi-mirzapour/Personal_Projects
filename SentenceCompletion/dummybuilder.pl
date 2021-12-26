:- module(dummybuilder,
			[schemeGenerate,
			scheme/2,
			schemeS/2
			]).
						
:- chr_constraint schemeU/2.


/*========================================================================
   Schemes Generator (List of Categories) Builder
   
             Usage:        schemeGenerate
========================================================================*/

schemeGenerate :-
	setof(X,y(s,X),L),
	schemeGen_(L).

schemeGen_([]):-!.	
schemeGen_([H|T]):-
       length(H,M),
       schemeGen_(T),
       schemeU(M,H).	
	

y(s,X) :-
	y(np,A,_),
	y(vp,B,_),
	append(A,B,AB),
	X=AB.

	
y(np,X,1) :-
	X=[det,cn].
	
	
y(np,X,2) :-
	X=[pn].
	

y(np,X,3) :- 
	y(np,A1,B1),
	y(np,A2,B2),
	B1\==3, B2\==3 ->
    (
    append(A1,[rc],AB1),
	append(AB1,[v(tv)],AB2),
	append(AB2,A2,AB),
	X=AB
	).


y(np,X,4) :- 
	y(np,A1,B1),
	y(np,A2,B2),
	B1\==4, B2\==4 ->
	(
	append(A1,[rc],AB1),
	append(AB1,A2,AB2),
	append(AB2,[v(tv)],AB),
	X=AB
	).


y(np,X,4) :- 
	y(np,A1,B1),
	y(np,A2,B2),
	B1\==4, B2\==4 ->
	(
	append(A1,[rc],AB1),
	append(AB1,A2,AB2),
	append(AB2,[v(tv)],AB),
	X=AB
	).

	
y(np,X,5) :- 
	y(np,A1,B1),
	B1\==5 ->
	(
	append(A1,[rc,v(iv)],AB),
	X=AB
	).	
	
		
y(vp,X,1) :-
	X=[v(iv)].

	
y(vp,X,2) :-
	y(np,A,_),
	append([v(tv)],A,AB),
	X=AB.


/*========================================================================
   Schemes Conversion 
        Usage:        
             Type the predicate 'convertScheme.'
             and then copy the result into the code file.
========================================================================*/

convertScheme:-
	scheme(A,B),
	list_to_clist(B,C),
	schemeS(A,C).


/*========================================================================
   List of Schemes    
    Sorted based on the length of categories in each list
========================================================================*/

scheme(1,[pn,v(iv)]).
scheme(2,[det,cn,v(iv)]).
scheme(3,[pn,v(tv),pn]).
scheme(4,[det,cn,v(tv),pn]).
scheme(5,[pn,v(tv),det,cn]).
scheme(6,[det,cn,rc,v(iv),v(iv)]).
scheme(7,[det,cn,v(tv),det,cn]).
scheme(8,[det,cn,rc,v(iv),v(tv),pn]).
scheme(9,[pn,v(tv),det,cn,rc,v(iv)]).
scheme(10,[det,cn,rc,det,cn,v(tv),v(iv)]).
scheme(11,[det,cn,rc,v(iv),v(tv),det,cn]).
scheme(12,[det,cn,rc,v(tv),det,cn,v(iv)]).
scheme(13,[det,cn,v(tv),det,cn,rc,v(iv)]).
scheme(14,[det,cn,rc,det,cn,v(tv),v(tv),pn]).
scheme(15,[det,cn,rc,v(tv),det,cn,v(tv),pn]).
scheme(16,[pn,v(tv),det,cn,rc,det,cn,v(tv)]).
scheme(17,[pn,v(tv),det,cn,rc,v(tv),det,cn]).
scheme(18,[det,cn,rc,det,cn,v(tv),v(tv),det,cn]).
scheme(19,[det,cn,rc,v(iv),v(tv),det,cn,rc,v(iv)]).
scheme(20,[det,cn,rc,v(tv),det,cn,v(tv),det,cn]).
scheme(21,[det,cn,v(tv),det,cn,rc,det,cn,v(tv)]).
scheme(22,[det,cn,v(tv),det,cn,rc,v(tv),det,cn]).
scheme(23,[det,cn,rc,det,cn,v(tv),v(tv),det,cn,rc,v(iv)]).
scheme(24,[det,cn,rc,v(iv),v(tv),det,cn,rc,det,cn,v(tv)]).
scheme(25,[det,cn,rc,v(iv),v(tv),det,cn,rc,v(tv),det,cn]).
scheme(26,[det,cn,rc,v(tv),det,cn,v(tv),det,cn,rc,v(iv)]).
scheme(27,[det,cn,rc,det,cn,v(tv),v(tv),det,cn,rc,det,cn,v(tv)]).
scheme(28,[det,cn,rc,det,cn,v(tv),v(tv),det,cn,rc,v(tv),det,cn]).
scheme(29,[det,cn,rc,v(tv),det,cn,v(tv),det,cn,rc,det,cn,v(tv)]).
scheme(30,[det,cn,rc,v(tv),det,cn,v(tv),det,cn,rc,v(tv),det,cn]).


schemeS(1,[ (cn,0), (det,0), (pn,1), (rc,0), (v(iv),1), (v(tv),0)]).
schemeS(2,[ (cn,1), (det,1), (pn,0), (rc,0), (v(iv),1), (v(tv),0)]).
schemeS(3,[ (cn,0), (det,0), (pn,2), (rc,0), (v(iv),0), (v(tv),1)]).
schemeS(4,[ (cn,1), (det,1), (pn,1), (rc,0), (v(iv),0), (v(tv),1)]).
schemeS(5,[ (cn,1), (det,1), (pn,1), (rc,0), (v(iv),0), (v(tv),1)]).
schemeS(6,[ (cn,1), (det,1), (pn,0), (rc,1), (v(iv),2), (v(tv),0)]).
schemeS(7,[ (cn,2), (det,2), (pn,0), (rc,0), (v(iv),0), (v(tv),1)]).
schemeS(8,[ (cn,1), (det,1), (pn,1), (rc,1), (v(iv),1), (v(tv),1)]).
schemeS(9,[ (cn,1), (det,1), (pn,1), (rc,1), (v(iv),1), (v(tv),1)]).
schemeS(10,[ (cn,2), (det,2), (pn,0), (rc,1), (v(iv),1), (v(tv),1)]).
schemeS(11,[ (cn,2), (det,2), (pn,0), (rc,1), (v(iv),1), (v(tv),1)]).
schemeS(12,[ (cn,2), (det,2), (pn,0), (rc,1), (v(iv),1), (v(tv),1)]).
schemeS(13,[ (cn,2), (det,2), (pn,0), (rc,1), (v(iv),1), (v(tv),1)]).
schemeS(14,[ (cn,2), (det,2), (pn,1), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(15,[ (cn,2), (det,2), (pn,1), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(16,[ (cn,2), (det,2), (pn,1), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(17,[ (cn,2), (det,2), (pn,1), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(18,[ (cn,3), (det,3), (pn,0), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(19,[ (cn,2), (det,2), (pn,0), (rc,2), (v(iv),2), (v(tv),1)]).
schemeS(20,[ (cn,3), (det,3), (pn,0), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(21,[ (cn,3), (det,3), (pn,0), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(22,[ (cn,3), (det,3), (pn,0), (rc,1), (v(iv),0), (v(tv),2)]).
schemeS(23,[ (cn,3), (det,3), (pn,0), (rc,2), (v(iv),1), (v(tv),2)]).
schemeS(24,[ (cn,3), (det,3), (pn,0), (rc,2), (v(iv),1), (v(tv),2)]).
schemeS(25,[ (cn,3), (det,3), (pn,0), (rc,2), (v(iv),1), (v(tv),2)]).
schemeS(26,[ (cn,3), (det,3), (pn,0), (rc,2), (v(iv),1), (v(tv),2)]).
schemeS(27,[ (cn,4), (det,4), (pn,0), (rc,2), (v(iv),0), (v(tv),3)]).
schemeS(28,[ (cn,4), (det,4), (pn,0), (rc,2), (v(iv),0), (v(tv),3)]).
schemeS(29,[ (cn,4), (det,4), (pn,0), (rc,2), (v(iv),0), (v(tv),3)]).
schemeS(30,[ (cn,4), (det,4), (pn,0), (rc,2), (v(iv),0), (v(tv),3)]).


/*========================================================================
   Scheme Update Tree Format
 
 Caution: 
 
 List format would only be generated 
 after calling predicate 'schemeGenerate'.

========================================================================  

 s(np(det, cn), vp(v(iv))) ;
 s(np(det, cn), vp(v(tv), np(det, cn))) ;
 s(np(det, cn), vp(v(tv), np(propn))) ;
 s(np(det, cn), vp(v(tv), np(np(det, cn), rc, v(tv), np(det, cn)))) ;
 s(np(det, cn), vp(v(tv), np(np(det, cn), rc, np(det, cn), v(tv)))) ;
 s(np(det, cn), vp(v(tv), np(np(det, cn), rc, v(iv)))) ;
 s(np(propn), vp(v(iv))) ;
 s(np(propn), vp(v(tv), np(det, cn))) ;
 s(np(propn), vp(v(tv), np(propn))) ;
 s(np(propn), vp(v(tv), np(np(det, cn), rc, v(tv), np(det, cn)))) ;
 s(np(propn), vp(v(tv), np(np(det, cn), rc, np(det, cn), v(tv)))) ;
 s(np(propn), vp(v(tv), np(np(det, cn), rc, v(iv)))) ;
 s(np(np(det, cn), rc, v(tv), np(det, cn)), vp(v(iv))) ;
 s(np(np(det, cn), rc, v(tv), np(det, cn)), vp(v(tv), np(det, cn))) ;
 s(np(np(det, cn), rc, v(tv), np(det, cn)), vp(v(tv), np(propn))) ;
 s(np(np(det, cn), rc, v(tv), np(det, cn)), vp(v(tv), np(np(det, cn), rc, v(tv), np(det, cn)))) ;
 s(np(np(det, cn), rc, v(tv), np(det, cn)), vp(v(tv), np(np(det, cn), rc, np(det, cn), v(tv)))) ;
 s(np(np(det, cn), rc, v(tv), np(det, cn)), vp(v(tv), np(np(det, cn), rc, v(iv)))) ;
 s(np(np(det, cn), rc, np(det, cn), v(tv)), vp(v(iv))) ;
 s(np(np(det, cn), rc, np(det, cn), v(tv)), vp(v(tv), np(det, cn))) ;
 s(np(np(det, cn), rc, np(det, cn), v(tv)), vp(v(tv), np(propn))) ;
 s(np(np(det, cn), rc, np(det, cn), v(tv)), vp(v(tv), np(np(det, cn), rc, v(tv), np(det, cn)))) ;
 s(np(np(det, cn), rc, np(det, cn), v(tv)), vp(v(tv), np(np(det, cn), rc, np(det, cn), v(tv)))) ;
 s(np(np(det, cn), rc, np(det, cn), v(tv)), vp(v(tv), np(np(det, cn), rc, v(iv)))) ;
 s(np(np(det, cn), rc, v(iv)), vp(v(iv))) ;
 s(np(np(det, cn), rc, v(iv)), vp(v(tv), np(det, cn))) ;
 s(np(np(det, cn), rc, v(iv)), vp(v(tv), np(propn))) ;
 s(np(np(det, cn), rc, v(iv)), vp(v(tv), np(np(det, cn), rc, v(tv), np(det, cn)))) ;
 s(np(np(det, cn), rc, v(iv)), vp(v(tv), np(np(det, cn), rc, np(det, cn), v(tv)))) ;
 s(np(np(det, cn), rc, v(iv)), vp(v(tv), np(np(det, cn), rc, v(iv)))).

========================================================================*/





/*========================================================================
   A Simple Scheme (Tree) Builder
   
             Usage:        y(s,X)

Caution: 
 Disabled for not making confusion for schemeGenerate.

========================================================================
y(s,X) :-
	y(np,A,_),
	y(vp,B,_),
	X=s(A,B).

	
y(np,X,1) :-
	X=np(det,cn).
	
	
y(np,X,2) :-
	X=np(propn).
	

y(np,X,3) :- 
	y(np,A1,B1),
	y(np,A2,B2),
	B1\==3, B2\==3 ->
	X= np(A1,rc,v(tv),A2).
	
	
y(np,X,4) :- 
	y(np,A1,B1),
	y(np,A2,B2),
	B1\==4, B2\==4 ->
	X= np(A1,rc,A2,v(tv)).

	
y(np,X,5) :- 
	y(np,A1,B1),
	B1\==5 ->
	X= np(A1,rc,v(iv)).	

	
y(vp,X,1) :-
	X=vp(v(iv)).

	
y(vp,X,2) :-
	y(np,A,_),
	X=vp(v(tv),A).
========================================================================*/

