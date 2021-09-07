#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(YEL "����" NOR, ({"hua zhong", "zhong"}));
	set_weight(100);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һö�޷�ȷ��Ʒ�ֵĻ���,���ԳԵ���\n");
		set("unit", "ֻ");
		set("value", 20);
		set("food_remaining", 1);
		    set("food_supply", 10);
	}
}

void init()
{
	add_action("do_zhonghua", "zhonghua");
}

int do_zhonghua()
{
	object me,ob;
 
	me = this_player();
	ob = this_object();

	if (me->query_temp("zhonghua") == 1)
	{
		tell_object(me,HIR "���������Ѿ������ˣ����ڸ�����(peiyu)���֡�"NOR"\n");
		return 1;
	}

	message_vision("$N�����ڵ�������һ���ӣ��ѻ��ַ��˽�ȥ��\n", me);
	tell_object(me, HIR "�����Ѿ������ˣ����ڸ�����(peiyu)���֡�"NOR"\n");
	me->add_temp("zhonghua", 1);
	destruct(ob);
	me->add("jing", -50);
	return 1;
}
