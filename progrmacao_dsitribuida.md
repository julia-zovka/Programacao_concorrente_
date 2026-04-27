# Programação distribuida --> Troca de Mensagens

Cada processo com sua memória e eles trocam mensagem entre si 

send e receive no canla de comunicação

Comunicação pode ser síncrona ou assícrona 

Assíncrona faz uso de um buffer para armazenar as mensagens

Envio das mensagens  é uma ação atômica --> rendevouz , o que ta pronto pra enviar e o que tá pronto pra receber


envio =  sem bloqueio

recebimento = com ou sem bloqueio


1. Síncrona ou Assincrona

2. Identificação dos processos, pra quem eu to mandando4

    Linha dedicada - sem custos de decifrar endereços
   
    Linha chaveada - custo de identificação
    
    Quadro de avisos - dispensa a identificação

4. Fluxo de dados
    Unidirecional - comunicação assíncrona
   
    Bidirecionaç - comunicação síncrona


6. Criação de Processos
    Estática (embarcados)
   
    Dinâmica- uso dinamico dos recurso  e balanceamento de carga





##Ada

Linguagem de departamento de defesa americano

Rendevouz 

1. Comunicação sincrona
2. duas tasks se encontram pra se comunicar
3. accepting task é a dona do rendevouz 
4. calling task tem que saber a identidade da accepting task e o nome do canal rendevouz

modelo assimétrico(identificação) --> programação de servidores

task = specification e body

task Buffer is


entry Append (I: in Integer);


entry Take (I: out Integer);


end Buffer;


task body Buffer is -->accepting task
begin

    accept Append(I:in Integer) do
       ..corpo do accept
    end Append;

end Buffer;


Buffer.Append(I); --> calling task
