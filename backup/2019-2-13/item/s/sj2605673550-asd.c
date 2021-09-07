// ITEM Made by player(ÎèÇàÒÂ:sj2605673550) /data/item/s/sj2605673550-asd.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Dec 31 23:39:04 2018
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("»¤¼×[2;37;0m", ({ "asd" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎèÇàÒÂ(sj2605673550)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸»¤¼×[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË»¤¼×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
