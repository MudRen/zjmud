// zhike.c ֹ��ҩ

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY"ֹ��ҩ"NOR, ({"zhike yao", "zhikeyao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��������ֹ��ҩ��\n");
		set("value", 100);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (! me->query_condition("ill_kesou"))
	{
		write("��������û�п��ԣ����ҳ�ҩ��\n");
		return 1;
	} else {
		me->clear_condition("ill_kesou");
		message_vision("$N����һ��ֹ��ҩ����������ˡ�\n", me);
		me->start_busy(2);
		destruct(this_object());
		return 1;
	}
}
