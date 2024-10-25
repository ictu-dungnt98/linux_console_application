#ifndef __TASK_LIST_H__
#define __TASK_LIST_H__

#include "ak.h"
#include "message.h"

#include "app.h"

#include "if_console.h"

#include "task_console.h"
#include "task_debug.h"

/** default if_des_type when get pool memory
 * this define MUST BE coresponding with app.
 */

#define AK_APP_TYPE_IF						IF_TYPE_APP_GW

enum {
	/* SYSTEM TASKS */
	AK_TASK_TIMER_ID,

	/* APP TASKS */
	GW_TASK_IF_CONSOLE_ID,
	GW_TASK_CONSOLE_ID,
	GW_TASK_DEBUG_ID,

	/* EOT task ID */
	AK_TASK_LIST_LEN,
};

extern ak_task_t task_list[];

#endif //__TASK_LIST_H__
