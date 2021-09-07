// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-sss.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 17:47:56 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÅ®ÉñµÄ¹â»Ô[2;37;0m", ({ "sss" }));
	set_weight(1750);
	set("item_make", 1);
	set("unit", "Ì×");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ì×Ö¸Ì×¡£
[1;31m¶À¹ÂÂÜÀòÕÒÅ®ÉñË¹ß¯Åµ£¨½è£©¹ıÀ´µÄ[2;37;0m
Ö¸Ì×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "´øÉÏ[2;37;0m\n");
	set("remove_msg", "È¡ÏÂ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return query("long") + item_long(); }
