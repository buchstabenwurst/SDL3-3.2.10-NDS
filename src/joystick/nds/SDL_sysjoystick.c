/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2025 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/
#include "SDL_internal.h"

#ifdef SDL_JOYSTICK_NDS

// This is the dummy implementation of the SDL joystick API

#include "../SDL_sysjoystick.h"
#include "../SDL_joystick_c.h"
#include "nds.h"

#define NB_BUTTONS 12


static bool NDS_JoystickInit(void)
{
    SDL_PrivateJoystickAdded(1);
    return true;
}

static int NDS_JoystickGetCount(void)
{
    return 1;
}

static void NDS_JoystickDetect(void)
{
}

static bool NDS_JoystickIsDevicePresent(Uint16 vendor_id, Uint16 product_id, Uint16 version, const char *name)
{
    return false;
}

static const char *NDS_JoystickGetDeviceName(int device_index)
{
    return "Nintendo DS";
}

static const char *NDS_JoystickGetDevicePath(int device_index)
{
    return NULL;
}

static int NDS_JoystickGetDeviceSteamVirtualGamepadSlot(int device_index)
{
    return -1;
}

static int NDS_JoystickGetDevicePlayerIndex(int device_index)
{
    return -1;
}

static void NDS_JoystickSetDevicePlayerIndex(int device_index, int player_index)
{
}

static SDL_GUID NDS_JoystickGetDeviceGUID(int device_index)
{
    SDL_GUID guid = SDL_CreateJoystickGUIDForName("Nintendo DS");
    return guid;
}

static SDL_JoystickID NDS_JoystickGetDeviceInstanceID(int device_index)
{
    return device_index + 1;
}

static bool NDS_JoystickOpen(SDL_Joystick *joystick, int device_index)
{

    joystick->nbuttons = NB_BUTTONS;
    joystick->naxes = 0;
    joystick->nhats = 0;
    return true;
}

static bool NDS_JoystickRumble(SDL_Joystick *joystick, Uint16 low_frequency_rumble, Uint16 high_frequency_rumble)
{
    return SDL_Unsupported();
}

static bool NDS_JoystickRumbleTriggers(SDL_Joystick *joystick, Uint16 left_rumble, Uint16 right_rumble)
{
    return SDL_Unsupported();
}

static bool NDS_JoystickSetLED(SDL_Joystick *joystick, Uint8 red, Uint8 green, Uint8 blue)
{
    return SDL_Unsupported();
}

static bool NDS_JoystickSendEffect(SDL_Joystick *joystick, const void *data, int size)
{
    return SDL_Unsupported();
}

static bool NDS_JoystickSetSensorsEnabled(SDL_Joystick *joystick, bool enabled)
{
    return SDL_Unsupported();
}

static void NDS_JoystickUpdate(SDL_Joystick *joystick)
{
    Uint64 timestamp = SDL_GetTicksNS();
    scanKeys();
    u32 updated_down = keysDown();
    u32 updated_up = keysUp();
    if (updated_down) {
        for (Uint8 i = 0; i < joystick->nbuttons; i++) {
            if (updated_down & BIT(i)) {
                SDL_SendJoystickButton(timestamp, joystick, i, true);
            }
        }
    }
    if (updated_up) {
        for (Uint8 i = 0; i < joystick->nbuttons; i++) {
            if (updated_up & BIT(i)) {
                SDL_SendJoystickButton(timestamp, joystick, i, false);
            }
        }
    }
}

static void NDS_JoystickClose(SDL_Joystick *joystick)
{
}

static void NDS_JoystickQuit(void)
{
}

static bool NDS_JoystickGetGamepadMapping(int device_index, SDL_GamepadMapping *out)
{
    // There is only one possible mapping.
    *out = (SDL_GamepadMapping){
        .a = { EMappingKind_Button, 0 },
        .b = { EMappingKind_Button, 1 },
        .x = { EMappingKind_Button, 10 },
        .y = { EMappingKind_Button, 11 },
        .back = { EMappingKind_Button, 2 },
        .guide = { EMappingKind_None, 255 },
        .start = { EMappingKind_Button, 3 },
        .leftstick = { EMappingKind_None, 255 },
        .rightstick = { EMappingKind_None, 255 },
        .leftshoulder = { EMappingKind_Button, 9 },
        .rightshoulder = { EMappingKind_Button, 8 },
        .dpup = { EMappingKind_Button, 6 },
        .dpdown = { EMappingKind_Button, 7 },
        .dpleft = { EMappingKind_Button, 5 },
        .dpright = { EMappingKind_Button, 4 },
        .misc1 = { EMappingKind_None, 255 },
        .right_paddle1 = { EMappingKind_None, 255 },
        .left_paddle1 = { EMappingKind_None, 255 },
        .right_paddle2 = { EMappingKind_None, 255 },
        .left_paddle2 = { EMappingKind_None, 255 },
        .leftx = { EMappingKind_None, 255 },
        .lefty = { EMappingKind_None, 255 },
        .rightx = { EMappingKind_None, 255 },
        .righty = { EMappingKind_None, 255 },
        .lefttrigger = { EMappingKind_None, 255 },
        .righttrigger = { EMappingKind_None, 255 },
    };
    return true;
}

SDL_JoystickDriver SDL_NDS_JoystickDriver = {
    NDS_JoystickInit,
    NDS_JoystickGetCount,
    NDS_JoystickDetect,
    NDS_JoystickIsDevicePresent,
    NDS_JoystickGetDeviceName,
    NDS_JoystickGetDevicePath,
    NDS_JoystickGetDeviceSteamVirtualGamepadSlot,
    NDS_JoystickGetDevicePlayerIndex,
    NDS_JoystickSetDevicePlayerIndex,
    NDS_JoystickGetDeviceGUID,
    NDS_JoystickGetDeviceInstanceID,
    NDS_JoystickOpen,
    NDS_JoystickRumble,
    NDS_JoystickRumbleTriggers,
    NDS_JoystickSetLED,
    NDS_JoystickSendEffect,
    NDS_JoystickSetSensorsEnabled,
    NDS_JoystickUpdate,
    NDS_JoystickClose,
    NDS_JoystickQuit,
    NDS_JoystickGetGamepadMapping
};

#endif // SDL_JOYSTICK_NDS
