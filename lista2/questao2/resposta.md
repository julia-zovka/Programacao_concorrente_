(a) Qual a vantagem do uso de canais em rela ̧c ̃ao `a mem ́oria compartilhada em Occam?
(b) O comando ALT  ́e determin ́ıstico ou n ̃ao determin ́ıstico? Explique.
(c) Existe possibilidade de deadlock nesse sistema? Em que situa ̧c ̃ao?
(d) O sistema garante justi ̧ca (fairness) entre os produtores? Justifique.


a - Garante maior integridade a=nas mensagens uma vez que o usod e memória compartilhada gera incongruências uma vez que lida com operaões de leitura e escirta, e a eliminiação de race conditions.Os canais são unidirecionais e ponta a ponta, reduzindo o risco dessa mensagem mudar de cocnteudo durente sua propagação, sem que outros porcessos acessem
b - Não determinístico uma vez que ele monitora vários processos e se vários estiverem capacitados de receber ou enviar uma mensaegm é escolhido 1 naleatoriamente
c - Sim, o programa entra em alt mas nenhum dos porcessos tá pronto para enviar ou recceber 
d - Sim, o comando ALT garante fairness pro canal que tiver pronto


Linguagem Sincronaa