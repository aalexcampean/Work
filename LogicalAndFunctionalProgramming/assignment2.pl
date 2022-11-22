% Student exercise profile
:- set_prolog_flag(occurs_check, error).        % disallow cyclic terms
:- set_prolog_stack(global, limit(8 000 000)).  % limit term space (8Mb)
:- set_prolog_stack(local,  limit(2 000 000)).  % limit environment space

% Your program goes here


% 1.
% a. Write a predicate to determine the lowest common multiple of a list formed from integer numbers.


%myGCD(A - first number/integer, B - second number/integer, R - result/integer)
%myGCD(i,i,o) - flow model
myGCD(A,B,R):-
    A=:=B,
    R is A.
myGCD(A,B,R):-
    A>B,
    A1 is A-B,
    myGCD(A1,B,R).
myGCD(A,B,R):-
    B>A,
    B1 is B-A,
    myGCD(A,B1,R).
%mathematical model:
%myGCD(A,B)	= A, if A = B
%			= myGCD(A-B,B,R), if A > B
%			= myGCD(A,B-A,R), if B > A


%myLCM(A - first number/integer, B - second number/integer, R - result/integer)
%myLCM(i,i,o) - flow model
myLCM(A,B,R):-
    A=:=B,
    R is A.
myLCM(A,B,R):-
    myGCD(A,B,R1),
    R is A*B/R1.
%mathematical model:
%myLCM(A,B)	= A, if A = B
%			= A*B/myGCD(A,B), otherwise


%myListLCM(L - list, R - result/integer)
%myListLCM(i,o) - flow model
myListLCM([E],E).
myListLCM([H|T],R):-
    myListLCM(T,R1),
    myLCM(H,R1,R).
%mathematical model:
%myListLCM([l1,l2,...,ln])	= l1, if n = 1
%							= myLCM(l1,myListLCM([l2,...,ln])), otherwise


% b. Write a predicate to add a value v after 1-st, 2-nd, 4-th, 8-th, ... element in a list.

%findPowerPos(N - number/integer)
%findPowerPos(i) - flow model
findPowerPos(1).
findPowerPos(N):-
    N mod 2 =:= 0,
    N1 is N/2,
    findPowerPos(N1).
%mathematical model:
%findPowerPos(N)	= true, if N = 1
%					= false, if N%2 /= 0
%					= false, if N = 0
%					= findPowerPos(N/2), otherwise


%myListAddition(L - list, V - value/integer, P - position/integer, R - result list)
%myListAddition(i,i,i,o) - flow model
myListAddition([],_,_,[]).
myListAddition([H|T],V,P,[H|[V|T1]]):-
    CurrentP is P,
    findPowerPos(CurrentP),
    NextP is P+1,
    myListAddition(T,V,NextP,T1).
myListAddition([H|T],V,P,[H|T1]):-
    NextP is P+1,
    myListAddition(T,V,NextP,T1).
%mathematical model:
%myListAddition([l1,l2,...,ln],V,P)	= [], if n = 0
%									= [l1,V,myListAddition([l2,...,ln],V,P+1)], if findPowerPos(P) is True
%									= [l1,myListAddition([l2,...,ln],V,P+1)], if findPowerPos(P) is False
%									

myListAdditionWrapper(L,V,R):-
    myListAddition(L,V,1,R).


%myListLCM([2,3,6,10],R)
%myListAdditionWrapper([1,2,34,56,78,89,900,34,32,5],0,R)
