.PHONY: ergodox
ergodox:
	./layers_to_c.sh ergodox
	cd qmk_firmware && make ergodox_ez:nadrieril:teensy

.PHONY: voyager
voyager:
	./layers_to_c.sh voyager
	cd qmk_firmware && make zsa/voyager:nadrieril:flash

ergodox_from_configurator:
	F=~/Downloads/*ergodox_ez_layout_ergodox_mine.json; cat $$F | jq . > layout/ergodox_keymap.json && rm $$F

voyager_from_configurator:
	F=~/Downloads/zsa_voyager_*.json; cat $$F | jq '.keymap = "voyager:default"' > layout/voyager_keymap.json && rm $$F

qmk_symlinks:
	mkdir -p qmk_firmware/keyboards/ergodox_ez/keymaps/nadrieril
	ln -sf $$PWD/layout/ergodox_config.h qmk_firmware/keyboards/ergodox_ez/keymaps/nadrieril/config.h
	ln -sf $$PWD/layout/ergodox_keymap.c qmk_firmware/keyboards/ergodox_ez/keymaps/nadrieril/keymap.c
	ln -sf $$PWD/layout/ergodox_rules.mk qmk_firmware/keyboards/ergodox_ez/keymaps/nadrieril/rules.mk
	ln -sf $$PWD/layout/common.h qmk_firmware/keyboards/ergodox_ez/keymaps/nadrieril/common.h
	mkdir -p qmk_firmware/keyboards/zsa/voyager/keymaps/nadrieril
	ln -sf $$PWD/layout/voyager_config.h qmk_firmware/keyboards/zsa/voyager/keymaps/nadrieril/config.h
	ln -sf $$PWD/layout/voyager_keymap.c qmk_firmware/keyboards/zsa/voyager/keymaps/nadrieril/keymap.c
	ln -sf $$PWD/layout/voyager_rules.mk qmk_firmware/keyboards/zsa/voyager/keymaps/nadrieril/rules.mk
	ln -sf $$PWD/layout/common.h qmk_firmware/keyboards/zsa/voyager/keymaps/nadrieril/common.h
