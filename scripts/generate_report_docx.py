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
        "(Insert TinkerCAD export PNG/PDF here.)"
    ).italic = True

    doc.add_heading("List of components and topics used", level=1)
    doc.add_paragraph(
        "Components: Uno, 3 LEDs + resistors, 2 buttons, LCD + pot, 7-seg + 595 + resistors, "
        "HC-SR04, buzzer, breadboard, wires."
    )
    doc.add_paragraph(
        "Topics: GPIO, Timers (Timer1 tick), Interrupts (Timer1 compare + PCINT), optional "
        "USART, optional ultrasonic + buzzer."
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
    doc.add_heading("NET3001 Group 19 — Project checklist", 0)

    doc.add_heading("Completed", level=1)
    done = [
        "Firmware: PlatformIO project, traffic light logic, GPIO / Timer1 / PCINT / USART",
        "Peripherals: LCD (parallel), 7-segment via 74HC595, HC-SR04, buzzer, LEDs, buttons",
        "Documentation: docs/PIN_LAYOUT.md aligned with include/PinMap.h",
        "readme.txt: build, upload, serial (9600 baud)",
        "Repository on GitHub with collaborator history",
        "Written report drafted (this pack: REPORT.docx)",
        "Member roles named (Abdul Rehman, Isaac Abdile)",
    ]
    for item in done:
        doc.add_paragraph(item, style="List Bullet")

    doc.add_heading("Remaining / to finalize", level=1)
    todo = [
        "Insert circuit diagram: export PNG or PDF from TinkerCAD into REPORT.docx (replace placeholder)",
        "Demo video: record, edit, and submit per instructor instructions",
        "Hardware: confirm breadboard matches PIN_LAYOUT; test pause, reset, phases, violation",
        "Serial: verify VIOLATION dist=… lines at 9600 baud on real Uno",
        "Tuning: adjust ultrasonic zone thresholds in firmware if real distances differ from simulation",
        "Submission: export or submit REPORT.docx (or PDF) per course portal; attach video link if required",
        "Final pass: spelling, course cover page / group number if required",
    ]
    for item in todo:
        doc.add_paragraph(item, style="List Bullet")

    doc.add_paragraph()
    note = doc.add_paragraph(
        "Tip: keep this checklist in sync with your instructor’s rubric and due dates."
    )
    note.runs[0].italic = True

    out = DOCS / "CHECKLIST.docx"
    doc.save(out)
    print(f"Wrote {out}")


if __name__ == "__main__":
    DOCS.mkdir(parents=True, exist_ok=True)
    add_report()
    add_checklist()
