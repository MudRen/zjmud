#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
	set_name( WHT "�Ұ׳���" NOR, ({ "chang shan", "cloth" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ���Ұ�ɫ����ͨ������\n");
		set("value", 50);
		set("material", "cloth");
		set("armor_prop/armor", 2);
	}
	setup();
}

