// heiyugao.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(HIC "���������" NOR, ({ "heiyugao" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ��ǧ�꼫�������Ƶĵĺ��������,��˵������������\n");
		set("only_do_effect", 1);
	}

	setup();
}

int do_effect(object me)
{
	me->receive_curing("jing", 1000);
	me->receive_curing("qi", 2000);
	tell_object(me, HIG "��ֻ��һ���������߾�������ѭ����һ�����죬������������ˣ�"NOR"\n");
	destruct(this_object());
	return 1;
}
