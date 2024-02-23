# PMW3360 I2C Interface

Implementation of [SunjunKim's PMW3360 library](https://github.com/SunjunKim/PMW3360) to send the data over I2C (acting as an I2C target sending mouse data to the controller).

The code is designed for Arduino style microcontrollers and tested on an Osoyoo ATmega32U4 Pro Micro (5v) (https://osoyoo.com/2018/06/25/osoyoo-pro-micro-board/).

The PMW3360 breakout board used was the JACK Enterprises PMW3360 Motion Sensor board (https://www.tindie.com/products/jkicklighter/pmw3360-motion-sensor/)

## Pin connections

<table>
    <tr><th>    Pro micro    </th><th>    Moonlander                </th></tr>
    <tr><td>    SDA (2)      </td><td>    SDA (ribbon cable 10)     </td></tr>
    <tr><td>    SCL (3)      </td><td>    SCL (ribbon cable 9)      </td></tr>
    <tr><td>    RAW          </td><td>    5v (ribbon cable 16)      </td></tr>
    <tr><td>    GND          </td><td>    gnd (ribbon cable 1)      </td></tr>
</table>
<table>
    <tr><th>    Pro micro    </th><th>  PMW3360 module     </th></tr>
    <tr><td>    (NONE)       </td><td>  RS                 </td></tr>
    <tr><td>    GND          </td><td>  GD                 </td></tr>
    <tr><td>    (NONE)       </td><td>  MT                 </td></tr>
    <tr><td>    10           </td><td>  SS (Slave select)  </td></tr>
    <tr><td>    15           </td><td>  SC (SPI Clock)     </td></tr>
    <tr><td>    16           </td><td>  MO (MOSI)	       </td></tr>
    <tr><td>    14           </td><td>  MI (MISO)          </td></tr>
    <tr><td>    VCC          </td><td>  VI                 </td></tr>
</table>
