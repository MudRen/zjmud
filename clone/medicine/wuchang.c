// jiuhua.c

#include <ansi.h>
#include "medicine.h"

void create()
{
	set_name(HIR "�޳���" NOR, ({"wuchang dan", "dan"}));
	set_weight(50);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�ž�Ө�����޳��������һ����������Ƶ���ҩ��\n");
		set("base_unit", "��");
		set("base_value", 80000);
		set("no_sell", 1);
		set("base_weight", 70);
		set("only_do_effect", 1);
		set("mixture", ([
			"herb" : ([ "tianqi"   : 1,
				    "honghua"  : 1,
				    "moyao"    : 1,
				    "xiongdan" : 1,
				    "heshouwu" : 2,
				    "renshen"  : 2,
				    "zzfen"    : 1,
				    "xuelian"  : 1,
				    "xuejie"   : 1,
				    "renshen"  : 1 ]),
			"neili" : 400,
			"jing"  : 60,
			"time"  : 8,
			"min_level" : 150,
			"taohua-yaoli" : 250,
		]));
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/wuchang") < 180)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	me->set_temp("last_eat/wuchang", time());

	message_vision(HIR "$N" HIR "�����޳�������ɫ��һ����Ρ�"NOR"\n", me);
	tell_object(me, HIY "��ֻ�����������棬������Ҫ���ȶ�����"NOR"\n");

	log_file("static/using", sprintf("%s(%s) eat �޳��� at %s.\n",
		 me->name(1), me->query("id"), ctime(time())));

	my = me->query_entire_dbase();
	my["neili"] = my["max_neili"] * 2;

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
