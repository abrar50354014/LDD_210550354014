cmd_/home/pi/dd-assignments/day_4/kern_charopcl/Module.symvers := sed 's/ko$$/o/' /home/pi/dd-assignments/day_4/kern_charopcl/modules.order | scripts/mod/modpost -m -a   -o /home/pi/dd-assignments/day_4/kern_charopcl/Module.symvers -e -i Module.symvers   -T -