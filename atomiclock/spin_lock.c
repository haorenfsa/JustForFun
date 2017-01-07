//lock应该从共享内存分配

#include "atomic_opt.h"
static void spin_wakeup(atomic_t *lock);

atomic_int_t spin_create(atomic_t *lock, u_char *name);
void spin_destroy(atomic_t *lock);
atomic_uint_t spin_trylock(atomic_t *lock);
void spin_lock(atomic_t *lock);
void spin_unlock(atomic_t *lock);
atomic_uint_t spin_force_unlock(atomic_t *lock, ngx_pid_t pid);
/*
ngx_int_t
ngx_shmtx_create(atomic_t *lock,  *addr, u_char *name)
{
    lock = addr

    if (mtx->spin == (ngx_uint_t) -1) {
        return NGX_OK;
    }

    mtx->spin = 2048;
}
*/