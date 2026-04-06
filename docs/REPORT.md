# Red-light traffic signal with ultrasonic “camera” (NET3001 Final)

## Title

Red-light traffic signal with ultrasonic zone detection and USART violation logging.

## Name of the group members and contributions

- **Abdul Rehman (Student 1)**: Hardware, TinkerCAD, video, serial testing.
- **Isaac Abdile (Student 2)**: Firmware, LCD/7-seg, report.

## Brief description of your system

10 s green, 5 s amber, 10 s red. LCD shows phase text; 7-segment countdown via 74HC595. Buttons pause/resume and reset to green at 10. On red, ultrasonic detects entering near zone; buzzer beeps once; LCD shows VIOLATION; USART prints `VIOLATION dist=XX cm`.

## Circuit diagram

_(Insert TinkerCAD export PNG/PDF here.)_

## List of components and topics used

**Components:** Uno, 3 LEDs + resistors, 2 buttons, LCD + pot, 7-seg + 595 + resistors, HC-SR04, buzzer, breadboard, wires.

**Topics:** GPIO, Timers (Timer1 tick), Interrupts (Timer1 compare + PCINT), optional USART, optional ultrasonic + buzzer.

## Detailed explanation (pseudo-code)

```
INIT pins, LCD, 7-seg, USART, Timer1 1 Hz, PCINT on buttons.
phase=GREEN, seconds=10, running=TRUE.
LOOP: handle debounced pause/reset; on 1 s tick update violation message timer or countdown phase;
      if RED and running, read ultrasonic, detect far-to-near while armed, trigger violation and USART;
      re-arm when far again.
```

## Short reflection

Hardest part: tuning zone thresholds and keeping ISRs short. Next time: USART calibration mode; optional Timer1 input capture on echo.
