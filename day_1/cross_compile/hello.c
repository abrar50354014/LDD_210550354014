#include<linux/module.h>
#include<linux/init.h>

static int  hello_init(void)
{
        printk("hello world\n");
        return 0;
}

static void  hello_cleanup(void)
{
        printk("good bye");
}

module_init(hello_init);
module_exit(hello_cleanup);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ABRAR");
MODULE_DESCRIPTION("A simple hello_world kernel module");


