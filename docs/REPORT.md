# Report (NET3001 Final) — source text for Word / PDF

Use this file to copy into **`docs/REPORT.docx`** or paste sections as needed. Export **`docs/Report(NET3001 Final).pdf`** if the course asks for PDF.

---

## What you still need to add (before submitting)

| Missing in draft | What to do |
|------------------|------------|
| **Circuit diagram** | Insert **TinkerCAD** schematic or wiring diagram (**PNG** or **PDF**). Replace the placeholder paragraph under *Circuit diagram*. |
| **Topics used** | Add a line or short paragraph (see below). Many rubrics expect **GPIO, Timer1, interrupts, USART**, etc. |
| **Parts list detail** | Add **LCD contrast pot**, **jumper wires**, **resistor values** if your instructor wants them (e.g. 220 Ω on LEDs). |
| **Cover / metadata** | If required: **course code**, **section**, **Group 19**, **date**, **instructor name**. |
| **Demo video** | Submit **link or file** per LMS (usually **not** embedded in the repo). |
| **Role wording** | Make sure **one** story: e.g. Abdul = build + TinkerCAD + video + serial; Isaac = firmware + LCD + 7-segment + report — avoid duplicating “hardware” under both unless you mean different things. |

---

## Title

Red-light traffic signal with ultrasonic “camera” (NET3001 Final)

---

## Name of the group members and contributions

- **Abdul Rehman (Student 1):** TinkerCAD schematic, demo video, serial monitor testing, hardware build / bench wiring.
- **Isaac Abdile (Student 2):** Firmware (PlatformIO), GPIO / Timer1 / interrupts / USART, LCD and 7-segment (shift registers), written report.

*(Adjust bullets to match what you actually did; keep it consistent with the video and repo.)*

---

## Brief description of your system

The traffic light runs **10 s green → 5 s amber → 10 s red**, repeating. A **16×2 LCD** shows the current phase text; a **7-segment display** shows the **seconds remaining** in the current phase, driven through **shift registers**. Two **push buttons**: **pause/resume** the countdown and **reset** to **green** with **10 s** left. While the light is **red** and not paused, an **ultrasonic sensor** estimates distance; if something crosses from a **far** zone to a **near** zone, the firmware treats it as a **red-light violation**: the **buzzer** sounds, the LCD shows a **VIOLATION** message, and **USART** at **9600 baud** prints a line such as `VIOLATION dist=XX cm`. Zone thresholds are constants in firmware (tuned on the real breadboard).

---

## Circuit diagram

**[Insert TinkerCAD export (PNG or PDF) here.]**

---

## List of components and topics used

**Components (representative):** Arduino Uno; **LEDs** (traffic lights) **with current-limiting resistors**; **2× push buttons**; **16×2 LCD** with **potentiometer** (contrast); **7-segment display** + **shift registers** + resistors as needed; **ultrasonic sensor**; **buzzer**; **breadboard** and **jumper wires**; **USB cable** for power and serial.

**Topics:** Digital **GPIO**; **Timer1** in CTC mode for a **~1 Hz** tick; **interrupts** (Timer1 compare ISR, pin-change on **push buttons**); **USART** for serial logging; **ultrasonic sensor** ranging; **shift registers** driving **7-segment** display; **LCD** in **4-bit** mode.

---

## Detailed explanation (pseudo-code)

Structured to match the actual `setup()` / `loop()` + `TrafficLight_step()` flow in firmware:

```
SETUP
  GPIO_init()           // LEDs, push buttons (pull-ups), buzzer, ultrasonic trig/echo, shift registers, LCD pins
  USART0_init_9600()
  LCD_init()
  SevenSeg_init()
  Buzzer_init()
  Ultrasound_init()
  PCINT_buttons_init()  // pin-change on pause / reset
  Timer1_init_1Hz_tick()  // Timer1 compare ~1 second
  sei()                   // global interrupts on

  phase ← GREEN
  sec_left ← 10
  running ← TRUE
  armed ← TRUE            // allow next far→near violation
  prev_cm ← large value

MAIN LOOP (repeat forever)
  TrafficLight_step()

TrafficLight_step()  // called every loop iteration
  // Buttons (debounced in software after PCINT edges)
  IF pause_click THEN running ← NOT running
  IF reset_click THEN
      phase ← GREEN, sec_left ← 10, running ← TRUE
      update LEDs, 7-segment, LCD; reset prev_cm / armed

  // Once per second (Timer1 tick consumed here, non-blocking)
  IF one_second_tick THEN
      IF violation_lcd_timer > 0 THEN
          violation_lcd_timer ← violation_lcd_timer − 1
          IF violation_lcd_timer = 0 THEN restore normal LCD text for current phase
      ELSE IF running THEN
          decrement sec_left OR roll to next phase (green→amber→red)
          refresh 7-segment and LCD

  // Only in RED + running
  IF phase = RED AND running THEN
      cm ← Ultrasound_read_cm()
      IF cm = 0 THEN skip   // timeout / bad sample
      IF armed AND prev_cm ≥ FAR_cm AND cm ≤ NEAR_cm THEN
          buzzer; LCD violation lines; USART "VIOLATION dist=…"
          armed ← FALSE     // don’t retrigger until path clears
      IF cm ≥ FAR_cm THEN armed ← TRUE
      prev_cm ← cm
```

---

## Short reflection

The hardest part was **calibrating the ultrasonic far/near thresholds** on real hardware (noise and timing differ from simulation). Keeping **ISRs small** (Timer1 only sets a flag; heavy work in `loop`) avoided blocking the rest of the system. If we extended the project, we might add a **serial calibration mode** to set thresholds without recompiling, or use **Timer1 input capture** for the echo pin instead of a timed poll loop.

---

## Regenerate Word from script (optional)

If `scripts/generate_report_docx.py` is present:

```bash
pip install python-docx
python scripts/generate_report_docx.py
```
