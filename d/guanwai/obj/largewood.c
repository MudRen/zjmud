// largewood.c

#include <ansi.h>

inherit COMBINED_ITEM;

void create()
{
	set_name(WHT "��ľ��" NOR, ({ "large wood", "wood" }));
	if (clonep())
		set_default_object(__FILE__);
	else
	{
		set("unit", "��");
		set("long", "���Ƿ��Գ���ɽ���ϺõĴ�ľ�ϡ�\n");
		set("base_value", 2000);
		set("base_unit", "��");
		set("base_weight", 50000);
	}
	set_amount(1);
}

int fire(object me, object ob)
{
	object fire;

	if (query_amount() < 1)
		return 0;

	if (environment()->query_temp("warm") >= 40)
		return notify_fail("�����Ѿ�̫���ˣ��㻹�ǻ����ط����ɡ�\n");

	message_vision("$N���˺ô󾢣�������" + ob->name() + "��" + name() +
		       "�����ˣ�һƬ���Ļ��ӳ�������ܡ�\n", me);

	fire = new("/clone/misc/needfire");
	fire->move(environment(me));
	fire->set_light_time(100);

	add_amount(-1);
	return 1;
}
