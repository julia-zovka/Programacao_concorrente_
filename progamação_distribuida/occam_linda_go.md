# Occam

canais unidirecionais -  diferente de go

criação de processos estática

canais ligam exatamente dois processos

## canais

CHAN OF BYTE comm 

CHAN OF BYTE keyboard :

CHAN OF BYTE screen


**SEQ**
````
WHILE TRUE
  BYTE ch :
  SEQ
    keyboard ? ch // ch recebe umminput do teclado
    screen ! ch // mostra ch na tela
    comm ! ch // envia ch para comunicação
````
? espera aquele input

! envia a mensagem


**PAR ---> roda em paralelo**

````
CHAN OF BYTE comm :
PAR
  WHILE TRUE
    BYTE ch :
    SEQ
      keyboard ? ch
      comm ! Ch

  WHILE TRUE
    BYTE ch :
    SEQ
      comm ? ch
      display ! ch
````


**ALT**
````
CHAN OF BYTE comm1 :
CHAN OF BYTE comm2 :
WHILE TRUE
  BYTE ch :
  ALT
    comm1 ? ch
    comm2 ? ch
````


**CALCULADORA DE MATRIZES**

versão 1
````
WHILE TRUE
  SEQ
    north ? x
    south ! x
    east ? sum
    sum := sum + a * x // a é o conteúdo inicializado em cada nó - valores da matriz 1
    west ! sum

````

versão 2
````
north ? x
WHILE TRUE
  SEQ
    PAR
      south ! x
      east ? sum
      temp := a * x
    PAR
      west ! sum + temp
      north ? x
````
as operações dentro do PAR podem acontcer a qualquer momento



# Linda

Espaço de tuplas (TS) ----> quadro de comunicação

casamento de padrões nas assinaturas das tuplas

out (1,2) ---> in(integer,integer)

(’A’,1)(character,integer)


- Output(T) - o que eu mando
- Input(T)- remove tupla T, suspende se não houver casamento do padrão   - o que eu espero
- Read(T)
- Try_Input(T) -- se a resposta não estiver disponível eu passo, input não bloqueante
- Try_Read(T)

# Go

canais uni e bidirecionais
````
comm := make(chan string)
keyboard := make(<-chan int)
screen := make(chan-> int)
````

canais que suportam buffer
````
ch := make(chan string, 2)
````

