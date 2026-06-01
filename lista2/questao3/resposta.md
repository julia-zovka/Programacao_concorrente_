(a) Qual a diferen ̧ca entre leitura destrutiva e n ̃ao destrutiva no modelo Linda?
(b) Por que o espa ̧co de tuplas reduz o acoplamento entre processos?
(c) Existe risco de starvation nesse sistema? Explique.
(d) Como garantir que duas workers n ̃ao processem a mesma tarefa?
(e) O modelo Linda  ́e mais pr ́oximo de mem ́oria compartilhada ou passagem de mensagens? Justifique.


a - read e try_read , se a tupla não estiver no espaço o processo  chamou read fica bloquado até que ela apareça no espaço
b -  Porque permite uma comunicação assincrona entre eles,  o produtor pode mandar varias tarefas antees que o leitor acesse uma delas e  diferentemente de ada os porcessos nao precisam conhecer a identidade dos outros
c -
d - por casamento de padroes, o compilador decide quais das workesrs pegA
e - memoria compartilhada uma vez que a tupla não tem um destinatarios especifico, a comunicação não é sincrona
