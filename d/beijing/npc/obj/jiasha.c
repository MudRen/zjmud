#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( HIR "��ɫ����" NOR, ({ "jia sha", "cloth" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ�����ɫ�����ġ�\n");
		set("value", 1000);
		set("material", "cloth");
		set("armor_prop/armor", 5);
	}
	setup();
}

