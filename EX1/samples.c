#include <stdio.h>
#include <stdlib.h>

char *substr(const char *src, int randomNumber, int mm)
{
  int len = mm;

  char *res = (char *)malloc(sizeof(char) * (len + 1));

  for (int i = randomNumber; i < (randomNumber + mm) && (*(src + i) != '\0'); i++)
  {
    *res = *(src + i);
    res++;
  }

  *res = '\0';

  return res - len;
}

int main(int argc, char *argv[])
{

  FILE *f = fopen(argv[1], "r");
  char *n = argv[2];
  char *m = argv[3];

  int nn = atoi(n);
  int mm = atoi(m);

  fseek(f, 0, SEEK_END);
  int filesize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *string = malloc(sizeof(char) * (filesize + 1));

  char c;
  int i = 0;

  while ((c = fgetc(f)) != EOF)
  {
    string[i] = c;
    i++;
  }

  string[i] = '\0';

  fclose(f);

  int j = 0;
  int randomNumber;
  srand(0);

  while (j < nn)
  {
    randomNumber = 0 + rand() % (filesize - mm);
    char *res = substr(string, randomNumber, mm);
    printf(">%s<\n", res);
    j++;
  }

  return 0;
}
