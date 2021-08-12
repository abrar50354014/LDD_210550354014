#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"cal.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABRAR");

static int a = 10;
static int b = 20;
static char* charvar = "";

module_param(charvar, charp, S_IRUGO);
module_param(a, int, S_IRUGO);
module_param(b, int,S_IRUGO);

static int __init calperm_init(void)
{
	printk("in calculator\n");
	if(strcmp(charvar,"add")==0)
	  {
		  printk("in %s function",charvar);
                  printk("value of addition is : %d",my_add(a,b));
	  }
	else if(strcmp(charvar,"sub")==0)
	  {
		  printk("in %s function",charvar);
                  printk("value of subtraction is : %d",my_sub(a,b));

	  }
	else if(strcmp(charvar,"mul")==0)
	  {
		  printk("in %s function",charvar);
                  printk("value of multiplication is : %d",my_mul(a,b));
	  }
	else if(strcmp(charvar,"div")==0)
          {
                  printk("in %s function",charvar);
                  printk("value of division is : %d",my_div(a,b));

   	  }
	else 
          {
                  printk("wrong entry");
 	  }



 /* switch(charvar)
  {
	  case 'add':
		  printk("in %s function",charvar);
		  printk("value of addition is : %d",my_add(a,b));
		  break;
	  case 'sub':
		  printk("in %s function",charvar);
                  printk("value of subtraction is : %d",my_sub(a,b));
		  break;
	  case 'mul':
		  printk("in %s function",charvar);
                  printk("value of multiplication is : %d",my_mul(a,b));
                  break;
	  case 'div':
		  printk("in %s function",charvar);
                  printk("value of division is : %d",my_div(a,b));
                  break; 
  }*/


  return 0;
}

void __exit calperm_exit(void)
{
  printk("job done good bye");
}


module_init(calperm_init);
module_exit(calperm_exit);
