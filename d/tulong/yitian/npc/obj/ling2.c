inherit F_UNIQUE;
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void init()
{
	add_action("do_du", "yandu");
}

void create()
{
	set_name(CYN "ʥ����" NOR, ({ "shenghuo ling2", "ling2" }) );
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("value", 10000);
		set("material", "steel");
		set("no_sell", "�����̵ģ�����ʲô���⣿");
		set("long", CYN "����һ�����������ĺ��ƣ��ǽ�������ʵؼ�Ӳ�ޱȣ�\n"
				"��͸���������������л�����ڣ�ʵ��������ӳ�⣬��\n"
				"ɫ��á����Ͽ̵��в��ٲ�˹���֡��ƺ�����ѧ�йء�"NOR"\n");
		set("wield_msg", CYN "$N" CYN "��ৡ���һ������������һƬ����������������С�"NOR"\n");
		set("unwield_msg", CYN "$N" CYN "��ʥ���������䡣"NOR"\n");

		set("skill", ([
			"name":		"shenghuo-ling",
			"exp_required":	1200000,	// minimum combat experience required
			"jing_cost":	100,	    // jing cost every time study this
			"difficulty":	47,	     // the base int to learn this skill
			"max_skill":	119,	    // the maximum level you can learn
			"min_skill":	50,	     // the maximum level you can learn
			"need" : ([ "sanscrit" : 150 ]),// need at least 150 lvl san
		]) );
	}
	init_sword(80);
	setup();
}
