// cdiamond.c ��ʯ����

#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
	set_name(HIW "��ʯ����" NOR, ({ "chipped diamond" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("long", HIW "һ���������������������С����ʯ������"NOR"\n");
		set("base_value", 20000);
		set("base_weight", 1);
		set("base_unit", "��");
		set("can_be_enchased", "/clone/gift/diamond");
		set("enchased_need", 3);
		set("yuanbao", 10);
		set("magic/type", "lighting");
		set("magic/power", 30);
	}
	set_amount(1);
	setup();
}
