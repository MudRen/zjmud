// shenglg.c

#include "herb.h"

void create()
{
	set_name(CYN "������" NOR, ({ "shenglong gu", "herb_slg" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 4000);
		set("base_weight", 120);
	}
	setup();
}
