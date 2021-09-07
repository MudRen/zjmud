// bicanfeng.c

#include <ansi.h>

inherit ITEM;

void create()
{
	set_name(GRN "�̲Ϸ�" NOR, ({"bican fen", "fen"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ���綾�Ķ�ҩ����������������м�Ѫ���֮Ч��\n");
		set("unit", "��");
		set("value", 20000);
		set("can_pour", 1);
		set("can_daub", 1);
		set("can_drug", 1);
		set("poison", ([
			"level" : 200,
			"id"    : "...",
			"name"  : "�綾",
			"duration": 15,
		]));
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$N��ͷ��һС��" + name() + "��������ȥ��\n", me);
	me->set_temp("die_reason", "���˱̲Ϸۣ�Ī������ļ�������");
	me->die();
	destruct(this_object());
	return 1;
}
