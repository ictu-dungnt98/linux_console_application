#include "timer.h"

#include "task_list.h"

ak_task_t task_list[] = {
	/* SYSTEM TASKS */
	{	AK_TASK_TIMER_ID,				TASK_PRI_LEVEL_1,	timer_entry						,	&timer_mailbox						,	"timer service"			},

	/* APP TASKS */
	{	GW_TASK_IF_CONSOLE_ID,			TASK_PRI_LEVEL_8,	gw_task_if_console_entry		,	&gw_task_if_console_mailbox			,	"terminal gate"			},
	{	GW_TASK_CONSOLE_ID,				TASK_PRI_LEVEL_8,	gw_task_console_entry			,	&gw_task_console_mailbox			,	"handle commands"		},
	{	GW_TASK_DEBUG_ID,				TASK_PRI_LEVEL_1,	gw_task_debug_entry				,	&gw_task_debug_mailbox				,	"task debug message"	},
};
