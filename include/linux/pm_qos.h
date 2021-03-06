#ifndef _LINUX_PM_QOS_H
#define _LINUX_PM_QOS_H
/* interface for the pm_qos_power infrastructure of the linux kernel.
 *
 * Mark Gross <mgross@linux.intel.com>
 */
#include <linux/plist.h>
#include <linux/notifier.h>
#include <linux/miscdevice.h>
#include <linux/workqueue.h>

enum {
	PM_QOS_RESERVED = 0,
	PM_QOS_CPU_DMA_LATENCY,
	PM_QOS_NETWORK_LATENCY,
	PM_QOS_NETWORK_THROUGHPUT,
	PM_QOS_MIN_ONLINE_CPUS,
	PM_QOS_MAX_ONLINE_CPUS,
	PM_QOS_CPU_FREQ_MIN,
	PM_QOS_CPU_FREQ_MAX,
	PM_QOS_GPU_FREQ_MIN,
	PM_QOS_GPU_FREQ_MAX,

	/* insert new class ID */

	PM_QOS_NUM_CLASSES,
};

#define PM_QOS_DEFAULT_VALUE -1

#define PM_QOS_CPU_DMA_LAT_DEFAULT_VALUE	(2000 * USEC_PER_SEC)
#define PM_QOS_NETWORK_LAT_DEFAULT_VALUE	(2000 * USEC_PER_SEC)
#define PM_QOS_NETWORK_THROUGHPUT_DEFAULT_VALUE	0
#define PM_QOS_MIN_ONLINE_CPUS_DEFAULT_VALUE	0
#define PM_QOS_MAX_ONLINE_CPUS_DEFAULT_VALUE	LONG_MAX
#define PM_QOS_CPU_FREQ_MIN_DEFAULT_VALUE	0
#define PM_QOS_CPU_FREQ_MAX_DEFAULT_VALUE	LONG_MAX
#define PM_QOS_GPU_FREQ_MIN_DEFAULT_VALUE	0
#define PM_QOS_GPU_FREQ_MAX_DEFAULT_VALUE	LONG_MAX

struct pm_qos_request {
	struct plist_node node;
	int pm_qos_class;
	struct delayed_work work; /* for pm_qos_update_request_timeout */
};

struct pm_qos_flags_request {
	struct list_head node;
	s32 flags;	/* Do not change to 64 bit */
};

enum pm_qos_type {
	PM_QOS_UNITIALIZED,
	PM_QOS_MAX,		/* return the largest value */
	PM_QOS_MIN		/* return the smallest value */
};

/*
 * Note: The lockless read path depends on the CPU accessing target_value
 * or effective_flags atomically.  Atomic access is only guaranteed on all CPU
 * types linux supports for 32 bit quantites
 */
struct pm_qos_constraints {
	struct plist_head list;
	s32 target_value;	/* Do not change to 64 bit */
	s32 default_value;
	enum pm_qos_type type;
	struct blocking_notifier_head *notifiers;
};

struct pm_qos_flags {
	struct list_head list;
	s32 effective_flags;	/* Do not change to 64 bit */
};

/* Action requested to pm_qos_update_target */
enum pm_qos_req_action {
	PM_QOS_ADD_REQ,		/* Add a new request */
	PM_QOS_UPDATE_REQ,	/* Update an existing request */
	PM_QOS_REMOVE_REQ	/* Remove an existing request */
};

#ifdef CONFIG_PM
int pm_qos_update_target(struct pm_qos_constraints *c, struct plist_node *node,
			 enum pm_qos_req_action action, int value);
bool pm_qos_update_flags(struct pm_qos_flags *pqf,
			 struct pm_qos_flags_request *req,
			 enum pm_qos_req_action action, s32 val);
void pm_qos_add_request(struct pm_qos_request *req, int pm_qos_class,
			s32 value);
void pm_qos_update_request(struct pm_qos_request *req,
			   s32 new_value);
void pm_qos_update_request_timeout(struct pm_qos_request *req,
				   s32 new_value, unsigned long timeout_us);
void pm_qos_remove_request(struct pm_qos_request *req);

int pm_qos_request(int pm_qos_class);
int pm_qos_add_notifier(int pm_qos_class, struct notifier_block *notifier);
int pm_qos_remove_notifier(int pm_qos_class, struct notifier_block *notifier);
int pm_qos_request_active(struct pm_qos_request *req);
#else
static inline int pm_qos_update_target(struct pm_qos_constraints *c,
				       struct plist_node *node,
				       enum pm_qos_req_action action,
				       int value)
			{ return 0; }
static inline void pm_qos_add_request(struct pm_qos_request *req,
				      int pm_qos_class, s32 value)
			{ return; }
static inline void pm_qos_update_request(struct pm_qos_request *req,
					 s32 new_value)
			{ return; }
static inline void pm_qos_remove_request(struct pm_qos_request *req)
			{ return; }

static inline int pm_qos_request(int pm_qos_class)
			{ return 0; }
static inline int pm_qos_add_notifier(int pm_qos_class,
				      struct notifier_block *notifier)
			{ return 0; }
static inline int pm_qos_remove_notifier(int pm_qos_class,
					 struct notifier_block *notifier)
			{ return 0; }
static inline int pm_qos_request_active(struct pm_qos_request *req)
			{ return 0; }
#endif

#endif
