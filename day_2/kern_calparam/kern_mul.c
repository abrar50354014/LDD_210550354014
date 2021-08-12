#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABRAR");


static int my_mul(int a, int b)
{
  return(a*b);
}

EXPORT_SYMBOL(my_mul);


static int __init mul_init(void)
{
  printk("\n we are in mul function\n");
  return 0;
}


static void __exit mul_exit(void)
{
 printk("\n GoodBye\n"); 
}

module_init(mul_init);
module_exit(mul_exit);

