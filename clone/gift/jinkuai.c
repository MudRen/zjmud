// jinkuai.c ���

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL "���" NOR, ({ "jin kuai", "jin", "kuai" }));
	set_weight(2000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���ƳγεĽ�顣\n");
		set("value", 2000000);
		set("suit_point",30);
		set("unit", "��");
	}
}

