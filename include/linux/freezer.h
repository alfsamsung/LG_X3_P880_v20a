/* Freezer declarations */

#ifndef FREEZER_H_INCLUDED
#define FREEZER_H_INCLUDED

#include <linux/sched.h>
#include <linux/wait.h>

#ifdef CONFIG_FREEZER
/*
 * Check if a process has been frozen
 */
static inline int frozen(struct task_struct *p)
{
	return p->flags & PF_FROZEN;
}

/*
 * Check if there is a request to freeze a process
 */
static inline int freezing(struct task_struct *p)
{
	return test_tsk_thread_flag(p, TIF_FREEZE);
}

/*
 * Request that a process be frozen
 */
static inline void set_freeze_flag(struct task_struct *p)
{
	set_tsk_thread_flag(p, TIF_FREEZE);
}

/*
 * Sometimes we may need to cancel the previous 'freeze' request
 */
static inline void clear_freeze_flag(struct task_struct *p)
{
	clear_tsk_thread_flag(p, TIF_FREEZE);
}

static inline bool should_send_signal(struct task_struct *p)
{
	return !(p->flags & PF_FREEZER_NOSIG);
}

/* Takes and releases task alloc lock using task_lock() */
extern void __thaw_task(struct task_struct *t);

extern bool __refrigerator(void);
extern int freeze_processes(void);
extern int freeze_kernel_threads(void);
extern void thaw_processes(void);

static inline bool try_to_freeze(void)
{
	might_sleep();
	if (likely(!freezing(current)))
		return false;
	return __refrigerator();
}

extern bool freeze_task(struct task_struct *p, bool sig_only);
extern void cancel_freezing(struct task_struct *p);

#ifdef CONFIG_CGROUP_FREEZER
extern int cgroup_freezing_or_frozen(struct task_struct *task);
#else /* !CONFIG_CGROUP_FREEZER */
static inline int cgroup_freezing_or_frozen(struct task_struct *task)
{
	return 0;
}
#endif /* !CONFIG_CGROUP_FREEZER */

/*
 * The PF_FREEZER_SKIP flag should be set by a vfork parent right before it
 * calls wait_for_completion(&vfork) and reset right after it returns from this
 * function.  Next, the parent should call try_to_freeze() to freeze itself
 * appropriately in case the child has exited before the freezing of tasks is
 * complete.  However, we don't want kernel threads to be frozen in unexpected
 * places, so we allow them to block freeze_processes() instead or to set
 * PF_NOFREEZE if needed and PF_FREEZER_SKIP is only set for userland vfork
 * parents.  Fortunately, in the ____call_usermodehelper() case the parent won't
 * really block freeze_processes(), since ____call_usermodehelper() (the child)
 * does a little before exec/exit and it can't be frozen before waking up the
 * parent.
 */

/*
 * If the current task is a user space one, tell the freezer not to count it as
 * freezable.
 */
static inline void freezer_do_not_count(void)
{
	if (current->mm)
		current->flags |= PF_FREEZER_SKIP;
}

/*
 * If the current task is a user space one, tell the freezer to count it as
 * freezable again and try to freeze it.
 */
static inline void freezer_count(void)
{
	if (current->mm) {
		current->flags &= ~PF_FREEZER_SKIP;
		try_to_freeze();
	}
}

/*
 * Check if the task should be counted as freezable by the freezer
 */
static inline int freezer_should_skip(struct task_struct *p)
{
	return !!(p->flags & PF_FREEZER_SKIP);
}

/*
 * These macros are intended to be used whenever you want allow a sleeping
 * task to be frozen. Note that neither return any clear indication of
 * whether a freeze event happened while in this function.
 */

/* Like schedule(), but should not block the freezer. */
#define freezable_schedule() \
({ \
	freezer_do_not_count(); \
	schedule(); \
	freezer_count(); \
})

/* Like schedule_timeout_killable(), but should not block the freezer. */
#define freezable_schedule_timeout_killable(timeout) \
({ \
	freezer_do_not_count(); \
	schedule_timeout_killable(timeout); \
	freezer_count(); \
})

/*
 * Tell the freezer that the current task should be frozen by it
 */
static inline void set_freezable(void)
{
	current->flags &= ~PF_NOFREEZE;
}

/*
 * Tell the freezer that the current task should be frozen by it and that it
 * should send a fake signal to the task to freeze it.
 */
static inline void set_freezable_with_signal(void)
{
	current->flags &= ~(PF_NOFREEZE | PF_FREEZER_NOSIG);
}

/*
 * Freezer-friendly wrappers around wait_event_interruptible(),
 * wait_event_killable() and wait_event_interruptible_timeout(), originally
 * defined in <linux/wait.h>
 */

#define wait_event_freezekillable(wq, condition)			\
({									\
	int __retval;							\
	freezer_do_not_count();						\
	__retval = wait_event_killable(wq, (condition));		\
	freezer_count();						\
	__retval;							\
})

#define wait_event_freezable(wq, condition)				\
({									\
	int __retval;							\
	do {								\
		__retval = wait_event_interruptible(wq, 		\
				(condition) || freezing(current));	\
		if (__retval && !freezing(current))			\
			break;						\
		else if (!(condition))					\
			__retval = -ERESTARTSYS;			\
	} while (try_to_freeze());					\
	__retval;							\
})


#define wait_event_freezable_timeout(wq, condition, timeout)		\
({									\
	long __retval = timeout;					\
	do {								\
		__retval = wait_event_interruptible_timeout(wq,		\
				(condition) || freezing(current),	\
				__retval); 				\
	} while (try_to_freeze());					\
	__retval;							\
})
#else /* !CONFIG_FREEZER */
static inline int frozen(struct task_struct *p) { return 0; }
static inline int freezing(struct task_struct *p) { return 0; }
static inline void set_freeze_flag(struct task_struct *p) {}
static inline void clear_freeze_flag(struct task_struct *p) {}

static inline bool __refrigerator(void) { return false; }
static inline int freeze_processes(void) { return -ENOSYS; }
static inline int freeze_kernel_threads(void) { return -ENOSYS; }
static inline void thaw_processes(void) {}

static inline bool try_to_freeze(void) { return false; }

static inline void freezer_do_not_count(void) {}
static inline void freezer_count(void) {}
static inline int freezer_should_skip(struct task_struct *p) { return 0; }
static inline void set_freezable(void) {}
static inline void set_freezable_with_signal(void) {}

#define freezable_schedule() schedule()

#define freezable_schedule_timeout_killable(timeout) \
	schedule_timeout_killable(timeout)

#define wait_event_freezable(wq, condition)				\
		wait_event_interruptible(wq, condition)

#define wait_event_freezable_timeout(wq, condition, timeout)		\
		wait_event_interruptible_timeout(wq, condition, timeout)

#define wait_event_freezekillable(wq, condition)		\
		wait_event_killable(wq, condition)

#endif /* !CONFIG_FREEZER */

#endif	/* FREEZER_H_INCLUDED */
