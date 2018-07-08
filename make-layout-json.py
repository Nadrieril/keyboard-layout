#!/usr/bin/env python
# Use with http://www.keyboard-layout-editor.com

import sys, re, json

xkb_line_regex = re.compile("^\s*key\s*(?P<key><\w+>)\s*{\s*\[\s*(\w+),\s*(\w+),\s*(\w+),\s*(\w+)\s*\]\s*};$")
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

with open("symbols.json") as f:
    symbol_dict = json.loads(f.read())

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

