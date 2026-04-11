NET3001 Final Project — Group 19
Red-light traffic signal with ultrasonic sensor zone detection + USART logging

Members
-------
Student 1 — Abdul Rehman
  Hardware build, TinkerCAD schematic, demo video, serial monitor testing.

Student 2 — Isaac Abdile
  Firmware (this repo), LCD + 7-segment via shift registers, written report.

Build / upload
--------------
PlatformIO, Arduino Uno. From this folder:
  pio run -t upload
Serial monitor: 9600 baud (see platformio.ini).

Report (submission)
-------------------
docs/REPORT.md      — full text + pseudo-code (copy into Word if needed)
docs/REPORT.docx    — Word source
docs/Report(NET3001 Final).pdf — PDF for hand-in
docs/PIN_LAYOUT.md  — pin table vs include/PinMap.h

Regenerate REPORT.docx: pip install python-docx && python scripts/generate_report_docx.py

Demo video: per LMS (usually not in this repo).
