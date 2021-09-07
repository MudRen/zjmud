// dahuan.c
// ��++

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(CYN "�󻹵�" NOR, ({ "dahuan dan", "dan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ������ɫ��ҩ�裬����Ч���൱����\n");
		set("base_unit", "��");
		set("base_value", 1500);
		set("base_weight", 60);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "chuanwu"  : 1,
				    "honghua"  : 1,
				    "dangui"   : 1,
				    "chenpi"   : 1,
				    "moyao"    : 1,
				    "shengdi"  : 1,
				    "yjhua"    : 1,
				    "heshouwu" : 1, ]),
			"neili" : 80,
			"jing"  : 30,
			"time"  : 3,
			"min_level" : 80,
			"medical" : 100,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dahuan") < 40)
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

	me->set_temp("last_eat/dahuan", time());

	message_vision(CYN "$N" CYN "С�ĵķ�����" + name() +
		       CYN "��������������������ɫ�����ö��ˡ�"NOR"\n", me);

	me->receive_curing("qi", 350);
	me->receive_heal("qi", 350);

	me->start_busy(1);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}

