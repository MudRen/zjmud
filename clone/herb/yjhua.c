// yjhua.c

#include "herb.h"

void create()
{
	set_name(YEL "���" NOR, ({ "yang jinhua", "herb_yjhua" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 400);
		set("base_weight", 20);
	}
	setup();
}
