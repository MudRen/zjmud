//zuixunfeng.c

#include <ansi.h>

inherit ITEM;
inherit F_LIQUID;

void create()
{
	set_name(MAG"��Ѭ��"NOR, ({ "zui xunfeng", "xunfeng" }));
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("long", "һ���������"MAG+"��Ѭ��"NOR"���������ࡣ\n");
		set("unit", "��");
		set("value", 500);
		set("max_liquid", 10);
	}
	set("liquid", ([
		"type": "alcohol",
		"name": MAG"��Ѭ��"NOR"����",
		"remaining": 25,
		"drunk_apply": 7,
	]) );
}
