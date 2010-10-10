#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int getIdleJobs ()
{
  FILE* file_loadavg = fopen("/proc/loadavg", "r");
  
  char line_loadavg[100];
  char jobs[10];
  char* tok;
  int word = 0;
  char running[5];
  char total[5];
  int jobs_attente;
    
  if (fgets(line_loadavg, 100, file_loadavg) != NULL)
  {
    tok = strtok(line_loadavg, " ");
    word = 0;
    while (tok != NULL)
    {
      word++;
      if (word == 4)
      {
	strcpy(jobs, tok);
	break;
      }
      tok = strtok(NULL, " ");
    }
    
    tok = strtok(jobs, "/");
    strcpy(running, tok);
    tok = strtok(NULL, "/");
    strcpy(total, tok);
    jobs_attente = atoi(total)-atoi(running);
  }
  else
  {
   perror("/proc/loadavg"); 
  } 
  
  fclose(file_loadavg);
  
  return jobs_attente;
}

float getIdleTime ()
{
  FILE* file_uptime = fopen("/proc/uptime", "r");
  char line_uptime[100];
  char total[50];
  char idle[50];
  int processors = sysconf(_SC_NPROCESSORS_CONF);
  float idletime;
  char* tok;

  if (fgets(line_uptime, 100, file_uptime) != NULL)
  {
    tok = strtok(line_uptime, " ");
    strcpy(total, tok);
    tok = strtok(NULL, " ");
    strcpy(idle, tok);    
    idletime = (atof(idle)/(atof(total)*processors))*100;
  }
  else
  {
   perror("/proc/uptime"); 
  } 
  fclose(file_uptime);
  return idletime;
}

int main (int argc, char** argv)	
{
  
  char o;
  int affiche_pourcentage = 0;
  int repeter = 0;
  int secondes = 1;
  
  
  while ((o = getopt(argc, argv, "ir:")) != -1)
  {
   switch (o)
   {
     case 'i':
       affiche_pourcentage = 1;
       break;
     case 'r':
       repeter = 1;
       secondes = atoi(optarg);
       break;
   }
  }
  
  printf("My PID: %d\n", getpid());
  
  if (repeter)
  {
    while (1)
    {
      printf("%d processes are sleeping\n", getIdleJobs());
      if (affiche_pourcentage) printf("Idle percentage: %f\n",getIdleTime());
      sleep(secondes);
    }
  }
  else
  {
    printf("%d processes are sleeping\n", getIdleJobs());
    if (affiche_pourcentage) printf("Idle percentage: %f\n",getIdleTime());
  }
  
}
