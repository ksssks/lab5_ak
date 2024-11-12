#ifndef HELLO1_H
#define HELLO1_H

#include <linux/ktime.h>

struct hello_data {
    struct list_head list;
    ktime_t time;
};

void print_hello(int repeat);

#endif
