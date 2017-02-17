#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/rbtree.h>
#include <linux/proc_fs.h>
#include <linux/stat.h>
static int dstruct_size = 16;
module_param(dstruct_size, int, S_IRUSR);
struct mytype{
struct rb_node parent;
struct rb_node node;
int random_number;
};
struct mytype *my_search(struct rb_root *root, unsigned short value)
{
	struct rb_node *node = root->rb_node;
	while(node){
		struct mytype *data = container_of(node, struct mytype, node);
		if(value < data->random_number)
			node = node->rb_left;
		else if (value > data->random_number)
			node = node->rb_right;
		else
			return data;
	}
	return NULL;
}


//struct rb_root mytree = RB_ROOT;
int my_insert(struct rb_root *root, struct mytype *data)
{
	struct rb_node **new = &(root->rb_node), *parent = NULL;
	//int random_value = data->random_number;
	while(*new){
		struct mytype *this = container_of(*new,struct mytype, node);
		parent = *new;
		if (data->random_number > this->random_number)
		{
			new = &((*new)->rb_right);
		}
		else if (data->random_number < this->random_number)
		{
			new = &((*new)->rb_left);		
		}
		else
			return 0;
	}
	rb_link_node(&(data->node), parent, new);
	rb_insert_color(&(data->node), root);
	return 1;

}
int RedBlackTree(void){
struct rb_root mytree = RB_ROOT;
struct mytype *b;
struct rb_node *node;
int i =0;
unsigned short z =0;
unsigned short y =0;
int mn=0;
int* a = kmalloc(sizeof(int), GFP_KERNEL);
*a = 0;
for(i=0; i<dstruct_size; i++){
	get_random_bytes(a, 1);
	b = (struct mytype *)kmalloc(sizeof(struct mytype), GFP_KERNEL);
	b->random_number = *a;
	mn = my_insert(&mytree,b);
}
for (node = rb_first(&mytree); node; node = rb_next(node))
	printk("key=%d\n", rb_entry(node, struct mytype, node)->random_number);	

for(i=0; i<100; i++){
	struct mytype *data = my_search(&mytree, z);
	if (data){
		printk(KERN_INFO "Found %d \n",data->random_number);
		rb_erase(&data->node, &mytree);
		kfree(data);
	}
	z++;
	
}
printk(KERN_INFO "\nAfter deleting from a range of 100 keys remaining\n");	
for (node = rb_first(&mytree); node; node = rb_next(node))
	printk("key left=%d\n", rb_entry(node, struct mytype, node)->random_number);	
printk(KERN_INFO "\nDeleting All Keys\n");
for(i=0; i<65535; i++){
	struct mytype *data = my_search(&mytree, y);
	if (data){
		printk(KERN_INFO "%d \n",data->random_number);
		rb_erase(&data->node, &mytree);
		kfree(data);
	}
	y++;
	
}		


return 0;
}

static int __init link_init(void){
RedBlackTree();
return 0;
}


static void __exit link_exit(void){
    printk(KERN_ALERT "Exiting the module \n");
}
module_init(link_init);
module_exit(link_exit);

