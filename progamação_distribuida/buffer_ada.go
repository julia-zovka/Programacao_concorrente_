/*task Buffer is
	entry Append (I: in Integer);
	entry Take (I: out Integer);
end Buffer;
task body Buffer is ...
	begin loop
	select
	when Count < N =>
	accept Append(I:in Integer) do
	B(In_Ptr) := I;
	end Append;
	Count := Count + 1;
	In_Ptr := (In_Ptr + 1) mod N;
	or
	when Count > 0 =>
	accept Take(I: out Integer) do
	I := B(Out_Ptr);
	end Take;
	Count := Count - 1;
	Out_Ptr := (Out_Ptr + 1) mod N;
	end select;
	end loop;
end Buffer;
*/

package main
import "fmt"

func Buffer(n int, appendChan chan int, takeChan chan chan int) {
	b := make([]int, n)
	count := 0
	inPtr := 0
	outPtr := 0
	for {
		var activeAppend chan int
		var activeTake chan chan int
		// --- The "Guards" (Logic equivalent to Ada's 'when') ---
		if count < n {
			activeAppend = appendChan
		}
		if count > 0 {
			activeTake = takeChan
		}
		select {
		case val := <-activeAppend:
			// Equivalent to 'accept Append'
			b[inPtr] = val
			inPtr = (inPtr + 1) % n
			count++
			fmt.Printf("Appended: %d | Count: %d\n", val, count)
		case responseChan := <-activeTake:
			// Equivalent to 'accept Take'
			val := b[outPtr]
			outPtr = (outPtr + 1) % n
			count--
			responseChan <- val // Send the value back to the caller
			fmt.Printf("Took: %d | Count: %d\n", val, count)
		}
	}
}

func main() {
	// Setup channels
	appendChan := make(chan int)
	takeReq := make(chan chan int)
	// Start the Buffer task (goroutine)
	go Buffer(5, appendChan, takeReq)
	// Simulate a Producer
	go func() {
		for i := 1; i <= 10; i++ {
			appendChan <- i
		}
	}()
	// Simulate a Consumer
	for i := 1; i <= 10; i++ {
		reply := make(chan int)
		takeReq <- reply
		fmt.Println("Consumer received:", <-reply)
	}
}

