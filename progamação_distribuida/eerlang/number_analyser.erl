-module(number_analyser).
-export([start/0,server/1]).
-export([add_number/2,analyse/1]).
-export([main/0]).
%% -export([lookup/2,insert/3]).
main() -> start(), add_number([1,2,3,4],'Jose'), analyse([1,2,3,4]).
start() ->
    register(number_analyser,
             spawn(number_analyser, server, [nil])).

%%Funções de Interface.
add_number(Seq, Dest) ->
    request({add_number,Seq,Dest}).
analyse(Seq) ->
    request({analyse,Seq}).
request(Req) ->
    number_analyser ! {self(), Req},
    receive
        {number_analyser,Reply} ->
            Reply
    end.

%%Servidor.
server(Table) ->
    receive
        {From, {analyse,Seq}} ->
           Result = lookup(Seq,Table),
           From ! {number_analyser, Result},
           server(Table);
        {From, {add_number, Seq, Dest}} ->
            From ! {number_analyser, ack},
            server(insert(Seq, Dest, Table))
    end.


lookup(What, [{What, Value}|_]) -> Value;
lookup(What, [_|T]) -> lookup(What, T);
lookup(_,_) -> undefined.

insert(Seq, Dest, Table) -> [{Seq,Dest}|Table].

