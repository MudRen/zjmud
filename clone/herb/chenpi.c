// chenpi.c

#include "herb.h"

void create()
{
	set_name(YEL "��Ƥ" NOR, ({ "chenpi", "herb_chenpi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 10);
		set("base_weight", 20);
	}
	setup();
}
