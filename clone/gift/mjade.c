// mjade.c ��֮���

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIG "��֮���" NOR, ({ "magic jade" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIG "һ�Ż���������Ĺ�ʵ���䣬�����Բ�ͬѰ���ĸо���"NOR"\n");
		set("base_value", 200000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"god_eyes");
		set("enchased_need", ({
			(["id":"magic crystal","name":"��֮ˮ��"]),
			(["id":"magic diamond","name":"��֮��ʯ"]),
			(["id":"magic agate","name":"��֮���"]),
		}));
		set("magic/type", "cold");
		set("magic/power", 150);
	}
	set_amount(1);
	setup();
}
