obj-m := list123.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all: list123.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS =$(PWD) clean
