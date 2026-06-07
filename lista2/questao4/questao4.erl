-module(biblioteca).
-export([start/0, server/1, cliente/2]).

start() ->
    AcervoInicial = [
        {"Ep", disponivel},
        {"metodol", disponivel},
        {"aaaaaa", disponivel}
    ],
    register(lib_server, spawn(biblioteca, server,[AcervoInicial] )).


server(Acervo) ->
    receive
        {request, From, consulta, Livro} ->
            Status = verificar_status(Livro, Acervo),
            From ! {response, Livro, Status},
            server(Acervo); 

        {request, From, emprestimo, Livro} ->
            case verificar_status(Livro, Acervo) of
                disponivel ->
                    NovoAcervo = atualizar_status(Livro, indisponivel, Acervo),
                    From ! {response, Livro, emprestado},
                    server(NovoAcervo);
                _ ->
                    From ! {response, Livro, indisponivel},
                    server(Acervo) 
            end;

        {request, From, devolucao, Livro} ->
            NovoAcervo = atualizar_status(Livro, disponivel, Acervo),
            From ! {response, Livro, devolvido},
            server(NovoAcervo)
            
    end.


cliente(Operacao, Livro) ->
    lib_server ! {request, self(), Operacao, Livro},
    
    receive
        {response, Livro, Status} ->
            io:format("Livro <~s>: <~p>~n", [Livro, Status])
    end.

verificar_status(Livro, Acervo) ->
    case lists:keyfind(Livro, 1, Acervo) of
        {Livro, Status} -> Status;
        false -> indisponivel
    end.

atualizar_status(Livro, NovoStatus, Acervo) ->
    lists:keystore(Livro, 1, Acervo, {Livro, NovoStatus}).




%1> spawn(biblioteca, cliente, [consulta, "Ep"]).
%%2> spawn(biblioteca, cliente, [emprestimo, "aaaaaa"]).
%%3> spawn(biblioteca, cliente, [consulta, "metodol"]).