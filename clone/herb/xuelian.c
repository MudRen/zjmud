// xuelian.c

#include "herb.h"

void create()
{
	set_name(HIW "ѩ��" NOR, ({ "xuelian", "herb_xuelian" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 30000);
		set("base_weight", 40);
	}
	setup();
}
