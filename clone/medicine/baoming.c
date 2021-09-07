// baoming.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIG "����������" NOR, ({"baoming dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�ŵ��̵ĵ�ҩ�裬������������ҩ����Ч�����ޱȡ�\n");
		set("base_unit", "��");
		set("base_value", 100000);
		set("no_sell", 1);
		set("base_weight", 80);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tianqi"   : 1,
				    "xuejie"   : 1,
				    "xuelian"  : 1,
				    "lurong"   : 1,
				    "xiefen"   : 1,
				    "honghua"  : 1,
				    "moyao"    : 1,
				    "zzfen"    : 1,
				    "heshouwu" : 1,
				    "renshen"  : 1,
				    "dangui"   : 1,
				    "chenpi"   : 1 ]),
			"neili" : 300,
			"jing"  : 50,
			"time"  : 5,
			"min_level" : 140,
			"shenlong-mixin" : 200,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/baoming") < 120)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	me->set_temp("last_eat/baoming", time());

	message_vision(HIG "$N" HIG "����һ��" + name() +
		       HIG "���۾�ֱð�̹⣡\n", me);
	tell_object(me, HIG "��һ�����ֻ���þ��������������㣬��������֮����"NOR"\n");

	log_file("static/using", sprintf("%s(%s) eat ���������� at %s.\n",
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
