#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(HIW "����" NOR, ({ "soup" }));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ�������˱ǵ��������\n");
		set("unit", "ֻ");
		set("value", 10);
		set("max_liquid", 4);
	}

	set("liquid", ([
		"type": "water",
		"name": "����",
		"remaining": 6,
		"drunk_supply": 30,
	]));
}
