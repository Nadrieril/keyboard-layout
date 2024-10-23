.PHONY: ergodox
ergodox:
	./build-ergodox.sh

.PHONY: voyager
voyager:
	cd qmk_firmware && make zsa/voyager:nadrieril:flash

json_from_configurator:
	F=~/Downloads/*ergodox_ez_layout_ergodox_mine.json; cat $$F | jq . > ergodox_layout/layers.json && rm $$F
