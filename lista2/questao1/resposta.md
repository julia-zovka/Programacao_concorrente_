

(a) Qual o papel do channel bufferizado nesse sistema?
(b) O que aconteceria se o channel fosse n ̃ao-bufferizado?
(c) Existe risco de deadlock? Justifique.
(d) Esse sistema pode sofrer starvation? Em que situa ̧c ̃ao?
(e) Onde ocorre sincroniza ̧c ̃ao impl ́ıcita no Go nesse c ́odigo?


a - fdaz o suporte a comunicação assíncrono, no sentido de qunado não tiver atendente disponível no momoento de envio não bloquear o programa
b - No momento do envio de mais de uma mensagem pro mesmo canal o progrma pararia
c - 
d - 