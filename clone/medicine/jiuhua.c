// jiuhua.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIG "�Ż���¶��" NOR, ({"jiuhua wan", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�ž�Ө��͸�ľŻ���¶�裬�����������Ч��\n");
		set("base_unit", "��");
		set("base_value", 100000);
		set("no_sell", 1);
		set("base_weight", 80);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tianqi"   : 1,
				    "juhua"    : 1,
				    "zihua"    : 1,
				    "lanhua"   : 1,
				    "yjhua"    : 1,
				    "honghua"  : 1,
				    "moyao"    : 1,
				    "xiongdan" : 1,
				    "heshouwu" : 1,
				    "renshen"  : 1,
				    "dangui"   : 1,
				    "chenpi"   : 1 ]),
			"neili" : 300,
			"jing"  : 50,
			"time"  : 7,
			"min_level" : 140,
			"taohua-yaoli" : 200,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/jiuhua") < 120)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	me->set_temp("last_eat/jiuhua", time());

	message_vision(HIG "$N" HIG "��������һ��" + name() +
		       HIG "���������ɣ�����ҩЧ��ȫ�����ա�"NOR"\n", me);
	tell_object(me, HIG "��һ�����ֻ���þ��������������㣬��������֮����"NOR"\n");

	log_file("static/using", sprintf("%s(%s) eat �Ż���¶�� at %s.\n",
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
