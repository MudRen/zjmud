// liang-xie.c

#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
	set_name( HIC "��Ь" NOR, ({ "liang xie", "xie" }) );
	set_weight(1000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "˫");
	     set("icon", "05047");
		set("long", "һ˫ϸ����Ƥƽ��С��Ь��\n");
		set("value", 1);
		set("material", "boots");
		set("armor_prop/dodge", 5);
	}
	setup();
}

int query_autoload() { return 1; }

