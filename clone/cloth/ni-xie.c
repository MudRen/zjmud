// nixie.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( HIC "�಼��Ь" NOR, ({ "ni xie", "xie" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "˫");
	      set("icon", "05048");
		set("long", "һ˫�಼��Ь��\n");
		set("value", 0);
		set("material", "boots");
		set("armor_prop/dodge", 5);
		set("female_only", 1);
	}
	setup();
}