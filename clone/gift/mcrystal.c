// mcrystal.c ��֮ˮ��

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "��֮ˮ��" NOR, ({ "magic crystal" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "һ����˸�������â�ķ�ɫˮ�������˸е�һ������ļ¡�"NOR"\n");
		set("base_value", 200000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"god_eyes");
		set("enchased_need", ({
			(["id":"magic agate","name":"��֮���"]),
			(["id":"magic diamond","name":"��֮��ʯ"]),
			(["id":"magic jade","name":"��֮���"]), 
		}));
		set("magic/type", "magic");
		set("magic/power", 150);
	}
	set_amount(1);
	setup();
}
