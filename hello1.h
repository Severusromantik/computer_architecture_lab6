#ifndef HELLO1_H
#define HELLO1_H

#include <linux/types.h>
#include <linux/list.h>
#include <linux/ktime.h>

struct hello_event {
	struct list_head list;
	ktime_t duration;
};

void print_hello(void);

#endif
