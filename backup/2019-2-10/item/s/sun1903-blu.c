// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-blu.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:12:02 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[34mÃÎ²·[2;37;0m", ({ "blu" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ìõ¿ã×Ó¡£
[34mÆÆÆÆµÄ¿ã×Ó£¬ÄÜÂú×ãÎÒÂğ£¿[2;37;0m
¿ã×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[2;37;0m[34mÃÎ²·[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[34mÃÎ²·[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
