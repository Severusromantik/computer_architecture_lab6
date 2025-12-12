#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/moduleparam.h>
#include <linux/errno.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world user module (Lab 5)");
MODULE_LICENSE("Dual BSD/GPL");

static uint repeat_count = 1;
module_param(repeat_count, uint, 0644);
MODULE_PARM_DESC(repeat_count, "The number of times to call print_hello() from hello1 module.");

static int __init hello2_init(void)
{
	int i;
	if (repeat_count > 10) {
		pr_err("Error: repeat_count (%u) is too high (> 10). Module not loaded.\n", repeat_count);
		return -EINVAL;
	}

	if (repeat_count == 0 || (repeat_count >= 5 && repeat_count <= 10)) {
		pr_warn("Warning: repeat_count (%u) is suboptimal (0 or 5-10).\n", repeat_count);
	}

	for (i = 0; i < repeat_count; i++) {
		print_hello();
	}

	pr_info("Hello2 module loaded. Finished calls to hello1.\n");
	return 0;
}

static void __exit hello2_exit(void)
{
	pr_info("Hello2 module unloaded.\n");
}

module_init(hello2_init);
module_exit(hello2_exit);
