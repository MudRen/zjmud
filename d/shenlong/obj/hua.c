//hua.c ���㻨

inherit ITEM;

#include <ansi.h>

void create()
{
	set_name(HIG"���㻨"NOR, ({"baixiang hua", "baixiang"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����޵Ļ�������Ũ���쳣��\n");
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N��" + name() + "�ӽ�������¾�������ȥ��\n", me);
	destruct(this_object());
	return 1;
}

