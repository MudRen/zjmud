// shancha.c

#include "herb.h"

void create()
{
	set_name(WHT "ɽ�軨" NOR, ({ "shancha", "herb_shancha" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 200);
		set("base_weight", 20);
	}
	setup();
}
