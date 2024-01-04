#include <stdlib.h>
#include <stdio.h>
#include <sys/syscall.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

void converter(char *f)
{
  char *fDuplicate = strdup(f);
  int len = strlen(fDuplicate);
  fDuplicate[len - 4] = '\0';
  strcat(fDuplicate, ".epub");

  execlp("pandoc", "pandoc", f, "-o", fDuplicate, "--quiet", (char *)NULL);
}


void createProcesses(char *f)
{
  int pid;

  if ((pid = fork()) < 0) // Pegar no Child Process
  {
    printf("[%d] converting %s \n", pid, f);
    perror("fork: ");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) // Child Process Executa o Programa
  {
    converter(f);
    perror("execlp: ");
    exit(EXIT_FAILURE);
  }

  if (pid >= 1) // Parent Process Espera
  {
    printf("[pid%d] converting %s \n", pid, f);
  }
}

int main(int argc, char *argv[])
{
  for (int i = 0; i < argc - 1; i++) // Criar procesos
  {
    createProcesses(argv[i + 1]);
  }

  for (int i = 0; i < argc; i++) // Fechar procesos
  {
    wait(NULL);
  }

  system("zip ebooks *.epub");
  return (1);
}

