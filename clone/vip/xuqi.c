
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
	set_name("������", ( {"xuqi pan"}));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("long", "����һֻ�����̣����Բ�����ǰ������200w����֮ǰ���޴�ʹ�á�\n");
		set("unit", "ֻ");
		set("base_unit", "ֻ");
		set("base_weight", 1);
		set("base_value", 10);
		set("yuanbao", 200);
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

	if (me->query("combat_exp")>2000000)
		return notify_fail("�ѳ����������ƣ�����ʹ��"+ name() +"��\n");

	if (me->query("meili") >= me->query("max_neili"))
		return notify_fail("�����ڲ���ʹ��"+ name() +"��\n");
	else
	{
		me->set("neili",me->query("max_neili"));

		message_vision("$Nʹ����һ��" + name() + "����ʱ��Ϣ�ָ��ˡ�\n", me);
		me->start_busy(1);

		return 1;
	}

}
