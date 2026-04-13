class Barbeiro extends Thread {
    private final Barbearia barbearia;

    public Barbeiro(Barbearia barbearia) {
        this.barbearia = barbearia;
    }

    public void run() {
        try {
            while (true) {
                barbearia.proximoCliente();
            }
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
}
