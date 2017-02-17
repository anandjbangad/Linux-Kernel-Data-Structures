                                                                        
obj-m := RedBlackTree.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all: RedBlackTree.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS =$(PWD) clean

