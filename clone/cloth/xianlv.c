// xianlv.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( HIW "����" NOR, ({ "shoes", "xian lv" }) );
	set_weight(10);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "˫");
		set("icon","03007");
		set("long", "һ˫���˲Ŵ���Ь������������ͨͨ�ġ�\n");
		set("value", 1);
		set("armor_prop/armor", 1);
		set("material", "boots");
	}
	setup();
}
