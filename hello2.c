//
// Created by goodvice on 26/12/23.
//

#include <linux/init.h>
#include <linux/module.h>
#include "hello1.h"

MODULE_AUTHOR("Andrii Lysak <andrii.lysak.200@gmail.com>");
MODULE_DESCRIPTION("Importing and using functions from another module");
MODULE_LICENSE("Dual BSD/GPL");

static uint repeat_counter = 1;
module_param(repeat_counter, uint, S_IRUGO);
MODULE_PARM_DESC(repeat_counter, "Number of times the message should be printed");

static int __init hello2_init(void) {
    if (repeat_counter == 0) {
        pr_warn("Warning: repeat_counter is equal to 0\n");
    } else if (repeat_counter >= 5 && repeat_counter <= 10) {
        pr_warn("Warning: repeat_counter is between 5 and 10\n");
    } else if (repeat_counter > 10) {
        pr_err("Error: repeat_counter cannot be greater than 10\n");
        return -EINVAL;
    }

    print_hello(repeat_counter);

    return 0;
}

static void __exit hello2_exit(void) {

}

module_init(hello2_init);
module_exit(hello2_exit);