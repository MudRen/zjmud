#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( MAG "����" NOR, ({ "diao qiu", "cloth" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ������Ƥ����������ϸ�µ�Ƥ���ף���������\n");
		set("value", 1000);
		set("material", "cloth");
		set("armor_prop/armor", 20);
	}
	setup();
}

