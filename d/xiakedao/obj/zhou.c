// zhou.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("������", ({ "zhou"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����Ĳ�Ʒ�����ࡣ\n");
		set("value", 20000);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	int neili_limit;
	int neili;

	neili = me->query("max_neili");
	neili_limit = me->query_neili_limit();

	if (neili < neili_limit)
	{
		neili += random(50) + 1;
		if (neili >= neili_limit) neili = neili_limit;
		me->add("neili", 25 - random(50));
		message_vision(HIY "$N" HIY "����һ�������࣬��Ȼ��"
			       "ֻ��һ������ֱ���ķ�..."NOR"\n", me);
	} else
		message_vision(HIY "$N" HIY "����һ�������࣬����ô���е��..."NOR"\n",
			       me);

	destruct(this_object());
	return 1;
}
