// shedu.c

#include <ansi.h>
inherit ITEM;

void create()
{
	set_weight(50);
	set_name(HIG "�߶�" NOR, ({"she du", "du", "shedu"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�����߶���Һ���ƶ��ɵĶ�ҩ��ֻҪһ����Ϳ������������أ�\n");
		set("value", 50);
		set("poison_type", "poison");
		set("can_pour", 1);
		set("can_daub", 1);
		set("can_drug", 1);
		set("poison", ([
			"level" : 250,
			"id"    : "ŷ����",
			"name"  : "�߶�",
			"duration": 20,
		]));
		set("no_sell", 1);
		set("only_do_effect", 1);
	}
	setup();
}

int do_effect(object me)
{
	message_vision("$Nһ�������Ѷ�ҩȫ�����������С�\n",me);
	me->set_temp("die_reason", "�����߶�����������");
	me->die();
	destruct(this_object());
	return 1;
}

