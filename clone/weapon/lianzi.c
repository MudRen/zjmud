// tielianzi.c
#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name("������", ({ "tie lianzi", "lianzi", "tie" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 300);
		set("base_value", 1);
		set("material", "iron");
		set("long", HIW "��������һ������ȡʤ�İ��������ߵߵġ�"NOR"\n");
		set("wield_msg", HIC "$N" HIC "Ѹ�ٵشӰ��������ͳ�һ"
				 "Щ�����ӣ��������оʹ�������"NOR"\n");
		set("unwield_msg", HIC "$N" HIC "������ʣ�µ������Ӿ���"
				   "�Żذ������С�"NOR"\n");
	}
	set_amount(50);
	init_throwing(25);
	setup();
}
