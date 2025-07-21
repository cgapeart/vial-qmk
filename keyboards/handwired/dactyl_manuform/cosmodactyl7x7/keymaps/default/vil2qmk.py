#!/usr/bin/env python3
"""
Convert a Vial .vil file to QMK keymap.json.
Usage:
    python vil2keymap.py <input.vil> [output.json]

If no output filename is given, keymap.json is written in the
current directory.
Generated using chatgpt - use at your own risk.
"""

import json
import sys
from pathlib import Path

# ----------------------------------
# Vial → QMK key‑code translation
# ----------------------------------
CODE_MAP: dict[str, str] = {
    # Examples – adjust to your needs
    "KC_LCTRL": "KC_LCTL",
    "KC_RCTRL": "KC_RCTL",
    "KC_RSHIFT": "KC_RSFT",
    "KC_LSHIFT": "KC_LSFT",
    "0x7e40": "QK_USER_0",
    "0x7e41": "QK_USER_1",
    "0x7e42": "QK_USER_2",
    "0x7e43": "QK_USER_3",
    "0x7e44": "QK_USER_4",
    "0x7e45": "QK_USER_5",
    "0x7e46": "QK_USER_6",
    "0x7e47": "QK_USER_7",
    "0x7e48": "QK_USER_8",
    "0x7e49": "QK_USER_9",
    "0x7e4a": "QK_USER_10",
    "0x7e4b": "QK_USER_11",
    "0x7e4c": "QK_USER_12",
    "0x7e4d": "QK_USER_13",
    "0x7e4e": "QK_USER_14",
    "0x7e4f": "QK_USER_15",
    "USER0": "QK_USER_0",
    "USER1": "QK_USER_1",
    "USER2": "QK_USER_2",
    "USER3": "QK_USER_3",
    "USER4": "QK_USER_4",
    "USER5": "QK_USER_5",
    "USER6": "QK_USER_6",
    "USER7": "QK_USER_7",
    "USER8": "QK_USER_8",
    "USER9": "QK_USER_9",
    "USER10": "QK_USER_10",
    "USER11": "QK_USER_11",
    "USER12": "QK_USER_12",
    "USER13": "QK_USER_13",
    "USER14": "QK_USER_14",
    "USER15": "QK_USER_15",
    "KC_RBRACKET" : "KC_RBRC",
    "KC_LBRACKET" : "KC_LBRC",
    "KC_BSLASH": "KC_BACKSLASH",
    "KC_SCOLON": "KC_SEMICOLON",
    "KC_PGDOWN": "KC_PGDN",
    "KC_BSPACE": "KC_BACKSPACE"
}


def vil_to_qmk(vil_data: dict) -> dict:
    """Return a QMK‑style dict from a Vial .vil dict."""
    layers_out = []
    for layer in vil_data["layout"]:
        flat = []
        for row in layer:
            for k in row:
                if(k != -1):
                    flat.append(CODE_MAP.get(k,k))
        layers_out.append(flat)

    return {
        # Fall back to sensible defaults if fields are missing
        "keyboard": vil_data.get("keyboard", "cosmodactyl7x7"),
        "keymap": vil_data.get("keymap", "default"),
        "layout": vil_data.get("layout_name", "LAYOUT_mine"),
        "layers": layers_out,
        "author": vil_data.get("author", "auto‑converted"),
    }


def main() -> None:
    if len(sys.argv) < 2:
        sys.exit("Usage: vil2keymap.py <input.vil> [output.json]")

    in_path = Path(sys.argv[1])
    out_path = Path(sys.argv[2]) if len(sys.argv) > 2 else Path("keymap.json")

    try:
        vil_data = json.loads(in_path.read_text(encoding="utf-8"))
    except Exception as exc:
        sys.exit(f"Error reading {in_path}: {exc}")

    qmk_json = vil_to_qmk(vil_data)
    out_path.write_text(json.dumps(qmk_json, indent=2) + "\n", encoding="utf-8")
    print(f"Wrote {out_path} ({len(qmk_json['layers'])} layers)")


if __name__ == "__main__":
    main()
