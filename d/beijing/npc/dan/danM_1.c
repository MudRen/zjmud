#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIM"���ѵ�"NOR, ({"longxian dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("base_unit", "��");
		set("base_value", 0);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dan(M)") < 400)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();

	me->set_temp("last_eat/dan(M)", time());

	if (me->improve_neili(1))
	{
		message_vision(HIM "$N" HIM "����һ�����ѵ�����������һ��������"NOR"\n", me);
		tell_object(me, "��е��������ۺ���һЩ��\n");
		me->add("max_neili", 1);
	} else
	{
		message_vision(HIC "$N" HIC "����һ�����ѵ�����ɫ���˱䣬����һ˿������"NOR"\n", me);
		tell_object(me, "��е���Ϣ���ȣ��������յ�ҩ��Ч����\n");
	}

	me->start_busy(6);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}
