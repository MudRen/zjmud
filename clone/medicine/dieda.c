// dieda.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(CYN "����������" NOR, ({"dieda gao", "gao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�齺״�Ķ���������Ч���Ƚ�ҩҪ��һЩ��\n");
		set("base_unit", "��");
		set("base_value", 1200);
		set("base_weight", 50);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "chuanwu"  : 1,
				    "honghua"  : 1,
				    "dangui"   : 1,
				    "chenpi"   : 1,
				    "moyao"    : 1,
				    "shengdi"  : 1, ]),
			"neili" : 70,
			"jing"  : 25,
			"time"  : 1,
			"min_level" : 50,
			"medical" : 80,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dieda") < 10)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();
	if (my["eff_qi"] == my["max_qi"])
	{
		write("�����ڲ�û�����ˣ����ط���" + name() + "��\n");
		return 1;
	}

	me->set_temp("last_eat/dieda", time());

	message_vision(CYN "$N" CYN "�ſ��죬�͵�������" + name() +
		       CYN "������ĺ���һ����"NOR"\n", me);

	me->receive_curing("qi", 100);
	me->receive_heal("qi", 100);

	me->start_busy(1);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
