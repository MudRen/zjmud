// fuling.c ����
// By Lgg,1998.10

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(YEL"����"NOR, ({"fu ling"}));
	set_weight(500);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ����͵����ߣ�����������ҩ��\n");
		set("only_do_effect", 1);
	}

	setup();
}

int do_effect(object me)
{
	write("���������ڰ����߳�����ȥ��\n");
	destruct(this_object());
	return 1;
}
