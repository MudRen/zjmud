#include "herb.h"

void create()
{
	set_name(HIY "�ٻ�" NOR, ({ "teng huang", "herb_tenghuang" }));
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

