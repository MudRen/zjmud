// diamond.c ��ʯ

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIW "��ͨ��ʯ" NOR, ({ "diamond" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "һ��������������ʯ��"NOR"\n");
		set("base_value", 50000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"fdiamond");
		set("enchased_need", 3);
		set("magic/type", "lighting");
		set("magic/power", 100);
	}
	set_amount(1);
	setup();
}
