// hedinghong.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(RED"�׶���"NOR, ({"heding hong", "hong"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һƿ�綾�Ķ�ҩ, ��������������м�Ѫ���֮Ч. \n");
		set("unit", "ƿ");
		set("value", 20000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N��ͷ��ཹ�ཹ���һƿ" + name() + "��\n", me);
	me->set_temp("die_reason", "���˺׶��죬�ж�����");
	me->die();
	destruct(this_object());
	return 1;
}
