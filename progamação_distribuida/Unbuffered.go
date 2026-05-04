package main
import (
    "fmt"
    "time"
)
func main() {
    // Cria um canal sem buffer (Go também permite criar canais com Buffer):
    ch := make(chan string)

    // cria uma thread e ela começa a rodar:
    go func() {
        fmt.Println("Sending...") 
        // envia "hello" somente quando outro processo puder receber
        ch <- "hello"
        fmt.Println("Sent!")
    }()
    time.Sleep(time.Second) // gera uma espera
    // Ao receber, desbloqueia o processo que envia o hello
    msg := <-ch
    fmt.Println("Received:", msg)
}
// Saída:
// Sending...
// [pausa]
// Sent!
// Received: hello
