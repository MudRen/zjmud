// jade.c ���

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIG "���" NOR, ({ "jade" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIG "һ���͸���ε���䡣"NOR"\n");
		set("base_value", 50000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"fjade");
		set("enchased_need", 3);
		set("magic/type", "cold");
		set("magic/power", 60);
	}
	set_amount(1);
	setup();
}
