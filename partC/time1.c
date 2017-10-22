#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include <limits.h>
#include <sys/time.h>
#define MAX_SIZE 65536
#define N 10
#define MAX_LENGTH 80

/*void display(char *); 
//char* findStatus(int);

void display(char *str) 
{
	
            	printf("%s ", str);
    	

	
}
*/






int main()
{	struct timeval gtodTimes[N];
	int fileDesc;
	int i;
	int bytes_read;
//	int index, returnVal;
//	char * result;
//	char buffer[64];
//strcpy(buffer," ");
char *result[N];
//char *result = calloc(N,sizeof(char*));
	fileDesc = open("/dev/mytime", O_RDONLY);
	
	if (fileDesc < 0)
	{
		perror("Device Failed to Open !!");
      		return -1;
   	}
	
        for(i=0;i<N;i++)
{
gettimeofday(&gtodTimes[i],0);
result[i]=(char*) calloc(N,MAX_SIZE);
bytes_read = read(fileDesc,result[i],MAX_SIZE);
if(bytes_read== -1)
{
perror("Error Reading");
}

}
close(fileDesc);
for(i=0;i<N;i++)
{
printf("(%d)\n",(i+1));
printf("GETTIMEOFDAY:%ld%ld\n",gtodTimes[i].tv_sec,gtodTimes[i].tv_usec);
printf("PROCCLOCKTIMES::%s\n",result[i]);
}
//	result = (char *)calloc(MAX_SIZE , sizeof(char));			
//	returnVal = read(fileDesc, result,  MAX_SIZE);
//printf("%s",buffer);	
//	char* token = strtok(result, " ");
//	while (token != NULL) 
//	{
//		display(token);
//		token = strtok(NULL, " ");
//	}

   	
 	return 0;
}
