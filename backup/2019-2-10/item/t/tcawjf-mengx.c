// ITEM Made by player(知知:tcawjf) /data/item/t/tcawjf-mengx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan  6 20:57:31 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[36m知佰認定[2;37;0m", ({ "mengx" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "嫖");
	set("long", "宸頁喇[37m貧硬混鑓[2;37;0m繕崙遇撹議匯嫖擦遮。
擦遮垉貧震彭匯佩弌忖?挫涼?(tcawjf)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "挫是[2;37;0m\n");
	set("remove_msg", "[33m$N[33m用和阻[2;37;0m[36m知佰認定[2;37;0m[33m。[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
