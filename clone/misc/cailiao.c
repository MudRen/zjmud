// cailiao.c

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name("����", ({ "cai liao", "liao" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "���˵�ԭ�ϣ�����ܲ�����Ѽ���⡣\n");
		set("base_unit", "��");
		set("base_value", 50);
		set("base_weight", 80);
	}
	setup();

	set_amount(1);
}
