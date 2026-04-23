# Extended Explanation Notes

## 1) What does `static` mean?

In this project, `static` appears mostly in `.cpp` files for variables and helper functions.

- `static` on a **global variable** in a `.cpp` file means the variable is only visible inside that file.  
  Example: `static uint8_t s_sec_left;` in `TrafficLight.cpp`.
- `static` on a **function** in a `.cpp` file means that helper function is private to that file.  
  Example: `static void tick_one_second(void)`.

Why we used it:
- It keeps module internals hidden.
- It prevents naming conflicts across files.
- It makes the public API cleaner (only exposed via `.h` files).

Possible oral answer:
- "We used `static` so internal state and helper functions stay private to each module and cannot be accidentally called or modified from other files."

---

## 2) "loop", "public", and "private" - what are they?

### `loop` (Arduino context)
- `setup()` runs once at startup.
- `loop()` runs forever.
- In our code style, `loop()` usually calls `TrafficLight_step()` repeatedly, and that function handles one slice of logic each pass.

### `public` and `private` (C++ classes)
- `public` members can be accessed from outside the class.
- `private` members can only be accessed from inside the class.

Important: this codebase is mostly **C-style modules** (`.h` + `.cpp`) rather than C++ classes, so we do not heavily use `public/private` keywords.  
Instead, we simulate "private" with `static` in `.cpp`, and "public" with function declarations in `.h`.

Possible oral answer:
- "We did not structure most modules as C++ classes, so public/private is represented by header-exposed functions (public) and static internal helpers (private)."

---

## 3) Why were LCD, USART, and ShiftReg rewritten?

Honest explanation you can give:

- We did not find complete starter code we could confidently build on.
- Embedded systems syntax and register-level flow were not as familiar to us as higher-level languages.
- So we rebuilt these modules from scratch in a clean, modular workflow.
- AI was used as a tutor/guide to explain each hardware step and help us structure it properly, not just to paste random code.

Why this rewrite is meaningful:
- It gave us predictable behavior and full control over timing and hardware registers.
- It made the project easier to debug because each module has a clear API.
- It improved maintainability by separating responsibilities:
  - `LCD` handles display protocol,
  - `USART0` handles serial diagnostics,
  - shift register logic is encapsulated in `SevenSeg`.

---

## 4) What are `uint8_t` and `uint16_t`?

These are fixed-width integer types from `<stdint.h>`:

- `uint8_t` = unsigned 8-bit integer (0 to 255)
- `uint16_t` = unsigned 16-bit integer (0 to 65535)

Why used in embedded:
- Exact bit size matters for register operations and memory usage.
- It avoids compiler/platform ambiguity from plain `int`.

Examples in this project:
- `uint8_t` for flags, countdown values, bit operations.
- `uint16_t` for distance in centimeters and values that may exceed 255.

Possible oral answer:
- "We chose fixed-width types because embedded programming needs predictable memory size and register-safe behavior."

---

## 5) Why `#ifndef` instead of `#pragma once`?

Technical reason:
- Both prevent multiple-inclusion problems.
- `#ifndef` include guards are the classic, fully portable method across older/strict toolchains.

Your contextual answer (as requested):
- We saw `#ifndef` used in videos/materials and got advice from someone working in embedded that it is commonly preferred in low-level environments.
- It is simple and safe, so we kept it.

Possible oral answer:
- "We used include guards because they are portable and standard in embedded projects, and we followed that convention from guidance we received."

---

## 6) TrafficLight comments and architecture

`TrafficLight.cpp` is the orchestrator:
- reads buttons and timer ticks,
- updates phase transitions and LEDs,
- drives LCD/7-segment outputs,
- checks ultrasonic crossing in red phase,
- triggers buzzer + serial logging on violation.

Design style:
- State machine phases (`GREEN -> AMBER -> RED`).
- Small helper functions for each concern.
- `static` internal state to keep control centralized and safe.

---

## 7) ShiftReg module file clarification

There is no separate file named `ShiftReg.cpp` in this project.

Shift-register behavior is implemented inside:
- `src/SevenSeg.cpp`
- `include/SevenSeg.h`

So when asked about "ShiftReg module", refer to the `SevenSeg` module as the shift-register-backed display driver.

