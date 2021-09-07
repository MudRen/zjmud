
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
	set_name("���쵤", ( {"zhoutian dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һ�����쵤����������1000�㵱ǰ������30��������һ�Ρ�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 1);
		set("base_value", 10);
		set("no_sell", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->is_busy())
		return notify_fail("����æ���ء�\n");

	if (me->query_enemy()&&sizeof(filter_array(me->query_enemy(),(: userp :))))
		return notify_fail("���ں���Ҷ���ս��������ʹ��"+ name() +"��\n");

	if (time()-me->query("last_zhoutian") < 30)
		return notify_fail("����ԣ���ҭ�š�\n");

	if (me->query("meili") >= me->query("max_neili"))
		return notify_fail("�����ڲ���Ҫ����"+ name() +"��\n");
	else
	{
		me->add("neili",1000);

		message_vision("$N����һ" + query("unit") + name() + "����ʱ��Ϣ˳����ࡣ\n", me);
		me->start_busy(1);
		me->set("last_zhoutian",time());
		add_amount(-1);

		return 1;
	}

}
