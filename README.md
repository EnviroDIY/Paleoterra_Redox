# Paleo Terra Redox sensors

A collection of Arduino scripts and instructions to operate Redox sensors and reference electrodes from [Paleo Terra](https://paleoterra.nl).

Paleo Terra makes three types of redox probes:
* **Passive probes**
  * Measured with data logger's analog-to-digital (A/D) converter
  * low amperage requires low impedance system
* **Amplified probes**
  * Measured with data logger's analog-to-digital (A/D) converter
  * Powered amplifier
* **Active probes**
  * Have onboard analog-to-digital (A/D) converter, a [MicroChip MCP3421](https://www.microchip.com/wwwproducts/en/en520011)
    * 2.7V to 5.5V supply voltage
  * Digital data communication via I2C
