#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(HIG "���ɱ�" NOR, ({"mint ice","mint","ice"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",HIG "����һ�����Ƶı��ɱ������������˲������Ρ�"NOR"\n");
		set("unit", "��");
		set("value", 1000);
		set("max_liquid", 5);
	}

	set("liquid", ([
		"type": "water",
		 "name":HIG "���ɱ�" NOR,
		"remaining": 10,
		"supply": 20,
		"drunk_apply": 5,
	]));
}
