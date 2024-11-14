LIST_EVENTS=list_events.c
MAX_EVENT_VALUE=111

cat <<EOF > $LIST_EVENTS
#include <string.h>
#include <linux/input-event-codes.h>

#define MIN_EVENT_VALUE 1
#define MAX_EVENT_VALUE $MAX_EVENT_VALUE

int get_event_value_from_name(const char* event_name)
{
  /* If it's a valid digit, use it */
  int int_value = atoi(event_name);
  if(int_value != 0)
    if(int_value >= MIN_EVENT_VALUE && int_value <= MAX_EVENT_VALUE)
    {
      return int_value;
    }
    else
      return 0;

EOF

egrep '#define KEY_[A-Z0-9]{1,}[[:space:]]+[0-9]{1,3}' /usr/include/linux/input-event-codes.h \
  | egrep -v '0x[0-9a-f]{1,}' \
  | awk -v max_val=$MAX_EVENT_VALUE '($3 > 0) && ($3 <= max_val)' \
  | while read line ; do
	#echo $line
	echo $line | sed -E "s/\#define (KEY_[A-Z0-9_]+) ([0-9]+)/\tif (strcmp(event_name, \"\1\") == 0) return \1 ;/" >> $LIST_EVENTS
done

cat <<EOF >> $LIST_EVENTS
	return -1;
}
EOF