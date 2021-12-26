:- module(predicates,
			[init/2,
			pair2list/3,
			storeInputInfo/2,
			removeFirst/3,
			missingList/3,
			list_to_dupr/2,
			count_C_in_L/3,
			list_to_clist/2,
			fixSegmentation/2,
			init/2,
			initiate/1,
			show_constraints/1,
			eliminate_non_proper_candidates/2,
			choose_best_candidate/2,
			prescribe_candidate/1]).

:- chr_constraint init1/2.

init(X,Z) :- accRev(X,[],Y), init1(Y,Z). 

init1([],_)    <=> true.
init1([H|T],Z) <=> length(T,N),M is N+1, x(H,N,M,Z), init1(T,Z).

storeInputInfo(X,W) :- 
	accRev(X,[],Y), 
	storeInputInfo1(Y,Z), 
	accRev(Z,[],W).

storeInputInfo1([],[]).
storeInputInfo1([H1|T1],[(H1,H2,H3)|T2]):- 
	length([H1|T1],H3), 
	H2 is H3-1, 
	storeInputInfo1(T1,T2).


initiate(X):- findall(Y,initiate_(X,Y),Z), generate_x_scheme(Z).


generate_x_scheme([]):-!.
generate_x_scheme([[(cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F)]|T]):-
	assert(utteranceFixer:y_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,0),(vp,0),(s,0),0,0,0)),
	x_scheme((cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,0),(vp,0),(s,0),0,0,0),
	generate_x_scheme(T).


initiate_(X,Y) :- initiate__(X,Z), list_to_clist(Z,Y). 

initiate__([],[])   :- !.
initiate__([H|T],[Cat|Y]) :- 
	lex(H,[Cat]),
	initiate__(T,Y).
	
fixSegmentation(X,W) :- 
	accRev(X,[],Y), 
	fixSegmentation_(Y,Z), 
	accRev(Z,[],W).

fixSegmentation_([],[]).
fixSegmentation_([H1|T1],[(H1,H2)|T2]):- 
	length([H1|T1],H2), 
	fixSegmentation_(T1,T2).	


accRev([H|T],A,R):-  accRev(T,[H|A],R). 
accRev([],R,R). 


show_constraints([]) :-!.
show_constraints([[A,B,C,D,E,F,G,H,I,J,K,L]|T]):-
	writeln([(cn,A),(det,B),(pn,C),(rc,D),(v(iv),E),(v(tv),F),(np,G),(vp,H),(s,I),J,K,L]),
	show_constraints(T).


% Caution : Use this predicate after calling the 'eliminate_non_sentence_candidates'
choose_best_candidate([],[]) :-!.
choose_best_candidate([[A1,B1,C1,D1,E1,F1,G1,H1,I1,J1,K1,L1]],M) :-
	 M=[[A1,B1,C1,D1,E1,F1,G1,H1,I1,J1,K1,L1]].
choose_best_candidate([[A1,B1,C1,D1,E1,F1,G1,H1,I1,J1,K1,L1],[A2,B2,C2,D2,E2,F2,G2,H2,I2,J2,K2,L2]|T],M) :-
	(
	
	( costBC([A1,B1,C1,D1,E1,F1,G1,H1,I1],BC1),
	  costBC([A2,B2,C2,D2,E2,F2,G2,H2,I2],BC2),
	 BC2 =< BC1,
	 J1 =<J2  	
	)

	 ->
	 choose_best_candidate([[A1,B1,C1,D1,E1,F1,G1,H1,I1,J1,K1,L1]|T],M)
	 ;
	 choose_best_candidate([[A2,B2,C2,D2,E2,F2,G2,H2,I2,J2,K2,L2]|T],M)
	).




eliminate_non_proper_candidates([],[]) :-!.
eliminate_non_proper_candidates([[A,B,C,D,E,F,G,H,I,J,K,L]|T],M) :-
	(  (J==100 ; (J==0,K==0,L==0))
	 ->
	 eliminate_non_proper_candidates(T,M)
	 ;
	 (eliminate_non_proper_candidates(T,N),
	 M=[[A,B,C,D,E,F,G,H,I,J,K,L]|N])
	).


pair2list(X,Y,[(X,Y)]).


removeFirst(X,[X|Tail],Tail) :- !.
removeFirst(X,[Head|Tail],[Head|NewTail]):-
removeFirst(X,Tail,NewTail).


missingList([],A,A):-!.
missingList(_,[],[]):-!.
missingList([H1|T1],L2,L3):-
	memberchk(H1,L2),!,
	removeFirst(H1,L2,HL12),
	missingList(T1,HL12,L3).
missingList([_|T1],L2,L3):-
	missingList(T1,L2,L3).


list_to_dupr([],[]):-!.	
list_to_dupr([H],[H]):-!.	
list_to_dupr([H,H|T],A):-
	list_to_dupr([H|T],L),!,
	A=L.
list_to_dupr([H1,H2|T],A):-
	list_to_dupr([H2|T],L),
	A=[H1|L].	



/*========================================================================
        Caution:       Change the first argument of
                      'list_to_clist_' with the outcome 
                      of lexicon:generateAllLexicon(Lt).       
========================================================================*/
list_to_clist(A,B):-
	    list_to_clist_([cn, det, pn, rc, v(iv), v(tv)],A,B).

list_to_clist_([],_,[]):-!.
list_to_clist_([H|T],A,B):-
	count_C_in_L(H,A,N),
	list_to_clist_(T,A,C),
	B=[(H,N)|C].

	
count_C_in_L(_,[],0):-!.
count_C_in_L(E,[T|L],C):-
	count_C_in_L(E,L,R),
    (E=T ->
     C is R+1
     ;
     C is R).	
	
/*========================================================================
		Writing implicit prescribed suggestions in the 
		best candidate for 'Missing & Extra' finder        
========================================================================*/
	
prescribe_candidate([[A1,_,_,_,_,_,_,_,_,_,_,_]]) :- 
    A1<0 ,
    abs(A1,ABS),
	write('Missing '),
	write(ABS),
	write(' Common Noun(s)'),
	nl,
	fail.
prescribe_candidate([[_,B1,_,_,_,_,_,_,_,_,_,_]]) :- 
    B1<0 ,
    abs(B1,ABS),
	write('Missing '),
	write(ABS),
	write(' Determiner(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,C1,_,_,_,_,_,_,_,_,_]]) :- 
    C1<0 ,
    abs(C1,ABS),
	write('Missing '),
	write(ABS),
	write(' Proper Noun(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,D1,_,_,_,_,_,_,_,_]]) :- 
    D1<0 ,
    abs(D1,ABS),
	write('Missing '),
	write(ABS),
	write(' Relative Clause(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,E1,_,_,_,_,_,_,_]]) :- 
    E1<0 ,
    abs(E1,ABS),
	write('Missing '),
	write(ABS),
	write(' Intransitive Verb(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,_,F1,_,_,_,_,_,_]]) :- 
    F1<0 ,
    abs(F1,ABS),
	write('Missing '),
	write(ABS),
	write(' Transitive Verb(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,_,_,G1,_,_,_,_,_]]) :- 
    G1<0 ,
    abs(G1,ABS),
	write('Missing '),
	write(ABS),
	write(' Noun Phrase(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,_,_,_,H1,_,_,_,_]]) :- 
    H1<0 ,
    abs(H1,ABS),
	write('Missing '),
	write(ABS),
	write(' Verb Phrase(s)'),
	nl,
	fail.									
prescribe_candidate([[A1,_,_,_,_,_,_,_,_,_,_,_]]) :- 
    A1>0 ,
	write('Extra '),
	write(A1),
	write(' Common Noun(s)'),
	nl,
	fail.
prescribe_candidate([[_,B1,_,_,_,_,_,_,_,_,_,_]]) :- 
    B1>0 ,
	write('Extra '),
	write(B1),
	write(' Determiner(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,C1,_,_,_,_,_,_,_,_,_]]) :- 
    C1>0 ,
	write('Extra '),
	write(C1),
	write(' Proper Noun(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,D1,_,_,_,_,_,_,_,_]]) :- 
    D1>0 ,
	write('Extra '),
	write(D1),
	write(' Relative Clause(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,E1,_,_,_,_,_,_,_]]) :- 
    E1>0 ,
	write('Extra '),
	write(E1),
	write(' Intransitive Verb(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,_,F1,_,_,_,_,_,_]]) :- 
    F1>0 ,
	write('Extra '),
	write(F1),
	write(' Transitive Verb(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,_,_,G1,_,_,_,_,_]]) :- 
    G1>0 ,
	write('Extra '),
	write(G1),
	write(' Noun Phrase(s)'),
	nl,
	fail.
prescribe_candidate([[_,_,_,_,_,_,_,H1,_,_,_,_]]) :- 
    H1>0 ,
	write('Extra '),
	write(H1),
	write(' Verb Phrase(s)'),
	nl,
	fail.
prescribe_candidate([[0,0,0,0,0,0,0,0,_,_,_,_]]) :- 
	write('No suggestion'),
	nl,!,fail. 		