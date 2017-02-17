                                                                        
obj-m := maps.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all: maps.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS =$(PWD) clean

