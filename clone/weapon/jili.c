// jili.c

#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name("����޼", ({ "tie jili", "jili" }));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("base_unit", "ö");
		set("base_weight", 300);
		set("base_value", 0);
		set("material", "iron");
		set("long", HIG "����޼�������ڴ㶾�����������С��"NOR"\n");
	}

	set_amount(50);
	init_throwing(50);
	setup();
}

