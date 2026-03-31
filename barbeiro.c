/* Barbearia com duas portas (entrada e
saída) e algumas cadeiras (espera)
 Barbeiro atende um cliente de cada vez
 Se faltam clientes, o barbeiro dorme
 Se um cliente chega, ele acorda o
barbeiro para que corte seu cabelo
 Cliente dorme nas cadeiras de espera se
o barbeiro está ocupado
*/
Clientes e barbeiros são processos
Barbearia é o monitor
Relação cliente/servidor(barbeiro)


get_haircut
get_next_custumer
 finished_cut


Monitor Barbearia_Monitor {
  int cadeiras [N];
  int In_Ptr = 0; // proximo que chega
  int Out_Ptr = 0; // proximo atendido
  int Count = 0;
  Condition Not_Full, Not_Empty, Corte_Finalizado;;


void chega_cliente(int Id) {
  while (Count == N) {wait(Not_Full)}; // not full = tem lugar pra mais cliente
  cadeiras[In_Ptr] = Id; // joga na fila
  In_Ptr = (In_Ptr + 1) % N;
  Count++;
  signal(Not_Empty); // acorda barbeirooo

  wait(Corte_Finalizado); 

}

void corta_cabelo() { // tira da fila
  while (Count == 0) {wait(Not_Empty)}; // espera chegar clinte, barbeiro dorme
  int Id = cadeiras[Out_Ptr]; 
  Out_Ptr = (Out_Ptr + 1) % N;
  Count--;
  signal(Not_Full);
  return Id; //corta o cabelo dese cliente id 
}

void finished_cut() {
    // Avisa ao cliente que estava sendo atendido que ele pode sair
    signal(Corte_Finalizado);
}

  
  
}

Producer_cliente (int Id) { // chega  an fila, appende
  while (TRUE) {
    Barbearia_Monitor.chega_cliente(Id);
//espera corte
  }
}

Consumer_barbeiro () { //libera lugares na fila
int cliente_atual;
while (TRUE) {
cliente_atual = Barbearia_Monitor.corta_cabelo();
corta_cabelo(cliente_atual);
Barbearia_Monitor.finished_cut();
}
}
