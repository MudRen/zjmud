// fashao.c ������

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY"������"NOR, ({"tuishao ling", "tuishao ling"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ���η��յ�ҩ����Ч������\n");
		set("value", 200);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (! me->query_condition("ill_fashao"))
	{
		write("��������û�з��գ����ҳ�ҩ��\n");
		return 1;
	} else {
		me->clear_condition("ill_fashao");
		message_vision("$N����һ�������飬������������ˡ�\n", me);
		me->start_busy(2);
		destruct(this_object());
		return 1;
	}
}
