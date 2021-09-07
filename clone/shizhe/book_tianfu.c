// jinsha.c

#include <ansi.h>
inherit COMBINED_ITEM;
string query_autoload() { return query_amount() + ""; }

void autoload(string param)
{
	int amt;

	if (sscanf(param, "%d", amt) == 1)
		set_amount(amt);
}

void setup()
{
	set_amount(1);
	::setup();
}

void create()
{
	set_name(HIM "�츳������" NOR, ({ "tianfu jineng shu" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "���������츳���ܵĵ��ߣ��м��ʻ�������츳���ܺ������츳���ܡ�\n");
		set("unit", "��");
		set("base_unit", "��");
		set("base_value", 500);
		set("yuanbao", 20);
        set("no_sell", 1);
		set("only_do_effect", 1);
		set("base_weight", 1);
	}
	setup();
}

int do_effect(object me)
{
	if(me->query("combat_exp", 1) < 2) 
                return notify_fail("��û��ʵս�������޷�ʹ��" + name() + "��\n");

	message_vision(CYN "$N" CYN "ʹ����һ"+query("unit") + name() + CYN "���о����������һ�㡣"NOR"\n", me);

	UPDATE_D->born_player(me);
	add_amount(-1);

	return 1;
}
