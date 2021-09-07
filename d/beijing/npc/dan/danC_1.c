#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIW"С�Ƶ�"NOR, ({"xiaoyun dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_value", 50);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;
	int jl, mj;

	if (time() - me->query_temp("last_eat/dan(C)") < 180)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();
	jl = (int)me->query("jingli") + 100;
	mj = (int)me->query("max_jingli") * 2;

	if (jl > mj)
	{
		write("�����ھ�����Ϊ�������" + name() + "��\n");
		return 1;
	}

	me->set_temp("last_eat/dan(C)", time());

	message_vision(HIW "$N����һ��С�Ƶ���������֮һ�𣬾���������ߡ�"NOR"\n", me);
	me->add("jingli", 100);

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
