// moyao.c

#include "herb.h"

void create()
{
	set_name(WHT "ûҩ" NOR, ({ "moyao", "herb_moyao" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 300);
		set("base_weight", 50);
	}
	setup();
}
