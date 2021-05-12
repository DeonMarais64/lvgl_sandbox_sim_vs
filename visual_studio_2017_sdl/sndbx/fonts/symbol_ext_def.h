#ifndef SYMBOL_EXT_DEF_H
#define SYMBOL_EXT_DEF_H

#ifdef __cplusplus
extern "C" {
#endif
#ifdef LV_CONF_INCLUDE_SIMPLE
#include "lv_conf.h"
#else
#include "../../lv_conf.h"
#endif

/*
 * To Do: Add others ad and when needed, see
 * https://fontawesome.com/icons?d=listing&s=brands,regular,solid&m=free
 * http://www.ltg.ed.ac.uk/%7Erichard/utf-8.cgi?input=b0&mode=hex
 */
 
#define SYMBOL_EXT_DEGREE_SIGN	"\xc2\xb0"		/* 0xb0 */

/* These two in sandbox font set. */
#define SYMBOL_EXT_QUESTION		"\xef\x81\x99" /* 0xf059 */
#define SYMBOL_EXT_INFO			"\xef\x81\x9a" /* 0xf05a */

/* The rest, envisioned to be used in future,
 * To be added to the fonts then.
 * */
#define SYMBOL_EXT_HAND_RIGHT	"\xef\x82\xa4" /* 0xf0a4 */
#define SYMBOL_EXT_HAND_LEFT	"\xef\x82\xa5" /* 0xf0a5 */
#define SYMBOL_EXT_HAND_UP		"\xef\x82\xa6" /* 0xf0a6 */
#define SYMBOL_EXT_HAND_DOWN	"\xef\x82\xa7" /* 0xf0a7 */
#define SYMBOL_EXT_PLAY_CIRCLE	"\xef\x85\x84" /* 0xf144 */
#define SYMBOL_EXT_PAUSE_CIRCLE	"\xef\x8a\x8b" /* 0xf28b */
#define SYMBOL_EXT_STOP_CIRCLE	"\xef\x8a\x8d" /* 0xf28d */

/* Chevron arrows. Same as used in lvgl but on circles */
#define SYMBOL_EXT_LEFT_CIRCLE	"\xef\x84\xb7" /* 0xf137 */
#define SYMBOL_EXT_RIGHT_CIRCLE	"\xef\x84\xb8" /* 0xf138 */
#define SYMBOL_EXT_UP_CIRCLE	"\xef\x84\xb9" /* 0xf139 */
#define SYMBOL_EXT_DOWN_CIRCLE	"\xef\x84\xba" /* 0xf13a */

/* Arrow-Alt-circles */
#define SYMBOL_EXT_ARROW_DOWN_CIRCLE	"\xef\x8d\x98" /* 0xf358 */
#define SYMBOL_EXT_ARROW_LEFT_CIRCLE	"\xef\x8d\x99" /* 0xf359 */
#define SYMBOL_EXT_ARROW_RIGHT_CIRCLE	"\xef\x8d\x9a" /* 0xf35a */
#define SYMBOL_EXT_ARROW_UP_CIRCLE		"\xef\x8d\x9b" /* 0xf35b */


#ifdef __cplusplus
} /* extern "C" */
#endif


#endif /* SYMBOL_EXT_DEF_H */
