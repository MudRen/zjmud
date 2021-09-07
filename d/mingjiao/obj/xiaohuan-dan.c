// xiaohuan-dan.c С����

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("С����", ({"xiaohuan dan", "xiaohuan", "dan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��Ө����Բ��С�������˵���������ҩ��������������Ч�ޱȡ�\n");
		set("value", 10000);
		set("no_drop", "�������������뿪�㡣\n");
		set("only_do_effect", 1);
	}

	set("shaolin", 1);
	setup();
}

int do_effect(object me)
{
	if (me->query("neili") >= me->query("max_neili") * 2)
		return notify_fail("������û��Ҫ��С������\n");

	if (me->query_skill_mapped("force") != "hunyuan-yiqi")
	{
		me->set("neili", 0);
		message_vision(HIR "$N" HIR "����һ��С������ֻ�����������ѣ�ԭ�������ڹ�����������������Ϊ��"NOR"\n", me);
		me->unconcious();
		destruct(this_object());
		return 1;
	}

	if ((int)me->query_condition("bonze_drug" ) > 0 )
	{
		me->add("neili", -200);
		message_vision(HIR "$N����һ��С������ֻ����ͷ�ؽ��ᣬҡҡ������ԭ����ʳ̫��̫�࣬ҩЧ�ʵ��䷴��"NOR"\n", me);
	}
	else
	{
		me->add("neili", 200);
		message_vision(HIY "$N����һ��С������ֻ�����������࣬��֫�ٺ�������ӯ�ޱȣ��������ڶ�����"NOR"\n", me);
	}

	me->apply_condition("bonze_drug", 30);

	destruct(this_object());
	return 1;
}
