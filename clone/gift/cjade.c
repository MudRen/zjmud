// cjade.c ����Ƭ

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIG "����Ƭ" NOR, ({ "chipped jade" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIG "һƬ��Ө��͸���������Ƭ��"NOR"\n");
		set("base_value", 20000);
		set("base_unit", "Ƭ");
		set("base_weight", 1);
		set("can_be_enchased", __DIR__"jade");
		set("enchased_need", 3);
		set("magic/type", "cold");
		set("magic/power", 30);
	}
	set_amount(1);
	setup();
}
