#include <linux/kfifo.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/random.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>

static int dstruct_size = 16;
module_param(dstruct_size, int, S_IRUSR);
static int link_init(void)
{
        
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

	static void link_exit(void){
        printk(KERN_ALERT "Exiting the module \n");
}
module_init(link_init);
module_exit(link_exit);










