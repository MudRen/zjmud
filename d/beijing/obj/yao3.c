// yao3.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIY "��ҩ" NOR, ({ "jinchuang yao", "jinchuang", "yao" }));
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("long", "����һ��������ʿ�ر��Ľ�ҩ��\n");
		set("value", 5000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	if ((int)me->query("eff_qi") >= (int)me->query("max_qi"))
		return notify_fail("�����ڲ���Ҫ�ý�ҩ��\n");

	me->receive_curing("qi", 50);
	message_vision("$N����һ����ҩ����ɫ�������ö��ˡ�\n", me);
	destruct(this_object());
	return 1;
}
