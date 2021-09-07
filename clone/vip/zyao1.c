
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
	set_name("����������", ( {"baoming dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ��������������������ȫ�ָ��������ơ�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 90000);
		set("no_sell", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

if (sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ��"+ name() +"��\n");

	if (me->query("eff_qi")*100/ (me->query("max_qi")+me->query_gain_qi())>99 && me->query("eff_jing")*100/ me->query("max_jing")>99)
		return notify_fail("�����ڲ���Ҫ����"+ name() +"��\n");
	else
	{
		if( me->query_condition("medicine")>0 )
			return notify_fail("����һ�η�ҩ��ҩ�Ի�û�й��أ�\n");

		me->set("eff_qi",me->query("max_qi")+me->query_gain_qi());
		me->set("eff_jing",me->query("max_jing"));

		message_vision("$N����һ" + query("unit") + name() + "����ʱ����Ȭ���ˡ�\n", me);
		me->apply_condition("medicine",4);
		me->start_busy(2);
		if (query_amount() < 2) write("���"+ name() +"�����ˡ�\n");
		add_amount(-1);
		return 1;
	}

}
