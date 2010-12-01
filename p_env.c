#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

char* getEnv (char* pid)
{
  int i;
  char* path = malloc(22*sizeof(char));
  sprintf(path, "/proc/%s/environ", pid);

  FILE* file_env = fopen(path, "r");

  free(path);

  if (file_env == NULL)
  {
    printf("%s is not a valid PID.\n", pid);
    exit(2);
  }
  char* line_env;
  line_env = malloc(2048*sizeof(char));

  if (fgets(line_env, 2048, file_env) != NULL)
  {
    fclose(file_env);
    for (i=0; !(line_env[i] == '\0' && line_env[i+1] == '\0'); i++)
        if (line_env[i] == '\0')
            line_env[i] = '\n';
    return line_env;
  }
  else
    perror(path);
  return NULL;
}


int main (int argc, char** argv)
{
    if (argc < 2)
    {
        printf("Usage: %s <pid>\n", argv[0]);
        exit(1);
    }

    char* env = getEnv(argv[1]);
    printf("%s\n", env);
    free(env);
    return 0;
}
