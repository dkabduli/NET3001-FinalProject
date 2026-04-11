#!/usr/bin/env python3
"""Regenerate docs/REPORT.docx and docs/CHECKLIST.docx (requires: pip install python-docx)."""

from pathlib import Path

from docx import Document
from docx.shared import Pt
from docx.enum.text import WD_LINE_SPACING

ROOT = Path(__file__).resolve().parents[1]
DOCS = ROOT / "docs"


def add_report():
    doc = Document()
    title = doc.add_heading(
        'Red-light traffic signal with ultrasonic “camera” (NET3001 Final)', 0
    )
    title.runs[0].font.size = Pt(16)

    doc.add_heading("Title", level=1)
    doc.add_paragraph(
        "Red-light traffic signal with ultrasonic zone detection and USART violation logging."
    )

    doc.add_heading("Name of the group members and contributions", level=1)
    doc.add_paragraph(
        "Abdul Rehman (Student 1): Hardware, TinkerCAD, video, serial testing.",
        style="List Bullet",
    )
    doc.add_paragraph(
        "Isaac Abdile (Student 2): Firmware, LCD/7-seg, report.",
        style="List Bullet",
    )

    doc.add_heading("Brief description of your system", level=1)
    doc.add_paragraph(
        "10 s green, 5 s amber, 10 s red. LCD shows phase text; 7-segment countdown via "
        "74HC595. Buttons pause/resume and reset to green at 10. On red, ultrasonic detects "
        "entering near zone; buzzer beeps once; LCD shows VIOLATION; USART prints "
        "VIOLATION dist=XX cm."
    )

    doc.add_heading("Circuit diagram", level=1)
    doc.add_paragraph(
        "Circuit diagram (schematic or TinkerCAD export) as required for submission."
    )

    doc.add_heading("List of components and topics used", level=1)
    doc.add_paragraph(
        "Components: Uno, 3 LEDs + resistors, 2 buttons, LCD + pot, 7-seg + 595 + resistors, "
        "HC-SR04, buzzer, breadboard, wires."
    )
    doc.add_paragraph(
        "Topics: GPIO, timers (Timer1 compare for 1 Hz tick), interrupts (Timer1 compare and "
        "pin-change on buttons), USART, ultrasonic ranging, buzzer output."
    )

    doc.add_heading("Detailed explanation (pseudo-code)", level=1)
    code = (
        "INIT pins, LCD, 7-seg, USART, Timer1 1 Hz, PCINT on buttons.\n"
        "phase=GREEN, seconds=10, running=TRUE.\n"
        "LOOP: handle debounced pause/reset; on 1 s tick update violation message timer or "
        "countdown phase;\n"
        "      if RED and running, read ultrasonic, detect far-to-near while armed, trigger "
        "violation and USART;\n"
        "      re-arm when far again."
    )
    p = doc.add_paragraph(code)
    p.paragraph_format.line_spacing_rule = WD_LINE_SPACING.SINGLE
    p.paragraph_format.left_indent = Pt(12)
    for run in p.runs:
        run.font.name = "Consolas"
        run.font.size = Pt(9)

    doc.add_heading("Short reflection", level=1)
    doc.add_paragraph(
        "Hardest part: tuning zone thresholds and keeping ISRs short. Next time: USART "
        "calibration mode; optional Timer1 input capture on echo."
    )

    out = DOCS / "REPORT.docx"
    doc.save(out)
    print(f"Wrote {out}")


def add_checklist():
    doc = Document()
    doc.add_heading("NET3001 Group 19 — Submission package", 0)

    doc.add_heading("Repository contents", level=1)
    items = [
        "Firmware: PlatformIO project — traffic light logic, GPIO, Timer1, PCINT, USART, LCD, "
        "7-segment (74HC595), HC-SR04, buzzer, LEDs, buttons",
        "Documentation: docs/PIN_LAYOUT.md, readme.txt; written report: REPORT.docx",
        "Member roles: Abdul Rehman (Student 1), Isaac Abdile (Student 2) — see REPORT.docx",
    ]
    for item in items:
        doc.add_paragraph(item, style="List Bullet")

    doc.add_heading("Course deliverables", level=1)
    doc.add_paragraph(
        "Submit written report, video, and code per the instructor’s LMS instructions "
        "(file formats and due dates)."
    )

    out = DOCS / "CHECKLIST.docx"
    doc.save(out)
    print(f"Wrote {out}")


if __name__ == "__main__":
    DOCS.mkdir(parents=True, exist_ok=True)
    add_report()
    add_checklist()
