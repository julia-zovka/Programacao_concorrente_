package main

import (
	"fmt"
	"time"
)

func main() {
	

	type Chamado struct {
		ID   int
		Tipo string
    
	ch := make(chan Chamado, 10)   
	done := make(chan bool)          // Canal para os workers avisarem que terminaram

	go func() {
		tipos := []string{"Problema em laboratório", "Falha na rede", "Dúvida em sistemas acadêmicos"}

		for i := 0; i < 15; i++ {
			tipoAtual := tipos[i%3]
			ch <- Chamado{ID: i, Tipo: tipoAtual}
			fmt.Printf("[Helpdesk] Chamado #%d criado\n", i)
		}
		close(ch)
	}() 

	numWorkers := 3
	for i := 1; i <= numWorkers; i++ {
		go func(idAtendente int) {
			for chamado := range ch {
				time.Sleep(time.Millisecond * 300)
				fmt.Printf("Atendente %d resolveu chamado %d (tipo %s)\n", idAtendente, chamado.ID, chamado.Tipo)
			}
			done <- true
		}(i)
	}

	for i := 0; i < numWorkers; i++ {
		<-done // Bloqueia e espera o próximo worker terminar
	}

	fmt.Println("Sistema encerrado com sucesso.")
}