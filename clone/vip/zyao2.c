
#include <ansi.h>

inherit COMBINED_ITEM;

string query_autoload()
{
	return query_amount() + "";
}

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name("�����컯��", ( {"zaohua dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�������컯�������Բ����Լ��ĵ�ǰ������\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 50000);
		set("no_sell", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (me->query_temp("dgjj/zongjue"))
		return notify_fail("��Ŀǰ��״̬�޷�ʹ��"+ name() +"��\n");

	if (me->query_enemy()&&sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ��"+ name() +"��\n");

	if (me->query("neili")> me->query("max_neili"))
		return notify_fail("�����ڲ���Ҫ����"+ name() +"��\n");
	else
	{
		if( me->query_condition("medicine")>0 )
			return notify_fail("����һ�η�ҩ��ҩ�Ի�û�й��أ�\n");

		me->set("neili",me->query("max_neili")*2);

		message_vision("$N����һ" + query("unit") + name() + "���ٸ�������ӯ��\n", me);
		me->apply_condition("medicine",4);
		me->start_busy(2);
		if (query_amount() < 2) write("���"+ name() +"�����ˡ�\n");
		add_amount(-1);
		return 1;
	}

}
