// fangfeng.c

#include "herb.h"

void create()
{
	set_name(HIB "����" NOR, ({ "fang feng", "herb_fangfeng" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "Ƭ");
		set("base_value", 5000);
		set("base_weight", 40);
	}
	setup();
}
