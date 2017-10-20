#include<stdio.h>
#include<stdlib.h>

#include<unistd.h>
#include<linux/unistd.h>
#include<time.h>
#define _NR_sys_myfoo 326
int main()
{
int y;
struct timespec current_time={0,0};
int u;
//current_time = (struct timespec *)malloc(1*sizeof(struct timespec));

//long s;
//int n=0;
//&current_time = &n;
//void * p=current_time;
y = syscall(326);
u = syscall(_NR_sys_myfoo,&current_time);
//long s=myfoo(&current_time);

printf("syscall return value :%d\n%d",u,y);
printf("Time : %10i.%09i\n",(int)current_time.tv_sec,(int)current_time.tv_nsec);
printf("Time : %ld\n",(((current_time.tv_sec)*1000000000)+(current_time.tv_nsec)));//negative value of y will indicate a failure
return 0;
}

