(a) Qual a diferen ̧ca entre leitura destrutiva e n ̃ao destrutiva no modelo Linda?


(b) Por que o espa ̧co de tuplas reduz o acoplamento entre processos?


(c) Existe risco de starvation nesse sistema? Explique.


(d) Como garantir que duas workers n ̃ao processem a mesma tarefa?


(e) O modelo Linda  ́e mais pr ́oximo de mem ́oria compartilhada ou passagem de mensagens? Justifique.







a - read e try_read , se a tupla não estiver no espaço o processo  chamou read fica bloquado até que ela apareça no espaço


b -  Porque permite uma comunicação assincrona entre eles,  o produtor pode mandar varias tarefas antees que o leitor acesse uma delas e  diferentemente de ada  e occam os porcessos nao precisam conhecer a identidade dos outros


c - no meu codigo especifo acho que não mas poderia aconetecer no cenário em que varias operações são colocados no espaço de tuplas e como esse não ter uma ordem predefinida  poderia ter algum desses jobs que não seria tratado. Já olhand de um outro ponto de vista pode ter um starvation de workers no sentido que de varios workers tentam pegar o mesmo job e essa escolha é aleatória do compilador.


d - por casamento de padroes, o compilador decide quais das workesrs pega


e - memoria compartilhada uma vez que a tupla não tem um destinatarios especifico, a comunicação não é sincrona


* independencia em relacao a workers
* flexibilidade