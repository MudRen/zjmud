// qianjinzi.c

#include "herb.h"

void create()
{
	set_name(HIY "ǧ����" NOR, ({ "qian jinzi", "herb_qianjinzi" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "������ҩҩ�ġ�\n");
		set("base_unit", "��");
		set("base_value", 3000);
		set("base_weight", 20);
	}
	setup();
}
