// potato.c

inherit ITEM;
inherit F_FOOD;
#include <ansi.h>

void create()
{
	set_name(HIY"������ţ��"NOR, ({ "potato" }));
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ���������ڵ�������ţ�⣬ɢ�������˵�������\n");
		set("unit", "��");
		set("value", 100);
		set("food_remaining", 20);
		set("food_supply", 35);
		set("material", "meat");
	}
	setup();
}

