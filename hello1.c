#define DEBUG
#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/slab.h>
#include <linux/errno.h>
#include <linux/ktime.h>
#include "hello1.h"

MODULE_AUTHOR("Serhii Popovych <serhii.popovych@globallogic.com>");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);

void print_hello(void)
{
	struct hello_event *entry;
	ktime_t start_time, end_time;

	start_time = ktime_get();

	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry) {
		pr_err("hello1: Failed to allocate memory for event data.\n");
		return;
	}

	pr_info("Hello, world!\n");

	end_time = ktime_get();
	entry->duration = ktime_sub(end_time, start_time);

	list_add_tail(&entry->list, &hello_list);
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("hello1: Module loaded. Providing print_hello symbol.\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_event *entry, *tmp;

	pr_debug("hello1: >> Starting cleanup loop <<\n");

	list_for_each_entry_safe(entry, tmp, &hello_list, list) {
		pr_debug("hello1: Print duration (ns): %lld\n", ktime_to_ns(entry->duration));
		list_del(&entry->list);
		kfree(entry);
	}
	pr_debug("hello1: >> Cleanup loop finished <<\n");

	pr_info("hello1: Module finished.\n");
}

module_init(hello1_init);
module_exit(hello1_exit);
