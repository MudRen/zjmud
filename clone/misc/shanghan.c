// shanghan.c �˺���

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY"�˺���"NOR, ({"shh chou", "shanghan chou"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ר���˺���ҩ�������ޱȡ�\n");
		set("value", 1000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (!me->query_condition("ill_shanghan"))
	{
		write("��������û�е��˺������ҳ�ҩ��\n");
		return 1;
	} else {
		me->clear_condition("ill_shanghan");
		message_vision("$N����һ���˺����ɫ�������ö��ˡ�\n", me);
		me->start_busy(2);
		destruct(this_object());
		return 1;
	}
}

