NET3001 Final — pin layout (Arduino Uno)

| Signal           | Arduino pin | MCU     | Notes                |
| ---------------- | ----------- | ------- | -------------------- |
| USART RX         | D0          | PD0     | USB serial           |
| USART TX         | D1          | PD1     | Serial Monitor       |
| HC-SR04 Echo     | D2          | PD2     | Input                |
| Buzzer           | D3          | PD3     | To GND               |
| LCD DB4–DB7      | D4–D7       | PD4–PD7 | 4-bit data           |
| LCD RS           | D8          | PB0     |                      |
| LCD E            | D9          | PB1     |                      |
| Button pause     | D10         | PB2     | To GND, pull-up      |
| 595 SER          | D11         | PB3     |                      |
| 595 SRCLK        | D12         | PB4     |                      |
| 595 RCLK         | D13         | PB5     |                      |
| Button reset     | A0          | PC0     | To GND, pull-up      |
| LED green        | A2          | PC2     | LED → resistor → GND |
| LED amber        | A3          | PC3     |                      |
| LED red          | A4          | PC4     |                      |
| HC-SR04 Trig     | A5          | PC5     | Output               |

See `include/PinMap.h` for register symbols.
