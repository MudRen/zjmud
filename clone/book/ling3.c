inherit F_UNIQUE;
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
	set_name(HIW "ʥ����" NOR, ({ "shenghuo ling", "ling" }) );
	set_weight(1000);
	if (clonep())
		destruct(this_object());
	else
	{
		set("unit", "��");
		set("value", 10000);
		set("material", "steel");
		set("no_put", 1);
		set("no_sell", "�����̵ģ�����������ҲֵǮ��");
		set("long", CYN "����һ�����������ĺ��ƣ��ǽ��������"
			    "�ؼ�Ӳ�ޱȣ���͸������\n���������л����"
			    "�ڣ�ʵ��������ӳ�⣬��ɫ��á����Ͽ̵���"
			    "��\n�ٲ�˹�ģ��ƺ�����ѧ�йأ�������£�"
			    "����Ҫ��ϸ�ж�һ�����С�"NOR"\n");
		set("wield_msg", HIR "$N" HIR "��ৡ���һ�����������"
				 "��һƬ����������������С�"NOR"\n");
		set("unwield_msg", HIR "$N" HIR "��ʥ���������䡣\n"
				   NOR);
		set("skill", ([
			"name":	 "shenghuo-ling",
			"exp_required": 1500000,
			"jing_cost":    120,
			"difficulty":   50,
			"max_skill":    179,
			"min_skill":    119,
			"need" : ([ "sanscrit" : 150 ]),
		]) );
	}
	init_sword(80);
	setup();
}


