//neck.c

#include <ansi.h>
#include <armor.h>

inherit NECK;

void create()
{
	set_name(HIW"�׽���Ȧ"NOR, ({ "baijin xiangquan", "xiangquan", "neck" }));
	set("weight", 200);
	if (clonep())
		set_default_object(__FILE__);
	else 
	{
		set("unit", "��");
		set("value", 3500);
		set("material", "gold");
		set("armor_prop/armor", 1);
	}

	setup();
}
