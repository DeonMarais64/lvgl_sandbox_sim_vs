/*
 * glObjects.h
 *
 *  Created on: 04 May 2018
 *      Author: Deon-Marais
 */

#ifndef GLOBJECTS_H_
#define GLOBJECTS_H_

#include "C-Types.h"
#include "lvgl/lvgl.h"

/**
 * Objects: Typed and Grouped as I see them
 * https://docs.littlevgl.com/en/html/object-types/index.html
 */
typedef lv_obj_t * PObj;	/* Base Object		: https://docs.littlevgl.com/en/html/object-types/obj.html */

typedef PObj PScrn;			/* Screen			 													*/

/* Simple Output only objects */
typedef PObj PArc;			/* Arc				: https://docs.littlevgl.com/en/html/object-types/arc.html */
typedef PObj PImg;			/* Image			: https://docs.littlevgl.com/en/html/object-types/img.html */
typedef PObj PLbl;			/* Label, Text		: https://littlevgl.com/object-types/label-lv_label */
typedef PObj PLne;			/* Line				: https://littlevgl.com/object-types/line-lv_line */
typedef PObj PPreload;		/* Preload			: https://docs.littlevgl.com/en/html/object-types/preload.html */

/* Generally Macro objects in which to place other objects */
typedef PObj PCanvas;		/* Canvas 			: https://docs.littlevgl.com/en/html/object-types/canvas.html */
typedef PObj PCnt;			/* Container 		: https://littlevgl.com/object-types/container-lv_cont */
typedef PObj PPge;			/* Page 			: https://littlevgl.com/object-types/page-lv_page */
typedef PObj PTabv;			/* Tab view			: https://littlevgl.com/object-types/tab-view-lv_tabview */
typedef PObj PTable;		/* Table			: https://docs.littlevgl.com/en/html/object-types/table.html */
typedef PObj PTilev;		/* Tile view		: https://docs.littlevgl.com/en/html/object-types/tileview.html */
typedef PObj PWin;			/* Window			: https://littlevgl.com/object-types/window-lv_win */

/* Data Visualiser objects, Meters, Indicators etc */
typedef PObj PBar;			/* Bar				: https://littlevgl.com/object-types/bar-lv_bar */
typedef PObj PChrt;			/* Chart			: https://littlevgl.com/object-types/chart-lv_chart */
typedef PObj PLed;			/* LED				: https://littlevgl.com/object-types/led-lv_led */
typedef PObj PLmtr;			/* Line Meter		: https://littlevgl.com/object-types/line-meter-lv_lmeter */
typedef PObj PGge;			/* Gauge			: https://littlevgl.com/object-types/gauge-lv_gauge */

/* User Feedback and output */
typedef PObj PMbox;			/* Message Box 		: https://littlevgl.com/object-types/message-box-lv_mbox */
typedef PObj PTa;			/* Text Area		: https://littlevgl.com/object-types/text-area-lv_ta */

/* User Interactive, responds to user input/gestures */
typedef PObj PBtn;			/* Button			: https://littlevgl.com/object-types/button-lv_btn */
typedef PObj PBtnImg;		/* Image Button		: https://docs.littlevgl.com/en/html/object-types/imgbtn.html */
typedef PObj PBtnm;			/* Button Matrix	: https://littlevgl.com/object-types/button-matrix-lv_btnm */
typedef PObj PCalendar;		/* Calendar			: https://docs.littlevgl.com/en/html/object-types/calendar.html */
typedef PObj PCb;			/* Check Box		: https://littlevgl.com/object-types/check-box-lv_cb */
typedef PObj PDdLst;		/* Drop Down List	: https://littlevgl.com/object-types/drop-down-list-lv_ddlist */
typedef PObj PLst;			/* List				: https://littlevgl.com/object-types/list-lv_list */
typedef PObj PKb;			/* Key Board		: https://littlevgl.com/object-types/keyboard-lv_kb */
typedef PObj PRlr;			/* Roller			: https://littlevgl.com/object-types/roller-lv_roller */
typedef PObj PSldr;			/* Slider			: https://littlevgl.com/object-types/slider-lv_slider */
typedef PObj PSpbx;			/* Spin Box			: https://docs.littlevgl.com/en/html/object-types/spinbox.html# */
typedef PObj PSw;			/* Switch			: https://littlevgl.com/object-types/switch-lv_sw */

/* Generally Macro object abstraction */
typedef PObj PPar;			/* Parent			*/

#define LV_HOR_MAX	(LV_HOR_RES_MAX-1)
#define LV_VER_MAX	(LV_VER_RES_MAX-1)


#endif /* GLOBJECTS_H_ */
