// yuhulu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("���«", ({ "yu hulu", "hulu" }));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һ�������̵ĺ�«�����羫�¡�\n");
		set("value", 8000);
		set("material", "jade");
	}
	setup();
}
