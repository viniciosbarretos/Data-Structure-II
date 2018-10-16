Objetivos
- Utilização de CPU:
    - Manter a CPU tão ocupada quanto possível. Maximizar

- Vazão (throughput):
    - Número de processos que completam sua execução por unidade de tempo. Maximizar
    
- Tempo de Uso:
    - Tempo necessário para executar um processo particular. Minimizar
    

Geração dos processos
    - Aleatórios
    - Contínuos
    - Usuário não deve escolher entre criar ou não (Slide 39)
    - Novos processos são gerados a cada ciclo de quantum
    
Características
    - Quantum ideal: 20 a 50
    - Quando um processo é bloqueado (dependência de E/S, processo aleatório), outro deve ser executado. (CPU sempre ocupada)
    
    
Pendências
    - Quando uma interrupção de E/S ocorre, o escalonador deve decidir por: i) executar o processo que estava esperando esse evento; ii) continuar executando o processo que já estava sendo executado ou; iii) executar um terceiro processo que esteja pronto para ser executado. (??????)
    

