/**
 * @file sndbx_conf.h
 *
 */

#ifndef SNDBX_CONF_H
#define SNDBX_CONF_H

/*Enable Sandbox*/
#define SNDBX_USE_SNDBX 1

/* Create respective buttons in the toolbar */
#define SNDBX_USE_BTN_HELP		1
#define SNDBX_USE_BTN_INFO		1
#define SNDBX_USE_BTN_SETTINGS	1

#define SNDBX_USE_BTNS (SNDBX_USE_BTN_HELP||SNDBX_USE_BTN_INFO||SNDBX_USE_BTN_SETTINGS)

/* Allow for unmaganed pages */
#define SNDBX_USE_UNMANAGED_PGE	1

/* Tracing/debug */
#define SNDBX_USE_MEM_TRACE		1
#define SNDBX_USE_NAV_TRACE		1

#endif /*SNDBX_CONF_H*/