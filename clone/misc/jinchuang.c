// jinchuang.c ��ҩ

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIY "��ҩ" NOR, ({"jinchuang yao", "jinchuang", "yao"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��������ʿ�ر��Ľ�ҩ��\n");
		set("value", 1000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if (me->is_busy())
		return notify_fail("�𼱣������ԣ�С�ı�ҭ���ˡ�\n");

	if ((int)me->query("eff_qi") == (int)me->query("max_qi"))
		return notify_fail("�����ڲ���Ҫ�ý�ҩ��\n");
	else
	{
		me->receive_curing("qi", 250);
		message_vision("$N����һ����ҩ����ɫ�������ö��ˡ�\n", me);
		me->start_busy(2);
		destruct(this_object());
		return 1;
	}
}

