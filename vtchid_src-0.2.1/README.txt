
    vtchid  -- VT Controller HID driver


Introduction
 The `vtchid' is a device driver to use VT Controller, as known as
Steel Battalion Controler.  This driver implemented as HID minidriver.
This software is distributed as FREE, NO GUARANTEE, NO LIMITATION.
(This means treat as Public Domain Software.)


Requirements
 OS    : Windows XP/2000
 Device: VT Controller
         Connector converter between XBox <-> USB


Install
 - Extract packed file.
 - Connect VT Controller to USB Port.
 - When appears device driver wizard, select `vtchid.inf' file.
 - Optionally, copy `vtchidldr.exe' to somewhere and regist short-cut
   to this program.
   For more information, see Profile Loader.


Upgrade
 - Extract packed file.
 - Select `VT Controller' from Device Manager, and press `Driver
   upgrade' button at Driver tab of Property.
 - Select `vtchid.inf' and install.


Profile Loader
 `vtchidldr.exe' is a program to load current settings for driver.

 This program allows following options.

 - vtchidldr    FILENAME
   vtchidldr -l FILENAME : Load specified file as profile.
			   "-l" can be omit.
 - vtchidldr -s FILENAME : Save current profile to specified file.

 If no option specified, only load current setting.


Axes and Buttons
 Default setting of axis and buttons.

 - Axes: AIMING LEVER   => X, Y
	 GEAR LEVER     => Z
	 SIGHT STICK    => Rx, Ry
	 ROTATION LEVER => Rz
	 TUNER DIAL     => Slider
 - Buttons:
   - Button  1: MAIN WEAPON
   - Button  2: SUB WEAPON
   - Button  3: LOCK ON
   - Button  4: EJECT CMD
   - Button  5: COCKPIT HATCH
   - Button  6: IGNITION
   - Button  7: START
   - Button  8: MULTI MONITOR - OPEN/CLOSE
   - Button  9: MULTI MONITOR - MAP ZOOM IN/OUT
   - Button 10: MULTI MONITOR - MODE SELECT
   - Button 11: SUB MONITOR MODE SELECT
   - Button 12: MAIN MONITOR ZOOM - IN
   - Button 13: MAIN MONITOR ZOOM - OUT
   - Button 14: F.S.S
   - Button 15: MANIPULATOR
   - Button 16: LINE COLOR CHANGE
   - Button 17: WASHING
   - Button 18: EXTINGUISHER
   - Button 19: CHAFF
   - Button 20: TANK DETACH
   - Button 21: OVERRIDE
   - Button 22: NIGHT SCOPE
   - Button 23: F1
   - Button 24: F2
   - Button 25: F3
   - Button 26: WEAPON CONTROLS - MAIN
   - Button 27: WEAPON CONTROLS - SUB
   - Button 28: WEAPON CONTROLS - MAGAZINE CHANGE
   - Button 29: SIGHT CHANGE - PUSH
   - Button 30: FOOT PEDAL - LEFT
   - Button 31: FOOT PEDAL - CENTER
   - Button 32: FOOT PEDAL - RIGHT
 - Modifiers:
   - Modifier  1: COMMUNICATION TUNER - 1
   - Modifier  2: COMMUNICATION TUNER - 2
   - Modifier  3: COMMUNICATION TUNER - 3
   - Modifier  4: COMMUNICATION TUNER - 4
   - Modifier  5: COMMUNICATION TUNER - 5
   - Modifier  6: FILT CONTROL SYSTEM
   - Modifier  7: OXYGEN SUPPLY SYSTEM
   - Modifier  8: FUEL FLOW RATE
   - Modifier  9: BUFFER MATERIAL
   - Modifier 10: VT-LOCATION MEASUREMENT

 * Axis Throttle is not assigned by default.
 * POV 1 and 2 are no assigned by default.


Modifiers
 There are 16 modiiers which has ON and OFF state.  These can change
 axis, buttons setting by it's state.

 For example, see Samples.


Samples
 There are setting samples in samples/ directory.

 - axis.sdp        Sample of axis setting.
		   AIMING LEVER is X, Y axis same as default.
		   SIGHT CHANGE is Rx, Ry axis in reverse.
		   ROTATION LEVER is narrowed Rz axis.
		   FOOT PEDAL LEFT and RIGHT are RZ axis.

 - buttons.sdp	   Sample of button setting.
		   MAIN WEAPON is button 1.
		   SUB WEAPON is button 2 in reverse.
		   F1 button is button 3 on when pressed.
		   F2 button is button 3 off when pressed.
		   Left side of ROTATION LEVER is button 4.
		   Right side of ROTATION LEVER is button 4.

 - modiiers.sdp	   Sample of modifier setting.
		   Toggle switches on right colum are mod 1 to 3, and
		   MAIN WEAPON assignment is change by each on/off
		   combinations.
		   Pressing F1 changes on/off state of mod 8.
		   Pressing F2 changes on/off state of mod 9/10.

 - delay.sdp	   Sample of delay action.
		   When pressing MAIN WEAPON, executes
		   button 1 on -> wait for 1sec -> button 1 off

 - apply.sdp	   Sample of execute other Action list.
		   When pressing MAIN WEAPON, executes
		   button 9 on -> wait for 1sec -> button 9 off ->
		   button 10 on -> wait for 1sec -> button 10 off
		   (First half and latter half are different Action list.)
		   And, when pressing SUB WEAPON, executes turn on and
		   off button 1 to 8 in order, and repeat. When press
		   LOCK ON in repeating, mod 1 is turn on and repeat
		   is stop.

 - mouse.sdp	   Sample of mouse setting.
		   SIGHT CHANGE is cursor movement.
		   MAIN WEAPON and SUB WEAPON are button 1 and 2 (left
		   click and right click).

 - keyboard.sdp	   Sample of keyboard setting.
		   MAIN WEAPON is key A.
		   SUB WEAPON is sequence of A, B, C.


How to connect XBox controller connector to USB port
  (USB Type A Male <-> USB Type A Female) + (XBox Male <-> XBox Female)
= (USB Type A Male <- ) + ( -> USB Type A Female) +
                              (XBox Male <- ) + ( -> Xbox Female)
= (USB Type A Male <-> Xbox Female) + (XBox Male <-> USB Type A Female)


How to build driver from source
 - Install Cygwin environment with development packages (binutils,
   fileutils, gcc, make, w32api).
 - Install DirectX headers for Cygwin.
   <http://www.libsdl.org/extras/win32/cygwin/>
 - Install Borland C++ Compiler 5.5 (only to use Japanese resource).
   <http://www.borland.co.jp/cppbuilder/freecompiler/>
 - Extract source files.
 - Enter extracted directory, and type `make'.
   (if do not use Japanese resource, type `make USE_BRCC=no')


Link
 - USB.org - HID Tools: <http://www.usb.org/developers/hidpage/>
 - Microsoft Windows Driver Development Kits:
   <http://www.microsoft.com/whdc/ddk/winddk.mspx>
 - HID Game Controllers and DirectInput:
   <http://www.microsoft.com/whdc/hwdev/tech/input/hidgame.mspx>
 - Device driver for Xbox controller:
   <http://www.katch.ne.jp/~morii/xgc/>
 - XID: <http://www.grooveyardfunk.com/projects/xid/>
 - Dhauzimmer's X36/X45 USB filter driver: <http://vega.dyndns.org/x36/>
 - hfsd: <http://www.tamanegi.org/prog/hfsd/>
 - vtchid: <http://www.tamanegi.org/prog/vtchid/>


$Id: README.txt,v 1.7 2004/06/14 14:01:31 hos Exp $
