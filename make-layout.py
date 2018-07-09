#!/usr/bin/env python
# Use with http://www.keyboard-layout-editor.com

import sys, re, json, yaml

KEYMAP = sys.argv[1]

XKB_TEMPLATE = """
xkb_keymap {{
    xkb_keycodes  {{ {keycodes} }};
    xkb_types     {{ {types} }};
    xkb_compat    {{ {compat} }};
    xkb_symbols   {{
{symbols[before]}
{symbols[keys]}
{symbols[after]}
    }};
    xkb_geometry  {{ {geometry} }};
}};
"""
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


with open("data/key-names.json") as f:
    layout_order = json.loads(f.read())

with open(KEYMAP) as f:
    keymap = yaml.safe_load(f.read())

keys_to_symbols = {
    k: v
    for (k, v) in zip(layout_order, keymap["symbols"]["keys"])
}


with open("custom.xkb", "w") as f:
    keymap["symbols"]["keys"] = "\n".join(
        "key %s { [], [ %s ] };" % (k, v)
        for (k, v) in keys_to_symbols.items()
    )
    f.write(XKB_TEMPLATE.format(**keymap))


with open("data/layout-template.json") as f:
    layout_template = f.read()

fingers_map_name = keymap.get("fingers_map", "default")
with open("data/finger-maps/{}.json".format(fingers_map_name)) as f:
    fingers = json.loads(f.read())
    for key, f in fingers.items():
        layout_template = layout_template.replace("\"%s\"" % (key,),
                "{\"c\":\"%s\"},\"%s\"" % (finger_colors[f], key))

for (key, symbs) in keys_to_symbols.items():
    symbs = [ pretty(x.strip()) for x in symbs.split(",") ]
    if symbs[1] == symbs[0].upper():
        symbs[0] = symbs[1]
        symbs[1] = ""
    symb_str = "%s\\n\\n\\n%s\\n\\n\\n\\n\\n\\n%s" % (symbs[1], symbs[2], symbs[0])
    layout_template = layout_template.replace(key, symb_str)


print(layout_template)

