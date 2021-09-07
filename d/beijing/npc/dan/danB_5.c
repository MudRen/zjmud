#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIR"���굤"NOR, ({"huanhun dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_value", 90);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dan(B)") < 25)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();
	if (my["qi"] == my["max_qi"])
	{
		write("�������������棬�������" + name() + "��\n");
		return 1;
	}

	me->set_temp("last_eat/dan(B)", time());

	message_vision(HIR "$N����һ�����굤����Ϣ�õ�����ȫ�Ĳ��䡣"NOR"\n", me);
	me->receive_curing("qi", 1000);
	me->receive_heal("qi", 1000);

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
