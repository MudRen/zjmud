// shengdi.c����

#include "herb.h"

void create()
{
	set_name(WHT "����" NOR, ({ "shengdi", "herb_shengdi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 500);
		set("base_weight", 60);
	}
	setup();
}
