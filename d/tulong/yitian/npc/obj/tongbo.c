#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
void create()
{
	set_name(YEL "ͭ��" NOR,  ({ "tong bo", "tong", "bo" }));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ������ͭ������ࡣ\n");
		set("value", 2000);
		set("material", "gold");
	}
	init_hammer(20);
	setup();
}

