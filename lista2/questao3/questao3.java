import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.locks.ReentrantLock;

class TupleSpace {
    private final List<Object[]> space = new ArrayList<>();
    private final ReentrantLock lock = new ReentrantLock();

    public void output(Object... fields) {
        lock.lock();
        try {
            space.add(fields);
            System.out.println("[ESPAÇO] out -> " + Arrays.toString(fields));
        } finally {
            lock.unlock();
        }
    }

    public Object[] tryInput(Object... pattern) {
        lock.lock();
        try {
            for (Object[] tuple : space) {
                if (matches(pattern, tuple)) {
                    space.remove(tuple); // Remoção destrutiva
                    return tuple;
                }
            }
            return null; // Caso não encontre, retorna null imediatamente sem travar
        } finally {
            lock.unlock();
        }
    }

    public Object[] tryRead(Object... pattern) {
        lock.lock();
        try {
            for (Object[] tuple : space) {
                if (matches(pattern, tuple)) {
                    return tuple; // Retorna a tupla encontrada mas mantém no ArrayList
                }
            }
            return null;
        } finally {
            lock.unlock();
        }
    }

    // Algoritmo de Casamento de Padrões (Pattern Matching do Linda)
    private boolean matches(Object[] pattern, Object[] tuple) {
        if (pattern.length != tuple.length) return false;
        
        for (int i = 0; i < pattern.length; i++) {
            Object p = pattern[i];
            Object t = tuple[i];
            
            if (p instanceof Class<?>) {
                if (!((Class<?>) p).isInstance(t)) {
                    return false;
                }
            } 
            // Se for um valor fixo, exige casamento exato
            else if (p != null && !p.equals(t)) {
                return false;
            }
        }
        return true;
    }
}

public class Main {
    public static void main(String[] args) throws InterruptedException {
        TupleSpace ts = new TupleSpace();

        Thread cliente = new Thread(() -> {
            System.out.println("\n--- Cliente Iniciando a Inserção de Tarefas ---");
            ts.output("job", 101, "SOMA", new int[]{10, 20});
            ts.output("job", 102, "MULT", new int[]{5, 6});
            ts.output("job", 103, "SOMA", new int[]{40, 2});
            ts.output("job", 104, "MULT", new int[]{7, 3});
            ts.output("job", 105, "SUB",  new int[]{50, 10}); // Tipo inválido para testar robustez
        });

        Runnable workerLogic = () -> {
            String workerName = Thread.currentThread().getName();
            System.out.println("[" + workerName + "] Iniciado.");

            // Executa ciclos de busca por tarefas no espaço
            for (int i = 0; i < 8; i++) {
                try { Thread.sleep(200); } catch (InterruptedException ignored) {}

                Object[] tarefa = ts.tryInput("job", Integer.class, String.class, int[].class);

                if (tarefa == null) {
                    System.out.println("[" + workerName + "] Nenhuma tarefa no espaço. Aguardando...");
                    continue;
                }

                int id = (Integer) tarefa[1];
                String tipo = (String) tarefa[2];
                int[] valores = (int[]) tarefa[3];
                
                System.out.println("[" + workerName + "] tryInput Sucesso -> Retirou Job #" + id + " (" + tipo + ")");

                Object resposta;
                if (tipo.equals("SOMA")) {
                    resposta = valores[0] + valores[1];
                } else if (tipo.equals("MULT")) {
                    resposta = valores[0] * valores[1];
                } else {
                    System.out.println("[" + workerName + "] Erro: Tarefa #" + id + " possui tipo incompativel.");
                    continue
                }

                try { Thread.sleep(300); } catch (InterruptedException ignored) {} 

                // Insere o resultado no formato: ("result", id, resposta)
                ts.output("result", id, resposta);
            }
        };

        Thread worker1 = new Thread(workerLogic, "Worker-1");
        Thread worker2 = new Thread(workerLogic, "Worker-2");

        Thread consultor = new Thread(() -> {
            try { Thread.sleep(2500); } catch (InterruptedException ignored) {} // Aguarda as threads agirem
            System.out.println("\n--- Consultor Iniciando Leituras  ---");

            for (int idBusca = 101; idBusca <= 105; idBusca++) {
                Object[] resultado = ts.tryRead("result", idBusca, Object.class);

                if (resultado != null) {
                    System.out.println("[CONSULTOR] tryRead Encontrado -> ID: " + resultado[1] + " | Resposta: " + resultado[2]);
                } else {
                    System.out.println("[CONSULTOR] Resultado do ID " + idBusca + " ainda nao esta pronto.");
                }
            }
        });

        // Dispara o ambiente distribuído em memória
        worker1.start();
        worker2.start();
        cliente.start();
        consultor.start();

        // Garante a sincronização do encerramento
        cliente.join();
        worker1.join();
        worker2.join();
        consultor.join();

    }
}