// fuzi.c

#include "herb.h"

void create()
{
	set_name(WHT "����" NOR, ({ "fu zi", "herb_fuzi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 1000);
		set("base_weight", 20);
	}
	setup();
}
