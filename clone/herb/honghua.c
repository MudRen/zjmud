// honghua.c

#include "herb.h"

void create()
{
	set_name(HIR "�컨" NOR, ({ "honghua", "herb_honghua" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 80);
		set("base_weight", 20);
	}
	setup();
}
