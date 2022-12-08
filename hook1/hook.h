#ifndef __KERNEL_HOOK_H
#define __KERNEL_HOOK_H

typedef int (*sys_mkdir_t)(const char*, mode_t);

extern sys_mkdir_t sys_mkdir_old;
extern void** sys_call_table;

int sys_mkdir_hook(const char* path, mode_t mode);
void ** get_syscall_table();

void hook_syscall(void** sys_fn_old, void* sys_fn_hook, int syscall_id);
void unhook_syscall(void* sys_fn_old, int syscall_id);

#define WP 0x00010000UL

inline void set_WP_0();
inline void set_WP_1();

#endif