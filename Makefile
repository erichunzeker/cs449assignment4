obj-m := rps_dev.o 

export PATH:=$(PATH):~wahn/public/cs449/debian-headers/usr/bin:~wahn/public/cs449/debian-headers/usr/lib/gcc/i486-linux-gnu/4.6
export LD_LIBRARY_PATH:=$(LD_LIBRARY_PATH):~wahn/public/cs449/debian-headers/usr/lib/i386-linux-gnu

KDIR  := ~wahn/public/cs449/debian-headers/lib/modules/3.2.0-4-686-pae/build
PWD   := $(shell pwd)

default:
	$(MAKE) -C $(KDIR) M=$(PWD) PATH=$(PATH) LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) modules
	gcc -m32 rps_ctrl.c -o rps_ctrl
	gcc -m32 rps.c -o rps
clean: 
	$(MAKE) -C $(KDIR) M=$(PWD) PATH=$(PATH) LD_LIBRARY_PATH=$(LD_LIBRARY_PATH) clean
	rm rps_ctrl rps
