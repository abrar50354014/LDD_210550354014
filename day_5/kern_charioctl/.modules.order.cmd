cmd_/home/pi/dd-assignments/day_5/kern_charioctl/modules.order := {   echo /home/pi/dd-assignments/day_5/kern_charioctl/my_ioctl.ko;   echo /home/pi/dd-assignments/day_5/kern_charioctl/kern_add.ko;   echo /home/pi/dd-assignments/day_5/kern_charioctl/kern_sub.ko;   echo /home/pi/dd-assignments/day_5/kern_charioctl/kern_mul.ko;   echo /home/pi/dd-assignments/day_5/kern_charioctl/kern_div.ko; :; } | awk '!x[$$0]++' - > /home/pi/dd-assignments/day_5/kern_charioctl/modules.order