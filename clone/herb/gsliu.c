// gsliu.c

#include "herb.h"

void create()
{
	set_name(CYN "��ʯ��" NOR, ({ "gan shiliu", "herb_gsliu" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "Ƭ");
		set("base_value", 200);
		set("base_weight", 75);
	}
	setup();
}
