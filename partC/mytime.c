#include <linux/init.h> 
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/major.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <asm/errno.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/stat.h>
#include <linux/miscdevice.h>
#include <linux/sched.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

char * char_buff;
static int BUFFER_SIZE = 32768;

void currenttime(void);
int __init my_module_init(void);
void __exit my_module_exit(void);
static int dev_open(struct inode *, struct file *);
static int dev_close(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);

static struct file_operations fops = {

	.owner = THIS_MODULE,
	.open = dev_open,
	.release = dev_close,
	.read = dev_read
};

static struct miscdevice char_device = {
	
	.minor = MISC_DYNAMIC_MINOR,
	.name = "mytime",
	.fops = &fops 
};

int __init dev_init(void) 
{
	int status = misc_register(&char_device);
	if(status >= 0) 
	{
		printk (KERN_INFO "Registeration success.\n");
	}	
	else
	{
		printk (KERN_INFO "Registeration failed.\n");
	}
	return status;
}

void __exit dev_exit(void)
{	
	misc_deregister(&char_device);
}

static int dev_open(struct inode *inode, struct file *file)
{
	printk(KERN_INFO "Device opened.\n");
	char_buff=( char* ) kzalloc(BUFFER_SIZE, GFP_KERNEL);
	if(char_buff == NULL) 
	{
		printk (KERN_INFO "Allocation memory failed.\n");
		return -1;	
	}
	return 0;
}

static int dev_close(struct inode *inode, struct file *file)
{	
	kfree( char_buff );
	printk(KERN_INFO "Device closed.\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buffer, size_t len, loff_t *offset)
{  
   	int retVal;
   	
   	strcpy(char_buff, "");
//char buf[64];
   	
   	//strcpy(buf, "");
//sprintf(buf,"HELLO WORLD\n");
   	currenttime();
   	
   	retVal = copy_to_user(buffer,char_buff ,len);
   	if (retVal != 0)
	{
		printk(KERN_INFO "Failed to read\n");
		return retVal;
	}
   	return retVal;
}


void currenttime(void)
{
	struct timespec xtime,xtime1;
	char temp[64];
	char temp1[64];
xtime = current_kernel_time();
getnstimeofday(&xtime1);


long n = (xtime.tv_sec*1000000000)+(xtime.tv_nsec);
long p = (xtime1.tv_sec*1000000000)+(xtime1.tv_nsec);
printk(KERN_INFO "CURRENT_TIME:%ld",(xtime.tv_sec*1000000000)+(xtime.tv_nsec));
printk(KERN_INFO "CURRENT_TIME:%10i.%09i",xtime.tv_sec,xtime.tv_nsec);
printk(KERN_INFO "CURRENT_TIME:%ld %ld",xtime.tv_sec,xtime.tv_nsec);
printk(KERN_INFO"CURRENT_TIME:%ld",n);
printk(KERN_INFO"GETINSTIMEOFDAY::%ld",p);
sprintf(temp,"CURRENT_KERNEL_TIME: %ld %ld\n",xtime.tv_sec,xtime.tv_nsec);
sprintf(temp1,"GETNSTIMEOFDAY: %ld %ld\n\n",xtime1.tv_sec,xtime1.tv_nsec);
printk(KERN_INFO "%s", temp);
strcat(temp,temp1);
strcat(char_buff, temp);

}

module_init(dev_init);
module_exit(dev_exit);
