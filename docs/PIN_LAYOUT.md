NET3001 Final — pin layout (Arduino Uno)

| Signal              | Arduino pin | MCU     | Notes                |
| ------------------- | ----------- | ------- | -------------------- |
| USART RX            | D0          | PD0     | USB serial           |
| USART TX            | D1          | PD1     | Serial Monitor       |
| Ultrasonic echo     | D2          | PD2     | Input                |
| Buzzer              | D3          | PD3     | To GND               |
| LCD DB4–DB7         | D4–D7       | PD4–PD7 | 4-bit data           |
| LCD RS              | D8          | PB0     |                      |
| LCD E               | D9          | PB1     |                      |
| Push button (pause) | D10         | PB2     | To GND, pull-up      |
| Shift register SER  | D11         | PB3     |                      |
| Shift register CLK  | D12         | PB4     |                      |
| Shift register RCLK | D13         | PB5     |                      |
| Push button (reset) | A0          | PC0     | To GND, pull-up      |
| LED green           | A2          | PC2     | LED → resistor → GND |
| LED amber           | A3          | PC3     |                      |
| LED red             | A4          | PC4     |                      |
| Ultrasonic trigger  | A5          | PC5     | Output               |

See `include/PinMap.h` for register symbols.
