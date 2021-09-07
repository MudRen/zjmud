// shengsheng.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIR "�����컯��" NOR, ({"shengsheng dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�ź�ɫ��ҩ�裬�����������Ч��\n");
		set("base_unit", "��");
		set("base_value", 100000);
		set("no_sell", 1);
		set("base_weight", 80);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tianqi"   : 1,
				    "gsliu"    : 1,
				    "duhuo"    : 1,
				    "lurong"   : 1,
				    "juhua"    : 1,
				    "honghua"  : 1,
				    "hafen"    : 1,
				    "xiongdan" : 1,
				    "heshouwu" : 1,
				    "renshen"  : 1,
				    "dangui"   : 1,
				    "chenpi"   : 1 ]),
			"neili" : 300,
			"jing"  : 50,
			"time"  : 7,
			"min_level" : 140,
			"yaowang-miaoshu" : 220,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/shengsheng") < 120)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	me->set_temp("last_eat/shengsheng", time());

	message_vision(HIG "$N" HIG "��������һ��" + name() +
		       HIG "���������ɣ�����ҩЧ��ȫ�����ա�"NOR"\n", me);
	tell_object(me, HIG "��һ�����ֻ���þ��������������㣬��������֮����"NOR"\n");

	log_file("static/using", sprintf("%s(%s) eat �����컯�� at %s.\n",
		 me->name(1), me->query("id"), ctime(time())));

	my = me->query_entire_dbase();
	my["eff_jing"] = my["max_jing"];
	my["jing"] = my["max_jing"];
	my["eff_qi"] = my["max_qi"];
	my["qi"] = my["max_qi"];
	if (my["jingli"] < my["max_jingli"])
		my["jingli"] = my["max_jingli"];
	if (my["neili"] < my["max_neili"])
		my["neili"] = my["max_neili"];

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
