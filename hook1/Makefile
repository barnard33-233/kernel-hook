obj-m := hook_mkdir.o
hook_mkdir-objs += hook.o
hook_mkdir-objs += module.o
hook_mkdir-objs += mkdir.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
