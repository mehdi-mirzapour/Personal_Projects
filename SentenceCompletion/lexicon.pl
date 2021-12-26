:- module(lexicon,[
			lex/2,
			generateAllLexicon/1
			]).

/*========================================================================
   Lexicon
   
             Usage:        lex(Lexicon Entry,List[Category])
========================================================================*/

lex(boy,[cn]).
lex(girl,[cn]).
lex(child,[cn]).
lex(teacher,[cn]).
lex(man,[cn]).
lex(magician,[cn]).

lex(john,[pn]).
lex(peter,[pn]).

lex(the,[det]).
lex(some,[det]).
lex(a,[det]).
lex(every,[det]).
lex(no,[det]).

lex(laughs,[v(iv)]).
lex(shouts,[v(iv)]).

lex(helped,[v(tv)]).
lex(admires,[v(tv)]).
lex(adopts,[v(tv)]).

lex(who,[rc]).
lex(that,[rc]).


/*========================================================================
   Generate all Lexicon Categories
   
             Usage:        generateAllLexicon(Lt)
========================================================================*/

generateAllLexicon(Lt) :-
	generateAllLexicon_(Ls),
	lex2List(Ls,Lc),
	sort(Lc,Lt).

generateAllLexicon_(Ls) :-
    findall(X,lex(_,X),L),
    sort(L,Ls).


lex2List([],[]) :-!.    
lex2List([[H]|T],L1) :-
	lex2List(T,L2),
	L1=[H|L2].
lex2List([[H1,H2]|T],L1) :-
	lex2List(T,L2),
	L1=[H1,H2|L2].	
	
	
			