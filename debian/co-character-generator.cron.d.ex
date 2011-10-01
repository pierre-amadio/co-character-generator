#
# Regular cron jobs for the co-character-generator package
#
0 4	* * *	root	[ -x /usr/bin/co-character-generator_maintenance ] && /usr/bin/co-character-generator_maintenance
