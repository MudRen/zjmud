// juhua.c

#include "herb.h"

void create()
{
	set_name(HIY "�ջ�" NOR, ({ "juhua", "herb_juhua" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 60);
		set("base_weight", 20);
	}
	setup();
}
