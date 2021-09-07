// tianxin.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIW "���Ľⶾ��" NOR, ({"tianxin dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ����ɫ��ҩ�裬�����൱�õĽⶾЧ����\n");
		set("base_unit", "��");
		set("base_value", 1700);
		set("base_weight", 50);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "yjhua"  : 1,
				    "duhuo"  : 1,
				    "chuanwu": 1,
				    "chenpi" : 1,
				    "fuzi"   : 1,
				    "shengdi": 1,
				    "moyao"  : 1,
				    "gsliu"  : 1, ]),
			"neili" : 100,
			"jing"  : 35,
			"time"  : 3,
			"min_level" : 120,
			"yaowang-miaoshu" : 120,
		]));
	}
	setup();
}

int do_effect(object me)
{
	if (time() - me->query_temp("last_eat/tianxin") < 20)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	if (! me->query_skill_mapped("force"))
	{
		write("��û�м����κ��ڹ�����ô����ҩ������������\n");
		return 1;
	}

	me->set_temp("last_eat/tianxin", time());

	message_vision(HIY "$N" HIY "��������һ������������" + name() +
		       HIY "����ϥ���£���ʼ�˹��ƶ���"NOR"\n", me);

	// �˹�����
	me->add_temp("apply/dispel_poison", 180);
	SKILL_D("force")->exert_function(me, "dispel");
	me->add_temp("apply/dispel_poison", -180);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
