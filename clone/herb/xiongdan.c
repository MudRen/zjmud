// xiongdan.c

#include "herb.h"

void create()
{
	set_name(HIR "�ܵ�" NOR, ({ "xiongdan", "herb_xiongdan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 10000);
		set("base_weight", 70);
	}
	setup();
}
