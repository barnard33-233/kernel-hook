#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/string.h>
#include <linux/syscalls.h>

#include "hook.h"

void** sys_call_table;
sys_mkdir_t sys_mkdir_old;

static int __init init_module(void){
  printk("hook_mkdir initializing\n");
  sys_call_table = get_syscall_table();
  set_WP_0();
  hook_syscall(&(void*)sys_mkdir_old, sys_mkdir_hook, __NR_mkdir);
  set_WP_1();
}

static void __exit exit_module(void){
  set_WP_0();
  unhook_syscall((void*)sys_mkdir_old, __NR_mkdir);
  set_WP_1();
  printk("hook_mkdir exited\n");
}

module_init(init_module);
module_exit(exit_module);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("barnard33-233");
MODULE_DESCRIPTION("Hook mkdir.");