/*
 * main.c  -- entry point of dll
 *
 * $Id: main.c,v 1.3 2004/06/13 13:03:46 hos Exp $
 *
 */

#include <windows.h>
#include <objbase.h>
#include "main.h"


/* global datas */

HINSTANCE instance = NULL;


/* Class ID of this DLL: {AEC7D9E1-1B01-4009-BF71-8D45CAD1BECD} */
static const GUID self_clsid =
{
    0xaec7d9e1, 0x1b01, 0x4009,
    { 0xbf, 0x71, 0x8d, 0x45, 0xca, 0xd1, 0xbe, 0xcd }
};



/* DLL entry point */
BOOL WINAPI DllMain(HINSTANCE inst, DWORD reason, LPVOID rsrv)
{
    if(reason == DLL_PROCESS_ATTACH) {
        instance = inst;

        DisableThreadLibraryCalls(instance); /* just for optimize */
    }

    return TRUE;
}



/* COM entry points */

static LONG ref_count = 0;

STDAPI DllGetClassObject(REFCLSID clsid, REFIID iid, LPVOID *obj)
{
    if(! IsEqualGUID(clsid, &self_clsid)) {
        *obj = NULL;
        return CLASS_E_CLASSNOTAVAILABLE;
    }

    return class_factory_alloc(iid, obj);
}

STDAPI DllCanUnloadNow(void)
{
    if(ref_count > 0) {
        return S_FALSE;
    }

    return S_OK;
}


/* internal APIs */

int dll_inc_ref(void)
{
    InterlockedIncrement(&ref_count);

    return ref_count;
}

int dll_dec_ref(void)
{
    InterlockedDecrement(&ref_count);

    return ref_count;
}


/* misc APIs */
int display_message_box(UINT text_id, UINT caption_id, HWND hwnd, DWORD style)
{
    MSGBOXPARAMS param;

    memset(&param, 0, sizeof(param));
    param.cbSize = sizeof(param);
    param.hwndOwner = hwnd;
    param.hInstance = instance;
    param.lpszText = (LPCTSTR)text_id;
    param.lpszCaption = (LPCTSTR)caption_id;
    param.dwStyle = style;

    return MessageBoxIndirect(&param);
}
