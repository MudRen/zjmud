// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-lies.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Dec 19 17:34:15 2018
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("ÁÔÊÖÕ½ÈĞ[2;37;0m", ({ "lies" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
¶ñÄ§ÁÔÊÖĞÂ±øµÄÎäÆ÷[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "Õ½ÈĞ³öÇÊ[2;37;0m\n");
	set("unwield_msg", "ÊÕ»ØÁËÕ½ÈĞ¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
