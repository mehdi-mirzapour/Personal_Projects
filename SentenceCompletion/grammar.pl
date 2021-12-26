:- module(grammar,[x/4, x/5, x/8]).
:- chr_constraint x/4, x/5, x/8.

/*========================================================================
   Initialization
                  Add lexicon entries to inputs   
========================================================================*/
x(H,A,B,SII) <=> lex(H,[Cat|[]])| x(H,Cat,A,B,SII).
x(H,A,B,SII) <=> lex(H,[Cat|T])| x(H,[Cat|T],A,B,SII).

x(_,[],_,_,_)      <=> true.
x(H,[Cat|T],A,B,SII) <=> x(H,T,A,B,SII), x(H,Cat,A,B,SII).


/*========================================================================
   Grammar Rules
   
 Usage: 
 x(Lex,Cat,S,E,PosList,Dummy/NotDummy,Cost, storeInputInfo)
 x(L,Cat,S,E,PL,Dstat,Co,SII)
 d 'stands for'  Dummy
 nd 'stands for' NotDummy		
========================================================================*/

% det, cn -> np(det,cn) 
x(L1,det,S1,E1,SII),
x(L2,cn,S2,E2,SII) ==>
atom_concat(L1,' ',LI),
atom_concat(LI,L2,L3),
pair2list(S1,E1,PL1),
pair2list(S2,E2,PL2),
append(PL1,PL2,PLT),
cost(PLT,Co),
x(L3,np(det(L1),cn(L2)),S1,E2,PLT,nd,Co,SII).


% pn ->  np(propn)
x(L,pn,S,E,SII) <=>
x(L,np(propn(L)),S,E,[(S,E)],nd,0,SII).


% np, rc, v[iv] -> np(np,relc(rc,v(iv))) 
x(L1,C1,S1,_,PL1,nd,_,SII),
x(L2,rc,S2,E2,SII),
x(L3,v(iv),S3,E3,SII) ==>
'=..'(C1,[A1|_]), A1==np, 
pair2list(S2,E2,PL2),
pair2list(S3,E3,PL3),
intersection(PL1,PL2,PL12), PL12=[],
intersection(PL1,PL3,PL13), PL13=[],
intersection(PL2,PL3,PL23), PL23=[] |
atom_concat(L1,' ',LI1),
atom_concat(LI1,L2,LI3),
atom_concat(LI3,' ',LI4),
atom_concat(LI4,L3,L4),
append(PL1,PL2,PLI1),
append(PLI1,PL3,PLT),
cost(PLT,Co),
x(L4,np(C1,relc(rc(L2),v(iv(L3)))),S1,E3,PLT,nd,Co,SII). 


% np, rc, np, v[tv] -> np(np,relc(rc,np,v(tv))) 
x(L1,C1,S1,_,PL1,nd,_,SII),
x(L2,rc,S2,E2,SII),
x(L3,C2,_,_,PL2,nd,_,SII),
x(L4,v(tv),S4,E4,SII) ==>
'=..'(C1,[A1|_]), A1==np,
'=..'(C2,[A2|_]), A2==np, 
pair2list(S2,E2,PL3),
pair2list(S4,E4,PL4),
intersection(PL1,PL2,PL12), PL12=[],
intersection(PL1,PL3,PL13), PL13=[],
intersection(PL1,PL4,PL14), PL14=[], 
intersection(PL2,PL3,PL23), PL23=[],
intersection(PL2,PL4,PL24), PL24=[],
intersection(PL3,PL4,PL34), PL34=[] |
atom_concat(L1,' ',LI1),
atom_concat(LI1,L2,LI3),
atom_concat(LI3,' ',LI4),
atom_concat(LI4,L3,LI5),
atom_concat(LI5,' ',LI6),
atom_concat(LI6,L4,L5),
append(PL1,PL3,PLI1),
append(PLI1,PL2,PLI2),
append(PLI2,PL4,PLT),
cost(PLT,Co),
x(L5,np(C1,relc(rc(L2),C2,v(tv(L4)))),S1,E4,PLT,nd,Co,SII). 


% np, rc, v[tv], np -> np(np,relc(rc,v(tv),np)) 
x(L1,C1,S1,_,PL1,nd,_,SII),
x(L2,rc,S2,E2,SII),
x(L3,v(tv),S3,E3,SII),
x(L4,C4,_,E4,PL4,nd,_,SII)  ==>
'=..'(C1,[A1|_]), A1==np,
'=..'(C4,[A4|_]), A4==np, 
pair2list(S2,E2,PL2),
pair2list(S3,E3,PL3),
intersection(PL1,PL2,PL12), PL12=[],
intersection(PL1,PL3,PL13), PL13=[],
intersection(PL1,PL4,PL14), PL14=[], 
intersection(PL2,PL3,PL23), PL23=[],
intersection(PL2,PL4,PL24), PL24=[],
intersection(PL3,PL4,PL34), PL34=[] |
atom_concat(L1,' ',LI1),
atom_concat(LI1,L2,LI3),
atom_concat(LI3,' ',LI4),
atom_concat(LI4,L3,LI5),
atom_concat(LI5,' ',LI6),
atom_concat(LI6,L4,L5),
append(PL1,PL2,PLI1),
append(PLI1,PL3,PLI2),
append(PLI2,PL4,PLT),
cost(PLT,Co),
x(L5,np(C1,relc(rc(L2),v(tv(L3)),C4)),S1,E4,PLT,nd,Co,SII). 


% v[iv] ->  vp(v(iv))
x(L,v(iv),S,E,SII) ==>
x(L,vp(v(iv(L))),S,E,[(S,E)],nd,0,SII).


% v[tv], np -> vp(v(tv),np) 
x(L1,v(tv),S1,E1,SII),
x(L2,C2,_,E2,PL2,nd,_,SII) ==>
pair2list(S1,E1,PL1),
intersection(PL1,PL2,PL12), PL12=[],
'=..'(C2,[A2|_]), A2==np |
atom_concat(L1,' ',LI),
atom_concat(LI,L2,L3),
append(PL1,PL2,PLT),
cost(PLT,Co),
x(L3,vp(v(tv(L1)),C2),S1,E2,PLT,nd,Co,SII).


% np, vp -> s(v(tv),np) 
x(L1,C1,S1,_,PL1,nd,_,SII),
x(L2,C2,_,E2,PL2,nd,_,SII) ==>
intersection(PL1,PL2,PL12), PL12=[],
'=..'(C1,[A1|_]), A1==np,
'=..'(C2,[A2|_]), A2==vp |
atom_concat(L1,' ',LI),
atom_concat(LI,L2,L3),
append(PL1,PL2,PLT),
cost(PLT,Co),
x(L3,s(C1,C2),S1,E2,PLT,nd,Co,SII).


/*========================================================================
   Extra S() Rules Elimination   
========================================================================*/

x(_,Cat1,_,_,PL1,_,_,SII2) \ x(_,Cat2,_,_,PL2,_,_,SII2) <=>
'=..'(Cat1,[A1|_]), A1==s, length(PL1,M1), 
'=..'(Cat2,[A2|_]), A2==s, length(PL2,M2), M1>M2  | true.

x(_,Cat1,_,_,PL1,_,Co1,SII2) \ x(_,Cat2,_,_,PL2,_,Co2,SII2) <=>
'=..'(Cat1,[A1|_]), A1==s, length(PL1,M1), 
'=..'(Cat2,[A2|_]), A2==s, length(PL2,M2), M1==M2, Co1<Co2  | true.
