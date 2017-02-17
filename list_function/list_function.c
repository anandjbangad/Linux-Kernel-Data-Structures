#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/random.h>

static int dstruct_size = 16;
module_param(dstruct_size, int, S_IRUSR);
struct dstruct_size
{
	int random_number;
	struct list_head list_start;
};
static LIST_HEAD(list_1);
//struct dstruct_size current123; // creating a structure variable
//INIT_LIST_HEAD(&list_1);
    // Initializing the list_head

int link_list_implementation_add(void){
	struct dstruct_size *tmp = (struct dstruct_size *)kmalloc(sizeof(struct dstruct_size),GFP_KERNEL); // creating a pointer variable tmp which is of type struct my_list
	//struct list_head *pos,*q;
	unsigned int i =0;
	for(i=0; i<dstruct_size; i++){
		int *r =(int *) kmalloc(sizeof(int),GFP_KERNEL);
		*r=0;
		tmp = (struct dstruct_size *) kmalloc(sizeof(struct dstruct_size), GFP_KERNEL);
		get_random_bytes(r,2);
		tmp->random_number = *r;
	//	printk(KERN_INFO "Contents of List %d\n",*r);
		list_add(&tmp->list_start,&list_1);
	}
	return 0;
}
int link_list_implementation_traverse(void){
	struct dstruct_size *tmp = (struct dstruct_size *)kmalloc(sizeof(struct dstruct_size),GFP_KERNEL); // creating a pointer variable tmp which is of type struct my_list
	 // creating a pointer variable tmp which is of type struct my_list
	struct list_head *pos,*q;
	list_for_each(pos, &list_1){
		tmp = list_entry(pos,struct dstruct_size,list_start);
		printk(KERN_INFO "Contents of List %d\n",tmp->random_number);
	}
	return 0;
}
int link_list_implementation_delete(void){
	struct dstruct_size *tmp = (struct dstruct_size *)kmalloc(sizeof(struct dstruct_size),GFP_KERNEL);
	struct list_head *pos,*q;
	list_for_each_safe(pos,q,&list_1){
		tmp = list_entry(pos,struct dstruct_size, list_start);
		printk(KERN_INFO "freeing item %d\n", tmp->random_number);
		list_del(pos);
		kfree(tmp);
	}
	return 0;
}
static int link_init(void)
{
	//struct dstruct_size current123; // creating a structure variable
	//INIT_LIST_HEAD(&list_1);
	/* code */
	int m =0;
	int n=0;
	int o=0;
	m = link_list_implementation_add();
	n = link_list_implementation_traverse();
	o = link_list_implementation_delete();
	return 0;
}

static void link_exit(void){
	printk(KERN_ALERT "Exiting the module \n");
}


module_init(link_init);
module_exit(link_exit);



