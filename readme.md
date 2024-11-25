# Moonrover MK2 QMK fork
This is a fork of the ZSA fork of QMK Firmware.

Replaces the right thumb cluster with a trackball running a PMW3360 sensor on an arduino-based MCU. Connects to the keyboard directly via the original ribbon cable, no external wires to connect, and the keyboard (with trackball) is just as portable as the original keyboard.

![image](https://github.com/nivekmai/qmk_firmware/assets/1008043/e52484b2-b58b-4cc2-8ec7-28c9f30fe073)

Essential code is in 2 places: 
- [Accessory code](accessories/ardunio/PMW3360_I2C)
  - See the [README](accessories/ardunio/PMW3360_I2C/README.md) for details.
- [Configuration code](keyboards/zsa/moonlander/keymaps/nivekmai/keymap.c)
  - This repo currently contains a custom implementation of a drag scroll. You can ignore the `is_scrolling` code to receive mouse movements from the accessory.
  - config.h: can be completely copied from Oryx
  - rules.mk: mostly copied from Oryx, need to add the pointer commands though
  - keymap.c: where all the drag scroll code lives, can add the entire Oryx file after `END OVERRIDES`, `MOUSE_SCROLL_V` is the keycode to toggle drag scroll on/off (I like to put in KC_F24) and then just do a search/replace before flashing)
  - See the [original docs](https://docs.qmk.fm/#/feature_pointing_device?id=custom-driver) for more information.
 
See the [printables page](https://www.printables.com/model/776160-moonrover-mk2) (or the [archived copy](printables.pdf) in this repo) for hardware instructions and models (also [archived copy in the accessories folder](accessories/ardunio/PMW3360_I2C/moonrover-mk2-model_files.zip))

## Working setup/installation (as of 11/25/2024)
- ```qmk configure user.keyboard=zsa/moonlander user.keymap=nivekmai```
- ```qmk compile```
- Use [QMK Toolbox](https://qmk.fm/toolbox) to flash to keyboard

# ZSA's fork of QMK Firmware

[![Current Version](https://img.shields.io/github/tag/zsa/qmk_firmware.svg)](https://github.com/zsa/qmk_firmware/tags)
[![Build firmware](https://github.com/zsa/qmk_firmware/actions/workflows/build.yml/badge.svg)](https://github.com/zsa/qmk_firmware/actions/workflows/build.yml)
[![Unit Tests](https://github.com/zsa/qmk_firmware/actions/workflows/unit_test.yml/badge.svg)](https://github.com/zsa/qmk_firmware/actions/workflows/unit_test.yml)
[![GitHub contributors](https://img.shields.io/github/contributors/zsa/qmk_firmware.svg)](https://github.com/zsa/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/zsa/qmk_firmware.svg?style=social&label=Fork)](https://github.com/zsa/qmk_firmware/)

This purpose of this fork is maintain a clean repo that only contains the keyboard code that we need, and as little else as possible.  This is to keep it lightweight, since we only need a couple of keyboards. This is the repo that the EZ Configurator will pull from.
## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [VitePress](https://vitepress.dev/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls).


## Supported Keyboards

* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Planck EZ](/keyboards/planck/ez)
* [Moonlander Mark I](/keyboards/moonlander)

## Building

To set up the local build enviroment to create the firmware image manually, head to the [Newbs guide from QMK](https://docs.qmk.fm/#/newbs).
And instead of using just `qmk setup`, you will want to run this instead:

```sh
qmk setup zsa/qmk_firmware -b firmware24
```

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

# Update Process

1. Check out branch from ZSA's master branch:
    1. `git remote add zsa https://github.com/zsa/qmk_firmware.git`
    2. `git fetch --all`
    3. `git checkout -B branchname zsa/master`
    4. `git push -u zsa branchname`
2. Check for core changes:
    - [https://github.com/qmk/qmk_firmware/commits/master/quantum](https://github.com/qmk/qmk_firmware/commits/master/quantum)
    - [https://github.com/qmk/qmk_firmware/commits/master/tmk_core](https://github.com/qmk/qmk_firmware/commits/master/tmk_core)
    - [https://github.com/qmk/qmk_firmware/commits/master/util](https://github.com/qmk/qmk_firmware/commits/master/util)
    - [https://github.com/qmk/qmk_firmware/commits/master/drivers](https://github.com/qmk/qmk_firmware/commits/master/drivers)
    - [https://github.com/qmk/qmk_firmware/commits/master/lib](https://github.com/qmk/qmk_firmware/commits/master/lib)
    - These folders are the important ones for maintaining the repo and keeping it properly up to date. Most, but not all, changes on this list should be pulled into our repo.
4. `git merge (hash|tag)`
    - `git rm -rf docs users layouts .vscode` to remove the docs and user code that we don't want.
    - To remove all of the keyboard exept the ones we want:
      ```sh
      find ./keyboards -mindepth 1 -maxdepth 1 -type d -not -name ergodox_ez -not -name planck -not -name moonlander -not -name zsa -exec git rm -rf '{}' \;
      find ./keyboards/planck -mindepth 1 -maxdepth 1 -type d -not -name ez -not -name base -not -name glow -not -name keymaps -exec git rm -rf '{}' \;
      ```
    - To remove all of the keymaps from folder that we don't want:
      ```sh
      find ./keyboards/ -mindepth 3 -maxdepth 3 -type d -not -name ld -not -name default -not -name oryx -not -name webusb -not -name base -not -name glow -not -name reactive -not -name shine -not -name keymaps -not -name halfmoon -exec git rm -rf '{}' \;
      ```
    - Restore necessary files/folders:
      ```sh
      git checkout HEAD -- keyboards/handwired/pytest
      ```
    - Resolve merge conflicts, and commit.

4. Commit update
   * Include commit info in `[changelog.md](changelog.md)`
5. Open Pull request, and include information about the commit

## Strategy

To keep PRs small and easier to test, they should ideally be 1:1 with commits from QMK Firmware master. They should only group commits if/when it makes sense. Such as multiple commits for a specific feature (split RGB support, for instance)
