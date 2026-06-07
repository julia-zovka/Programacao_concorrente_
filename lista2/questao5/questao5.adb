with Ada.Text_IO; use Ada.Text_IO;

procedure Controle_UTI is

    task Controladora_Equipamento is
        entry Solicitar_Acesso(Nome : in String);
        entry Liberar_Acesso(Nome   : in String);
    end Controladora_Equipamento;

    task body Controladora_Equipamento is
        begin loop
            accept Solicitar_Acesso(Nome : in String) do
                Put_Line(Nome & " solicitou acesso");
                Put_Line(Nome & " recebeu acesso");
            end Solicitar_Acesso; 

            accept Liberar_Acesso(Nome : in String) do
                Put_Line(Nome & " liberou o equipamento");
            end Liberar_Acesso;

        end loop;
   end Controladora_Equipamento;

   task type Profissional(Nome_Id : access constant String);

   task body Profissional is
   begin
      Controladora_Equipamento.Solicitar_Acesso(Nome_Id.all);
      delay 2;
      Controladora_Equipamento.Liberar_Acesso(Nome_Id.all);
   end Profissional;

   Nome_1 : aliased constant String := "Dr. Joao";
   Nome_2 : aliased constant String := "Dr. Maria";
   Nome_3 : aliased constant String := "Dr. Carlos";

   Med1 : Profissional(Nome_1'Access);
   Med2 : Profissional(Nome_2'Access);
   Med3 : Profissional(Nome_3'Access);

begin
   null;
end Controle_UTI;