// spin.c ����

#include <weapon.h>
#include <ansi.h>

inherit PIN;

void create()
{
	set_name(HIW "����" NOR, ({ "pin", "silver pin", "yin zhen", "zhen" }));
	set_weight(24);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "���Ǹ����˼Ҳ�ʹ�õ����롣\n");
		set("value", 120);
		set("material", "silver");
		set("wield_msg", YEL "$N��һ��������һ��$n" YEL "��\n");
		set("unwield_msg", YEL "$N������$n" YEL "��\n");
	}

	init_pin(8);
	setup();
}
