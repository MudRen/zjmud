#include "herb.h"

void create()
{
	set_name(HIY "���" NOR, ({ "ma huang", "herb_mahuang" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 1000);
		set("base_weight", 50);
	}
	setup();
}

