#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIG "���" NOR, ({ "da cong", "cong","da" }) );
	set_weight(100);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", "һ�����ʵĴ�С�\n");
		set("unit", "��");
		set("value", 2);
		set("food_remaining", 1);
		set("food_supply", 5);
	}
	setup();
}

