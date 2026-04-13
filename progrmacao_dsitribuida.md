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

3. Fluxo de dados
    Unidirecional - comunicação assíncrona
    Bidirecionaç - comunicação síncrona


4. Criação de Processos
    Estática (embarcados)
    Dinâmica- uso dinamico dos recurso  e balanceamento de carga