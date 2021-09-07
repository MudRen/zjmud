// pin.c ����

#include <weapon.h>
#include <ansi.h>

inherit PIN;

void create()
{
	set_name("����", ({ "pin", "zhen" }));
	set_weight(15);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���������·����룬��Ϊ�ֳ���\n");
		set("value", 10);
		set("material", "steel");
		set("wield_msg", YEL "$N��һ��������һ��$n" YEL "��\n");
		set("unwield_msg", YEL "$N������$n" YEL "��\n");
	}

	init_pin(10);
	setup();
}
