////erro

package main

import "fmt"

func main() {
    const N = 5
    // Isso cria um canal com capacidade N. 
    // Ele age EXATAMENTE como o seu buffer circular em Ada.
    buffer := make(chan int, N)

    // (Equivalente ao entry Append)
    go func() {
        for i := 1; i <= 10; i++ {
            buffer <- i // Bloqueia automaticamente se o buffer estiver cheio (Count == N)
            fmt.Printf("Produzido: %d\n", i)
        }
    }()

    //(Equivalente ao entry Take
    for i := 1; i <= 10; i++ {
        val := <-buffer // Bloqueia automaticamente se o buffer estiver vazio (Count == 0)
        fmt.Printf("Consumido: %d\n", val)
    }
}
