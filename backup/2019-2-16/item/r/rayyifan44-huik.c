// ITEM Made by player(¶Éºú:rayyifan44) /data/item/r/rayyifan44-huik.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 12 14:26:56 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("»Ò¿ã[2;37;0m", ({ "huik" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ìõ¿ã×Ó¡£
¿ã×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶Éºú(rayyifan44)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸»Ò¿ã[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË»Ò¿ã[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
