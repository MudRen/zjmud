// ccrystal.c ˮ����Ƭ

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIM "ˮ����Ƭ" NOR, ({ "chipped crystal" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIM "һƬ��ɫ��ˮ����Ƭ��"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "Ƭ");
		set("can_be_enchased", __DIR__"crystal");
		set("enchased_need", 3);
		set("magic/type", "magic");
		set("magic/power", 30);
	}
	set_amount(1);
	setup();
}
