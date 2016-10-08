# Makefile (!not makefile)
ifneq ($(KERNELRELEASE),)
obj-m       := gpio.o
else
KDIR        := /home/fang/raspberrypi/linux-rpi-3.18.y
PWD         := $(shell pwd)
default:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules
clean:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) clean
endif
