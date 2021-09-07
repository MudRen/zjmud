// medicine: xuelian.c
// Jay 3/18/96

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name("��ɽѩ��", ({"xuelian", "lian", "lotus"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "֧");
		set("long", "����һֻ֧���ں���ĵط�����������ѩ����\n");
		set("value", 100);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
       if ((int)me->query("eff_qi") >= (int)me->query("max_qi"))
		return notify_fail("�����ڲ��ó��ⱦ����\n");

       me->receive_curing("qi", 200);
       message_vision("$NС�ĵس���һ��ѩ������ʱ����������ˬ�˲��٣�\n",
		      me);

       destruct(this_object());
       return 1;
}
