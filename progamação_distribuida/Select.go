package main
import (
    "fmt"
    "time"
)
func main() {
    // um canal para cada entry
    ch1 := make(chan string)
    ch2 := make(chan string)

    go func() {
        time.Sleep(2000 * time.Millisecond)
        ch1 <- "from channel 1"
    }()

    go func() {
        time.Sleep(2000 * time.Millisecond)
        ch2 <- "from channel 2"
    }()

    // Wait for both channels, handling whichever is ready first
    for i := 0; i < 2; i++ {
        time.Sleep(100 * time.Millisecond)
        select {
        case msg1 := <-ch1:
            fmt.Println(msg1)
        case msg2 := <-ch2:
            fmt.Println(msg2)
        case <-time.After(2 * time.Second):
            fmt.Println("Timed out waiting for result")
//        default:
            // No message available right now, do something else
//            fmt.Println("No message, moving on")
        }
    }
}


