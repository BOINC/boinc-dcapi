/*
 * DC-API: Distributed Computing Platform for Master-Worker Applications
 *
 * Common definitions for both the master and client side
 *
 * Authors:
 * 	Gabor Gombas <gombasg@sztaki.hu>
 *
 * Copyright MTA SZTAKI, 2006
 */
#ifndef __DC_COMMON_H_
#define __DC_COMMON_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************
 * Constant definitions
 */

/* API error codes */
enum {
	DC_OK,			/* No error */
	DC_ERR_NOTIMPL,		/* Not implemented by the API or by the
				   underlying grid infrastructure */
	DC_ERR_UNKNOWN_WU,	/* Unknown WU identifier */
	DC_ERR_TIMEOUT,		/* Timeout */
};

/* Flags describing what capabilities does the underlying grid system
 * support */
typedef enum {
	DC_GC_EXITCODE		= (1 << 0),	/* DC_Result contains the
						   client's exit code */
	DC_GC_STDOUT		= (1 << 1),	/* The client's standard output
						   is available for the
						   master */
	DC_GC_STDERR		= (1 << 2),	/* Client's standard error is
						   available for the master */
	DC_GC_LOG		= (1 << 3),	/* Log file generated by the
						   execution environment is
						   available for the master */
	DC_GC_SUSPEND		= (1 << 4),	/* DC_suspendWU() works */
	DC_GC_SUBRESULT		= (1 << 5),	/* Sub-results work */
	DC_GC_MESSAGING		= (1 << 6)	/* Message sending works */
} DC_GridCapabilities;

/* File classification when passing a physical file name to DC-API */
typedef enum {
	DC_FILE_REGULAR,		/* Not persistent, needs copy */
	DC_FILE_PERSISTENT,		/* Persistent, link is enough */
	DC_FILE_VOLATILE		/* DC-API should remove the original */
} DC_FileMode;

/* Maximum length of messages sent between the client and the master */
#define DC_MAX_MESSAGE_LENGTH	16384


/********************************************************************
 * Macro definitions
 */

/* Support non-gcc compatible compilers */
#ifndef __GNUC__
#define __attribute__(x)
#endif


/********************************************************************
 * Function prototypes
 */

/** Determines the maximum allowed message length.
 *
 * @Returns: the message length in bytes.
 */
int DC_getMaxMessageSize(void);

/** Determines the maximum number of sub-results.
 * On the master side, it returns the maximum value that can be passed to
 * DC_createWU(). On the client side, it returns the actual value for the
 * running WU.
 *
 * @Returns: the max. number of sub-results.
 */
int DC_getMaxSubresults(void);

/** Determines the basic capabilities of the underlying grid infrastructure.
 *
 * @Returns: the grid capabilities: values of #DC_GridCapabilities constants
 * OR'ed together.
 */
DC_GridCapabilities DC_getGridCapabilities(void);

#ifdef __cplusplus
}
#endif

#endif /* __DC_COMMON_H_ */
