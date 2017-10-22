


#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#include <limits.h>
#define MAX_SIZE 65536
void display(char *); 

void display(char *str) 
{
	
            	printf("%s ", str);
    	

	
}







int main(int argc, char *argv[])
{	
	int fileDesc;
	int index, returnVal;
	char * result;
	char buffer[64];
strcpy(buffer," ");
	fileDesc = open("/dev/mytime", O_RDONLY);
	
	if (fileDesc < 0)
	{
		perror("Device Failed to Open !!");
      		return -1;
   	}
        

	result = (char *)calloc(MAX_SIZE , sizeof(char));			
	returnVal = read(fileDesc, result,  MAX_SIZE);
printf("%s",buffer);	
	char* token = strtok(result, " ");
	while (token != NULL) 
	{
		display(token);
		token = strtok(NULL, " ");
	}

   	close(fileDesc);
   	return 0;
}
