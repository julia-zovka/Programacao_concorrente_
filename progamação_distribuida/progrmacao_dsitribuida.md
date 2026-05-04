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
```
task Buffer is
entry Append (I: in Integer);
entry Take (I: out Integer);
end Buffer;
````

````
task body Buffer is -->accepting task
begin
    accept Append(I:in Integer) do
       ..corpo do accept
    end Append;
end Buffer;
````
````
Buffer.Append(I); --> calling task
````

Select edntro do body, pra criar condições para escolher que chamada vai receber

````
task body Buffer is ...
begin loop
select
when Count < N =>
accept Append(I:in Integer) do
B(In_Ptr) := I;
end Append;
Count := Count + 1;
In_Ptr := (In_Ptr + 1) mod N;
or
when Count > 0 =>
accept Take(I: out Integer) do
I := B(Out_Ptr);
end Take;
Count := Count - 1;
Out_Ptr := (Out_Ptr + 1) mod N;
end select;
end loop;
end Buffer;
````
- else ...
- delay  ...
- terminate

accept aninhados resolve o problema de ordem


criar task dinamicamente


** Ada e Go **

ada usa entries e go canais na definição da task

ada usa entry(definição) e accept(body) nas calling e accepting tasks


Ada
````
task Server is
entry GetData(Item : out Integer);
end Server;
task body Server is
begin
accept GetData(Item : out Integer) do
Item := 42; -- Rendezvous action
end GetData;
end Server;
````
Go
````
package main
import "fmt"
func main() {// canal é o ponto de rendezvous
getData := make(chan int)
go func() { // equivalente à task Server, quando chamada
getData <- 42 // equivalente ao Accept
}()
data := <-getData // Cliente bloqueia até servidor enviar
fmt.Println(data)
}
````
