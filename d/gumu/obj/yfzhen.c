// yfzhen.c

#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name(HIG "�����" NOR, ({ "yufeng zhen", "zhen" }) );
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("value", 0);
		set("base_unit", "��");
		set("base_weight", 10);
		set("base_value", 0);
		set("material", "iron");
		set("long", HIG "����һЩϸ�����룬������"NOR"\n");
	}
	set_amount(50);
	init_throwing(50);
	setup();
}
