// jiuhua.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(YEL "��Ԫ��ɢ" NOR, ({"zhending san", "san"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ������ɫ�ķ�ĩ�������������Ч����\n");
		set("base_unit", "��");
		set("base_value", 1900);
		set("base_weight", 60);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "chuanwu"  : 1,
				    "xuejie"   : 1,
				    "yjhua"    : 1,
				    "xiongdan" : 1,
				    "shancha"  : 1,
				    "gsliu"    : 1,
				    "zzfen"    : 1,
				    "xuelian"  : 1,
				    "lurong"   : 1, ]),
			"neili" : 150,
			"jing"  : 60,
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

	if (time() - me->query_temp("last_eat/zhending") < 10)
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

	me->set_temp("last_eat/zhending", time());

	message_vision(YEL "$N" YEL "һ���죬������" + name() +
		       YEL "������ȥ����ö��ˡ�"NOR"\n", me);

	me->receive_curing("jing", 300);
	me->receive_heal("jing", 300);

	me->start_busy(1);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
