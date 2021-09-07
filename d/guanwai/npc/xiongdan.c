// xiongdan.c
inherit ITEM;

#include <ansi.h>

void init()
{
	if (find_call_out("destdan") != -1)
		return;

	call_out("destdan", 10);
}

void destdan()
{
	object ob;
	message_vision("$N�������紵�ţ�һ��Ͳ��������ˡ�\n", this_object());
	ob = new(__DIR__"xiongdan1");
	ob->move(environment());
	destruct(this_object());
}

void create()
{
	set_name(HIG "�����ܵ�" NOR, ({"dan", "xiong dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�������ܵ����������ڵģ�ʮ�����ˡ�\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	me->improve_neili(2);

	me->set("neili", me->query("max_neili"));
	me->set("qi", me->query("eff_qi"));
	message_vision("$N����һ�������ܵ���ֻ���þ�"
		       "��������������ԴԴ��������Ѫ��ӯ��\n",me);
	destruct(this_object());
	return 1;
}
