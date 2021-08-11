#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABRAR");


static int my_div(int a, int b)
{
  return(a/b);
}

EXPORT_SYMBOL(my_div);


static int __init div_init(void)
{
  printk("\n we are in div function\n");
  return 0;
}


static void __exit div_exit(void)
{
 printk("\n GoodBye\n"); 
}

module_init(div_init);
module_exit(div_exit);
