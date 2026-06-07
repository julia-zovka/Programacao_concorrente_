
## prova 1

- Programas concorrente tem que lidar com multiplos processos rodam simultaneamente, a comunicação entre eles, race consition, garantir que o sistema não tenha starvation ou  deadlock coisas que não são preocupações de progrmas sequenciais

- Monitores são um mecanisno nativo de java que garante a exclusão mutuas de processos atraves de metodos syncronized e signal e wait  fazedno que somente um deles entre na região crítica apesar de não ter essa estruttura nativa em c ela pode ser simulada ocm mutex, dadno lock e unlock ao entrrar e sair dessa região  conditions

- Rendevouz é um mecanismo de encontro de processos em ada, uma linguagem de comunicaão sincrona e unidirecional. A accepting task aceita uma requisição por vez dentro do
  loop depois é chamada recursivamente de formar a ficar disponível para outras requisições

- Monitores X troca de mensagem(go, occam, ada, erlang)  Entender se [e um projeot de um sistema  dsitribuisdo, se sim, usar troca de mensagem

- a - sim pois garante que leitores e escritores não acessem a memória ao mesmo tempo

- b - não pois os signal ok_to_write não garantem uma ordem de qual escritor  vai acessar o documento, se tiver varias escritores essa escolha vai ser aleatoria. A minha correçaõ seria implemntar algo parecifdo com uma fila 



## prova 2

-  Evitar race condition, garantir exclusão mutua para que somente um processo consiga acessar aquela região critica por vez, garantir que não haja deadlock ou starvation e que o sistema funcione  justamente parar todos os processos

-  filosofos em ada -- task, entry, body accept x ??
-  task controladora dos garfos como server e filosofos como clientes, cada filodos como por vez
  
````
ask body Coordenador_Garfos is
    -- Array para rastrear se o garfo está disponível (True) ou ocupado (False)
    Garfos : array (0 .. 4) of Boolean := (others => True);
    
    -- Funções auxiliares para mapear os garfos vizinhos do filósofo
    Left  : Integer;
    Right : Integer;
begin
    loop
        select
            -- Só aceita o pedido se AMBOS os garfos do filósofo estiverem livres
            when Garfos(Id) and Garfos((Id + 1) rem 5) =>
                accept Pegar_Garfos (Id : in Integer) do
                    Garfos(Id) := False;
                    Garfos((Id + 1) rem 5) := False;
                end Pegar_Garfos;
        or
            -- Sempre aceita a devolução dos garfos
            accept Largar_Garfos (Id : in Integer) do
                Garfos(Id) := True;
                Garfos((Id + 1) rem 5) := True;
            end Largar_Garfos;
        end select;
    end loop;
end Coordenador_Garfos;
````

````
task type Filosofo (Id : Integer);

task body Filosofo is
begin
    loop
        -- 1. O filósofo está pensando
        Pensar; 

        -- 2. Tenta pegar os garfos (Rendez-vous de solicitação)
        -- Se os garfos não estiverem disponíveis, o filósofo fica bloqueado aqui
        Coordenador_Garfos.Pegar_Garfos(Id);

        -- 3. O filósofo está comendo (Se passou do ponto acima, ele tem ambos os garfos)
        Comer;

        -- 4. Devolve os garfos (Rendez-vous de liberação)
        Coordenador_Garfos.Largar_Garfos(Id);
    end loop;
end Filosofo;

-- Criação das instâncias dos filósofos
F0 : Filosofo(0);
F1 : Filosofo(1);
F2 : Filosofo(2);
F3 : Filosofo(3);
F4 : Filosofo(4);
````



-  Os leitores e escritotes querem acessar esse espaço de memoria compartilhada mas mais de um escritor ao mesmo tempo ou um escrtor e um leiotr gera incngruencias nessa memorial. Nesse sentido o objetivo  dos  monitoeres fazer com que apens um escritor escreva por vez e que leitores e escritores nap acessem essa regoão simultaneamente. Dessa forma podierai implementar metodos m=synchronized em java com operacaoes de wait e signal ou mutex e condition em c de forma a implemtar os metodso star read, end read, star wirte e end wirte 



## Prova 3 

- É o problema de mais de um processo acessando a mesma região ou um outro porcesso.Nos preocupamos nesse sentido quando lidando com problems concorrente de multiplos processos existindo paralelamente.A solução com monitores se da pelo fato qeu wue eles são nativamente implemntam exclusçoa mutua por meio de conditions e wait e signal

- O modelo de concorrencia baseado em loinda se dá num espaço de tuplas, a operacoa de output coloca tuplas nesse espaço e input tira. A comunicaçõa entre os porcessos ocorre de maneira assincrona.Como vantagem tem essa flecxibilidade em relacãço a que processo vai pegar a tupla, diferente mente de ada, occam e erlang que os processos precisam saber da identidade do outro. De desvantagm seria a possivel inativade de um dos workers uma vez que quando mais de um workers tenta da input numa tupla a escolha de qual dos workers consegue pegala é aleatorioa entçao um worker pode ficar sempre nessa situaçao de tentar pegar algo e não processar nada.







===== monitores em java =====

- metodos synchronized com wait e signal
- lock e condition --- parecidissima a implemntaco em c = condition e mutex
