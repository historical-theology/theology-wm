#/bin/sh
# requires acpi to be installed

status () { 

	echo -n "Corey's ThinkPad | Battery: $(acpi | awk '{print $4}' | sed s/,//) | $(date '+%Y-%m-%d %H:%M:%S')"
}

while :; do
	
	xsetroot -name "$(status)"
	sleep 1

done