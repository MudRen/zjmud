// fdiamond.c ������ʯ

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIW "������ʯ" NOR, ({ "flawless diamond" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "һ�ž��������ľ�����ʯ�������쳣��"NOR"\n");
		set("base_value", 100000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", __DIR__"mdiamond");
		set("enchased_need", 3);
		set("magic/type", "lighting");
		set("magic/power", 125);
	}
	set_amount(1);
	setup();
}
