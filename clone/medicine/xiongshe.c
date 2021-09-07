// xiongshe.c
// ���� max

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIG "��ת������" NOR, ({ "xiongshe wan", "wan" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�ŵ��̵ĵ�ҩ�裬���ܵ��ߵ�����ϡҩ�ľ��ƶ��ɡ�\n");
		set("base_unit", "��");
		set("base_value", 100000);
		set("no_sell", 1);
		set("base_weight", 100);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tianqi"   : 1,
				    "xuelian"  : 1,
				    "lurong"   : 1,
				    "honghua"  : 1,
				    "zzfen"    : 1,
				    "heshouwu" : 1,
				    "renshen"  : 1,
				    "dangui"   : 1,
				    "xiongdan" : 3,
				    "shedan"   : 2, ]),
			"neili" : 300,
			"jing"  : 50,
			"time"  : 5,
			"min_level"     : 150,
			"xiaoyao-qixue" : 250,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/xiongshe") < 120)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	me->set_temp("last_eat/xiongshe", time());

	message_vision(HIM "$N" HIG "����һ��" + name() +
		       HIM "������ֱð�Ϲ⣡\n", me);
	tell_object(me, HIG "��һ�����ֻ���þ��������������㣬��������֮����"NOR"\n");

	log_file("static/using", sprintf("%s(%s) eat ��ת������ at %s.\n",
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

