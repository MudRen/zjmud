// hafen

#include "herb.h"

void create()
{
	set_name(RED "���" NOR, ({ "ha fen", "herb_hafen" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 5000);
		set("base_weight", 50);
	}
	setup();
}
