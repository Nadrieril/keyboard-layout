.PHONY: ergodox
ergodox:
	./layers_to_c.sh ergodox
	cd qmk_firmware && make ergodox_ez:nadrieril:teensy

.PHONY: voyager
voyager:
	./layers_to_c.sh voyager
	cd qmk_firmware && make zsa/voyager:nadrieril:flash

json_from_configurator:
	F=~/Downloads/*ergodox_ez_layout_ergodox_mine.json; cat $$F | jq . > ergodox_layout/layers.json && rm $$F
