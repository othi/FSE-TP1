#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main ()	
{
  FILE* file = fopen("/proc/cpuinfo", "r");
  
  char line[100];
  int nbProcesseurs = 0;
  char modele[75];
  char tailleCache[10];
  
  
  while (fgets(line, 100, file) != NULL)
  {
    if (strstr(line, "processor") != NULL)
    {
      nbProcesseurs++;
      continue;
    }
    if (strlen(tailleCache) <= 0)
    {
      if (strstr(line, "cache size") != NULL)
      {
	strcpy(tailleCache, line+13);
	continue;
      }
    }
    if (strlen(modele) <= 0)
    {
     if (strstr(line, "model name") != NULL)
     {
      strcpy(modele, line+13); 
      continue;
     }
    }
  }
  
  printf("Nombre de processeurs: %d\n", nbProcesseurs);
  printf("Nom du modèle: %s", modele);
  printf("Taille du cache: %s", tailleCache);

  fclose(file);
  
}
