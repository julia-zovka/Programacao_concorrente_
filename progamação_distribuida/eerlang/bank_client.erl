-module(bank_client).
-export([ask/1, deposit/2, withdraw/2]).

call_bank(Msg) ->
    bank_server ! {self(), Msg},
    receive
      {bank_server, Reply} -> 
         Reply
    end.

ask(Who) -> call_bank({ask, Who}).

deposit(Who, Amount) ->  call_bank({deposit, Who, Amount}).

withdraw(Who, Amount) -> call_bank({withdraw, Who, Amount}).


%%head_office() -> 'bank@ericsson.se'.
%%
%%call_bank(Msg) ->
%%    Headoffice = head_office(),
%%    monitor_node(Headoffice, true),
%%    {bank_server, Headoffice} ! {self(), Msg},
%%    receive
%%      {bank_server, Reply} ->
%%          monitor_node(Headoffice, false),
%%          Reply;
%%      {nodedown, Headoffice} ->
%%          no
%%    end.

