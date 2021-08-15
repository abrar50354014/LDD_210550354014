#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include<linux/spinlock.h>
#include<linux/delay.h>
#define NAME spindevice

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABRAR");


//function prototypes
int NAME_open(struct inode *inode,struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
ssize_t synch_spinlock_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp);


//structure defining operations that the driver provides
struct file_operations fops = 
{
	.owner	= THIS_MODULE,
	.open	= NAME_open,
	.release= NAME_release,
	.read = synch_spinlock_read

};


//structure for a chararcter driver
struct cdev *my_cdev;
//declare spinlock variable
spinlock_t slock;
//variable declerations to char driver
        int result;
        int major,minor;
        dev_t mydev;


//init module
static int __init synch_spinlock_init(void)
{

	mydev=MKDEV(255,0);  //creating a device number statically
        major=MAJOR(mydev);
        minor=MINOR(mydev);
        printk("\n major number %d.....minor number %d\n",major,minor);

	result=register_chrdev_region(mydev,1,"spindevice");//register device$
        if(result<0)
        {
                printk("\nthe region is not obtainable\n");
                return(-1);

        }

	//create character driver
	my_cdev = cdev_alloc();//allocate memory to char device structure
	my_cdev->ops = &fops;//link file operations to char device
	result = cdev_add(my_cdev,mydev,1);//notify kernal abt device
	if(result<0)
	{
		printk("\nchar device not created\n");
		unregister_chrdev_region(mydev,1);
		return (-1);
	}
	//initialize the spinlock
	spin_lock_init(&slock);
	return 0;
			
}

//cleanup module
void __exit synch_spinlock_exit(void)
{
	unregister_chrdev_region(mydev,1);//unregister the device numbers and devuce created
	cdev_del(my_cdev);
	printk("device unregisterd that was allocated");
}

//open sys call
int NAME_open(struct inode *inode,struct file *filp)
{
	printk("\nthis is kernal..... open call\n");
	return 0;
}

//close sys call
int NAME_release(struct inode *inode, struct file *filp)
{
	printk("\n release method of character device\n");
	return 0;
}

//
ssize_t synch_spinlock_read(struct file *filp, char __user *Ubuff, size_t count, loff_t *offp)
{
	static unsigned int value=10;
	printk("in read function\n");
	//get spinlock
	spin_lock(&slock);
/*>>>>>>/......critical section.........../<<<<*/
	mdelay(1000);
	value++;

	//send data to user
	copy_to_user(Ubuff, &value, sizeof(value));

	//release spinlock
	spin_unlock(&slock);
/*>>>>>>/......critcal section............./<<<<*/
	return sizeof(value);
}




module_init(synch_spinlock_init);
module_exit(synch_spinlock_exit);
