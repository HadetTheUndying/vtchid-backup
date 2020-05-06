/*
 * report_data.h  -- define report data format 
 *
 * $Id: report_data.h,v 1.6 2004/06/14 12:28:51 hos Exp $
 *
 */


/* read report */

#define INPUT_REPORT_NUM_JOY_BUTTON 32
#define INPUT_REPORT_NUM_KBD_CODE   232
#define INPUT_REPORT_NUM_MOU_BUTTON 5

#pragma pack(push, 1)
struct controller_joy_input_report {
    UCHAR report_id;            /* Report ID: 1 */

    union {
        struct {
            UCHAR x;            /* X:  0x00 - 0xff */
            UCHAR y;            /* Y:  0x00 - 0xff */
            UCHAR z;            /* Z:  0x00 - 0xff */
            UCHAR rx;           /* RX: 0x00 - 0xff */
            UCHAR ry;           /* RY: 0x00 - 0xff */
            UCHAR rz;           /* RZ: 0x00 - 0xff */
            UCHAR slider;       /* SL: 0x00 - 0xff */
            UCHAR throttle;     /* TH: 0x00 - 0xff */
        };

        struct {
            UCHAR axis[8];      /* x, y, z, rx, ry, yz, slider, throttle */
        };
    };

    UCHAR hat1 : 4;             /* H1: 0x00 - 0x07 */
    UCHAR hat2 : 4;             /* H2: 0x00 - 0x07 */

    UCHAR button[(INPUT_REPORT_NUM_JOY_BUTTON + 7) / 8]; /* BN: 0x00/0x01 */

    USHORT modifier;            /* modifier state */
};

struct controller_kbd_input_report {
    UCHAR report_id;            /* Report ID: 2 */

    UCHAR keys[(INPUT_REPORT_NUM_KBD_CODE + 7) / 8]; /* 232 keys */
};

struct controller_mou_input_report {
    UCHAR report_id;            /* Report ID: 3 */

    CHAR x;                     /* x:     0x81 - 0x7f */
    CHAR y;                     /* y:     0x81 - 0x7f */
    CHAR wheel;                 /* wheel: 0x81 - 0x7f */

    UCHAR button[(INPUT_REPORT_NUM_MOU_BUTTON + 7) / 8]; /* 5 buttons */
};
#pragma pack(pop)


/* write report */

#define WRITE_REPORT_CMD_LIGHT 0x01
#define WRITE_REPORT_CMD_RELOAD_SETTING 0x02

struct controller_output_report {
    UCHAR report_id;            /* Report ID: 1 */

    UCHAR command;              /* command: 0x00 - 0xff */
    union {
        struct {
            UCHAR button_light[30]; /* BL: 0x00 - 0x0f */
            UCHAR gear_light[7]; /* GL: 0x00 - 0x0f */
        } d;

        UCHAR all_light[37];
    };
};

#define WRITE_REPORT_LIGHT_SET(_dst_,_val_,_constp_) \
  ((_dst_) = (_val_) | ((_constp_) ? 0x80 : 0x00))
#define WRITE_REPORT_LIGHT_VAL(_val_) ((_val_) & 0x0f)
#define WRITE_REPORT_LIGHT_CONSTP(_val_) ((_val_) & 0x80)


/* setting stored in registroy */
#define REGISTRY_REL_PATH L"Software\\noname\\vtchid"
#define REGISTRY_BASE_PATH L"\\Registry\\Machine\\" REGISTRY_REL_PATH


/* configuration of value processor */

/* 5 axis, gear lever, tuner dial, 39 digital buttons, 3 analog buttons */
enum {
    CONTROLLER_EVT_CODE_AIM_X = 0x0000,
    CONTROLLER_EVT_CODE_AIM_Y,
    CONTROLLER_EVT_CODE_SIGHT_X,
    CONTROLLER_EVT_CODE_SIGHT_Y,
    CONTROLLER_EVT_CODE_ROTATION,

    CONTROLLER_EVT_CODE_AXIS_MAX = CONTROLLER_EVT_CODE_ROTATION,

    CONTROLLER_EVT_CODE_GEAR_R,
    CONTROLLER_EVT_CODE_GEAR_N,
    CONTROLLER_EVT_CODE_GEAR_1,
    CONTROLLER_EVT_CODE_GEAR_2,
    CONTROLLER_EVT_CODE_GEAR_3,
    CONTROLLER_EVT_CODE_GEAR_4,
    CONTROLLER_EVT_CODE_GEAR_5,

    CONTROLLER_EVT_CODE_GEAR_MIN = CONTROLLER_EVT_CODE_GEAR_R,
    CONTROLLER_EVT_CODE_GEAR_MAX = CONTROLLER_EVT_CODE_GEAR_5,

    CONTROLLER_EVT_CODE_TUNER_E,
    CONTROLLER_EVT_CODE_TUNER_ENE,
    CONTROLLER_EVT_CODE_TUNER_NE,
    CONTROLLER_EVT_CODE_TUNER_NNE,
    CONTROLLER_EVT_CODE_TUNER_N,
    CONTROLLER_EVT_CODE_TUNER_NNW,
    CONTROLLER_EVT_CODE_TUNER_NW,
    CONTROLLER_EVT_CODE_TUNER_WNW,
    CONTROLLER_EVT_CODE_TUNER_W,
    CONTROLLER_EVT_CODE_TUNER_WSW,
    CONTROLLER_EVT_CODE_TUNER_SW,
    CONTROLLER_EVT_CODE_TUNER_SSW,
    CONTROLLER_EVT_CODE_TUNER_S,
    CONTROLLER_EVT_CODE_TUNER_SSE,
    CONTROLLER_EVT_CODE_TUNER_SE,
    CONTROLLER_EVT_CODE_TUNER_ESE,

    CONTROLLER_EVT_CODE_TUNER_MIN = CONTROLLER_EVT_CODE_TUNER_E,
    CONTROLLER_EVT_CODE_TUNER_MAX = CONTROLLER_EVT_CODE_TUNER_ESE,

    CONTROLLER_EVT_CODE_MAIN_WEAPON,
    CONTROLLER_EVT_CODE_SUB_WEAPON,
    CONTROLLER_EVT_CODE_LOCK_ON,
    CONTROLLER_EVT_CODE_EJECT_CMD,
    CONTROLLER_EVT_CODE_COCPIT_HATCH,
    CONTROLLER_EVT_CODE_IGNITION,
    CONTROLLER_EVT_CODE_START,
    CONTROLLER_EVT_CODE_MLM_OPEN_CLOSE,
    CONTROLLER_EVT_CODE_MLM_MAP_ZOOM,
    CONTROLLER_EVT_CODE_MLM_MODE_SELECT,
    CONTROLLER_EVT_CODE_SM_MODE_SELECT,
    CONTROLLER_EVT_CODE_MM_ZOOM_IN,
    CONTROLLER_EVT_CODE_MM_ZOOM_OUT,

    CONTROLLER_EVT_CODE_FSS,
    CONTROLLER_EVT_CODE_MANIPULATOR,
    CONTROLLER_EVT_CODE_LINE_COLOR_CHANGE,
    CONTROLLER_EVT_CODE_WASHING,
    CONTROLLER_EVT_CODE_EXTINGUISHER,
    CONTROLLER_EVT_CODE_CHAFF,
    CONTROLLER_EVT_CODE_TANK_DETACH,
    CONTROLLER_EVT_CODE_OVERRIDE,
    CONTROLLER_EVT_CODE_NIGHT_SCOPE,
    CONTROLLER_EVT_CODE_F1,
    CONTROLLER_EVT_CODE_F2,
    CONTROLLER_EVT_CODE_F3,
    CONTROLLER_EVT_CODE_WC_MAIN,
    CONTROLLER_EVT_CODE_WC_SUB,
    CONTROLLER_EVT_CODE_WC_MAGAZINE_CHANGE,
    CONTROLLER_EVT_CODE_CT_1,
    CONTROLLER_EVT_CODE_CT_2,
    CONTROLLER_EVT_CODE_CT_3,
    CONTROLLER_EVT_CODE_CT_4,
    CONTROLLER_EVT_CODE_CT_5,

    CONTROLLER_EVT_CODE_SIGHT_BUTTON,
    CONTROLLER_EVT_CODE_FILT_CONTROL_SYSTEM,
    CONTROLLER_EVT_CODE_OXYGEN_SUPPLY_SYSTEM,
    CONTROLLER_EVT_CODE_FUEL_FLOW_RATE,
    CONTROLLER_EVT_CODE_BUFFER_MATERIAL,
    CONTROLLER_EVT_CODE_VT_LOCATION_MEASUREMENT,

    CONTROLLER_EVT_CODE_FOOT_PEDAL_LEFT,
    CONTROLLER_EVT_CODE_FOOT_PEDAL_CENTER,
    CONTROLLER_EVT_CODE_FOOT_PEDAL_RIGHT,

    CONTROLLER_NUM_EVENT        /* = 70 */
};

/* 16 modifiers */
#define CONTROLLER_MODEFIER(n) ((USHORT)(1 << ((n) - 1)))

/* sizeof(struct controller_modifier_config) == 8 */
struct controller_modifier_config {
    USHORT mod;                 /* modifier */
    USHORT mod_mask;            /* modifier mask */

    USHORT action_idx;          /* index of action list */

    char reserved[2];
};


/* controller_action_config.type */
#define CONTROLLER_ACTION_NOP   0x00
#define CONTROLLER_ACTION_MOD   0x01
#define CONTROLLER_ACTION_DELAY 0x02
#define CONTROLLER_ACTION_JOY   0x03
#define CONTROLLER_ACTION_APPLY 0x04
#define CONTROLLER_ACTION_MOU   0x10
#define CONTROLLER_ACTION_KBD   0x11

/* controller_action_config.joy.flags */
#define CONTROLLER_ACTION_JOY_VAL_MIN     0x0001
#define CONTROLLER_ACTION_JOY_VAL_MAX     0x0002
#define CONTROLLER_ACTION_JOY_VAL_MDL     0x0003
#define CONTROLLER_ACTION_JOY_VAL_THROUGH 0x0004
#define CONTROLLER_ACTION_JOY_VAL_REVERSE 0x0005
#define CONTROLLER_ACTION_JOY_VAL_SPEC    0x0006
#define CONTROLLER_ACTION_JOY_VAL_RATIO   0x0007

/* controller_action_config.joy.code */
enum {
    CONTROLLER_ACTION_JOY_CODE_X = 0x0000,
    CONTROLLER_ACTION_JOY_CODE_Y,
    CONTROLLER_ACTION_JOY_CODE_Z,
    CONTROLLER_ACTION_JOY_CODE_RX,
    CONTROLLER_ACTION_JOY_CODE_RY,
    CONTROLLER_ACTION_JOY_CODE_RZ,
    CONTROLLER_ACTION_JOY_CODE_SLIDER,
    CONTROLLER_ACTION_JOY_CODE_THROTTLE,

    CONTROLLER_ACTION_JOY_CODE_HAT1_TOP,
    CONTROLLER_ACTION_JOY_CODE_HAT1_RIGHT,
    CONTROLLER_ACTION_JOY_CODE_HAT1_BOTTOM,
    CONTROLLER_ACTION_JOY_CODE_HAT1_LEFT,

    CONTROLLER_ACTION_JOY_CODE_HAT2_TOP,
    CONTROLLER_ACTION_JOY_CODE_HAT2_RIGHT,
    CONTROLLER_ACTION_JOY_CODE_HAT2_BOTTOM,
    CONTROLLER_ACTION_JOY_CODE_HAT2_LEFT,

    CONTROLLER_ACTION_JOY_CODE_BTN_MIN
};

#define CONTROLLER_ACTION_JOY_CODE_BTN(n) \
  (CONTROLLER_ACTION_JOY_CODE_BTN_MIN + (n))

#define CONTROLLER_ACTION_JOY_CODE_MAX \
  CONTROLLER_ACTION_JOY_CODE_BTN(INPUT_REPORT_NUM_JOY_BUTTON - 1)

/* controller_action_config.kbd.flags */
#define CONTROLLER_ACTION_KBD_PRESS   0x0001
#define CONTROLLER_ACTION_KBD_RELEASE 0x0002
#define CONTROLLER_ACTION_KBD_THROUGH 0x0003
#define CONTROLLER_ACTION_KBD_REVERSE 0x0004

/* controller_action_config.kbd.code */
/*   see; Universal Serial Bus HID Usage Tables
          Chapter 10 Keyboard/Keypad Page (0x07) */
#define CONTROLLER_ACTION_KBD_CODE_MIN 0x0000
#define CONTROLLER_ACTION_KBD_CODE_MAX \
  (CONTROLLER_ACTION_KBD_CODE_MIN + INPUT_REPORT_NUM_KBD_CODE - 1)

/* controller_action_config.mou.flags */
#define CONTROLLER_ACTION_MOU_VAL_MIN     0x0001
#define CONTROLLER_ACTION_MOU_VAL_MAX     0x0002
#define CONTROLLER_ACTION_MOU_VAL_MDL     0x0003
#define CONTROLLER_ACTION_MOU_VAL_THROUGH 0x0004
#define CONTROLLER_ACTION_MOU_VAL_REVERSE 0x0005
#define CONTROLLER_ACTION_MOU_VAL_SPEC    0x0006
#define CONTROLLER_ACTION_MOU_VAL_RATIO   0x0007

/* controller_action_config.mou.code */
#define CONTROLLER_ACTION_MOU_CODE_X      0x00
#define CONTROLLER_ACTION_MOU_CODE_Y      0x01
#define CONTROLLER_ACTION_MOU_CODE_WHEEL  0x02
#define CONTROLLER_ACTION_MOU_CODE_BTN(n) (0x03 + (n))

#define CONTROLLER_ACTION_MOU_CODE_MAX \
  CONTROLLER_ACTION_MOU_CODE_BTN(INPUT_REPORT_NUM_MOU_BUTTON - 1)

/* sizeof(struct controller_action_config) == 32 */
struct controller_action_config {
    UCHAR type;                 /* type of action */

    char reserved[3];

    union {
        /* modifier */
        struct {
            USHORT mod;         /* modifier */
            USHORT mod_mask;    /* modifier mask */
        } mod;

        /* delay */
        struct {
            ULONG msec;         /* millisecond */
        } delay;

        /* joystick */
        struct {
            USHORT flags;       /* flags */
            USHORT code;        /* code */
            UCHAR val;          /* optional value */
            char reserved[1];
            SHORT ratio_numerator; /* numerator of ratio */
            SHORT ratio_denominator; /* denominator of ratio */
            SHORT offset;       /* offset */
        } joy;

        /* apply other action */
        struct {
            USHORT mod;         /* modifier: apply if match */
            USHORT mod_mask;    /* modifier mask */
            USHORT action_idx;  /* action index */
        } apply;

        /* keyboard */
        struct {
            USHORT flags;       /* flags */
            USHORT code;        /* code */
        } kbd;

        /* mouse */
        struct {
            USHORT flags;       /* flags */
            USHORT code;        /* code */
            UCHAR val;          /* optional value */
            char reserved[1];
            SHORT ratio_numerator; /* numerator of ratio */
            SHORT ratio_denominator; /* denominator of ratio */
            SHORT offset;       /* offset */
        } mou;

        char place_holder[28];
    };
};
