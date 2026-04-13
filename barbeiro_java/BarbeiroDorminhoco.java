public class BarbeiroDorminhoco {
    public static void main(String[] args) {
        Barbearia barbearia = new Barbearia(3);

        new Barbeiro(barbearia).start();

        for (int i = 1; i <= 10; i++) {
            new Cliente(barbearia, i).start();

            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
