// shizi.c

#include <weapon.h>
#include <ansi.h>

inherit THROWING;

void create()
{
	set_name(WHT "ʯ��" NOR, ({ "shi zi", "shi", "zi" }) );
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "Щ");
		set("value", 0);
		set("base_unit", "��");
		set("base_weight", 100);
		set("base_value", 0);
		set("material", "iron");
		set("long", "һ�Ų�ͬ��Сʯ�ӡ�\n");
	}
	set_amount(10);
	init_throwing(2);
	setup();
}
