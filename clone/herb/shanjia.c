// shanjia

#include "herb.h"

void create()
{
	set_name(GRN "ɽ��" NOR, ({ "shan jia", "herb_shanjia" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "Ƭ");
		set("base_value", 2000);
		set("base_weight", 60);
	}
	setup();
}
