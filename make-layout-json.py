#!/usr/bin/env python
# Use with http://www.keyboard-layout-editor.com

import sys, re, json

xkb_line_regex = re.compile("^\s*key\s*(?P<key><\w+>)\s*{\s*\[\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+)\s*\]\s*};$")
symbol_dict = {
    "Eurosign": "€",
    "ae": "æ",
    "agrave": "à",
    "ampersand": "&",
    "apostrophe": "'",
    "asciicircum": "^",
    "asciitilde": "~",
    "asterisk": "*",
    "at": "@",
    "backslash": "\\\\",
    "bar": "|",
    "braceleft": "{",
    "braceright": "}",
    "bracketleft": "[",
    "bracketleft": "[",
    "bracketright": "]",
    "bracketright": "]",
    "ccedilla": "ç",
    "colon": ":",
    "comma": ",",
    "dead_circumflex": "^",
    "dead_diaeresis": "¨",
    "dead_grave": "`",
    "dead_tilde": "~",
    "degree": "°",
    "dollar": "$",
    "downarrow": "↓",
    "eacute": "é",
    "egrave": "è",
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
    "paragraph": "¶",
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
    "quotedbl": "\\\"",
    "rightarrow": "→",
    "section": "§",
    "semicolon": ";",
    "slash": "/",
    "sterling": "£",
    "twosuperior": "²",
    "ugrave": "ù",
    "underscore": "_",
    "uparrow": "↑",
}
finger_colors = {
     0: "#474747",
     1: "#7d1b22",
     2: "#2d7370",
    -2: "#365c70",
     3: "#1e5422",
    -3: "#1e5422",
     4: "#6e0964",
    -4: "#6e0964",
     5: "#705800",
    -5: "#705800",
}

def pretty(x):
    if x in symbol_dict:
        return symbol_dict[x]
    elif len(x) == 1:
        return x
    else:
        # print(x, file=sys.stderr)
        return "" #"•" # "ⁿ̸ₐ"

with open("keyboard-layout.json") as f:
    layout = f.read()

with open("fingers.json") as f:
    fingers = json.loads(f.read())
    for key, f in fingers.items():
        layout = layout.replace("\"%s\"" % (key,), "{\"c\":\"%s\"},\"%s\"" %
                (finger_colors[f], key))

with open("custom.xkb") as f:
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
        layout = layout.replace(key, symb_str)

print(layout)

