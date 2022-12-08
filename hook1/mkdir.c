#include <stdint.h>
#include <sys/module.h>
#include <linux/kernel.h>

#include "hook.h"

int sys_mkdir_hook(const char* path, mode_t mode){
  printk(KERN_INFO"open %s\n", path);
  return sys_mkdir_old(path, mode);
}