package main
import (
    "fmt"
    "time"
	"sync"
)

//15 chamos
//buffer 10 lugares
//3 wor

func main (){
	var wg sync.WaitGroup

	type Chamado struct {
		ID int
		Tipo String
	}
	ch := make(chan Chamado,10)// buffer de 10 chamados

	go  func(){
		tipos := []string{"Problema em laboratório", "Falha na rede", "Dúvida em sistemas acadêmicos"}

		for i:= 0;i<15;i++{
			tipoAtual := tipos[i%3]

			ch <- Chamado{ID:i, Tipo:tipoAtual}
			fmt.Printf("[Helpdesk] Chamado #%d criado\n", i)

		}
		close(ch)		
	}


	///workers
	for i := 1; i <=3; i++ {
		wg.Add(1)
		
		// Inicia cada atendente em uma goroutine
		go func(idAtendente int) {
			// O loop range esvazia o canal até ele ser fechado pelo produtor
			for chamado := range ch {
				// Simula o tempo de atendimento
				time.Sleep(time.Millisecond * 300) 
				
				// Print exatamente como exigido no enunciado
				fmt.Printf("Atendente %d resolveu chamado %d (tipo %s)\n", idAtendente, chamado.ID, chamado.Tipo)
			}
			wg.Done()
		}(i) // Passa o ID do atendente como parâmetro para evitar problemas de concorrência com a variável 'i'
	}

	wg.Wait()
	fmt.Println("Sistema encerrado com sucesso.")


}