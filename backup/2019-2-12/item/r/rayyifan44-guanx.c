// ITEM Made by player(Ğşºú:rayyifan44) /data/item/r/rayyifan44-guanx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan  7 15:23:23 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("¹ÙÑ¥[2;37;0m", ({ "guanx" }));
	set_weight(3000);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«Ñ¥×Ó¡£
Ñ¥×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞşºú(rayyifan44)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸¹ÙÑ¥[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË¹ÙÑ¥[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
