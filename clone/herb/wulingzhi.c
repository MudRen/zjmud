// wulingzhi.c

#include "herb.h"

void create()
{
	set_name(MAG "����֬" NOR, ({ "wu lingzhi", "herb_wulingzhi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 5000);
		set("base_weight", 100);
	}
	setup();
}
