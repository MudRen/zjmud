// icecream-chocolate.c

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(WHT "ѩ��" NOR, ({ "chocolate icecream", "chocolate", "icecream" }) );
	set_weight(50);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "һ֧�ɿ�����ζ��ѩ�⣬����ɿڣ����в����ǳ������׷��֡�"NOR"\n");
		set("value", 1000);
		set("unit", "֧");
		set("food_remaining", 2);
		set("food_supply", 100);
	}
	setup();
}

int query_autoload() { return 1; }
