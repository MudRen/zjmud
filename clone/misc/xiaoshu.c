// xiaoshu.c ������

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY"������"NOR, ({"xiaoshu wan", "xiaoshuwan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����������ҩ�����̼�Ч��\n");
		set("value", 600);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (!me->query_condition("ill_zhongshu"))
	{
		write("��������û��������ҳ�ҩ��\n");
		return 1;
	} else {
		me->clear_condition("ill_zhongshu");
		message_vision("$N����һ�������裬������������ˡ�\n", me);
		me->start_busy(2);
		destruct(this_object());
		return 1;
	}
}
