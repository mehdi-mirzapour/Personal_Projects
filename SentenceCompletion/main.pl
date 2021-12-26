:- use_module(library(chr)).


:- use_module(grammar).
:- use_module(predicates).
:- use_module(costcalc).
:- use_module(lexicon).
:- use_module(dummybuilder).
:- use_module(utteranceFixer).

:- chr_constraint start/1.

%Lexicon entry for lists to be fixed.
start(X)   <=>   storeInputInfo(X,Z), init(X,Z).

findMissingExtra(X) :- 
	retractall(y_scheme(_,_,_,_,_,_,_,_,_,_,_,_)),
	set_prolog_flag(chr_toplevel_show_store,false),
	initiate(X),
	findall([A,B,C,D,E,F,G,H,I,J,K,L],
			y_scheme((cn,A), (det,B), (pn,C), (rc,D), (v(iv),E), (v(tv),F), (np,G), (vp,H), (s,I),J,K,L),
			Z),
	nl,
	writeln('Rule(s):'),
	show_constraints(Z),
%	nl,
%	writeln('Possible Candidate(s):'),
	eliminate_non_proper_candidates(Z,Z1),
%	show_constraints(Z1),
	nl,
	writeln('Best Candidate(s):'),
	choose_best_candidate(Z1,Z2),
	show_constraints(Z2),
	nl,
	writeln('Suggestions:'),
	prescribe_candidate(Z2),			
	retractall(y_scheme(_,_,_,_,_,_,_,_,_,_,_,_)).
	
	