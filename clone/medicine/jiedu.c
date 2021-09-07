// jiedu.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIY "ţ�ƽⶾ��" NOR, ({"jiedu wan", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ����ɫ��ҩ�裬��ţ�Ƹ���ԭ���Ƴɣ����в���ĽⶾЧ����\n");
		set("base_unit", "��");
		set("base_value", 1400);
		set("base_weight", 55);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "yjhua"  : 1,
				    "juhua"  : 1,
				    "xuejie" : 1,
				    "chenpi" : 1,
				    "xiefen" : 1,
				    "shengdi": 1,
				    "lanhua" : 1,
				    "gsliu"  : 1, ]),
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
	if (time() - me->query_temp("last_eat/jiedu") < 20)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	if (! me->query_skill_mapped("force"))
	{
		write("��û�м����κ��ڹ�����ô����ҩ������������\n");
		return 1;
	}

	me->set_temp("last_eat/jiedu", time());

	message_vision(HIY "$N" HIY "��������һ������������" + name() +
		       HIY "����ϥ���£���ʼ�˹��ƶ���"NOR"\n", me);

	// �˹�����
	me->add_temp("apply/dispel_poison", 100);
	SKILL_D("force")->exert_function(me, "dispel");
	me->add_temp("apply/dispel_poison", -100);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
