#include "herb.h"

void create()
{
	set_name(HIW "����" NOR, ({ "yan wo", "herb_yanwo" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 50000);
		set("base_weight", 35);
	}
	setup();
}

