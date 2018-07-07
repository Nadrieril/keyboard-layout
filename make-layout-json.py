#!/usr/bin/env python

import re

xkb_line_regex = re.compile("^\s*key\s*(?P<key><\w+>)\s*{\s*\[\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+)\s*\]\s*};$")
symbol_dict = {
    "ae": "æ",
    "ampersand": "&",
    "apostrophe": "'",
    "asciicircum": "^",
    "asciitilde": "~",
    "asterisk": "*",
    "at": "@",
    "bar": "|",
    "backslash": "\\\\",
    "braceleft": "{",
    "braceright": "}",
    "bracketleft": "[",
    "bracketleft": "[",
    "bracketright": "]",
    "bracketright": "]",
    "colon": ":",
    "comma": ",",
    "dead_circumflex": "^",
    "dead_grave": "`",
    "dead_tilde": "~",
    "dollar": "$",
    "downarrow": "↓",
    "equal": "=",
    "exclam": "!",
    "grave": "`",
    "greater": ">",
    "leftarrow": "←",
    "less": "<",
    "minus": "-",
    "mu": "µ",
    "notsign": "¬",
    "numbersign": "#",
    "paragraph": "§",
    "parenleft": "(",
    "parenleft": "(",
    "parenright": ")",
    "parenright": ")",
    "percent": "%",
    "period": ".",
    "periodcentered": "·",
    "plus": "+",
    "question": "?",
    "quotedbl": "\\\"",
    "rightarrow": "→",
    "semicolon": ";",
    "slash": "/",
    "twosuperior": "²",
    "underscore": "_",
    "uparrow": "↑",
}
def pretty(x):
    x = symbol_dict.get(x, x)
    return x if len(x) == 1 else ""

with open("keyboard-layout.json") as f:
    json = f.read()

with open("latin.xkb") as f:
    for row in f:
        if row == "": continue
        r = re.match(xkb_line_regex, row)
        if r is None: continue
        key = r.group("key")
        symbs = [ pretty(r.group(i)) for i in range(2, 5) ]
        if symbs[1] == symbs[0].upper():
            symbs[0] = symbs[1]
            symbs[1] = ""
        symb_str = "%s\\n\\n\\n%s\\n\\n\\n\\n\\n\\n%s" % (symbs[1], symbs[2], symbs[0])
        json = json.replace(key, symb_str)

print(json)

