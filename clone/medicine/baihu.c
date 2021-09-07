#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIW "�׻�������" NOR, ({"duoming dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", HIW "�䵱�ɵ�����ʥҩ�������Ƹ������ˣ�Ч��������"NOR"\n");
		set("base_unit", "��");
		set("base_value", 80000);
		set("no_sell", 1);
		set("base_weight", 80);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tianqi"   : 1,
				    "juhua"    : 1,
				    "zihua"    : 1,
				    "lanhua"   : 1,
				    "niuxi"   : 1,
				    "xiefen"   : 1,
				    "moyao"    : 1,
				    "shengdi"  : 1,
				    "yjhua"    : 1,
				    "renshen"  : 1,
				    "guiwei"   : 1,
				    "chenpi"   : 1 ]),
			"neili" : 300,
			"jing"  : 50,
			"time"  : 7,
			"min_level" : 140,
			"liandan-shu" : 180,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/duoming") < 120)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	me->set_temp("last_eat/duoming", time());

	message_vision(HIW "$N" HIW "����һ��" + name() + HIW "��˫Ŀ΢�գ�����ҩЧ��ȫ�����ա�"NOR"\n", me);
	tell_object(me, HIW "ͻȻ�������Ѫ����ͨ��������֮����"NOR"\n");

	log_file("static/using", sprintf("%s(%s) eat �׻������� at %s.\n",
		 me->name(1), me->query("id"), ctime(time())));

	my = me->query_entire_dbase();
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];

	me->start_busy(2);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}

