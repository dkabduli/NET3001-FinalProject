# NET3001 Group 19 — Project checklist

Edit this file as you go; regenerate Word copies with `python3 scripts/generate_report_docx.py` if you change structure (or update `docs/CHECKLIST.docx` by hand).

## Completed

- [x] Firmware: PlatformIO project, traffic light logic, GPIO / Timer1 / PCINT / USART
- [x] Peripherals in code: LCD, 7-segment via 74HC595, HC-SR04, buzzer, LEDs, buttons
- [x] `docs/PIN_LAYOUT.md` aligned with `include/PinMap.h`
- [x] `readme.txt`: build, upload, serial (9600 baud)
- [x] Repository on GitHub (collaborators)
- [x] Written report in **`docs/REPORT.docx`** (Word)
- [x] Member roles named (Abdul Rehman, Isaac Abdile)

## Remaining / to finalize

- [ ] Insert circuit diagram: TinkerCAD export (PNG/PDF) into **`docs/REPORT.docx`** (replace placeholder)
- [ ] Demo video: record and submit per instructor instructions
- [ ] Hardware: breadboard matches `PIN_LAYOUT`; test pause, reset, all phases, violation
- [ ] Serial: verify `VIOLATION dist=…` at **9600** baud on real Uno
- [ ] Tuning: adjust ultrasonic zone thresholds in firmware if real hardware differs from sim
- [ ] Course submission: upload **`REPORT.docx`** (or PDF if required) + video link as specified
- [ ] Final pass: spelling, cover page / group number if the course requires it

---

*Word versions: `docs/REPORT.docx`, `docs/CHECKLIST.docx`*
