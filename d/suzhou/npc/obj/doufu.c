// huotui.c

inherit ITEM;
inherit F_FOOD;
#include <ansi.h>

void create()
{
	set_name(WHT"�ձ�����"NOR, ({ "riben doufu", "doufu" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ���۰��ͻ����ձ�������\n");
		set("unit", "��");
		set("value", 100);
		set("food_remaining", 10);
		set("food_supply", 25);
		set("material", "meat");
	}
	setup();
}

