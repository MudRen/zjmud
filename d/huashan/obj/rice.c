// rice.c

inherit ITEM;
inherit F_FOOD;
#include <ansi.h>

void create()
{
	set_name(YEL"���׷�"NOR, ({ "rice", "mi fan" }) );
	set_weight(300);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��������Ļ��׷���\n");
		set("unit", "��");
		set("value", 80);
		set("food_remaining", 4);
		set("food_supply", 30);
		set("material", "rice");
	}
	setup();
}

