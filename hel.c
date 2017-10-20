#include<linux/kernel.h>
#include<linux/time.h>
#include<asm/uaccess.h>
#include<linux/slab.h>
#include<linux/errno.h>
#include<linux/syscalls.h>
#include<linux/export.h>
int sys_myfoo(struct timespec *current_time)
{
struct timespec xtime;

xtime = current_kernel_time();
//int p;

long n =  (xtime.tv_sec*1000000000)+(xtime.tv_nsec);

//if(!(access_ok(VERIFY_WRITE,current_time,sizeof(current_time))))
//{
//printk(KERN_ERR "NOT VALID");
//}
//printk(KERN_INFO "VALID");

printk(KERN_INFO "%10i.%09i",xtime.tv_sec,xtime.tv_nsec);
printk(KERN_INFO "%ld",(xtime.tv_sec*1000000000)+(xtime.tv_nsec));
printk(KERN_INFO "%ld",n);
if(copy_to_user(current_time,&xtime,sizeof(xtime)))
{
	return -EFAULT;
}

   return 0;

}


EXPORT_SYMBOL(sys_myfoo);
