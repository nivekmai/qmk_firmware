# Moonrover MK1(r2)

<img src="https://github.com/nivekmai/qmk_firmware/assets/1008043/fad5d58f-a6a2-4e84-833f-6648be2c4cbb" width="400" />

## Revision 2 of Moonrover Mark 1

This setup adds a [Pimoroni trackball](https://shop.pimoroni.com/products/trackball-breakout?variant=27672765038675) to the [ZSA Moonlander](https://www.zsa.io/moonlander/). The trackball is connected via I<sup>2</sup>C breakout that ZSA exposed over the ribbon cable to attach the thumb cluster (designed with replacing the right thumb in mind).

> [!NOTE]
> This setup isn't ideal (the pimoroni trackball is not good enough to be a mouse replacement), and therefore I'm moving onto a better trackball setup in my [MK2](https://github.com/nivekmai/qmk_firmware/tree/i2c-arduino-trackball) branch. I recommend checking that out for a proper trackball setup for the Moonlander.

The benefits of the MK1 setup is that it's relatively straightforward to build.

## BOM

- [ZSA Moonlander](https://www.zsa.io/moonlander/)
- [Pimoroni trackball](https://shop.pimoroni.com/products/trackball-breakout?variant=27672765038675)
- (recommended) FPC 16P 0.5mm pitch ribbon cable beakout (I used [this one](https://www.amazon.com/dp/B0CLYBRHXD?psc=1&ref=ppx_yo2ov_dt_b_product_details))
- FPC 16P 0.5mm pitch ribbon cable
  - The one that came with the moonlander is probably too short when connecting to a breakout board
  - I used [this one](https://www.amazon.com/dp/B09R8X99HL?psc=1&ref=ppx_yo2ov_dt_b_product_details) 

## Wiring

Connect via the ribbon cable that's normally used to connect the right thumb cluster:

<img src="https://github.com/nivekmai/qmk_firmware/assets/1008043/458c08e5-850f-483c-8d06-5a1924142ea2" width="400" />

<table>
    <tr>
        <td>Moonlander</td>    <td>Pimoroni trackball</td>
    </tr><tr>
        <td>1</td>             <td>GND</td>
    </tr><tr>
        <td>9</td>             <td>SCL</td>
    </tr><tr>
        <td>10</td>            <td>SDA</td>
    </tr><tr>
        <td>16</td>            <td>3-5V</td>
    </tr><tr>
        <td>None</td>          <td>INT</td>
    </tr>
</table>

> [!CAUTION]
> If you use a B type cable like I did, make sure you reverse the pins from the ribbon cables. On the breakout board I used, the opposite side has reversed pins which made things easier.

## Hardware

Model available on [printables](https://www.printables.com/model/751773-moonrover-mk1).

----

# ZSA's fork of QMK Firmware

[![Current Version](https://img.shields.io/github/tag/zsa/qmk_firmware.svg)](https://github.com/zsa/qmk_firmware/tags)
[![Build firmware](https://github.com/zsa/qmk_firmware/actions/workflows/build.yml/badge.svg)](https://github.com/zsa/qmk_firmware/actions/workflows/build.yml)
[![Unit Tests](https://github.com/zsa/qmk_firmware/actions/workflows/unit_test.yml/badge.svg)](https://github.com/zsa/qmk_firmware/actions/workflows/unit_test.yml)
[![GitHub contributors](https://img.shields.io/github/contributors/zsa/qmk_firmware.svg)](https://github.com/zsa/qmk_firmware/pulse/monthly)
[![GitHub forks](https://img.shields.io/github/forks/zsa/qmk_firmware.svg?style=social&label=Fork)](https://github.com/zsa/qmk_firmware/)

This purpose of this fork is maintain a clean repo that only contains the keyboard code that we need, and as little else as possible.  This is to keep it lightweight, since we only need a couple of keyboards. This is the repo that the EZ Configurator will pull from.
## Documentation

* [See the official documentation on docs.qmk.fm](https://docs.qmk.fm)

The docs are powered by [Docsify](https://docsify.js.org/) and hosted on [GitHub](/docs/). They are also viewable offline; see [Previewing the Documentation](https://docs.qmk.fm/#/contributing?id=previewing-the-documentation) for more details.

You can request changes by making a fork and opening a [pull request](https://github.com/qmk/qmk_firmware/pulls), or by clicking the "Edit this page" link at the bottom of any page.


## Supported Keyboards

> [!NOTE]
> The pimoroni trackball setup is only tested on the moonlander, but QMK natively supports the trackball so installing it on any other ZSA keyboard shouldn't be too complicated.

* [ErgoDox EZ](/keyboards/ergodox_ez/)
* [Planck EZ](/keyboards/planck/ez)
* [Moonlander Mark I](/keyboards/moonlander)

## Building

To set up the local build enviroment to create the firmware image manually, head to the [Newbs guide from QMK](https://docs.qmk.fm/#/newbs).
And instead of using just `qmk setup`, you will want to run this instead:

```sh
qmk setup nivekmai/qmk_firmware -b pimoroni
```

## Maintainers

QMK is developed and maintained by Jack Humbert of OLKB with contributions from the community, and of course, [Hasu](https://github.com/tmk). The OLKB product firmwares are maintained by [Jack Humbert](https://github.com/jackhumbert), the Ergodox EZ by [ZSA Technology Labs](https://github.com/zsa), the Clueboard by [Zach White](https://github.com/skullydazed), and the Atreus by [Phil Hagelberg](https://github.com/technomancy).

# Update Process

This branch doesn't really introduce anything that should be merged into QMK (or the ZSA branch), so updates aren't expected.
