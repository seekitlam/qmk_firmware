# QMK Firmware for Epomaker TH96

This is a QMK firmware for [Epomaker TH96](https://epomaker.com/products/epomaker-th96?_pos=1&_sid=3c7159ad2&_ss=r&variant=40077772193865) wired version.

The purpose of this repo is to learn QMK and to solve several issues of the original firmware running on M1 Mac Mini.

[Epomaker TH96 repo](https://github.com/Epomaker/qmk_firmware) has knob issue. The keyboard crashes/bricks after turning the knob. There is also another [repo by nikchi](https://github.com/nikchi/qmk_firmware) which has keymap issues.

Keymap and several other changes from Epomaker are merged into nikchi's repo. Everything seems to work after flashing.

## Steps
Follow [these instructions](https://docs.qmk.fm/#/getting_started_build_tools) to setup your environment, to compile and to flash the firmware.

### DFU (Bootloader) Mode

To get into DFU mode for this keyboard, hold the ESC key and connect the USB cable. 

After flashing with this firmware, QK_BOOT is mapped to the DEL key in the MAC_FN layer. FN + DEL put the keyboard into DFU mode.

## Issues

1. Some keys like KC_VOLU/KC_VOLD in MAC_FN layer stop working after resume in MacOS. Temporary solution is to reboot the keyboard. QK_RBT (resets the keyboard and oes not load the bootloader) is mapped to the top key next to the knob on MAC_FN layer. A convenient way to reboot the keyboard without replugging the cable.
