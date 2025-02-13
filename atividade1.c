#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void executar_comando(const char *cmd, const char *arg) {
    execl(cmd, arg, (char *)NULL);
    perror("execl falhou");
    exit(1);
}

int main() {
    pid_t f1, f2, n1, n2, n3, n4;

    printf("Processo P1 (Pai) PID: %d\n", getpid());

    f1 = fork();  // Cria F1
    if (f1 == 0) {
        // Processo F1
        n1 = fork();  // Cria N1
        if (n1 == 0) {
            executar_comando("/bin/ls", "ls");  // Lista arquivos do diretório
        }

        n2 = fork();  // Cria N2
        if (n2 == 0) {
            executar_comando("/usr/bin/whoami", "whoami");  // Mostra o usuário atual
        }

        // Espera N1 e N2 terminarem
        wait(NULL);
        wait(NULL);
        printf("Processo F1 (PID: %d, Pai: %d) finalizado\n", getpid(), getppid());
        exit(0);
    }

    f2 = fork();  // Cria F2
    if (f2 == 0) {
        // Processo F2
        n3 = fork();  // Cria N3
        if (n3 == 0) {
            executar_comando("/bin/date", "date");  // Mostra a data atual
        }

        n4 = fork();  // Cria N4
        if (n4 == 0) {
            executar_comando("/usr/bin/uptime", "uptime");  // Mostra tempo de atividade do sistema
        }

        // Espera N3 e N4 terminarem
        wait(NULL);
        wait(NULL);
        printf("Processo F2 (PID: %d, Pai: %d) finalizado\n", getpid(), getppid());
        exit(0);
    }

    // Processo P1 espera F1 e F2 terminarem
    wait(NULL);
    wait(NULL);
    printf("Processo P1 (Pai) PID: %d finalizado\n", getpid());

    return 0;
}
