// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-bzq.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 17 22:45:07 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35m°ÙñŞÈ¹[2;37;0m", ({ "bzq" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ìõ¿ã×Ó¡£
[1;35mÒ»¼şÆ¯ÁÁµÄĞ¡È¹×Ó[2;37;0m
¿ã×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "silk");
	set("wear_msg", "´©ÉÏ[2;37;0m\n");
	set("remove_msg", "ÍÑÏÂ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
