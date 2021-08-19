#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/kernel.h>
#include "ioctll.h"
#define DRIVER_NAME "ioctldev"
//function prototypes
int open(struct inode *inode, struct file *filp);
int release(struct inode *inode, struct file *filp);
ssize_t read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t write(struct file*filp, const char __user *Ubuff,size_t count, loff_t *offp);
long ioctl(struct file *filp, unsigned int cmd, unsigned long arg);


//file operations
struct file_operations fops=
{
	.owner = THIS_MODULE,
	.open = open,
	.release = release,
	.read = read,
	.write = write,
	.unlocked_ioctl = ioctl

};

//variable defination
int major,minor=0;
dev_t mydev;
struct cdev mycdev;
struct class *my_class;
struct device *my_device;


int baudrate;


//open function

int  open(struct inode *inode, struct file *filp)
{
	printk("in open file function");
	return 0;

}
//close function
int release(struct inode *inode, struct file *filp)
{
	printk("in close function");
	return 0;
}

//write function
ssize_t write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)\
{
	char Kbuff[100];
	ssize_t ret;
	unsigned long res;

	res= copy_from_user((char *)Kbuff, (char*) Ubuff,count);
	if(res==0)
	{
		printk("message from user:%s\n",Kbuff);
		printk("written succesfull");
		ret=count;
		return ret;
	}

        
	if(res<0)
        {
                printk("error writing message");
                ret = -EFAULT;
		return ret;
        }
	return 0;
}

//read function
ssize_t read(struct file *filp,char __user *Ubuff,size_t count, loff_t *offp)
{
	char Kbuff[100] = "hellu user this is kernel";
	ssize_t ret;
	unsigned long res;
	res= copy_to_user((char*)Ubuff,(char*)Kbuff,count);
	if(res==0)
        {
                printk("message to user:%s\n",Kbuff);
                printk("read succesfull");
                ret=count;
                return ret;
        }
  
        
        if(res<0)
        {
                printk("error writing message");
                ret = -EFAULT;
                return ret;
        }
	return 0;

}

long ioctl(struct file *filp, unsigned int cmd, unsigned long arg)
{

	printk("in ioctl func");
	static int count =0;
	switch(cmd){
		case SET_BAUDRATE:
			if(count == 0)
			{
				copy_from_user(&baudrate,(int*) arg,sizeof(baudrate));
				printk(" baud rate is set to %d",baudrate);
				break;
			}
		case SEND_BAUDRATE:
			if(count == 0)
			{
				copy_to_user((int*)arg, &baudrate, sizeof(baudrate));
				printk("data sent");
				break;
			}
	}
	return 0;
}

static int __init my_init(void)
{
	//alloc major no minor no
	alloc_chrdev_region(&mydev,minor,1,DRIVER_NAME);
	major=MAJOR(mydev);
	minor=MINOR(mydev);
	printk("major =%d, minor=%d\n",major,minor);
	//initializing adding
	cdev_init(&mycdev,&fops);
	cdev_add(&mycdev, mydev,1); 
	//create node
	my_class = class_create(THIS_MODULE,DRIVER_NAME);
	my_device = device_create(my_class,NULL,mydev,NULL,"ioctldev");
	return 0;

}
void __exit my_exit(void)
{
	//delete node
	device_destroy(my_class,mydev);
	class_destroy(my_class);
	//unregister
	cdev_del(&mycdev);
	unregister_chrdev_region(mydev,1);
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABRAR");
