#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/stat.h>

#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

#include <ao/ao.h>
#include <mpg123.h>

#include "ak.h"
#include "timer.h"

#include "cmd_line.h"

#include "app.h"
#include "app_dbg.h"
#include "shell.h"

#include "task_list.h"

static int32_t shell_ver(uint8_t* argv);
static int32_t shell_help(uint8_t* argv);
static int32_t shell_dbg(uint8_t* argv);
static int32_t shell_fw(uint8_t* argv);
static int32_t shell_play(uint8_t* argv);
static int32_t shell_znp(uint8_t* argv);

uint8_t FW_Link_Request_Frame[] = { \
	/* header */\
	0xef, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3, 0x0, 0x6a, 0x32, 0x6b, \
	/* data */ \
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1, 0x0, 0x6a, 0x1, 0x0, 0x12, 0x0, 0x38, 0xff, 0x0, 0x0, 0x0, 0x7, 0x0, 0x0, 0x0, 0x1, 0x0, 0x6, 0x0, 0x80, 0xff, 0x7, 0xb, 0x80, 0x79, 0x40, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
	};

cmd_line_t lgn_cmd_table[] = {
	{(const int8_t*)"ver",		shell_ver,		(const int8_t*)"get kernel version"},
	{(const int8_t*)"help",		shell_help,		(const int8_t*)"help command info"},
	{(const int8_t*)"dbg",		shell_dbg,		(const int8_t*)"debug"},
	{(const int8_t*)"fw",		shell_fw,		(const int8_t*)"firmware update"},
	{(const int8_t*)"play",		shell_play,		(const int8_t*)"audio play"},
	{(const int8_t*)"znp",		shell_znp,		(const int8_t*)"zigbee znp"},

	/* End Of Table */
	{(const int8_t*)0,(pf_cmd_func)0,(const int8_t*)0}
};

int32_t shell_ver(uint8_t* argv) {
	(void)argv;
	APP_PRINT("version: %s\n", AK_VERSION);
	return 0;
}

int32_t shell_help(uint8_t* argv) {
	uint32_t idx = 0;
	switch (*(argv + 4)) {
	default:
		APP_PRINT("\nCOMMANDS INFORMATION:\n\n");
		while(lgn_cmd_table[idx].cmd != (const int8_t*)0) {
			APP_PRINT("%s\n\t%s\n\n", lgn_cmd_table[idx].cmd, lgn_cmd_table[idx].info);
			idx++;
		}
		break;
	}
	return 0;
}

int32_t shell_dbg(uint8_t* argv) {
	switch (*(argv + 4)) {

	case 'f': {
		FATAL("Test Safe Exit", 0x01);
	}
		break;

	default:
		break;
	}

	return 0;
}

int32_t shell_fw(uint8_t* argv) {
	switch (*(argv + 3)) {

	default:
		break;
	}
	return 0;
}

int32_t shell_play(uint8_t* argv) {
	switch (*(argv + 5)) {

	default:
		break;
	}
	return 0;
}

int32_t shell_znp(uint8_t* argv) {
	switch (*(argv + 4)) {

	default:
		break;
	}

	return 0;
}
