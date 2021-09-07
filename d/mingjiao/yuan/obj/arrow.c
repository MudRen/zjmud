// arrow.c

#include <weapon.h>
#include <ansi.h>

inherit THROWING;

int is_arrow() { return 1; }

void create()
{
	set_name(HIC "��β��" NOR, ({ "fengwei jian", "arrow", "jian" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("value", 0);
		set("base_unit", "֧");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("long", "���Ƿ�β������������������Ƶ�ʮ�����͡�\n");
		set("wound_percent", 80);
	}
	set_amount(10);
	init_throwing(200);
	setup();

	set("no_wield", "�ⲻ������װ���ġ�\n");
}
