#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/types.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/uaccess.h>
#include "ioctl.h"
#include "cal.h"

#define NAME charioctl

int a = 0;
int b = 0;
int res = 0;
int op = 0;
//function prototypes
int NAME_open(struct inode *inode,struct file *filp);
int NAME_release(struct inode *inode, struct file *filp);
long NAME_ioctl(struct file *filp, unsigned int cmd, unsigned long arg);


//structure defining operations that the driver provides
struct file_operations fops = 
{
	.owner	= THIS_MODULE,
	.open	= NAME_open,
	.release= NAME_release,
	.unlocked_ioctl = NAME_ioctl,

};



//structure for a chararcter driver
struct cdev *my_cdev;


//init module
static int __init chardevice_init(void)
{
	int result;
	int major,minor;
	dev_t mydev;
	mydev=MKDEV(255,0);  //creating a device number
	major=MAJOR(mydev);
	minor=MINOR(mydev);
	printk("\n major number %d.....minor number %d\n",major,minor);
	result=register_chrdev_region(mydev,1,"charioctl");//register device region
	if(result<0)
	{
		printk("\nthe region is not obtainable\n");
		return(-1);
				
	}

	my_cdev = cdev_alloc();//allocate memory to char device structure
	my_cdev->ops = &fops;//link file operations to char device
	result = cdev_add(my_cdev,mydev,1);//notify kernal abt device
	if(result<0)
	{
		printk("\nchar device not created\n");
		unregister_chrdev_region(mydev,1);
		return (-1);
	}
	return 0;		
}

//cleanup module
void __exit chardevice_exit(void)
{
	dev_t mydev;
	int major,minor;
	mydev=MKDEV(255,0);
	major=MAJOR(mydev);
	minor=MINOR(mydev);
	printk("\n major numberr: %d.....minor number: %d\n",major,minor);
	unregister_chrdev_region(mydev,1);//unregister the device numbers and device created
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


long NAME_ioctl (struct file *filp, unsigned int cmd, unsigned long arg)
{
	static int count = 0;
	printk("\n IOCTL Function");
	switch (cmd){
		case WR_VALUE:
			if(count == 0)
                		{
                			copy_from_user(&op,(int*)arg,sizeof(op));
                			printk("operator = %d\n",op);
               				break;
				}
			else if(count == 1)
				{

                			copy_from_user(&a,(int*)arg,sizeof(a));
                			printk("a = %d\n",a);
                			break;

            			}

			else if(count == 2)
				{
               				copy_from_user(&b,(int*)arg,sizeof(b));
                			printk("b = %d\n",b);
                			break;
				}

		case RD_VALUE:
			if(op == 1)
			{
                		res = my_add(a,b);
				printk("in addition");
			}
            		else if(op == 2)
			{
                		res = my_sub(a,b);
				printk("in subtraction");
			}
            		else if(op == 3)
			{
				printk("in multiplication");
                		res = my_mul(a,b);
			}
            		else if(op == 4)
			{
				printk("in division");
                		res = my_div(a,b);
			}
            		else
			{
				break;
			}

            		copy_to_user((int*) arg, &res,sizeof(res));
            		break;

	}
	count+=1;
	if(count == 3)
		count =0;
	return 0;
}

module_init(chardevice_init);
module_exit(chardevice_exit);
