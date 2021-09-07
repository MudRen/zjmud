// ITEM Made by player(ÎèÇàÒÂ:sj2605673550) /data/item/s/sj2605673550-kzz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 27 13:50:51 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("¿ã×Ó[2;37;0m", ({ "kzz" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ìõ¿ã×Ó¡£
¿ã×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎèÇàÒÂ(sj2605673550)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸¿ã×Ó[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË¿ã×Ó[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
