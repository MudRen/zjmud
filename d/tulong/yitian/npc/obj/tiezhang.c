#include <weapon.h>
#include <ansi.h>
inherit STAFF;
void create()
{
	set_name(WHT "������" NOR,  ({ "tie zhang", "tie", "zhang" }));
	set_weight(20000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("icon", "05042");
		set("long", "һ��������������ȡ�\n");
		set("value", 2000);
		set("material", "gold");
	}
	init_staff(20);
	setup();
}

