// kongquedan.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(BLU "��ȸ��" NOR, ({"kongque dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һƿ�綾�Ķ�ҩ, ��������������м�Ѫ���֮Ч. \n");
		set("unit", "��");
		set("value", 20000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N��ͷ�ſ�����һ��" + name() + "��\n", me);
	me->set_temp("die_reason", "���˿�ȸ�����ж�����");
	me->die();
	destruct(this_object());
	return 1;
}
