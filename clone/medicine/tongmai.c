// jiuhua.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(WHT "����ͨ����" NOR, ({"tongmai dan", "dan"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ��ҩ�裬����ȥ��������������"
			    "����һ�㣬ʵ��Ч����������ʥҩ��\n");
		set("base_unit", "��");
		set("base_value", 1800);
		set("base_weight", 85);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "chuanwu"  : 1,
				    "honghua"  : 1,
				    "dangui"   : 1,
				    "chenpi"   : 1,
				    "moyao"    : 1,
				    "shengdi"  : 1,
				    "yjhua"    : 1,
				    "heshouwu" : 1,
				    "renshen"  : 1,
				    "lurong"   : 1, ]),
			"neili" : 150,
			"jing"  : 40,
			"time"  : 5,
			"min_level" : 120,
			"medical" : 150,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/tongmai") < 30)
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

	me->set_temp("last_eat/tongmai", time());

	message_vision(WHT "$N" WHT "��" + name() +
		       WHT "����һ�������˶ǣ�������ɫ�������ö��ˡ�"NOR"\n", me);

	me->receive_curing("qi", 1000);
	me->receive_heal("qi", 1000);

	me->start_busy(1);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
