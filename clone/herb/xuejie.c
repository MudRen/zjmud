// xuejie.c

#include "herb.h"

void create()
{
	set_name(RED "Ѫ��" NOR, ({ "xuejie", "herb_xuejie" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 200);
		set("base_weight", 40);
	}
	setup();
}
