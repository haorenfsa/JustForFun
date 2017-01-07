//note this is for amd64

//includes
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

//define types
typedef int64_t                 atomic_int_t;
typedef uint64_t				atomic_uint_t;
typedef volatile sys_uint_t		atomic_t;
struct atomic_shm_addr_t{
	atomic_t;
};

#define NGX_ATOMIC_T_LEN            (sizeof("-9223372036854775808") - 1)

#define MY_SMP_LOCK  "lock;"

/*
 * "cmpxchgq  r, [m]":
 *
 *     if (rax == [m]) {
 *         zf = 1;
 *         [m] = r;
 *     } else {
 *         zf = 0;
 *         rax = [m];
 *     }
 *
 *
 * The "r" is any register, %rax (%r0) - %r16.
 * The "=a" and "a" are the %rax register.
 * Although we can return result in any register, we use "a" because it is
 * used in cmpxchgq anyway.  The result is actually in %al but not in $rax,
 * however as the code is inlined gcc can test %al as well as %rax.
 *
 * The "cc" means that flags were changed.
 */
//如果lock == old，说明锁没动过，令lock = set， 返回 1
//否则锁动过，不操作，返回0
static inline atomic_int_t
atomic_cmp_set(atomic_t *lock, atomic_uint_t old,
    atomic_uint_t set)
{
    u_char  res;
	
	//lock在多核下为锁住总线
	//指令部：输出部：输入部：损坏部
    __asm__ volatile (
         SMP_LOCK
    "    cmpxchgq  %3, %1;   "
    "    sete      %0;       "
	
    : "=a" (res) : "m" (*lock), "a" (old), "r" (set) : "cc", "memory");

    return res;
}

/*
 * "xaddq  r, [m]":
 *
 *     temp = [m];
 *     [m] += r;
 *     r = temp;
 *
 *
 * The "+r" is any register, %rax (%r0) - %r16.
 * The "cc" means that flags were changed.
 */
//value += add, 返回原先的value
static inline atomic_int_t
atomic_fetch_add(atomic_t *value, atomic_int_t add)
{
    __asm__ volatile (

         NGX_SMP_LOCK
    "    xaddq  %0, %1;   "

    : "+r" (add) : "m" (*value) : "cc", "memory");

    return add;
}

