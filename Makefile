ifneq ($(KERNELRELEASE),)
obj-m := hello1.o hello2.o

else
KDIR := ~/repos/linux-stable
CCFLAGS := -I$(PWD)/inc

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules EXTRA_CFLAGS="$(CCFLAGS)"

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

endif
