// dahuang.c

#include "herb.h"

void create()
{
	set_name(HIY "���" NOR, ({ "da huang", "herb_dahuang" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 7000);
		set("base_weight", 100);
	}
	setup();
}
