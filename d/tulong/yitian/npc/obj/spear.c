#include <weapon.h>
#include <ansi.h>

inherit CLUB;

void create()
{
	set_name(HIW "������ǹ" NOR, ({ "chang qiang", "qiang", "spear"}) );
	set_weight(15000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "֧");
		set("value", 300);
		set("material", "silk");
	}
	init_club(10);
	setup();
}

