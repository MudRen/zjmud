// energy stone.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_name(HIY "��������ʯ" NOR, ({"energy stone", "stone"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", HIW "һ�龫������������ʯ��"NOR"\n");
		set("unit", "��");
		set("value", 50000);
		set("weight", 40);
		set("icon","06006");
		set("only_do_effect", 1);
		set("suit_point",10);  //һ���һ���
	}
	setup();
}

int do_effect(object me)
{
	mapping my;

	if (! me->is_magic_beast())
	{
		write("����˰�������ʯҲ�ܳ���\n");
		return 1;
	}

	me->set("food", 8*me->max_food_capacity());
	me->set("water",8*me->max_water_capacity());
	// me->start_busy(1);
	message_vision(HIR "$N" HIR "������һ������ʯ����ʱȫ������,���ɵĴ��˸����ã�����"NOR"\n",me);

	destruct(this_object());

	return 1;
}
