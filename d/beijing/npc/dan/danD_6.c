#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIW"��ɲ"NOR+HIR"�޳�"NOR+HIY"��"NOR, ({"luosha dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_value", 150);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dan(D)") < 240)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();

	me->set_temp("last_eat/dan(D)", time());

	message_vision(HIR "$N����һ����ɲ�޳����������õ�����ȫ�Ĳ��䡣"NOR"\n", me);
	me->set("neili", me->query("max_neili"));

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
