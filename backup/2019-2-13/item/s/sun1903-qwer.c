// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-qwer.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  2 16:15:52 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[33mÃÎĞş[2;37;0m", ({ "qwer" }));
	set_weight(1080);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«Ñ¥×Ó¡£
[1;33m²ÈÔÚ»ÆÉ«µÄÍÁµØÉÏ£¬³äÂú»ëºñÆøÏ¢µÄÑ¥×Ó£¬ÂıÂı¸¡ÏÖÔÚÃÎĞÇµÄ½ÅÉÏ[2;37;0m
Ñ¥×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[2;37;0m[33mÃÎĞş[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[33mÃÎĞş[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
