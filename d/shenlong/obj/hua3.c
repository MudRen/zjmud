// hua3.c

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIR "�ϳ���" NOR, ({"duanchang hua", "duanchang"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ϳ�����ͨ��ͨ�죬�������Σ������쳣��\n");
		set("no_get", "��������ҽ�ǰ��\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N��" + name() + "�ӽ�������¾�������ȥ��\n", me);
	me->set_temp("die_reason", "���¶ϳ������ж�������");
	me->die();
	destruct(this_object());
	return 1;
}
