(a) Por que o modelo de processos isolados do Erlang evita problemas de concorrˆencia como race conditions?


(b) O servidor implementado  ́e sequencial ou concorrente? Explique o impacto disso no desempenho.


(c) Se dois clientes solicitarem o empr ́estimo do mesmo livro ao mesmo tempo, o que acontece no seu
modelo?


(d) Existe possibilidade de deadlock nesse sistema? Justifique.


(e) Como vocˆe modificaria o sistema para que cada requisi ̧c ̃ao fosse tratada por um processo separado?






a - Porque eles náo compartilham memória entáo náo existe a possibilidade de dois processos quererem acessar a mesma informa;áo ao mesmo tempo. A comunicação entre os porcessos ocorre de maneira assíncrona.Cada processo tem seu endereçamento e garbage collector


b - Sequencial, ele processa uma mensagem por vez e depois chama ele proprio de novo para tratar outra


c - alguma das duas requisições vai ser tratada primeiro que a outra então para o segundo cliente o livro fica indisponível


d - Não, os cliente enviam as requisições de forma assincrnias e ficam esperando até que o servidor processe  mas o servidor não fica esperando uma vez que não faz requisiçõe spara outros processos


e - Tornando o servidor apenas um man in the middle que levaria as requisições para outros porcesoss de fomra que várias requisições de emprestimo consulta e devolução seriam tratadas paralelamente.Porém lele ficaria esperando a resposta com o novo acervo que esse processo filho faria de forma a não gerar inconsistencias no banco de dados



comunicação assíncrona e unidirecional


troca de mensagens --> processo que  vai receber ! mensagem enviada

```
From ! {number_analyser, Result}
````


casmento de padrão  nos receive também--- parecido com linda