// yuanzhi.c

#include "herb.h"

void create()
{
	set_name(HIB "Զ־" NOR, ({ "yuan zhi", "herb_yuanzhi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 3000);
		set("base_weight", 75);
	}
	setup();
}
