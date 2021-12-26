:- module(costcalc,[cost/2,costUF/2,costBC/2]).


/*========================================================================
   Cost Calculation
       Cost function calculates the cost of a phrase construction 
	   Zero means 'no cost' and the greater integer means the greater cost.
	   
	   Usage:           cost(List,Integer)
========================================================================*/


cost(A,B) :- cost2(A,C), sumlist(C,B).

cost2(A,C) :- costindex(A,B), cost1(A,B,C). 

cost1([],[],[]). 
cost1([(_,Y)|T1],[H2|T2],[H3|T3]) :- R1 is Y-H2, abs(R1,R2), R2=H3,cost1(T1,T2,T3). 

costindex(X,Y) :- costindex1(X,Z), reverse(Z,Y). 

costindex1([_],[1]).
costindex1([H1|T1],[H2|T2]) :- costindex1(T1,T2), length([H1|T1],H2). 


costUF([A,B,C,D,E,F,G,H,I],Cost):-

((I==1 )
->  
(A > 0 ->  Cost1 is A; Cost1 is 0),
(B > 0 ->  Cost2 is Cost1+B; Cost2 is Cost1),
(C > 0 ->  Cost3 is Cost2+C; Cost3 is Cost2),
(D > 0 ->  Cost4 is Cost3+D; Cost4 is Cost3),
(E > 0 ->  Cost5 is Cost4+E; Cost5 is Cost4),
(F > 0 ->  Cost6 is Cost5+F; Cost6 is Cost5),
(G > 0 ->  Cost7 is Cost6+G; Cost7 is Cost6),
(H > 0 ->  Cost  is Cost7+H; Cost  is Cost7)
;
Cost=100).



costBC([A,B,C,D,E,F,G,H,_],Cost):-
(A < 0 ->  Cost1 is A; Cost1 is 0),
(B < 0 ->  Cost2 is Cost1+B; Cost2 is Cost1),
(C < 0 ->  Cost3 is Cost2+C; Cost3 is Cost2),
(D < 0 ->  Cost4 is Cost3+D; Cost4 is Cost3),
(E < 0 ->  Cost5 is Cost4+E; Cost5 is Cost4),
(F < 0 ->  Cost6 is Cost5+F; Cost6 is Cost5),
(G < 0 ->  Cost7 is Cost6+G; Cost7 is Cost6),
(H < 0 ->  Cost  is Cost7+H; Cost  is Cost7).

	
	