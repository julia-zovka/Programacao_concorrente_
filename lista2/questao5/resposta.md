(a) Por que o uso de entry e accept em Ada evita condi ̧c ̃oes de corrida nesse sistema?
(b) Esse sistema garante exclus ̃ao m ́utua? Explique como.
(c) O que aconteceria se duas tasks chamassem Solicitar Acesso ao mesmo tempo?
(d) Esse sistema pode sofrer deadlock? Justifique.
(e) Compare essa abordagem com o uso de mutex em linguagens como C ou Java.

a-  cada entry tem uma fila de espera 
b - sim, uma vez uqe a comunicação ocorre em rendevouz, encontro da calling e accepting task
c - 