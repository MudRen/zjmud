// yudai.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("���", ({ "yu dai" }));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ������������������ͷף���Ϊ������\n");
		set("value", 10000);
		set("material", "silk");
	}
	setup();
}
