obj-m := list_function.o

KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
all: list_function.c
	make -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	make -C $(KDIR) SUBDIRS =$(PWD) clean



