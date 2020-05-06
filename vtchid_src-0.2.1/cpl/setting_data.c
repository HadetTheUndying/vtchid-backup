/*
 * setting_data.c  -- device setting data
 *
 * $Id: setting_data.c,v 1.3 2004/06/14 12:28:51 hos Exp $
 *
 */

#include <windows.h>
#include "util.h"
#include "main.h"


struct controller_modifier_config default_motion_mod[CONTROLLER_NUM_EVENT];
struct controller_modifier_config default_press_mod[CONTROLLER_NUM_EVENT];
struct controller_modifier_config default_release_mod[CONTROLLER_NUM_EVENT];
unsigned short default_action_list[NUM_OF_DEF_ACTION];
struct controller_action_config default_action[NUM_OF_DEF_ACTION];
LPWSTR default_profile_name = L"default profile";
LPWSTR default_action_name[] = {
    L"null action",
    L"axis X motion",
    L"axis Y motion",
    L"axis RX motion",
    L"axis RY motion",
    L"axis RZ motion",
    L"axis Z 0/6",
    L"axis Z 1/6",
    L"axis Z 2/6",
    L"axis Z 3/6",
    L"axis Z 4/6",
    L"axis Z 5/6",
    L"axis Z 6/6",
    L"axis Slider 0/15",
    L"axis Slider 1/15",
    L"axis Slider 2/15",
    L"axis Slider 3/15",
    L"axis Slider 4/15",
    L"axis Slider 5/15",
    L"axis Slider 6/15",
    L"axis Slider 7/15",
    L"axis Slider 8/15",
    L"axis Slider 9/15",
    L"axis Slider 10/15",
    L"axis Slider 11/15",
    L"axis Slider 12/15",
    L"axis Slider 13/15",
    L"axis Slider 14/15",
    L"axis Slider 15/15",
    L"button 1 press",
    L"button 1 release",
    L"button 2 press",
    L"button 2 release",
    L"button 3 press",
    L"button 3 release",
    L"button 4 press",
    L"button 4 release",
    L"button 5 press",
    L"button 5 release",
    L"button 6 press",
    L"button 6 release",
    L"button 7 press",
    L"button 7 release",
    L"button 8 press",
    L"button 8 release",
    L"button 9 press",
    L"button 9 release",
    L"button 10 press",
    L"button 10 release",
    L"button 11 press",
    L"button 11 release",
    L"button 12 press",
    L"button 12 release",
    L"button 13 press",
    L"button 13 release",
    L"button 14 press",
    L"button 14 release",
    L"button 15 press",
    L"button 15 release",
    L"button 16 press",
    L"button 16 release",
    L"button 17 press",
    L"button 17 release",
    L"button 18 press",
    L"button 18 release",
    L"button 19 press",
    L"button 19 release",
    L"button 20 press",
    L"button 20 release",
    L"button 21 press",
    L"button 21 release",
    L"button 22 press",
    L"button 22 release",
    L"button 23 press",
    L"button 23 release",
    L"button 24 press",
    L"button 24 release",
    L"button 25 press",
    L"button 25 release",
    L"button 26 press",
    L"button 26 release",
    L"button 27 press",
    L"button 27 release",
    L"button 28 press",
    L"button 28 release",
    L"modifier 1 on",
    L"modifier 1 off",
    L"modifier 2 on",
    L"modifier 2 off",
    L"modifier 3 on",
    L"modifier 3 off",
    L"modifier 4 on",
    L"modifier 4 off",
    L"modifier 5 on",
    L"modifier 5 off",
    L"button 29 press",
    L"button 29 release",
    L"modifier 6 on",
    L"modifier 6 off",
    L"modifier 7 on",
    L"modifier 7 off",
    L"modifier 8 on",
    L"modifier 8 off",
    L"modifier 9 on",
    L"modifier 9 off",
    L"modifier 10 on",
    L"modifier 10 off",
    L"button 30 press",
    L"button 30 release",
    L"button 31 press",
    L"button 31 release",
    L"button 32 press",
    L"button 32 release",
};

void generate_default_setting(void)
{
    int i, ai;
    USHORT code;
    USHORT btn_code = CONTROLLER_ACTION_JOY_CODE_BTN_MIN;
    USHORT mod_code = 0;

    memset(default_motion_mod, 0, sizeof(default_motion_mod));
    memset(default_press_mod, 0, sizeof(default_press_mod));
    memset(default_release_mod, 0, sizeof(default_release_mod));
    memset(default_action_list, 0, sizeof(default_action_list));
    memset(default_action, 0, sizeof(default_action));

    ai = 1;
    for(i = 0; i < CONTROLLER_NUM_EVENT; i++) {
        if(i <= CONTROLLER_EVT_CODE_AXIS_MAX) {
            /* motion action for axis: pass through value */

            switch(i) {
              case CONTROLLER_EVT_CODE_AIM_X:
                  code = CONTROLLER_ACTION_JOY_CODE_X;
                  break;

              case CONTROLLER_EVT_CODE_AIM_Y:
                  code = CONTROLLER_ACTION_JOY_CODE_Y;
                  break;

              case CONTROLLER_EVT_CODE_SIGHT_X:
                  code = CONTROLLER_ACTION_JOY_CODE_RX;
                  break;

              case CONTROLLER_EVT_CODE_SIGHT_Y:
                  code = CONTROLLER_ACTION_JOY_CODE_RY;
                  break;

              case CONTROLLER_EVT_CODE_ROTATION:
                  code = CONTROLLER_ACTION_JOY_CODE_RZ;
                  break;

              default:
                  /* not reach */
                  code = 0;
                  break;
            }

            default_motion_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_JOY;
            default_action[ai].joy.flags = CONTROLLER_ACTION_JOY_VAL_THROUGH;
            default_action[ai].joy.code = code;
            ai += 1;
        } else if(i <= CONTROLLER_EVT_CODE_GEAR_MAX) {
            /* gear lever: z axis */
            default_press_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_JOY;
            default_action[ai].joy.flags = CONTROLLER_ACTION_JOY_VAL_SPEC;
            default_action[ai].joy.code = CONTROLLER_ACTION_JOY_CODE_Z;
            default_action[ai].joy.val =
                (i - CONTROLLER_EVT_CODE_GEAR_MIN) * 0xff /
                (CONTROLLER_EVT_CODE_GEAR_MAX - CONTROLLER_EVT_CODE_GEAR_MIN);
            ai += 1;
        } else if(i <= CONTROLLER_EVT_CODE_TUNER_MAX) {
            /* tuner dial: slider axis */
            default_press_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_JOY;
            default_action[ai].joy.flags = CONTROLLER_ACTION_JOY_VAL_SPEC;
            default_action[ai].joy.code = CONTROLLER_ACTION_JOY_CODE_SLIDER;
            default_action[ai].joy.val =
                (i - CONTROLLER_EVT_CODE_TUNER_MIN) * 0xff /
                (CONTROLLER_EVT_CODE_TUNER_MAX -
                 CONTROLLER_EVT_CODE_TUNER_MIN);
            ai += 1;
        } else if(i <= CONTROLLER_EVT_CODE_WC_MAGAZINE_CHANGE ||
                  i == CONTROLLER_EVT_CODE_SIGHT_BUTTON ||
                  (i >= CONTROLLER_EVT_CODE_FOOT_PEDAL_LEFT &&
                   i <= CONTROLLER_EVT_CODE_FOOT_PEDAL_RIGHT)) {
            /* digital button, foot pedal: press/release button action */
            code = btn_code++;

            default_press_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_JOY;
            default_action[ai].joy.flags = CONTROLLER_ACTION_JOY_VAL_MAX;
            default_action[ai].joy.code = code;
            ai += 1;

            default_release_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_JOY;
            default_action[ai].joy.flags = CONTROLLER_ACTION_JOY_VAL_MIN;
            default_action[ai].joy.code = code;
            ai += 1;
        } else {
            /* communication tuner, toggle buttons: modifier */
            USHORT mod;

            mod = (1 << mod_code++);

            default_press_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_MOD;
            default_action[ai].mod.mod = mod;
            default_action[ai].mod.mod_mask = mod;
            ai += 1;

            default_release_mod[i].action_idx = ai;
            default_action_list[ai] = ai;
            default_action[ai].type = CONTROLLER_ACTION_MOD;
            default_action[ai].mod.mod = 0;
            default_action[ai].mod.mod_mask = mod;
            ai += 1;
        }
    }
}
