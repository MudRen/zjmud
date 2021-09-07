// renshenguo.c
#include <ansi.h>

inherit ITEM;

void init()
{
	if (find_call_out("destguo") != -1)
		return;

	call_out("destguo", 10);
}

void destguo()
{
	tell_room("�˲ι���������ˮ����һ��͸��õ��ˡ�\n", environment());
	destruct(this_object());
}

void create()
{
	set_name(HIR "�˲ι�" NOR, ({"guo", "renshen guo"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һֻ�˲ι�, �Ѿ�����, ����������ܲ�����С����\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->improve_neili(10);

	me->set("neili", me->query("max_neili"));
	me->set("eff_qi", me->query("max_qi"));
	me->set("qi", me->query("eff_qi"));
	message_vision("$N����һö�˲ι���ֻ���þ���������"
		       "��ԴԴ�������������ٸе������ɿʣ�\n",me);

	destruct(this_object());
	return 1;
}
