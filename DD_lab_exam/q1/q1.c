#include<linux/init.h>
#include<linux/module.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/device.h>
#include<linux/kdev_t.h>
#include<linux/kernel.h>
#include<linux/semaphore.h>


#define DRIVER_NAME "mydev"
//function prototypes
int open(struct inode *inode, struct file *filp);
int release(struct inode *inode, struct file *filp);
ssize_t read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);
ssize_t write(struct file*filp, const char __user *Ubuff,size_t count, loff_t *offp);

//file operations
struct file_operations fops=
{
        .owner = THIS_MODULE,
        .open = open,
        .release = release,
        .read = read,
        .write = write
};

//variable defination
int major,minor=0;
dev_t mydev;
struct cdev mycdev;
struct class *my_class;
struct device *my_device;

//semaphore strucutre
struct semaphore sem_dev;


char Kbuff[80];
int flag=1;

DECLARE_WAIT_QUEUE_HEAD (wait);

//open function

int  open(struct inode *inode, struct file *filp)
{
        printk("in open function");
        return 0;

}
//close function
int release(struct inode *inode, struct file *filp)
{
        printk("in close function");
        return 0;
}

//write function
ssize_t write(struct file *filp, const char __user *Ubuff, size_t count, loff_t *offp)
{
        ssize_t ret;
        unsigned long res;

        res= copy_from_user(Kbuff,Ubuff,count);
        if(res==0)
        {

                printk("message from user:%s\n",Kbuff);
                printk("written succesfull");
                ret=count;
		flag=0;
		wake_up_interruptible(&wait);
                return ret;
        }

        
	else
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
        ssize_t ret;
        unsigned long res;
	printk("in read function");
	down(&sem_dev);
	if(flag == 1)
	{
		wait_event_interruptible(wait,flag==0);
	}
        res= copy_to_user(Ubuff,Kbuff,count);
        if(res==0)
        {
                printk("reading succesfull");
                ret=count;
		flag=0;
                wake_up_interruptible(&wait);

                return ret;
        }
      
       
	else
        {
                printk("error writing message");
                ret = -EFAULT;
                return ret;
        }
	up(&sem_dev);
        return 0;
}

static int __init my_init(void)
{
        //alloc major no minor no
        alloc_chrdev_region(&mydev,minor,2,DRIVER_NAME);
        major=MAJOR(mydev);
        minor=MINOR(mydev);
        printk("major =%d, minor=%d\n",major,minor);
        //initializing adding
        cdev_init(&mycdev,&fops);
        cdev_add(&mycdev, mydev,2); 
        //create node
        my_class = class_create(THIS_MODULE,DRIVER_NAME);
        my_device = device_create(my_class,NULL,mydev,NULL,"mydev");
	//initialize semaphore
	sema_init(&sem_dev,1);
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



