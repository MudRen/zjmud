// lingzhi.c

#include "herb.h"

void create()
{
	set_name(HIG "��֥" NOR, ({ "lingzhi", "herb_lingzhi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 20000);
		set("base_weight", 70);
	}
	setup();
}
