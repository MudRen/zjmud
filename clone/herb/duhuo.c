// duhuo.c

#include "herb.h"

void create()
{
	set_name(HIB "����" NOR, ({ "du huo", "herb_duhuo" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 4000);
		set("base_weight", 50);
	}
	setup();
}
