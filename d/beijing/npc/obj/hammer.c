#include <weapon.h>
#include <ansi.h>
inherit HAMMER;
void create()
{
	set_name( "������",  ({ "hammer" }));
	set_weight(10000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("long", "һ����ͨ�Ĵ�������\n");
		set("value", 1000);
		set("material", "gold");
	}
	init_hammer(10);
	setup();
}

