// jiu.c
inherit ITEM;
#include <ansi.h>

void create()
{
	set_name(HIC "�����̻��" NOR, ({"xuanbingbihuo jiu", "jiu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����֮���������̻��, ��˵�ܽ�ٶ���\n");
		set("only_do_effect", 1);
		set("do_drink", 1);
	}

	setup();
}

int do_effect(object me)
{
	message_vision("$Nһ�ﲱ���������̻��һ���Ӿ͵����˿��С�\n", me);

	me->set("eff_jing", me->query("max_jing"));
	me->set("jing", me->query("max_jing"));
	tell_object(me, HIC "��ֻ��һ�����������ķΣ�����������ˬ��"NOR"\n");
	destruct(this_object());
	return 1;
}
