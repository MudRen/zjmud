#include <ansi.h>
inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(HIY "��֭��" NOR, ({"fruit water","fruit"}));
	set_weight(700);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long",HIG "����һ����������֭�ƳɵĹ�֭�������øպã����������˼��ˡ�"NOR"\n");
		set("unit", "��");
		set("value", 100);
		set("max_liquid", 5);
	}

	set("liquid", ([
		"type": "water",
		 "name":HIY "��֭��" NOR,
		"remaining": 5,
		"supply": 10,
		"drunk_apply": 3,
	]));
}
