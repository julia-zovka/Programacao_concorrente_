
## prova 1

- Programas concorrente tem que lidar com multiplos processos rodam simultaneamente, a comunicação entre eles, race consition, garantir que o sistema não tenha starvation ou  deadlock coisas que não são preocupações de progrmas sequenciais

- Monitores são um mecanisno nativo de java que garante a exclusão mutuas de processos fazedno que somente um deles entre na região crítica apesar de não ter essa estruttura nativa em c ela pode ser simulada ocm mutex ,
- dadno lock e unlock ao entrrar e sair dessa região

- Rendevouz é um mecanismo de encontro de processos em ada, uma linguagem de comunicaão sincrona e unidirecional. A accepting task aceita uma requisição por vez dentro do
  loop depois é chamada recursivamente de formar a ficar disponível para outras requisições

- Monitores X troca de mensagem(go, occam, ada, erlang) ???


- a - sim pois garante que leitores e escritores não acessem a memória ao mesmo tempo


- b - não pois os signal ok_to_write não garantem uma ordem de qual escritor  vai acessar o documento, se tiver varias escritores essa escolha vai ser aleatoria. A minha correçaõ seria implemntar algo parecifdo com uma fila 



## prova 2

-  Evitar race condition, garantir exclusão mutua para que somente um processo consiga acessar aquela região critica por vez, garantir que não haja deadlock ou starvation e que o sistema funcione  justamente parar todos os processos

-  filosofos em ada -- task, entry, body accept x ??

-  Os leitores e escritotes querem acessar esse espaço de memoria compartilhada mas mais de um escritor ao mesmo tempo ou um escrtor e um leiotr gera incngruencias nessa memorial. Nesse sentido o objetivo  dos  monitoeres fazer com que apens um escritor escreva por vez e que leitores e escritores nap acessem essa regoão simultaneamente.
-  I sso é implemntado aprtir de condition e OK_to_read e OK_towirtre que dentro dos metodos são gerenciadsa com wait e signal ou signal all


## Prova 3 

- É o problema de mais de um processo acessando a mesma região ou um outro porcesso.Nos preocupamos nesse sentido quando lidando com problems concorrente de multiplos processos existindo paralelamente.A solução com monitores se da pelo fato qeu wue eles são nativamente implemntam exclusçoa mutua por meio de conditions e wait e signal

- O modelo de concorrencia baseado em loinda se dá num espaço de tuplas, a operacoa de output coloca tuplas nesse espaço e input tira. A comunicaçõa entre os porcessos ocorre de maneira assincrona
