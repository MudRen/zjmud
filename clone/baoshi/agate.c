// agate.c ���

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIR "���" NOR, ({ "agate" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIR "һ�龧Ө��͸�İ���ɫ��觡�"NOR"\n");
		set("base_value", 50000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"fagate");
		set("enchased_need", 3);
		set("magic/type", "fire");
		set("magic/power", 100);
	}
	set_amount(1);
	setup();
}
