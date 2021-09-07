#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIR"�����޼���"NOR, ({"huiyang dan", "dan"}));
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

	if (time() - me->query_temp("last_eat/dan(B)") < 30)
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

	message_vision(HIR "$N����һ�������޼�������Ϣ�õ�����ȫ�Ĳ��䡣"NOR"\n", me);
	me->set("qi",me->query("max_qi"));
	me->set("eff_qi",me->query("max_qi"));

	me->start_busy(3);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
