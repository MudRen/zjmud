// fagate.c ϡ�����

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIR "ϡ�����" NOR, ({ "flawless agate" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIR "һ�������˵Ĵ���解�������ۼ���������С�"NOR"\n");
		set("base_value", 100000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"magate");
		set("enchased_need", 3);
		set("magic/type", "fire");
		set("magic/power", 125);
	}
	set_amount(1);
	setup();
}
