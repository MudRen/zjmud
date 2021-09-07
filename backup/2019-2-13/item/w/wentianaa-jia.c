// ITEM Made by player(ÎÊÌì:wentianaa) /data/item/w/wentianaa-jia.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 19 19:58:14 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33m»Æ½ğ¼×[2;37;0m", ({ "jia" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
[31m½ğ¼×Ò«Õ½³¡£¬ºìÅÛ·çÇåÑï¡£[2;37;0m
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎÊÌì(wentianaa)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸[1;33m»Æ½ğ¼×[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;33m»Æ½ğ¼×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
