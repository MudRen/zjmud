// rumor.c

#include <ansi.h>

inherit ITEM;
inherit F_AUTOLOAD;

void setup()
{}

void create()
{
	set_name(HIM "ҥ��������" NOR, ({"rumor generator", "rumor"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "����һ�ܿ������ֵֹ�������Ϳ��������ɫ��ר�����೤����ʿ��ҥʹ�á�\n");
		set("value", 1);
		set("no_sell", 1);
	}
	setup();
}

void init()
{
	object me;

	me = this_player();
	if (environment() != me)
		return;

	"/adm/npc/youxun"->append_receiver(me);
}

int query_autoload()
{
	return 1;
}
