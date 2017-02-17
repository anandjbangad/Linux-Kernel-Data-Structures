#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/idr.h>
#include <linux/kfifo.h>
#include <linux/rbtree.h>
#include <linux/proc_fs.h>
#include <linux/stat.h>

MODULE_AUTHOR("Anand");
MODULE_LICENSE("GPL");
static int dstruct_size = 16;
module_param(dstruct_size, int, 0);
static LIST_HEAD(list_1);
struct mytype{
struct rb_node node;
int random_number;
};
struct dstruct_size
{
	int random_number;
	struct list_head list_start;
};

int link_list_implementation(void){
	struct link_struct
{
	int random_number;
	struct list_head list_start;
};

	struct link_struct *tmp; // creating a pointer variable tmp which is of type struct my_list
	struct list_head *pos,*q;
	unsigned int i;
	struct link_struct current123; // creating a structure variable
	INIT_LIST_HEAD(&current123.list_start);
    // Initializing the list_head
    int *r = kmalloc(sizeof(int),GFP_KERNEL);
    *r=0;
    for(i =dstruct_size; i!=0; i--){
		tmp = (struct link_struct *) kmalloc(sizeof(struct link_struct), GFP_KERNEL);
		get_random_bytes(r,2);
		tmp->random_number = *r;
		list_add(&(tmp->list_start), &(current123.list_start));
	}
	list_for_each(pos, &current123.list_start){
		tmp = list_entry(pos, struct dstruct_size, list_start);
		printk(KERN_INFO "Contents of List %d\n",tmp->random_number);
	}
	list_for_each_safe(pos,q,&current123.list_start){
		tmp = list_entry(pos,struct link_struct, list_start);
		printk(KERN_INFO "freeing item %d\n", tmp->random_number);
		list_del(pos);
	}
	return 0;
}
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
	//	printk(KERN_INFO "Contents of List %d\n",tmp->random_number);
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
int map(void){
	struct node{
	unsigned short data;
};
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

int queue123(void){

        struct kfifo my_queue;
        int *buffer;
        int return11;
        //DECLARE_KFIFO(my_queue,4096);
        buffer = kmalloc(4096,GFP_KERNEL);
        return11 = kfifo_init(&my_queue,buffer,4096);
        unsigned int i = 0;
        int *r =(int *) kmalloc(sizeof(int),GFP_KERNEL);
        *r=0;

        for(i= 0; i<dstruct_size; i++){
		get_random_bytes(r , 1);
        printk(KERN_INFO "Enqueued :%d \n",*r);
		kfifo_in(&my_queue, r ,sizeof(int));
        }

        unsigned int val;
        int ret;
        //takes the struct my_queue, copies data to buufer & val, takes size of$
        // returs the size of data copied
       //kfifo_out_peek takes a look at the elements without deleting it
//      for(i=0; i<32;i++){
//      ret = kfifo_out_peek(&my_queue,&val,sizeof(val));
//      if(ret != sizeof(val))
//              return -EINVAL;
//      printk(KERN_INFO "Enqueued %u\n",val);
//      }

        // Dequeuing
        int m = kfifo_avail(&my_queue);
//printk(KERN_INFO "Value issssssss %d ",m);
        int ret1;
        int val1;

        for(i=0;i<dstruct_size;i++){
                ret1 = kfifo_out(&my_queue, &val1, sizeof(int));
                if(ret1 != sizeof(int))
                        return -EINVAL;
                printk(KERN_INFO"DEQUEED %u\n",val1);
        }
	        return 0;

}

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

static int link_init(void)
{
	int a=0;
	int b =0;
	int c=0;
	int d=0;
	int e =0;
	int f=0;
	int g=0;
	printk(KERN_INFO "\nNormal Link List implementation\n");
	a = link_list_implementation();
	printk(KERN_INFO "\nlink_list_implementation : Add\n");
	b = link_list_implementation_add();
	printk(KERN_INFO "\nlink_list_implementation : Traverse\n");
	c = link_list_implementation_traverse();
	printk(KERN_INFO "\nlink_list_implementation : Delete\n");
	d = link_list_implementation_delete();
	printk(KERN_INFO "\n Map Implementation");
	e = map();
	printk(KERN_INFO "\n Queue Implemetation");
	f =queue123();
	printk(KERN_INFO "\n Red Black Tree Implementation");
	g = RedBlackTree();
	return 0;
}

static void link_exit(void){
	printk(KERN_ALERT "Exiting the module \n");
}
module_init(link_init);
module_exit(link_exit);




