// xiefen.c

#include "herb.h"

void create()
{
	set_name(HIM "Ы��" NOR, ({ "xiefen", "herb_xiefen" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 500);
		set("base_weight", 35);
	}
	setup();
}
