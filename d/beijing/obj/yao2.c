// yao2.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC "�ش���" NOR, ({"huichun wan", "wan"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 2000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N����һ��" + name() + "��\n", me);

	me->receive_curing("jing", (int)me->query("max_jing") / 40);
	destruct(this_object());
	return 1;
}
