// taoxian.c

#include "herb.h"

void create()
{
	set_name(MAG "����" NOR, ({ "tao xian", "herb_taoxian" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 5000);
		set("base_weight", 40);
	}
	setup();
}
