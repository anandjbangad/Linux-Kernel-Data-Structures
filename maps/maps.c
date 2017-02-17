#include <linux/slab.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/random.h>
#include <linux/idr.h>

MODULE_AUTHOR("Anand");
MODULE_LICENSE("GPL");


static int dstruct_size = 16;

module_param(dstruct_size, int, 0);
MODULE_PARM_DESC(dstruct_size, "List Size");

struct node{
	unsigned short data;
};

int map(void){
	unsigned int i;
	struct idr map;
	idr_init(&map);
	for(i = 0; i < dstruct_size; i++){
		int id;			
		int* r = kmalloc(sizeof(int), GFP_KERNEL);
		get_random_bytes(r, 1);
		idr_preload(GFP_KERNEL);
		id = idr_alloc(&map, r, 10, 10+dstruct_size, GFP_KERNEL);
		idr_preload_end();
		if(id == -ENOSPC)
			return 0;	
		else if(id == -ENOMEM)
			return 0;
	}

	for(i = 0; i < dstruct_size; i++){
		int id = 10 + i;			
		struct node *ptr = idr_find(&map, id);
		if (ptr == NULL)
			return -EINVAL;
		printk(KERN_INFO "ID is %d & Value is %d \n", id, ptr->data);
		idr_remove(&map, id);
	}
	idr_destroy(&map);
	return 0;
}

static int __init link_init(void)
{
	 map();
	 return 0;
}

static void __exit link_exit(void)
{
        printk(KERN_INFO "Exiting Module");
}

module_init(link_init);
module_exit(link_exit);
