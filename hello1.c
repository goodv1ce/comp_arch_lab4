//
// Created by goodvice on 26/12/23.
//

#include <linux/init.h>
#include <linux/module.h>
#include <linux/printk.h>
#include <linux/list.h>
#include <linux/ktime.h>
#include <linux/slab.h>
#include "hello1.h"

MODULE_AUTHOR("Andrii Lysak <andrii.lysak.200@gmail.com>");
MODULE_DESCRIPTION("Exporting functions for use in another module");
MODULE_LICENSE("Dual BSD/GPL");

struct hello_data {
    struct list_head tlist;
    ktime_t timestamp;
    ktime_t print_time;
};

static struct list_head list;

void print_hello(unsigned int hello_count) {
    struct hello_data *data;
    int i;

    for (i = 0; i < hello_count; i++) {
        data = kmalloc(sizeof(*data), GFP_KERNEL);
        data->timestamp = ktime_get();
        INIT_LIST_HEAD(&data->tlist);
        list_add_tail(&data->tlist, &list);
        pr_info(KERN_ALERT "Hello, world!\n");
        data->print_time = ktime_get();
    }
}

    EXPORT_SYMBOL(print_hello);

    static int __init hello1_init(void) {
        INIT_LIST_HEAD(&list);
        return 0;
    }

    static void __exit hello1_exit(void) {
        struct hello_data *data, *tmp;
        list_for_each_entry_safe(data, tmp, &list, tlist) {
            s64 nanoseconds = ktime_to_ns(data->timestamp);
            pr_info("Time before printing: %lld\n", nanoseconds);

            nanoseconds = ktime_to_ns(data->print_time) - ktime_to_ns(data->timestamp);
            pr_info("Time for printing: %lld\n", nanoseconds);

            list_del(&data->tlist);
            kfree(data);
        }
    }

module_init(hello1_init);
module_exit(hello1_exit);
