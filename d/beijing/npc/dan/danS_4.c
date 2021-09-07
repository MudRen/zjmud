#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(HIW"�׻�"NOR+HIY"��ũ��"NOR, ({"baihu dan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����300�㾭���Ǳ�ܣ���������������������ȴ30�롣\n");
		set("base_unit", "��");
		set("no_drop", "�������������뿪�㡣\n");
		set("no_sell", "�������������뿪�㡣\n");
		set("no_put", "�����������ܷ����Ƕ���\n");
		set("no_get", "�������������뿪�Ƕ���\n");
		set("no_steal", "�������������뿪�Ƕ���\n");
		set("no_beg", "�������������뿪�Ƕ���\n");
		set("base_value", 0);
		set("only_do_effect", 1);
	}
	setup();
	set_amount(1);
}

int do_effect(object me)
{
	mapping my;

	if (time() - me->query_temp("last_eat/dan(S)") < 30)
	{
		write("��շ��ù�ҩ����ҩ�Է�����Ч���Ժ���ܼ������á�\n");
		return 1;
	}

	my = me->query_entire_dbase();

	me->set_temp("last_eat/dan(S)", time());

	message_sort(HIW "$N" HIW "����һ��$n" HIW "��ֻ��ȫ��"
		     "�����������ϣ�����ԴԴ���ϵ�ӿ�뵤�˵"
		     "������������á���ʱ�е���̨�������һ��"
		     "ƽ����������ѧ����ѧ֪ʶһһӿ����ͷ����"
		     "��̨�����ڹ�ͨ��$N" HIW "�е��ľ����Ǳ��"
		     "����һ���Ľ�չ��"NOR"\n", me, this_object());
	me->set("jingli", me->query("max_jingli"));
	me->set("neili", me->query("max_neili"));
	me->add("combat_exp", 300);
	me->add("potential", 300);

	me->start_busy(2);

	add_amount(-1);
	if (query_amount() < 1)
		destruct(this_object());

	return 1;
}

void owner_is_killed()
{
	destruct(this_object());
}
