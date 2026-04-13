class Barbearia {
    private final int cadeiras;
    private int clientesEsperando = 0;

    private boolean barbeiroOcupado = false;

    public Barbearia(int cadeiras) {
        this.cadeiras = cadeiras;
    }

    public synchronized void entrarBarbearia(int id) throws InterruptedException {
        // Se não houver cadeiras, cliente vai embora
        if (clientesEsperando == cadeiras) {
            System.out.println("Cliente " + id + " foi embora (sem vaga).");
            return;
        }

        clientesEsperando++;
        System.out.println("Cliente " + id + " chegou. Esperando: " + clientesEsperando);

        notifyAll(); // acorda barbeiro se estiver dormindo

        // Espera até ser chamado (barbeiro disponível)
        while (barbeiroOcupado) {
            wait();
        }

        // Vai para o corte
        clientesEsperando--;
        barbeiroOcupado = true;

        System.out.println("Cliente " + id + " está cortando cabelo.");

        notifyAll(); // avisa o barbeiro que pode iniciar corte
    }

    public synchronized void proximoCliente() throws InterruptedException {
        // Espera até haver clientes
        while (clientesEsperando == 0) {
            System.out.println("Barbeiro dormindo...");
            wait();
        }

        // Espera até algum cliente sentar na cadeira do barbeiro
        while (!barbeiroOcupado) {
            wait();
        }

        cortar();

        // Finaliza atendimento
        barbeiroOcupado = false;
        System.out.println("Barbeiro terminou um corte.");

        notifyAll(); // libera próximo cliente
    }

    private void cortar() throws InterruptedException {
        Thread.sleep(2000); // simula corte
    }
}

