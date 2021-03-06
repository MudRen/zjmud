// ITEM Made by player(问天:wentianaa) /data/item/w/wentianaa-zhang.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:25:39 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m如来神掌[2;37;0m", ({ "zhang" }));
	set_weight(2250);
	set("item_make", 1);
	set("unit", "双");
	set("long", "这是由[37m上古寒铁[2;37;0m炼制而成的一双铁掌。
[1;33m一掌出，万物退。[2;37;0m
铁掌缘上刻着一行小字：问天(wentianaa)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "$n[1;33m从天而降[2;37;0m\n");
	set("remove_msg", "$n[1;33m消失不见[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }
