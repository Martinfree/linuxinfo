#include <stdio.h>
#include <stdlib.h>
#include <linux/sysinfo.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <time.h>

#define LITTLE_BUFFER 256
#define BIG_BUFFER 2048

char BUFFER[BIG_BUFFER];
char T[BIG_BUFFER];

struct Comp{
    char version[BIG_BUFFER];
    char cpuinfo[BIG_BUFFER];
    char partitions[LITTLE_BUFFER];
    char processors;
    //char memory[BIG_BUFFER];
    long time;
    long time_now;
    char memory[LITTLE_BUFFER];
    char processes[LITTLE_BUFFER];
};

struct sysinfo info;
struct Comp stats;

void version(char* c){
    FILE *file;
    file = fopen("/proc/version", "r");
    
    if (file == NULL)
    {
    
        printf("File not open");
    }else{
            while (fgets(BUFFER, sizeof(BUFFER),file) != NULL){}
         }
    strcpy(c,BUFFER);
    fclose(file);
}

int cpuinfo(char* c){
    FILE *file;
    file = fopen("/proc/cpuinfo","r");
    int i=0;
    int processors = 0;

    if (file == NULL)
    {
        printf("File not open");
    }else{
            while (fgets(BUFFER,sizeof(BUFFER),file))
            {
                if (i==0 && strstr(BUFFER,"model name")){strcpy(c,BUFFER);i++;}
                else if (i==1 && strstr(BUFFER,"cpu MHz")){strcat(c,BUFFER);i++;}
                if (strstr(BUFFER,"processor")){processors++;}
                }
        }
    fclose(file);
    
    return processors;
}

void partitions(char* c){
    FILE* file;
    file = fopen("/proc/partitions","r");

    if (file == NULL)
    {
        printf("File not open");
    }else{
        while (fgets(BUFFER,sizeof(BUFFER),file))
        {
            strcat(c,BUFFER);
        }
    }
}


/*void general(){
 
    
  
    stats.time = info.uptime/60;
    
    time_t T= time(NULL);
    struct  tm tm = *localtime(&T);
    printf("System Date is: %02d/%02d/%04d\n",tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900);
    printf("System Time is: %02d:%02d:%02d\n",tm.tm_hour, tm.tm_min, tm.tm_sec);

    printf("Boot : %u minutes ago\n",stats.time);
    printf("%s\n%s\nlogical processors: %d\n",stats.version,stats.cpuinfo,stats.processors);
    printf("major minor #blocks name\n%s\n",stats.partitions);
    printf("Total memory : %luMb\nAvailable memory : %luMb\nMemory used : %luMb\n",stats.memory[0]/1024,stats.memory[1]/1024,stats.memory[2]/1024);
    printf("Processes now : %u\n",stats.processes);

}*/
