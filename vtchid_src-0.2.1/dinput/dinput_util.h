/*
 * dinput_util.h  -- define utilities to use DirectInput
 *
 * $Id: dinput_util.h,v 1.2 2004/06/11 19:35:34 hos Exp $
 *
 */

/* open HID device of joystick from joystick ID */
HANDLE open_joystick_hid_device(USHORT joystick_id, DWORD file_flag);
