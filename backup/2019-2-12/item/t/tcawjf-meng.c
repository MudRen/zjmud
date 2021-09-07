// ITEM Made by player(知知:tcawjf) /data/item/t/tcawjf-meng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 12:49:09 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34m匯知認定[2;37;0m", ({ "meng" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "褒");
	set("long", "宸頁喇[1;35m舞鑓[2;37;0m繕崙遇撹議匯褒鑓嫺。
認定寂匯鵬遇狛��知嶄起峺匯屍寂[2;37;0m
鑓嫺垉貧震彭匯佩弌忖�挫涼�(tcawjf)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wear_msg", "哩状晴[2;37;0m\n");
	set("remove_msg", "[33m$N[33m用和阻[1;34m匯知認定[2;37;0m[33m。[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }
