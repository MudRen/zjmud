// jinhulu.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("���«", ({ "jin hulu", "hulu" }));
	set_weight(800);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "ֻ");
		set("long", "����һ���ƽ���Ƶĺ�«�������ġ�\n");
		set("value", 50000);
		set("material", "gold");
	}
	setup();
}
