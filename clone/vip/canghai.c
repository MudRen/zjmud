
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
	set_name(HIC"�׺���"NOR, ( {"canghai dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "������ȫ�ָ����������Լ����������ظ�ʹ�á�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_weight", 10);
		set("yuanbao", 2000);
		set("base_value", 2000);
		set("no_sell", 1);
        set("no_sell",1);
        set("no_give",1);
        set("no_drop",1);
        set("no_get",1);
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

//	if( me->query_condition("medicine")>0 )
//		return notify_fail("����һ�η�ҩ��ҩ�Ի�û�й��أ�\n");

	me->set("neili",me->query("max_neili")*2);
	me->set("eff_qi",me->query("max_qi")+me->query_gain_qi());
	me->set("qi",me->query("eff_qi"));
	me->set("eff_jing",me->query("max_jing"));
	me->set("jing",me->query("eff_jing"));

	message_vision("$N����һ" + query("unit") + name() + "����ʱ����Ȭ���ˡ�\n", me);
//	me->apply_condition("medicine",4);
	me->start_busy(1);

	return 1;
}
