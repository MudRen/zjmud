// guiwei.c

#include "herb.h"

void create()
{
	set_name(WHT "��β" NOR, ({ "gui wei", "herb_guiwei" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 3000);
		set("base_weight", 50);
	}
	setup();
}
