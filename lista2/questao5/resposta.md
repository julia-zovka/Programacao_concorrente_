(a) Por que o uso de entry e accept em Ada evita condi ̧c ̃oes de corrida nesse sistema?


(b) Esse sistema garante exclus ̃ao m ́utua? Explique como.


(c) O que aconteceria se duas tasks chamassem Solicitar Acesso ao mesmo tempo?


(d) Esse sistema pode sofrer deadlock? Justifique.


(e) Compare essa abordagem com o uso de mutex em linguagens como C ou Java.






a-  cada entry simula um canal e tem uma fila de espera e o accept do servidor garante que somente um processo acesse aquele recuro compartilhado


b - sim, uma vez que somente um dos medicos consegue acessar o equipamento por vez por meio do accept


c - uma delas e tratado primiero pela entry e a outra fica bloqueada esperando esse recurso na fila de espera da entry


d - Não, não existe cenário de espera circular ou outra situação que resultaria em deadlock.A task controladora não faz chamadas externas e não exitem dependencias com outros processos


e - o rendevouz em ada garante exclusáo mutua dos recursos assim como o mutex em c, sinalizando o encontro entre dois processos e liberando e avisando para os ooutros quando a ação acaba similar ao unlock do mutex.Como difernça tem o fato da fila, nas entries existe uma ordem de acordo com a chegada e nos mutexes tem um notify que não garante esse ordem



similaridades com go

- uma task seria uma funcao-- goroutine 
- entry -- canal
- rendevouz seria um caanl noa buferizado do go
