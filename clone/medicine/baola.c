#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIY "���Ʊ�����" NOR, ({"baola dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", HIY "�䵱�ɵ�����ʥҩ�����м��ѵĽⶾ��Ч��"NOR"\n");
		set("base_unit", "��");
		set("base_value", 100000);
		set("no_sell", 1);
		set("base_weight", 55);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tenghuang" : 2,
				    "mahuang"   : 2,
				    "xionghuang": 2,
				    "duhuo"     : 1,
				    "yanwo"     : 1,
				    "xiongdan"  : 1,
				    "lurong"    : 1,
				    "shancha"   : 1,
				    "renshen"   : 1,
				    "xuelian"   : 1,
				    "lingzhi"   : 1, ]),
			"neili" : 400,
			"jing"  : 60,
			"time"  : 8,
			"min_level" : 150,
			"liandan-shu" : 220,
		]));
	}
	setup();
}

int do_effect(object me)
{
	if (time() - me->query_temp("last_eat/jiedu") < 80)
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

	message_vision(HIY "$N" HIY "������һ��" + name() + HIY "����æ"
		       "��ϥ���£���ʼ�˹��ƶ���"NOR"\n", me);

	// �˹�����
	me->add_temp("apply/dispel_poison", 350);
	SKILL_D("force")->exert_function(me, "dispel");
	me->add_temp("apply/dispel_poison", -350);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}

