% Student exercise profile
:- set_prolog_flag(occurs_check, error).        % disallow cyclic terms
:- set_prolog_stack(global, limit(8 000 000)).  % limit term space (8Mb)
:- set_prolog_stack(local,  limit(2 000 000)).  % limit environment space


% 12.
% a. Define a predicate to add after every element from a list, the divisors of that number.


% insrtDiv(N:number, Div:number, L:list, R:list)
% Flow model: insert_div(i, i, i, o)
insrtDiv(N, Div, L, L) :- 
    Div > N div 2.
insrtDiv(N, Div, L, [Div|R]) :- 
    N mod Div =:= 0,
    NewDiv is Div + 1,
    insrtDiv(N, NewDiv, L, R).
insrtDiv(N, Div, L, R) :-
    NewDiv is Div + 1,
    insrtDiv(N, NewDiv, L, R).
% Mathematical model:
% insrtDiv(l1...ln, Div, L) =	L,	if Div > N div 2
% 								[Div, insrtDiv(l2...ln, Div + 1, L)],	if N % Div = 0
% 								[insrtDiv(l2...ln, Div + 1, L)],	otherwise(if N % Div != 0)


% divisors(L:list, R:list)
% Flow model: divisors(i, o)
divisors([], []).
divisors([H|T], [H|R]) :-
    divisors(T, TR),
    insrtDiv(H, 2, TR, R).
% Mathematical model:
% divisors(l1...ln) =	[],	if n = 0
% 						[insrtDiv(l1, 2), divisors(l2...ln)], otherwise


%------------------------------------------------------------------------------------------------------------------------


% b. For a heterogeneous list, formed from integer numbers and list of numbers, 
% define a predicate to add in every sublist the divisors of every element.
% Eg.: [1, [2, 5, 7], 4, 5, [1, 4], 3, 2, [6, 2, 1], 4, [7, 2, 8, 1], 2] =>
% [1, [2, 5, 7], 4, 5, [1, 4, 2], 3, 2, [6, 2, 3, 2, 1], 4, [7, 2, 8, 2, 4, 1], 2]


% hList(L:list, R:list)
% Flow model: hList(i, o)
hList([], []).
hList([H|T], [HR|TR]) :- 
    is_list(H), !,
    divisors(H, HR),
    hList(T, TR).
hList([H|T], [H|TR]) :-
    hList(T, TR).
% Mathematical model:
% hList(l1...ln) =	[],	if n = 0
%					[divisors(l1), hList(l2...ln)],	if is_list(l1) = True
% 					[l1, hList(l2...ln)], otherwise


