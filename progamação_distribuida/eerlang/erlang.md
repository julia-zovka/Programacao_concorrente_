#Erlang

- sistemas críticos
-  ajustes dinâmicos


````
module(math1).
export([area/1]).

area({square, Side}) ->
  Side * Side;
area({rectangle, X, Y}) ->
  X * Y;
area({triangle, A, B, C}) ->
  S = (A + B + C)/2,
  math:sqrt(S*(S-A)*(S-B)*(S-C)).

area({circle, raio}) ->
  3.14*raio*raio.
````
chamando no terminal
````
> c(math1).
{ok,math1}
> Thing = {triangle, 6, 7, 8}.
{triangle,6,7,8}
> math1:area(Thing).
20.3332
````



## Funções basicas

- spawn - cria um novo processo para avaliar uma função e retorna seu pid
  ````
   Pid = spawn (Módulo, Função,ListArg)
  ````
- ! (send)- Envia uma mensagem para um processo
  ````
    Pid ! Message
  ````
- receive: Recebe uma mensagem de um processo
  
  Não tem ordem, pega a que ta primero na caixa de mensagem
````
receive
  Message1 [when Guard1] ->
    Actions1;
  Message2 [when Guard2] ->
    Actions2;
...
end
``````
## Terminação de processos
processos ligados---> quando um termina ele manda sinal para os processos a qual ele é ligado

{`EXIT`, exiting_pid, Reason}

- exit
    exit(normal)
  
    exit(reason)
link(pid)
unlink(pid)
## Registranod processos

- register(Nome, Pid) -> Associa o Nome ao processo Pid.

- unregister(Nome)-- >Remove a associação entre Nome e um processo.

- whereis(Nome)-- >Retorna o identificador de processo associado com Nome. Se nenhum processo estiver associado com Nome, retorna undefined.

- registered()-->Retorna uma lista de todos os nomes registrados.



##Funcionamento Cliente Servidor
````
-module(number_analyser).
-export([start/0,server/1]).
-export([add_number/2,analyse/1]).

start() ->                      //// criacao do servidor
  register(number_analyser, spawn(number_analyser, server, [nil])).


%%Funções de Interface.
add_number(Seq, Dest) -> /// numeor e pessoa
  request({add_number,Seq,Dest}).

analyse(Seq) -> /// numero
  request({analyse,Seq}).

request(Req) ->
  number_analyser ! {self(), Req},
  receive
    {number_analyser,Reply} ->
    Reply
end.
````

````
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

````

