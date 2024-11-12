#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include <linux/list.h>
#include "hello1.h"

MODULE_AUTHOR("IO-24 Shulga Kyryl");
MODULE_DESCRIPTION("Hello, world in Linux Kernel Training - Module 1");
MODULE_LICENSE("Dual BSD/GPL");

static LIST_HEAD(hello_list);

void print_hello(int count)
{
	struct hello_data *data;
	int i;

	for (i = 0; i < count; i++) {
		data = kmalloc(sizeof(*data), GFP_KERNEL);
		if (!data) {
			pr_err("Failed to allocate memory\n");
			return;
		}

		data->time = ktime_get();
		list_add_tail(&data->list, &hello_list);
		pr_info("Hello, world!\n");
	}
}
EXPORT_SYMBOL(print_hello);

static int __init hello1_init(void)
{
	pr_info("Hello1 module loaded\n");
	return 0;
}

static void __exit hello1_exit(void)
{
	struct hello_data *data, *tmp;

	list_for_each_entry_safe(data, tmp, &hello_list, list) {
		pr_info("Time: %lld ns\n", ktime_to_ns(data->time));
		list_del(&data->list);
		kfree(data);
	}
	pr_info("Hello1 module unloaded\n");
}

module_init(hello1_init);
module_exit(hello1_exit);

