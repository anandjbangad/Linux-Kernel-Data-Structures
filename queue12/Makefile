                                                                        
obj-m := anand_queue.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all: anand_queue.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS =$(PWD) clean






