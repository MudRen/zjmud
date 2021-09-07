// jiuhua.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIW "���Ϸ���ɢ" NOR, ({"liuhe san", "san"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һС����ɫ�ķ�ĩ�������򶨵�Ч����\n");
		set("base_unit", "��");
		set("base_value", 1000);
		set("base_weight", 40);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "chuanwu"  : 1,
				    "xuejie"   : 1,
				    "yjhua"    : 1,
				    "xiongdan" : 1,
				    "shancha"  : 1,
				    "gsliu"    : 1, ]),
			"neili" : 80,
			"jing"  : 35,
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

	if (time() - me->query_temp("last_eat/liuhe") < 10)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();
	if (my["eff_jing"] == my["max_jing"])
	{
		write("�����ھ���״̬�ܺã��������" + name() + "��\n");
		return 1;
	}

	me->set_temp("last_eat/liuhe", time());

	message_vision(HIW "$N" HIW "һ���죬������" + name() +
		       HIW "������ȥ����ö��ˡ�"NOR"\n", me);

	me->receive_curing("jing", 80);
	me->receive_heal("jing", 80);

	me->start_busy(1);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
