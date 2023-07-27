#!/bin/sh

sudo insmod $FRWK_PATH/kernel_module/firemodule.ko
sudo -u firework python3 $FRWK_PATH/moduleManager/moduleManager.py | sudo $FRWK_PATH/Firework