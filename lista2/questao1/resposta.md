(a) Qual o papel do channel bufferizado nesse sistema?


(b) O que aconteceria se o channel fosse n ̃ao-bufferizado?


(c) Existe risco de deadlock? Justifique.


(d) Esse sistema pode sofrer starvation? Em que situa ̧c ̃ao?


(e) Onde ocorre sincroniza ̧c ̃ao impl ́ıcita no Go nesse c ́odigo?






a - fdaz o suporte a comunicação assíncrono, no sentido de qunado não tiver atendente disponível no momoento de envio não bloquear o programa


b - No momento do envio de mais de uma mensagem pro mesmo canal o progrma pararia


c - Não, com a sincronização dos workers e com o canal principal nao exite risco de deadlock, o close e o range tomam esse cuidado além das funções de workgroups, wg.wait, wg.add e wg.done


d - Não, ta funcinando como uma fila


e - No proprio canal e no buffer, as operações de envio e leitura são nativas atômicas e o gerenciamento do tamanho do buffer também de forma que o produtor, uma vez que ve p canal cheio nao fica mandadno chamados pro lixo