.PHONY: ergodox
ergodox:
	./layers_to_c.sh ergodox
	cd qmk_firmware && make ergodox_ez:nadrieril:teensy

.PHONY: voyager
voyager:
	./layers_to_c.sh voyager
	cd qmk_firmware && make zsa/voyager:nadrieril:flash

ergodox_from_configurator:
	F=~/Downloads/*ergodox_ez_layout_ergodox_mine.json; cat $$F | jq . > ergodox/layers.json && rm $$F

voyager_from_configurator:
	F=~/Downloads/zsa_voyager_*.json; cat $$F | jq '.keymap = "voyager:default"' > voyager/layers.json && rm $$F
