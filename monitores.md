# Monitores

Exclusão mútua e sincronização de condição

ADT --> acesso por funções 

procedimentos x y z ja tem exclusão mútua implícita 4

não tem mais de uma instância executando aquele código, entra e para no wait

wait e signal só sinaliza enquanto no semáforo tem um contador implícito

wait supende e libera a exclusão mútua
signal acorda o primeiro processo da fila

```
Monitor Producer_Consumer_Monitor {
  int B [0..N-1];
  int In_Ptr = 0; int Out_Ptr = 0;
  int Count = 0;
  Condition Not_Full, Not_Empty;
```
```
void Append(int I) {
while (Count == N) {wait(Not_Full)};
B [In_Ptr] = I; Count = Count + 1;
In_Ptr = (In_Ptr + 1) % N;
signal(Not_Empty);
}
```
```
void Take(int I) {
while (Count == 0) {wait(Not_Empty)};
I = B[Out_Ptr]; Count = Count - 1;
Out_Ptr = (Out_Ptr + 1) % N;
signal(Not_Full);
}
}
```

Acesso aos dados fica restrito, não tenho diretamente acesso ao buffer e variáveis comuns -->> Monitor
```
Producer () {
int I;
while (TRUE) {
Produce(I); XXX
Append(I);
}
}
```
```
Consumer {
int I;
while (TRUE) {
Take(I);
Consume(I); XXX
}
}
```

3 semáforos VS 1 monitor


wait(c, rank) --> wait normal mas na hora de ser acordade é por prioridade por esse rank em ordem crescente
minrank(c) --> retorna o ranl do primeiro da fila
signal_all(c) --> acorda todos, problema de leitores escritores --> Banco de dados



Leitores e Escritores

Variáveis de status
• Readers === # de leitores lendo
• Writing ==true quando o processo está escrevendo


Variáveis de condição
• OK_to_Read
• OK_to_Write


Vários podem estar lendo ao mesmo tempo
```
Reader () {
while (TRUE) {
Start_Read;
Read_the_Data;
End_Read;
}
}
```
1 por vez, esse processo exclui o reader e outros writers
```
Writer () {
while (TRUE) {
Start_Write;
Write_the_Data;
End_Write;
}
}
```

```
Monitor Reader_Writer_Monitor {
int Readers = 0;
BOOL Writing = False;
Condition OK_to_Read, OK_to_Write;

void Start_Read {
while (Writing) {wait(OK_to_Read);};
Readers = Readers + 1;
}

void End_Read {
Readers = Readers - 1;
if (Readers==0) {signal(OK_to_Write);};
}

void Start_Write {
if (Readers > 0 || Writing)
{wait(OK_to_Write);};
Writing = True;
}

void End_Write {
Writing := False;
signal(OK_to_Write);
signal_all(OK_to_Read);
}
}
```

** escritores tem prioridade no end_Write, acorda ele antes de acordar os leitores



Emulação de semáfores com monitores
```
monitor Semaphore_Emulation {
int S = 0;

Condition Not_Zero;
procedure P {
while (S==0) {wait(Not_Zero);};
S = S - 1;
}

procedure V {
S = S + 1;
signal(Not_Zero);
}
}
```
