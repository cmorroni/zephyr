/*
 * Copyright (c) 2016, Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**
 * @file
 *
 * @brief Public kernel APIs.
 */

#ifndef ZEPHYR_INCLUDE_KERNEL_H_
#define ZEPHYR_INCLUDE_KERNEL_H_

#if !defined(_ASMLANGUAGE)
#include <kernel_includes.h>
#include <errno.h>
#include <stdbool.h>
#include <toolchain.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Kernel APIs
 * @defgroup kernel_apis Kernel APIs
 * @{
 * @}
 */

#ifdef CONFIG_KERNEL_DEBUG
#define K_DEBUG(fmt, ...) printk("[%s]  " fmt, __func__, ##__VA_ARGS__)
#else
#define K_DEBUG(fmt, ...)
#endif

#if defined(CONFIG_COOP_ENABLED) && defined(CONFIG_PREEMPT_ENABLED)
#define _NUM_COOP_PRIO (CONFIG_NUM_COOP_PRIORITIES)
#define _NUM_PREEMPT_PRIO (CONFIG_NUM_PREEMPT_PRIORITIES + 1)
#elif defined(CONFIG_COOP_ENABLED)
#define _NUM_COOP_PRIO (CONFIG_NUM_COOP_PRIORITIES + 1)
#define _NUM_PREEMPT_PRIO (0)
#elif defined(CONFIG_PREEMPT_ENABLED)
#define _NUM_COOP_PRIO (0)
#define _NUM_PREEMPT_PRIO (CONFIG_NUM_PREEMPT_PRIORITIES + 1)
#else
#error "invalid configuration"
#endif

#define K_PRIO_COOP(x) (-(_NUM_COOP_PRIO - (x)))
#define K_PRIO_PREEMPT(x) (x)

#define K_ANY NULL
#define K_END NULL

#if defined(CONFIG_COOP_ENABLED) && defined(CONFIG_PREEMPT_ENABLED)
#define K_HIGHEST_THREAD_PRIO (-CONFIG_NUM_COOP_PRIORITIES)
#elif defined(CONFIG_COOP_ENABLED)
#define K_HIGHEST_THREAD_PRIO (-CONFIG_NUM_COOP_PRIORITIES - 1)
#elif defined(CONFIG_PREEMPT_ENABLED)
#define K_HIGHEST_THREAD_PRIO 0
#else
#error "invalid configuration"
#endif

#ifdef CONFIG_PREEMPT_ENABLED
#define K_LOWEST_THREAD_PRIO CONFIG_NUM_PREEMPT_PRIORITIES
#else
#define K_LOWEST_THREAD_PRIO -1
#endif

#define K_IDLE_PRIO K_LOWEST_THREAD_PRIO

#define K_HIGHEST_APPLICATION_THREAD_PRIO (K_HIGHEST_THREAD_PRIO)
#define K_LOWEST_APPLICATION_THREAD_PRIO (K_LOWEST_THREAD_PRIO - 1)

#ifdef CONFIG_OBJECT_TRACING
#define _OBJECT_TRACING_NEXT_PTR(type) struct type *__next;
#define _OBJECT_TRACING_LINKED_FLAG u8_t __linked;
#define _OBJECT_TRACING_INIT \
	.__next = NULL,	     \
	.__linked = 0,
#else
#define _OBJECT_TRACING_INIT
#define _OBJECT_TRACING_NEXT_PTR(type)
#define _OBJECT_TRACING_LINKED_FLAG
#endif

#ifdef CONFIG_POLL
#define _POLL_EVENT_OBJ_INIT(obj) \
	.poll_events = SYS_DLIST_STATIC_INIT(&obj.poll_events),
#define _POLL_EVENT sys_dlist_t poll_events
#else
#define _POLL_EVENT_OBJ_INIT(obj)
#define _POLL_EVENT
#endif

struct k_thread;
struct k_mutex;
struct k_sem;
struct k_msgq;
struct k_mbox;
struct k_pipe;
struct k_queue;
struct k_fifo;
struct k_lifo;
struct k_stack;
struct k_mem_slab;
struct k_mem_pool;
struct k_timer;
struct k_poll_event;
struct k_poll_signal;
struct k_mem_domain;
struct k_mem_partition;
struct k_futex;
struct z_futex_data;


enum k_objects {
	K_OBJ_ANY,

	/** @cond
	 *  Doxygen should ignore this build-time generated include file
	 *  when genrating API documentation.  Enumeration values are
	 *  generated during build by gen_kobject_list.py.  It includes
	 *  basic kernel objects (e.g.  pipes and mutexes) and driver types.
	 */
#include <kobj-types-enum.h>
	/** @endcond
	 */

	K_OBJ_LAST
};
/**
 * @defgroup usermode_apis User Mode APIs
 * @ingroup kernel_apis
 * @{
 */

__syscall void k_object_access_grant(void *object, struct k_thread *thread);
void k_object_access_revoke(void *object, struct k_thread *thread);
void k_object_access_all_grant(void *object);

/** @} */

/* can be used for creating 'dummy' threads, e.g. for pending on objects */
struct _thread_base {

	/* this thread's entry in a ready/wait queue */
	union {
		sys_dnode_t qnode_dlist;
		struct rbnode qnode_rb;
	};

	/* wait queue on which the thread is pended (needed only for
	 * trees, not dumb lists)
	 */
	_wait_q_t *pended_on;

	/* user facing 'thread options'; values defined in include/kernel.h */
	u8_t user_options;

	/* thread state */
	u8_t thread_state;

	/*
	 * scheduler lock count and thread priority
	 *
	 * These two fields control the preemptibility of a thread.
	 *
	 * When the scheduler is locked, sched_locked is decremented, which
	 * means that the scheduler is locked for values from 0xff to 0x01. A
	 * thread is coop if its prio is negative, thus 0x80 to 0xff when
	 * looked at the value as unsigned.
	 *
	 * By putting them end-to-end, this means that a thread is
	 * non-preemptible if the bundled value is greater than or equal to
	 * 0x0080.
	 */
	union {
		struct {
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
			u8_t sched_locked;
			s8_t prio;
#else /* LITTLE and PDP */
			s8_t prio;
			u8_t sched_locked;
#endif
		};
		u16_t preempt;
	};

#ifdef CONFIG_SCHED_DEADLINE
	int prio_deadline;
#endif

	u32_t order_key;

#ifdef CONFIG_SMP
	/* True for the per-CPU idle threads */
	u8_t is_idle;

	/* CPU index on which thread was last run */
	u8_t cpu;

	/* Recursive count of irq_lock() calls */
	u8_t global_lock_count;

#endif

#ifdef CONFIG_SCHED_CPU_MASK
	/* "May run on" bits for each CPU */
	u8_t cpu_mask;
#endif

	/* data returned by APIs */
	void *swap_data;

#ifdef CONFIG_SYS_CLOCK_EXISTS
	/* this thread's entry in a timeout queue */
	struct _timeout timeout;
#endif

	_wait_q_t join_waiters;
};

typedef struct _thread_base _thread_base_t;

#if defined(CONFIG_THREAD_STACK_INFO)
/* Contains the stack information of a thread */
struct _thread_stack_info {
	/* Stack start - Represents the start address of the thread-writable
	 * stack area.
	 */
	uintptr_t start;

	/* Stack Size - Thread writable stack buffer size. Represents
	 * the size of the actual area, starting from the start member,
	 * that should be writable by the thread
	 */
	size_t size;
};

typedef struct _thread_stack_info _thread_stack_info_t;
#endif /* CONFIG_THREAD_STACK_INFO */

/**
 * @ingroup thread_apis
 * Thread Structure
 */
struct k_thread {

	struct _thread_base base;

	/** defined by the architecture, but all archs need these */
	struct _callee_saved callee_saved;

	/** static thread init data */
	void *init_data;

	/**
	 * abort function
	 * */
	void (*fn_abort)(void);

#if defined(CONFIG_THREAD_MONITOR)
	/** thread entry and parameters description */
	struct __thread_entry entry;

	/** next item in list of all threads */
	struct k_thread *next_thread;
#endif

#if defined(CONFIG_THREAD_NAME)
	/** Thread name */
	char name[CONFIG_THREAD_MAX_NAME_LEN];
#endif

#ifdef CONFIG_THREAD_CUSTOM_DATA
	/** crude thread-local storage */
	void *custom_data;
#endif

#ifdef CONFIG_THREAD_USERSPACE_LOCAL_DATA
	struct _thread_userspace_local_data *userspace_local_data;
#endif

#ifdef CONFIG_ERRNO
#ifndef CONFIG_USERSPACE
	/** per-thread errno variable */
	int errno_var;
#endif
#endif

#if defined(CONFIG_THREAD_STACK_INFO)
	/** Stack Info */
	struct _thread_stack_info stack_info;
#endif /* CONFIG_THREAD_STACK_INFO */

#if defined(CONFIG_USERSPACE)
	/** memory domain info of the thread */
	struct _mem_domain_info mem_domain_info;
	/** Base address of thread stack */
	k_thread_stack_t *stack_obj;
	/** current syscall frame pointer */
	void *syscall_frame;
#endif /* CONFIG_USERSPACE */


#if defined(CONFIG_USE_SWITCH)
	/* When using __switch() a few previously arch-specific items
	 * become part of the core OS
	 */

	/** z_swap() return value */
	int swap_retval;

	/** Context handle returned via arch_switch() */
	void *switch_handle;
#endif
	/** resource pool */
	struct k_mem_pool *resource_pool;

	/** arch-specifics: must always be at the end */
	struct _thread_arch arch;
};

typedef struct k_thread _thread_t;
typedef struct k_thread *k_tid_t;

enum execution_context_types {
	K_ISR = 0,
	K_COOP_THREAD,
	K_PREEMPT_THREAD,
};

/**
 * @addtogroup thread_apis
 * @{
 */

typedef void (*k_thread_user_cb_t)(const struct k_thread *thread,
				   void *user_data);
				   
extern void k_thread_foreach(k_thread_user_cb_t user_cb, void *user_data);
extern void k_thread_foreach_unlocked(k_thread_user_cb_t user_cb, void *user_data);

/** @} */

/**
 * @defgroup thread_apis Thread APIs
 * @ingroup kernel_apis
 * @{
 */

#endif /* !_ASMLANGUAGE */


/*
 * Thread user options. May be needed by assembly code. Common part uses low
 * bits, arch-specific use high bits.
 */


#define K_ESSENTIAL (BIT(0))

#if defined(CONFIG_FP_SHARING)

#define K_FP_REGS (BIT(1))
#endif


#define K_USER (BIT(2))


#define K_INHERIT_PERMS (BIT(3))

#ifdef CONFIG_X86
/* x86 Bitmask definitions for threads user options */

#if defined(CONFIG_FP_SHARING) && defined(CONFIG_SSE)
/* thread uses SSEx (and also FP) registers */
#define K_SSE_REGS (BIT(7))
#endif
#endif

/* end - thread options */

#if !defined(_ASMLANGUAGE)
__syscall k_tid_t k_thread_create(struct k_thread *new_thread,
				  k_thread_stack_t *stack,
				  size_t stack_size,
				  k_thread_entry_t entry,
				  void *p1, void *p2, void *p3,
				  int prio, u32_t options, k_timeout_t delay);
extern FUNC_NORETURN void k_thread_user_mode_enter(k_thread_entry_t entry,
						   void *p1, void *p2,
						   void *p3);
#define k_thread_access_grant(thread, ...) \
	FOR_EACH_FIXED_ARG(k_object_access_grant, thread, __VA_ARGS__)

__syscall s32_t k_sleep(k_timeout_t timeout);

static inline s32_t k_msleep(s32_t ms)
{
	return k_sleep(Z_TIMEOUT_MS(ms));
}

__syscall void k_busy_wait(u32_t usec_to_wait);
__syscall void k_yield(void);
__syscall k_tid_t k_current_get(void);
__syscall void k_thread_abort(k_tid_t thread);
__syscall void k_thread_start(k_tid_t thread);

extern k_ticks_t z_timeout_expires(struct _timeout *timeout);
extern k_ticks_t z_timeout_remaining(struct _timeout *timeout);

/**
 * @cond INTERNAL_HIDDEN
 */

/* timeout has timed out and is not on _timeout_q anymore */
#define _EXPIRED (-2)

struct _static_thread_data {
	struct k_thread *init_thread;
	k_thread_stack_t *init_stack;
	unsigned int init_stack_size;
	k_thread_entry_t init_entry;
	void *init_p1;
	void *init_p2;
	void *init_p3;
	int init_prio;
	u32_t init_options;
	s32_t init_delay;
	void (*init_abort)(void);
	const char *init_name;
};

#define _THREAD_INITIALIZER(thread, stack, stack_size,           \
			    entry, p1, p2, p3,                   \
			    prio, options, delay, abort, tname)  \
	{                                                        \
	.init_thread = (thread),				 \
	.init_stack = (stack),					 \
	.init_stack_size = (stack_size),                         \
	.init_entry = (k_thread_entry_t)entry,			 \
	.init_p1 = (void *)p1,                                   \
	.init_p2 = (void *)p2,                                   \
	.init_p3 = (void *)p3,                                   \
	.init_prio = (prio),                                     \
	.init_options = (options),                               \
	.init_delay = (delay),                                   \
	.init_abort = (abort),                                   \
	.init_name = STRINGIFY(tname),                           \
	}

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @brief Statically define and initialize a thread.
 *
 * The thread may be scheduled for immediate execution or a delayed start.
 *
 * Thread options are architecture-specific, and can include K_ESSENTIAL,
 * K_FP_REGS, and K_SSE_REGS. Multiple options may be specified by separating
 * them using "|" (the logical OR operator).
 *
 * The ID of the thread can be accessed using:
 *
 * @code extern const k_tid_t <name>; @endcode
 *
 * @param name Name of the thread.
 * @param stack_size Stack size in bytes.
 * @param entry Thread entry function.
 * @param p1 1st entry point parameter.
 * @param p2 2nd entry point parameter.
 * @param p3 3rd entry point parameter.
 * @param prio Thread priority.
 * @param options Thread options.
 * @param delay Scheduling delay (in milliseconds), zero for no delay.
 *
 *
 * @internal It has been observed that the x86 compiler by default aligns
 * these _static_thread_data structures to 32-byte boundaries, thereby
 * wasting space. To work around this, force a 4-byte alignment.
 *
 */
#define K_THREAD_DEFINE(name, stack_size,                                \
			entry, p1, p2, p3,                               \
			prio, options, delay)                            \
	K_THREAD_STACK_DEFINE(_k_thread_stack_##name, stack_size);	 \
	struct k_thread _k_thread_obj_##name;				 \
	Z_STRUCT_SECTION_ITERABLE(_static_thread_data, _k_thread_data_##name) =\
		_THREAD_INITIALIZER(&_k_thread_obj_##name,		 \
				    _k_thread_stack_##name, stack_size,  \
				entry, p1, p2, p3, prio, options, delay, \
				NULL, name);				 	 \
	const k_tid_t name = (k_tid_t)&_k_thread_obj_##name

extern void k_sched_time_slice_set(s32_t slice, int prio);

/** @} */

/**
 * @addtogroup isr_apis
 * @{
 */

extern bool k_is_in_isr(void);

static inline bool k_is_pre_kernel(void)
{
	extern bool z_sys_post_kernel; /* in init.c */

	return !z_sys_post_kernel;
}

/**
 * @}
 */

/**
 * @addtogroup thread_apis
 * @{
 */

extern void k_sched_lock(void);
extern void k_sched_unlock(void);
__syscall int k_thread_name_set(k_tid_t thread_id, const char *value);
const char *k_thread_name_get(k_tid_t thread_id);
const char *k_thread_state_str(k_tid_t thread_id);

/**
 * @}
 */

/**
 * @addtogroup clock_apis
 * @{
 */

#define K_NO_WAIT Z_TIMEOUT_NO_WAIT
#define K_NSEC(t)      Z_TIMEOUT_NS(t)
#define K_USEC(t)      Z_TIMEOUT_US(t)
#define K_CYC(t)       Z_TIMEOUT_CYC(t)
#define K_TICKS(t)     Z_TIMEOUT_TICKS(t)
#define K_MSEC(ms)     Z_TIMEOUT_MS(ms)
#define K_SECONDS(s)   K_MSEC((s) * MSEC_PER_SEC)
#define K_MINUTES(m)   K_SECONDS((m) * 60)
#define K_HOURS(h)     K_MINUTES((h) * 60)
#define K_FOREVER Z_FOREVER

/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_timer {
	/*
	 * _timeout structure must be first here if we want to use
	 * dynamic timer allocation. timeout.node is used in the double-linked
	 * list of free timers
	 */
	struct _timeout timeout;

	/* wait queue for the (single) thread waiting on this timer */
	_wait_q_t wait_q;

	/* runs in ISR context */
	void (*expiry_fn)(struct k_timer *timer);

	/* runs in the context of the thread that calls k_timer_stop() */
	void (*stop_fn)(struct k_timer *timer);

	/* timer period */
	k_timeout_t period;

	/* timer status */
	u32_t status;

	/* user-specific data, also used to support legacy features */
	void *user_data;

	_OBJECT_TRACING_NEXT_PTR(k_timer)
	_OBJECT_TRACING_LINKED_FLAG
};

#define Z_TIMER_INITIALIZER(obj, expiry, stop) \
	{ \
	.timeout = { \
		.node = {},\
		.dticks = 0, \
		.fn = z_timer_expiration_handler \
	}, \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.expiry_fn = expiry, \
	.stop_fn = stop, \
	.status = 0, \
	.user_data = 0, \
	_OBJECT_TRACING_INIT \
	}

#define K_TIMER_INITIALIZER __DEPRECATED_MACRO Z_TIMER_INITIALIZER

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup timer_apis Timer APIs
 * @ingroup kernel_apis
 * @{
 */

typedef void (*k_timer_expiry_t)(struct k_timer *timer);
typedef void (*k_timer_stop_t)(struct k_timer *timer);

#define K_TIMER_DEFINE(name, expiry_fn, stop_fn) \
	Z_STRUCT_SECTION_ITERABLE(k_timer, name) = \
		Z_TIMER_INITIALIZER(name, expiry_fn, stop_fn)


extern void k_timer_init(struct k_timer *timer,
			 k_timer_expiry_t expiry_fn,
			 k_timer_stop_t stop_fn);
__syscall void k_timer_start(struct k_timer *timer, k_timeout_t duration, k_timeout_t period);
__syscall void k_timer_stop(struct k_timer *timer);
__syscall void k_timer_user_data_set(struct k_timer *timer, void *user_data);
__syscall void *k_timer_user_data_get(struct k_timer *timer);

/** @} */

/**
 * @addtogroup clock_apis
 * @{
 */


__syscall s64_t k_uptime_ticks(void);

static inline s64_t k_uptime_get(void)
{
	return 0;
}

static inline u32_t k_uptime_get_32(void)
{
	return 0;
}

static inline s64_t k_uptime_delta(s64_t *reftime)
{
	return 0;
}

static inline u32_t k_cycle_get_32(void)
{
	return 0;
}

/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_queue {
	sys_sflist_t data_q;
	struct k_spinlock lock;
	union {
		_wait_q_t wait_q;

		_POLL_EVENT;
	};

	_OBJECT_TRACING_NEXT_PTR(k_queue)
	_OBJECT_TRACING_LINKED_FLAG
};

#define _K_QUEUE_INITIALIZER(obj) \
	{ \
	.data_q = SYS_SLIST_STATIC_INIT(&obj.data_q), \
	.lock = { }, \
	{ \
		.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
		_POLL_EVENT_OBJ_INIT(obj) \
	}, \
	_OBJECT_TRACING_INIT \
	}

#define K_QUEUE_INITIALIZER __DEPRECATED_MACRO _K_QUEUE_INITIALIZER

extern void *z_queue_node_peek(sys_sfnode_t *node, bool needs_free);

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup queue_apis Queue APIs
 * @ingroup kernel_apis
 * @{
 */


__syscall void k_queue_init(struct k_queue *queue);
extern void k_queue_append(struct k_queue *queue, void *data);
__syscall s32_t k_queue_alloc_append(struct k_queue *queue, void *data);
extern void k_queue_prepend(struct k_queue *queue, void *data);
extern int k_queue_append_list(struct k_queue *queue, void *head, void *tail);
__syscall void *k_queue_get(struct k_queue *queue, k_timeout_t timeout);
__syscall int k_queue_is_empty(struct k_queue *queue);

static inline int z_impl_k_queue_is_empty(struct k_queue *queue)
{
	return (int)sys_sflist_is_empty(&queue->data_q);
}

/**
 * @brief Statically define and initialize a queue.
 *
 * The queue can be accessed outside the module where it is defined using:
 *
 * @code extern struct k_queue <name>; @endcode
 *
 * @param name Name of the queue.
 */
#define K_QUEUE_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_queue, name) = \
		_K_QUEUE_INITIALIZER(name)

/** @} */

struct k_fifo {
	struct k_queue _queue;
};

/**
 * @cond INTERNAL_HIDDEN
 */
#define Z_FIFO_INITIALIZER(obj) \
	{ \
	._queue = _K_QUEUE_INITIALIZER(obj._queue) \
	}

#define K_FIFO_INITIALIZER __DEPRECATED_MACRO Z_FIFO_INITIALIZER

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup fifo_apis FIFO APIs
 * @ingroup kernel_apis
 * @{
 */


#define k_fifo_init(fifo) \
	k_queue_init(&(fifo)->_queue)


#define k_fifo_put(fifo, data) \
	k_queue_append(&(fifo)->_queue, data)


#define k_fifo_put_list(fifo, head, tail) \
	k_queue_append_list(&(fifo)->_queue, head, tail)


#define k_fifo_get(fifo, timeout) \
	k_queue_get(&(fifo)->_queue, timeout)


#define k_fifo_is_empty(fifo) \
	k_queue_is_empty(&(fifo)->_queue)


#define K_FIFO_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_fifo, name) = \
		Z_FIFO_INITIALIZER(name)

/** @} */

struct k_lifo {
	struct k_queue _queue;
};

/**
 * @cond INTERNAL_HIDDEN
 */

#define _K_LIFO_INITIALIZER(obj) \
	{ \
	._queue = _K_QUEUE_INITIALIZER(obj._queue) \
	}

#define K_LIFO_INITIALIZER __DEPRECATED_MACRO _K_LIFO_INITIALIZER

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup lifo_apis LIFO APIs
 * @ingroup kernel_apis
 * @{
 */


#define k_lifo_put(lifo, data) \
	k_queue_prepend(&(lifo)->_queue, data)


#define k_lifo_get(lifo, timeout) \
	k_queue_get(&(lifo)->_queue, timeout)


#define K_LIFO_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_lifo, name) = \
		_K_LIFO_INITIALIZER(name)

/** @} */

/**
 * @cond INTERNAL_HIDDEN
 */
#define K_STACK_FLAG_ALLOC	((u8_t)1)	/* Buffer was allocated */

typedef uintptr_t stack_data_t;

struct k_stack {
	_wait_q_t wait_q;
	struct k_spinlock lock;
	stack_data_t *base, *next, *top;

	_OBJECT_TRACING_NEXT_PTR(k_stack)
	_OBJECT_TRACING_LINKED_FLAG
	u8_t flags;
};

#define _K_STACK_INITIALIZER(obj, stack_buffer, stack_num_entries) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q),	\
	.base = stack_buffer, \
	.next = stack_buffer, \
	.top = stack_buffer + stack_num_entries, \
	_OBJECT_TRACING_INIT \
	}

#define K_STACK_INITIALIZER __DEPRECATED_MACRO _K_STACK_INITIALIZER

/**
 * INTERNAL_HIDDEN @endcond
 */

struct k_work;
struct k_work_poll;

/* private, used by k_poll and k_work_poll */
typedef int (*_poller_cb_t)(struct k_poll_event *event, u32_t state);
struct _poller {
	volatile bool is_polling;
	struct k_thread *thread;
	_poller_cb_t cb;
};

/**
 * @addtogroup thread_apis
 * @{
 */

typedef void (*k_work_handler_t)(struct k_work *work);

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_work_q {
	struct k_queue queue;
	struct k_thread thread;
};

enum {
	K_WORK_STATE_PENDING,	/* Work item pending state */
};

struct k_work {
	void *_reserved;		/* Used by k_queue implementation. */
	k_work_handler_t handler;
	atomic_t flags[1];
};

struct k_delayed_work {
	struct k_work work;
	struct _timeout timeout;
	struct k_work_q *work_q;
};

struct k_work_poll {
	struct k_work work;
	struct _poller poller;
	struct k_poll_event *events;
	int num_events;
	k_work_handler_t real_handler;
	struct _timeout timeout;
	int poll_result;
};

extern struct k_work_q k_sys_work_q;

/**
 * INTERNAL_HIDDEN @endcond
 */

#define Z_WORK_INITIALIZER(work_handler) \
	{ \
	._reserved = NULL, \
	.handler = work_handler, \
	.flags = { 0 } \
	}

#define K_WORK_INITIALIZER __DEPRECATED_MACRO Z_WORK_INITIALIZER

#define K_WORK_DEFINE(work, work_handler) \
	struct k_work work = Z_WORK_INITIALIZER(work_handler)


static inline void k_work_init(struct k_work *work, k_work_handler_t handler)
{
}

extern void k_delayed_work_init(struct k_delayed_work *work,
				k_work_handler_t handler);


extern int k_delayed_work_cancel(struct k_delayed_work *work);


static inline void k_work_submit(struct k_work *work)
{
}


static inline int k_delayed_work_submit(struct k_delayed_work *work,
					k_timeout_t delay)
{
	return 0;
}

static inline s32_t k_delayed_work_remaining_get(struct k_delayed_work *work)
{
	return 0;
}

/** @} */
/**
 * @defgroup mutex_apis Mutex APIs
 * @ingroup kernel_apis
 * @{
 */

/**
 * Mutex Structure
 * @ingroup mutex_apis
 */
struct k_mutex {
	/** Mutex wait queue */
	_wait_q_t wait_q;
	/** Mutex owner */
	struct k_thread *owner;

	/** Current lock count */
	u32_t lock_count;

	/** Original thread priority */
	int owner_orig_prio;

	_OBJECT_TRACING_NEXT_PTR(k_mutex)
	_OBJECT_TRACING_LINKED_FLAG
};

/**
 * @cond INTERNAL_HIDDEN
 */
#define _K_MUTEX_INITIALIZER(obj) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.owner = NULL, \
	.lock_count = 0, \
	.owner_orig_prio = K_LOWEST_THREAD_PRIO, \
	_OBJECT_TRACING_INIT \
	}

#define K_MUTEX_INITIALIZER __DEPRECATED_MACRO _K_MUTEX_INITIALIZER

/**
 * INTERNAL_HIDDEN @endcond
 */


#define K_MUTEX_DEFINE(name) \
	Z_STRUCT_SECTION_ITERABLE(k_mutex, name) = \
		_K_MUTEX_INITIALIZER(name)


__syscall int k_mutex_init(struct k_mutex *mutex);
__syscall int k_mutex_lock(struct k_mutex *mutex, k_timeout_t timeout);
__syscall int k_mutex_unlock(struct k_mutex *mutex);

/**
 * @}
 */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_sem {
	_wait_q_t wait_q;
	u32_t count;
	u32_t limit;
	_POLL_EVENT;

	_OBJECT_TRACING_NEXT_PTR(k_sem)
	_OBJECT_TRACING_LINKED_FLAG
};

#define Z_SEM_INITIALIZER(obj, initial_count, count_limit) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.count = initial_count, \
	.limit = count_limit, \
	_POLL_EVENT_OBJ_INIT(obj) \
	_OBJECT_TRACING_INIT \
	}

#define K_SEM_INITIALIZER __DEPRECATED_MACRO Z_SEM_INITIALIZER

/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup semaphore_apis Semaphore APIs
 * @ingroup kernel_apis
 * @{
 */


__syscall int k_sem_init(struct k_sem *sem, unsigned int initial_count, unsigned int limit);
__syscall int k_sem_take(struct k_sem *sem, k_timeout_t timeout);
__syscall void k_sem_give(struct k_sem *sem);
__syscall unsigned int k_sem_count_get(struct k_sem *sem);

#define K_SEM_DEFINE(name, initial_count, count_limit) \
	Z_STRUCT_SECTION_ITERABLE(k_sem, name) = \
		Z_SEM_INITIALIZER(name, initial_count, count_limit); \
	BUILD_ASSERT(((count_limit) != 0) && \
		     ((initial_count) <= (count_limit)));

/** @} */

/**
 * @defgroup msgq_apis Message Queue APIs
 * @ingroup kernel_apis
 * @{
 */


struct k_msgq {
	/** Message queue wait queue */
	_wait_q_t wait_q;
	/** Lock */
	struct k_spinlock lock;
	/** Message size */
	size_t msg_size;
	/** Maximal number of messages */
	u32_t max_msgs;
	/** Start of message buffer */
	char *buffer_start;
	/** End of message buffer */
	char *buffer_end;
	/** Read pointer */
	char *read_ptr;
	/** Write pointer */
	char *write_ptr;
	/** Number of used messages */
	u32_t used_msgs;

	_OBJECT_TRACING_NEXT_PTR(k_msgq)
	_OBJECT_TRACING_LINKED_FLAG

	/** Message queue */
	u8_t flags;
};
/**
 * @cond INTERNAL_HIDDEN
 */


#define _K_MSGQ_INITIALIZER(obj, q_buffer, q_msg_size, q_max_msgs) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.msg_size = q_msg_size, \
	.max_msgs = q_max_msgs, \
	.buffer_start = q_buffer, \
	.buffer_end = q_buffer + (q_max_msgs * q_msg_size), \
	.read_ptr = q_buffer, \
	.write_ptr = q_buffer, \
	.used_msgs = 0, \
	_OBJECT_TRACING_INIT \
	}
#define K_MSGQ_INITIALIZER __DEPRECATED_MACRO _K_MSGQ_INITIALIZER
/**
 * INTERNAL_HIDDEN @endcond
 */


#define K_MSGQ_FLAG_ALLOC	BIT(0)

#define K_MSGQ_DEFINE(q_name, q_msg_size, q_max_msgs, q_align)		\
	static char __noinit __aligned(q_align)				\
		_k_fifo_buf_##q_name[(q_max_msgs) * (q_msg_size)];	\
	Z_STRUCT_SECTION_ITERABLE(k_msgq, q_name) =			\
	       _K_MSGQ_INITIALIZER(q_name, _k_fifo_buf_##q_name,	\
				  q_msg_size, q_max_msgs)


__syscall int k_msgq_put(struct k_msgq *msgq, void *data, k_timeout_t timeout);
__syscall int k_msgq_get(struct k_msgq *msgq, void *data, k_timeout_t timeout);
__syscall int k_msgq_peek(struct k_msgq *msgq, void *data);

/** @} */

/**
 * @cond INTERNAL_HIDDEN
 */

struct k_mem_slab {
	_wait_q_t wait_q;
	u32_t num_blocks;
	size_t block_size;
	char *buffer;
	char *free_list;
	u32_t num_used;

	_OBJECT_TRACING_NEXT_PTR(k_mem_slab)
	_OBJECT_TRACING_LINKED_FLAG
};

#define _K_MEM_SLAB_INITIALIZER(obj, slab_buffer, slab_block_size, \
			       slab_num_blocks) \
	{ \
	.wait_q = Z_WAIT_Q_INIT(&obj.wait_q), \
	.num_blocks = slab_num_blocks, \
	.block_size = slab_block_size, \
	.buffer = slab_buffer, \
	.free_list = NULL, \
	.num_used = 0, \
	_OBJECT_TRACING_INIT \
	}

#define K_MEM_SLAB_INITIALIZER __DEPRECATED_MACRO _K_MEM_SLAB_INITIALIZER


/**
 * INTERNAL_HIDDEN @endcond
 */

/**
 * @defgroup mem_slab_apis Memory Slab APIs
 * @ingroup kernel_apis
 * @{
 */

#define K_MEM_SLAB_DEFINE(name, slab_block_size, slab_num_blocks, slab_align) \
	char __noinit __aligned(WB_UP(slab_align)) \
	   _k_mem_slab_buf_##name[(slab_num_blocks) * WB_UP(slab_block_size)]; \
	Z_STRUCT_SECTION_ITERABLE(k_mem_slab, name) = \
		_K_MEM_SLAB_INITIALIZER(name, _k_mem_slab_buf_##name, \
					WB_UP(slab_block_size), slab_num_blocks)

extern int k_mem_slab_init(struct k_mem_slab *slab, void *buffer, size_t block_size, u32_t num_blocks);
extern int k_mem_slab_alloc(struct k_mem_slab *slab, void **mem, k_timeout_t timeout);
extern void k_mem_slab_free(struct k_mem_slab *slab, void **mem);

/** @} */

/**
 * @addtogroup mem_pool_apis
 * @{
 */

extern int k_mem_pool_alloc(struct k_mem_pool *pool, struct k_mem_block *block, size_t size, k_timeout_t timeout);
extern void k_mem_pool_free_id(struct k_mem_block_id *id);

/** @} */

/* polling API - PRIVATE */

#ifdef CONFIG_POLL
#define _INIT_OBJ_POLL_EVENT(obj) do { (obj)->poll_event = NULL; } while (false)
#else
#define _INIT_OBJ_POLL_EVENT(obj) do { } while (false)
#endif

/* private - types bit positions */
enum _poll_types_bits {
	/* can be used to ignore an event */
	_POLL_TYPE_IGNORE,

	/* to be signaled by k_poll_signal_raise() */
	_POLL_TYPE_SIGNAL,

	/* semaphore availability */
	_POLL_TYPE_SEM_AVAILABLE,

	/* queue/fifo/lifo data availability */
	_POLL_TYPE_DATA_AVAILABLE,

	_POLL_NUM_TYPES
};

#define Z_POLL_TYPE_BIT(type) (1 << ((type) - 1))

/* private - states bit positions */
enum _poll_states_bits {
	/* default state when creating event */
	_POLL_STATE_NOT_READY,

	/* signaled by k_poll_signal_raise() */
	_POLL_STATE_SIGNALED,

	/* semaphore is available */
	_POLL_STATE_SEM_AVAILABLE,

	/* data is available to read on queue/fifo/lifo */
	_POLL_STATE_DATA_AVAILABLE,

	/* queue/fifo/lifo wait was cancelled */
	_POLL_STATE_CANCELLED,

	_POLL_NUM_STATES
};

#define Z_POLL_STATE_BIT(state) (1 << ((state) - 1))

#define _POLL_EVENT_NUM_UNUSED_BITS \
	(32 - (0 \
	       + 8 /* tag */ \
	       + _POLL_NUM_TYPES \
	       + _POLL_NUM_STATES \
	       + 1 /* modes */ \
	      ))

/* end of polling API - PRIVATE */


/**
 * @defgroup poll_apis Async polling APIs
 * @ingroup kernel_apis
 * @{
 */

/* Public polling API */

/* public - values for k_poll_event.type bitfield */
#define K_POLL_TYPE_IGNORE 0
#define K_POLL_TYPE_SIGNAL Z_POLL_TYPE_BIT(_POLL_TYPE_SIGNAL)
#define K_POLL_TYPE_SEM_AVAILABLE Z_POLL_TYPE_BIT(_POLL_TYPE_SEM_AVAILABLE)
#define K_POLL_TYPE_DATA_AVAILABLE Z_POLL_TYPE_BIT(_POLL_TYPE_DATA_AVAILABLE)
#define K_POLL_TYPE_FIFO_DATA_AVAILABLE K_POLL_TYPE_DATA_AVAILABLE

/* public - polling modes */
enum k_poll_modes {
	/* polling thread does not take ownership of objects when available */
	K_POLL_MODE_NOTIFY_ONLY = 0,

	K_POLL_NUM_MODES
};

/* public - values for k_poll_event.state bitfield */
#define K_POLL_STATE_NOT_READY 0
#define K_POLL_STATE_SIGNALED Z_POLL_STATE_BIT(_POLL_STATE_SIGNALED)
#define K_POLL_STATE_SEM_AVAILABLE Z_POLL_STATE_BIT(_POLL_STATE_SEM_AVAILABLE)
#define K_POLL_STATE_DATA_AVAILABLE Z_POLL_STATE_BIT(_POLL_STATE_DATA_AVAILABLE)
#define K_POLL_STATE_FIFO_DATA_AVAILABLE K_POLL_STATE_DATA_AVAILABLE
#define K_POLL_STATE_CANCELLED Z_POLL_STATE_BIT(_POLL_STATE_CANCELLED)

/* public - poll signal object */
struct k_poll_signal {
	/** PRIVATE - DO NOT TOUCH */
	sys_dlist_t poll_events;

	/**
	 * 1 if the event has been signaled, 0 otherwise. Stays set to 1 until
	 * user resets it to 0.
	 */
	unsigned int signaled;

	/** custom result value passed to k_poll_signal_raise() if needed */
	int result;
};

#define K_POLL_SIGNAL_INITIALIZER(obj) \
	{ \
	.poll_events = SYS_DLIST_STATIC_INIT(&obj.poll_events), \
	.signaled = 0, \
	.result = 0, \
	}

struct k_poll_event {
	/** PRIVATE - DO NOT TOUCH */
	sys_dnode_t _node;

	/** PRIVATE - DO NOT TOUCH */
	struct _poller *poller;

	/** optional user-specified tag, opaque, untouched by the API */
	u32_t tag:8;

	/** bitfield of event types (bitwise-ORed K_POLL_TYPE_xxx values) */
	u32_t type:_POLL_NUM_TYPES;

	/** bitfield of event states (bitwise-ORed K_POLL_STATE_xxx values) */
	u32_t state:_POLL_NUM_STATES;

	/** mode of operation, from enum k_poll_modes */
	u32_t mode:1;

	/** unused bits in 32-bit word */
	u32_t unused:_POLL_EVENT_NUM_UNUSED_BITS;

	/** per-type data */
	union {
		void *obj;
		struct k_poll_signal *signal;
		struct k_sem *sem;
		struct k_fifo *fifo;
		struct k_queue *queue;
	};
};

#define K_POLL_EVENT_INITIALIZER(event_type, event_mode, event_obj) \
	{ \
	.poller = NULL, \
	.type = event_type, \
	.state = K_POLL_STATE_NOT_READY, \
	.mode = event_mode, \
	.unused = 0, \
	{ .obj = event_obj }, \
	}

#define K_POLL_EVENT_STATIC_INITIALIZER(event_type, event_mode, event_obj, \
					event_tag) \
	{ \
	.tag = event_tag, \
	.type = event_type, \
	.state = K_POLL_STATE_NOT_READY, \
	.mode = event_mode, \
	.unused = 0, \
	{ .obj = event_obj }, \
	}



extern void k_poll_event_init(struct k_poll_event *event, u32_t type, int mode, void *obj);
__syscall int k_poll(struct k_poll_event *events, int num_events, k_timeout_t timeout);
__syscall void k_poll_signal_init(struct k_poll_signal *signal);
__syscall void k_poll_signal_reset(struct k_poll_signal *signal);

static inline void z_impl_k_poll_signal_reset(struct k_poll_signal *signal)
{
}

__syscall void k_poll_signal_check(struct k_poll_signal *signal, unsigned int *signaled, int *result);
__syscall int k_poll_signal_raise(struct k_poll_signal *signal, int result);

/** @} */

#define z_except_reason(reason)	ARCH_EXCEPT(reason)
#define k_oops()	z_except_reason(K_ERR_KERNEL_OOPS)
#define k_panic()	z_except_reason(K_ERR_KERNEL_PANIC)

/*
 * private APIs that are utilized by one or more public APIs
 */

#ifdef __cplusplus
}
#endif

#include <syscalls/kernel.h>

#endif /* !_ASMLANGUAGE */

#endif /* ZEPHYR_INCLUDE_KERNEL_H_ */
