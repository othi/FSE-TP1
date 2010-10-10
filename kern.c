#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int getMaxPid ()
{
  FILE* file_pid = fopen("/proc/sys/kernel/pid_max", "r");
  char line_pid[10];

  if (fgets(line_pid, 10, file_pid) != NULL)
  {
    fclose(file_pid);
    return atoi(line_pid);
  }
  else
   perror("/proc/pid_max"); 
}

char* getOsRelease ()
{
  FILE* file_pid = fopen("/proc/sys/kernel/osrelease", "r");
  char* line_osrls;
  line_osrls = malloc(50*sizeof(char));

  if (fgets(line_osrls, 50, file_pid) != NULL)
  {
    fclose(file_pid);
    return line_osrls;
  }
  else
    perror("/proc/sys/kernel/osrelease"); 
}

char* getVersion ()
{
  FILE* file_version = fopen("/proc/sys/kernel/version", "r");
  char* line_version;
  line_version = malloc(50*sizeof(char));

  if (fgets(line_version, 50, file_version) != NULL)
  {
    fclose(file_version);
    return line_version;
  }
  else
    perror("/proc/sys/kernel/version"); 
}


int main ()
{
 char* osrls = getOsRelease();
 char* version = getVersion();
 printf("Max PID: %d\n", getMaxPid()); 
 printf("OS Release: %s", osrls);
 printf("Version: %s", version);
 free(osrls);
 free(version);
 
}