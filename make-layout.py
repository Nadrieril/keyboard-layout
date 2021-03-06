#!/usr/bin/env python
# Use with http://www.keyboard-layout-editor.com

import sys, re, json, yaml

KEYMAP = sys.argv[1]

XKB_TEMPLATE = """
default  partial alphanumeric_keys
xkb_symbols "basic" {{
{symbols[before]}
{symbols[keys]}
}};
"""
finger_colors = {
     0: "#474747",
     1: "#7d1b22",
    -1: "#7d1b22",
     2: "#2d7370",
    -2: "#365c70",
     3: "#1e5422",
    -3: "#1e5422",
     4: "#6e0964",
    -4: "#6e0964",
     5: "#705800",
    -5: "#705800",
}

with open("data/symbol-names.yaml") as f:
    symbol_dict = yaml.safe_load(f.read())
def pretty(x):
    if x in symbol_dict:
        return symbol_dict[x]
    elif len(x) == 1:
        return x
    else:
        # print(x, file=sys.stderr)
        return "" #"•" # "ⁿ̸ₐ"


with open("data/layout-template.json") as f:
    layout_template = f.read()

with open("data/ergodox-layout-template.json") as f:
    ergodox_layout_template = f.read()

layout_order = [
    x
    for row in json.loads(layout_template) if isinstance(row, list)
    for x in row if isinstance(x, str) and len(x) != 0 and x[0] == "<"
]

layout = ergodox_layout_template

with open(KEYMAP) as f:
    keymap = yaml.safe_load(f.read())

keys_to_symbols = {
    k: v
    for (k, v) in zip(layout_order, keymap["symbols"]["keys"])
}

with open("custom.xkb", "w") as f:
    keymap["symbols"]["keys"] = "\n".join(
        "key %s { [ %s ] };" % (k, v)
        for (k, v) in keys_to_symbols.items()
    )
    f.write(XKB_TEMPLATE.format(**keymap))


# fingers_map_name = keymap.get("fingers_map", "default")
# with open("data/finger-maps/{}.json".format(fingers_map_name)) as f:
#     fingers = json.loads(f.read())
#     for key, f in fingers.items():
#         layout = layout.replace("\"%s\"" % (key,),
#                 "{\"c\":\"%s\"},\"%s\"" % (finger_colors[f], key))

for (key, symbs) in keys_to_symbols.items():
    symbs = [ pretty(x.strip()) for x in symbs.split(",") ] + [""]*3
    if symbs[1] == symbs[0].upper():
        symbs[0] = symbs[1]
        symbs[1] = ""
    if symbs[0] == symbs[2]:
        symbs[2] = ""
    symb_str = f'"{symbs[1]}\\n\\n\\n{symbs[2]}\\n\\n\\n\\n\\n\\n{symbs[0]}"'
    if re.match("^[a-zA-Z]$", symbs[0]) \
        or re.match("^<i class.*>$", symbs[0]) \
        or symbs[0] in "⇧⎵" \
        or (len(symbs[0]) == 1 and symbs[1] == "" and symbs[2] == ""):
        size_str = '{"f":6, "fa": [3,0,0,4,0,0,0,0,0,0]}'
    else:
        size_str = '{"f":4}'
    symb_str = f'{size_str}, {symb_str}'
    layout = layout.replace(f'"{key}"', symb_str)


print(layout)

