// shedan.c

#include "herb.h"

void create()
{
	set_name(HIG "�ߵ�" NOR, ({ "shedan", "herb_shedan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 6000);
		set("base_weight", 30);
	}
	setup();
}

