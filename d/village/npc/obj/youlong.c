// youlong.c

#include <weapon.h>

inherit SWORD;

void create()
{
	set_name("������", ({ "youlong sword", "youlong", "sword" }) );
	set_weight(8000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long",
"���ǰѿ���������ͨ�ĳ���������ϸһ�����������м���ϸ����˸������\n");
		set("value", 2400);
		 set("icon","05069");
		set("material", "steel");
		set("wield_msg", 
"ֻ������쬡���һ����$N�������Ѿ�����һ�Ѻ�������ı�������$n��\n");
		set("unequip_msg", "$N�����е�$n��������Ľ��ʡ�\n");
		set("stable", 75);
	}
	init_sword(80);
	setup();
}
