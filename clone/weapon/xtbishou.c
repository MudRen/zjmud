#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(CYN "����" WHT "ذ��" NOR,  ({ "bi shou", "sword", "jian" }));

	set_weight(12000);

	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("no_sell", "����ý����Ը����Űɡ�\n");
		set("value", 100000);
		set("icon","05040");
		set("material", "xuantie");
		set("wield_msg", HIR "$N" HIR "���һ���������"
				 "ذ���������У�ֻ�е�һ�������������"NOR"\n");
		set("unwield_msg", HIR "$N" HIR "�����е�ذ�ײ��ѥ�С�"NOR"\n");
		set("stable", 100);
	}

	init_sword(200);

	setup();
	move("/d/beijing/aofu_mishi");
}
