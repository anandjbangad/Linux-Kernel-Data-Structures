#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/random.h>
int link_list_implementation(void);
static int dstruct_size = 16;
module_param(dstruct_size, int, S_IRUSR);
struct dstruct_size
{
	int random_number;
	struct list_head list_start;
};

static int link_init(void)
{
	/* code */
	int m=0;
	m = link_list_implementation();



	return 0;
}

static void link_exit(void){
	printk(KERN_ALERT "Exiting the module \n");
}

int link_list_implementation(void){
	struct dstruct_size *tmp; // creating a pointer variable tmp which is of type struct my_list
	struct list_head *pos,*q;
	unsigned int i;
	struct dstruct_size current123; // creating a structure variable
	INIT_LIST_HEAD(&current123.list_start);
    // Initializing the list_head
    int *r = kmalloc(sizeof(int),GFP_KERNEL);
    *r=0;
    
	for(i =dstruct_size; i!=0; i--){
		tmp = (struct dstruct_size *) kmalloc(sizeof(struct dstruct_size), GFP_KERNEL);
		get_random_bytes(r,2);
		tmp->random_number = *r;
		list_add(&(tmp->list_start), &(current123.list_start));
	}

	// Traversing List
	list_for_each(pos, &current123.list_start){
		tmp = list_entry(pos, struct dstruct_size, list_start);
		printk(KERN_INFO "Contents of List %d\n",tmp->random_number);
	}

	// Deleting the list
	/*As opposite, the safe foreach pre-saves the value of pos->next 
	in a temporary variable and then refers to the latter instead of 
	dereferencing pos: This is the us of q*/
	list_for_each_safe(pos,q,&current123.list_start){
		tmp = list_entry(pos,struct dstruct_size, list_start);
		printk(KERN_INFO "freeing item %d\n", tmp->random_number);
		list_del(pos);
	//	free(tmp);
		
	}
	return 0;
}

module_init(link_init);
module_exit(link_exit);




