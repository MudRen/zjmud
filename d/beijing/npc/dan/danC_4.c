#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIC"��Ȫ��"NOR, ({"biquan dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����1000�㾫������ȴ30�롣\n");
		set("base_unit", "��");
		set("base_value", 70);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;
	int jl, mj;

	if (time() - me->query_temp("last_eat/dan(D)") < 30)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();
	jl = (int)me->query("jingli") + 1000;
	mj = (int)me->query("max_jingli") * 2;

	if (jl > mj)
	{
		write("�����ھ�����Ϊ�������" + name() + "��\n");
		return 1;
	}

	me->set_temp("last_eat/dan(D)", time());

	message_vision(CYN "$N����һ����Ȫ����������֮һ�𣬾���������ߡ�"NOR"\n", me);
	me->add("jingli", 1000);

	me->start_busy(2);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
