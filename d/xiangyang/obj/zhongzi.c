// Object: /d/xiangyang/obj/zhongzi.c  ���ĺ�������
// Date: Feb. 2 2002 by Pound

#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(HIR "����" NOR, ({"zhongzi", "hua zhong", "zhong"}));
	set_weight(100);
	if (clonep())
	    set_default_object(__FILE__);
	else
	{
	    set("long", "һö�޷�ȷ��Ʒ�ֵĻ��֡�\n");
	    set("unit", "ֻ");
	    set("value", 0);
	    set("no_give", 1);
	    set("no_steal", 1);
	    set("no_drop", 1);
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

	if (me->query("yaowang/seeded"))
	{
	    tell_object(me, HIR "��������Ѿ������£�����Ӧ�ý��������ˡ�"NOR"\n");
	    return 1;
	}
	message_vision("$N�ڴ�ǰһ�������������ڣ��ѻ������˽�ȥ��\n", me);
	tell_object(me, HIR "��������Ѿ������£�����Ӧ�ý��������ˡ�"NOR"\n");
	me->set("yaowang/seeded", 1);
	destruct(ob);
	me->add("jing", -50);
	return 1;
}
