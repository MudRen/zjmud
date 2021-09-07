// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-ssf.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 10 20:56:23 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mË®ÊÖ·ş[2;37;0m", ({ "ssf" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
[1;34mÒ»¼ş³£¼ûµÄ¶«ÑóË®ÊÖ·ş£¬ÕæÆ¯ÁÁ[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "´©ÉÏ[2;37;0m\n");
	set("remove_msg", "ÍÑÏÂ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
