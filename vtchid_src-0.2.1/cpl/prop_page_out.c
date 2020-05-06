/*
 * prop_page_out.c  -- output test property page
 *
 * $Id: prop_page_out.c,v 1.8 2004/06/14 12:28:50 hos Exp $
 *
 */

#include <windows.h>
#include <commctrl.h>
#include <tchar.h>
#include "main.h"
#include "util.h"


/* prototypes */
static INT_PTR output_test_set_all(int val, prop_page_context_t *ctx);
static void output_test_update(BOOL set_from_list,
                               prop_page_context_t *ctx);
static int apply_to_device(prop_page_context_t *ctx);


/* page proc alist */
struct uint_ptr_pair output_test_page[];
static struct uint_ptr_pair command_proc_map[];
static struct uint_ptr_pair notify_proc_map[];


/* implementations */

/* WM_INITDIALOG */
static INT_PTR output_test_init_dialog(HWND hwnd, UINT msg,
                                       WPARAM wparam, LPARAM lparam,
                                       prop_page_context_t *ctx)
{
    int i;
    struct uint_ptr_pair id_item_map[] = {
        {IDC_TEST_LIGHT_LIST, &ctx->out.list},
        {IDC_TEST_LIGHT_SLIDER, &ctx->out.slider},

        {IDC_TEST_LIGHT_ALL, &ctx->out.all},
        {IDC_TEST_LIGHT_NONE, &ctx->out.none},

        {IDC_TEST_LIGHT_PATTERN_1, &ctx->out.pattern1},
        {IDC_TEST_LIGHT_PATTERN_2, &ctx->out.pattern2},
        {IDC_TEST_LIGHT_PATTERN_3, &ctx->out.pattern3},

        {0, NULL}
    };

    get_dialog_item(hwnd, id_item_map);
    ctx->command_proc = command_proc_map;
    ctx->notify_proc = notify_proc_map;

    /* list */
    {
        TCHAR str[256];
        RECT rect;
        int width;
        LVCOLUMN lvcol;

        const static struct {
            UINT id;
            double w_ratio;
        } col_header[] = {
            {IDS_TEST_LIGHT_NAME, 0.8},
            {IDS_TEST_LIGHT_BRIGHTNESS, 0.2},

            {0, 0}
        };

        ListView_SetExtendedListViewStyle(ctx->out.list,
                                          LVS_EX_FULLROWSELECT);

        GetClientRect(ctx->out.list, &rect);
        width = (rect.right - rect.left) - 20;

        for(i = 0; col_header[i].id != 0; i++) {
            memset(str, 0, sizeof(str));
            LoadString(instance, col_header[i].id, str, 255);

            memset(&lvcol, 0, sizeof(lvcol));
            lvcol.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;
            lvcol.pszText = str;
            lvcol.iSubItem = i;
            lvcol.cx = width * col_header[i].w_ratio;
            ListView_InsertColumn(ctx->out.list, i, &lvcol);
        }
    }

    /* list items */
    {
        LVITEM lvitem;

        for(i = 0; light_names[i] != NULL; i++) {
            memset(&lvitem, 0, sizeof(lvitem));
            lvitem.mask = LVIF_TEXT | LVIF_PARAM;
            lvitem.iItem = i;
            lvitem.iSubItem = 0;
            lvitem.pszText = light_names[i];
            lvitem.lParam = 0;
            ListView_InsertItem(ctx->out.list, &lvitem);
        }

        output_test_set_all(0x00, ctx);
        output_test_update(TRUE, ctx);
    }

    /* set slider range, position */
    SendMessage(ctx->out.slider, TBM_SETRANGE, FALSE, MAKELONG(0x00, 0x0f));
    SendMessage(ctx->out.slider, TBM_SETPOS, TRUE, 0x00);

    return TRUE;
}

/* WM_DESTROY */
static INT_PTR output_test_destroy(HWND hwnd, UINT msg,
                                   WPARAM wparam, LPARAM lparam,
                                   prop_page_context_t *ctx)
{
    output_test_set_all(0x00, ctx);
    output_test_update(TRUE, ctx);

    return TRUE;
}

/* IDC_TEST_LIGHT_ALL */
static INT_PTR output_test_all(HWND hwnd,
                               WORD code, WORD id, HWND ctrl,
                               prop_page_context_t *ctx)
{
    output_test_set_all(0x0f, ctx);
    output_test_update(TRUE, ctx);

    return TRUE;
}

/* IDC_TEST_LIGHT_NONE */
static INT_PTR output_test_none(HWND hwnd,
                                WORD code, WORD id, HWND ctrl,
                                prop_page_context_t *ctx)
{
    output_test_set_all(0x00, ctx);
    output_test_update(TRUE, ctx);

    return TRUE;
}

/* IDC_TEST_PATTERN_1 */
static INT_PTR output_test_pattern1(HWND hwnd,
                                    WORD code, WORD id, HWND ctrl,
                                    prop_page_context_t *ctx)
{
    /* todo: output pattern */

    return TRUE;
}

/* IDC_TEST_PATTERN_2 */
static INT_PTR output_test_pattern2(HWND hwnd,
                                    WORD code, WORD id, HWND ctrl,
                                    prop_page_context_t *ctx)
{
    /* todo: output pattern */

    return TRUE;
}

/* IDC_TEST_PATTERN_3 */
static INT_PTR output_test_pattern3(HWND hwnd,
                                    WORD code, WORD id, HWND ctrl,
                                    prop_page_context_t *ctx)
{
    /* todo: output pattern */

    return TRUE;
}

/* LVN_ITEMCHANGED */
static INT_PTR light_list_changed(HWND hwnd, NMHDR *nmh,
                                  prop_page_context_t *ctx)
{
    NMLISTVIEW *nmlv;

    nmlv = (NMLISTVIEW *)nmh;

    if(! (nmlv->uChanged & LVIF_STATE)) {
        return FALSE;
    }

    output_test_update(TRUE, ctx);

    return TRUE;
}

/* WM_HSCROLL */
static INT_PTR output_test_hscroll(HWND hwnd, UINT msg,
                                   WPARAM wparam, LPARAM lparam,
                                   prop_page_context_t *ctx)
{
    output_test_update(FALSE, ctx);

    return TRUE;
}


static INT_PTR output_test_set_all(int val, prop_page_context_t *ctx)
{
    int item;
    TCHAR str[256];
    LVITEM lvitem;

    for(item = -1;
        (item = ListView_GetNextItem(ctx->out.list, item, LVNI_ALL)) != -1; ) {
        memset(&lvitem, 0, sizeof(lvitem));
        lvitem.mask = LVIF_PARAM;
        lvitem.iItem = item;
        lvitem.iSubItem = 0;
        lvitem.lParam = val;
        ListView_SetItem(ctx->out.list, &lvitem);

        memset(str, 0, sizeof(str));
        wsprintf(str, _T("%d"), val);
        ListView_SetItemText(ctx->out.list, item, 1, str);
    }

    return TRUE;
}

static void output_test_update(BOOL set_from_list,
                               prop_page_context_t *ctx)
{
    LVITEM lvitem;
    TCHAR str[256];        
    int cnt, item, val;

    /* selected? */
    cnt = ListView_GetSelectedCount(ctx->out.list);
    if(cnt == 0) {
        EnableWindow(ctx->out.slider, FALSE);
        apply_to_device(ctx);

        return;
    }

    EnableWindow(ctx->out.slider, TRUE);

    /* get selected item */
    item = ListView_GetNextItem(ctx->out.list, -1, LVNI_ALL | LVNI_SELECTED);
    if(item == -1) {
        EnableWindow(ctx->out.slider, FALSE);
        apply_to_device(ctx);

        return;
    }

    if(set_from_list) {
        /* get value from list */
        memset(&lvitem, 0, sizeof(lvitem));
        lvitem.mask = LVIF_PARAM;
        lvitem.iItem = item;
        lvitem.iSubItem = 0;

        ListView_GetItem(ctx->out.list, &lvitem);
        val = lvitem.lParam;

        /* set value to slider */
        SendMessage(ctx->out.slider, TBM_SETPOS, (WPARAM)TRUE, (LPARAM)val);
    } else {
        /* get value from slider */
        val = SendMessage(ctx->out.slider, TBM_GETPOS, (WPARAM)0, (LPARAM)0);

        /* set value to list */
        memset(&lvitem, 0, sizeof(lvitem));
        lvitem.mask = LVIF_PARAM;
        lvitem.iItem = item;
        lvitem.iSubItem = 0;
        lvitem.lParam = val;
        ListView_SetItem(ctx->out.list, &lvitem);

        memset(str, 0, sizeof(str));
        wsprintf(str, _T("%d"), val);
        ListView_SetItemText(ctx->out.list, item, 1, str);
    }

    apply_to_device(ctx);

    return;
}


/* output */

static int build_output_report(struct controller_output_report *rep,
                               prop_page_context_t *ctx)
{
    LVITEM lvitem;
    int i;

    for(i = 0; i < sizeof(rep->all_light); i++) {
        memset(&lvitem, 0, sizeof(lvitem));
        lvitem.mask = LVIF_PARAM;
        lvitem.iItem = i;
        lvitem.iSubItem = 0;

        ListView_GetItem(ctx->out.list, &lvitem);

        WRITE_REPORT_LIGHT_SET(rep->all_light[i], lvitem.lParam,
                               (lvitem.lParam != 0));
    }

    return TRUE;
}

static int apply_to_device(prop_page_context_t *ctx)
{
    struct controller_output_report rep;
    int ret;

    /* report id, command */
    rep.report_id = 1;
    rep.command = WRITE_REPORT_CMD_LIGHT;

    /* set output report */
    ret = build_output_report(&rep, ctx);
    if(ret == FALSE) {
        return ret;
    }

    /* output to device */
    ret = output_to_device(ctx->data, &rep);

    return (ret != 0);
}


/* page proc alist */
struct uint_ptr_pair output_test_page[] = {
    {WM_INITDIALOG, output_test_init_dialog},
    {WM_DESTROY, output_test_destroy},
    {WM_COMMAND, window_command_proc},
    {WM_NOTIFY, window_notify_proc},
    {WM_HSCROLL, output_test_hscroll},

    {0, NULL}
};


/* WM_COMMAND proc */
static struct uint_ptr_pair all_proc_map[] = {
    {BN_CLICKED, output_test_all},

    {0, NULL}
};
static struct uint_ptr_pair none_proc_map[] = {
    {BN_CLICKED, output_test_none},

    {0, NULL}
};
static struct uint_ptr_pair pattern1_proc_map[] = {
    {BN_CLICKED, output_test_pattern1},

    {0, NULL}
};
static struct uint_ptr_pair pattern2_proc_map[] = {
    {BN_CLICKED, output_test_pattern2},

    {0, NULL}
};
static struct uint_ptr_pair pattern3_proc_map[] = {
    {BN_CLICKED, output_test_pattern3},

    {0, NULL}
};
static struct uint_ptr_pair command_proc_map[] = {
    {IDC_TEST_LIGHT_ALL, all_proc_map},
    {IDC_TEST_LIGHT_NONE, none_proc_map},
    {IDC_TEST_LIGHT_PATTERN_1, pattern1_proc_map},
    {IDC_TEST_LIGHT_PATTERN_2, pattern2_proc_map},
    {IDC_TEST_LIGHT_PATTERN_3, pattern3_proc_map},

    {0, NULL}
};


/* WM_NOTIFY proc */
static struct uint_ptr_pair list_proc_map[] = {
    {LVN_ITEMCHANGED, light_list_changed},

    {0, NULL}
};
static struct uint_ptr_pair notify_proc_map[] = {
    {IDC_TEST_LIGHT_LIST, &list_proc_map},

    {0, NULL}
};
