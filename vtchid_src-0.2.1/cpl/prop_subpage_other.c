/*
 * prop_page_other.c  -- misc setting property page
 *
 * $Id: prop_subpage_other.c,v 1.5 2004/06/14 13:00:11 hos Exp $
 *
 */

#include <windows.h>
#include <prsht.h>
#include "main.h"
#include "util.h"


/* page proc alist */
struct uint_ptr_pair other_setting_subpage[];
static struct uint_ptr_pair command_proc_map[];


/* implementations */

/* WM_INITDIALOG */
static INT_PTR other_setting_init_dialog(HWND hwnd, UINT msg,
                                       WPARAM wparam, LPARAM lparam,
                                       prop_page_context_t *ctx)
{
    int i;
    struct uint_ptr_pair id_item_map[] = {
        {IDC_BTN_THRESHOLD_SLIDER, &ctx->other.btn_threshold},
        {IDC_AXIS_THRESHOLD_SLIDER, &ctx->other.axis_threshold},
        {IDC_AUTO_LIGHT, &ctx->other.auto_light},
        {IDC_LIGHT_SLOWLY_OFF_SLIDER, &ctx->other.light_slowly_off_slider},

        {0, NULL}
    };

    get_dialog_item(hwnd, id_item_map);
    ctx->command_proc = command_proc_map;

    {
        struct {
            HWND slider;
            int from;
            int to;
            int freq;
        } slider[] = {
            {ctx->other.btn_threshold, 0x00, 0xff, 0x10},
            {ctx->other.axis_threshold, 0x00, 0x7f, 0x10},
            {ctx->other.light_slowly_off_slider, 0, 250, 10},

            {NULL, 0, 0}
        };

        for(i = 0; slider[i].slider != NULL; i++) {
            /* set range */
            SendMessage(slider[i].slider, TBM_SETRANGE,
                        FALSE, MAKELONG(slider[i].from, slider[i].to));
            SendMessage(slider[i].slider, TBM_SETTICFREQ, slider[i].freq, 0);
        }
    }

    return TRUE;
}

/* WM_DESTROY */
static INT_PTR other_setting_destroy(HWND hwnd, UINT msg,
                                     WPARAM wparam, LPARAM lparam,
                                     prop_page_context_t *ctx)
{
    return PSNRET_NOERROR;
}

/* WM_HSCROLL */
static INT_PTR other_setting_hscroll(HWND hwnd, UINT msg,
                                     WPARAM wparam, LPARAM lparam,
                                     prop_page_context_t *ctx)
{
    HWND ctl_hwnd;

    ctl_hwnd = (HWND)lparam;

    {
        struct {
            HWND slider;
            DWORD *val;
        } slider[] = {
            {ctx->other.btn_threshold,
             &ctx->data->conf.btn_threshold},
            {ctx->other.axis_threshold,
             &ctx->data->conf.lower_threshold},
            {ctx->other.light_slowly_off_slider,
             &ctx->data->conf.light_slowly_off_speed},

            {NULL, NULL}
        };
        int i;

        for(i = 0; slider[i].slider != NULL; i++) {
            *slider[i].val = SendMessage(slider[i].slider, TBM_GETPOS, 0, 0);
        }

        ctx->data->conf.upper_threshold =
            0xff - ctx->data->conf.lower_threshold;

        PropSheet_Changed(ctx->data->sheet_hwnd, ctx->page_hwnd);
    }

    return TRUE;
}

/* WM_SUBPAGE_CHANGE */
static INT_PTR other_setting_change(HWND hwnd, UINT msg,
                                    WPARAM wparam, LPARAM lparam,
                                    prop_page_context_t *ctx)
{
    int i;

    {
        struct {
            HWND slider;
            int pos;
        } slider[] = {
            {ctx->other.btn_threshold, ctx->data->conf.btn_threshold},
            {ctx->other.axis_threshold, ctx->data->conf.lower_threshold},
            {ctx->other.light_slowly_off_slider,
             ctx->data->conf.light_slowly_off_speed},

            {NULL, 0}
        };

        for(i = 0; slider[i].slider != NULL; i++) {
            /* set slider pos */
            SendMessage(slider[i].slider, TBM_SETPOS, TRUE, slider[i].pos);
        }
    }

    {
        struct {
            HWND checkbox;
            int state;
        } checkbox[] = {
            {ctx->other.auto_light,
             (ctx->data->conf.auto_light ? BST_CHECKED : BST_UNCHECKED)},

            {NULL, 0}
        };

        for(i = 0; checkbox[i].checkbox != NULL; i++) {
            /* set checkbox stat */
            SendMessage(checkbox[i].checkbox, BM_SETCHECK,
                        checkbox[i].state, 0);
        }
    }

    return TRUE;
}

/* BN_CLICKED */
static INT_PTR auto_light_clicked(HWND hwnd,
                                  WORD code, WORD id, HWND ctrl,
                                  prop_page_context_t *ctx)
{
    LRESULT state;

    state = SendMessage(ctx->other.auto_light, BM_GETCHECK, 0, 0);
    ctx->data->conf.auto_light = (state == BST_CHECKED ? 1 : 0);

    PropSheet_Changed(ctx->data->sheet_hwnd, ctx->page_hwnd);

    return TRUE;
}


/* page proc alist */
struct uint_ptr_pair other_setting_subpage[] = {
    {WM_INITDIALOG, other_setting_init_dialog},
    {WM_DESTROY, other_setting_destroy},
    {WM_HSCROLL, other_setting_hscroll},
    {WM_SUBPAGE_CHANGE, other_setting_change},
    {WM_COMMAND, window_command_proc},

    {0, NULL}
};


/* WM_COMMAND */
static struct uint_ptr_pair auto_light_proc_map[] = {
    {BN_CLICKED, auto_light_clicked},

    {0, NULL}
};
static struct uint_ptr_pair command_proc_map[] = {
    {IDC_AUTO_LIGHT, auto_light_proc_map},

    {0, NULL}
};
