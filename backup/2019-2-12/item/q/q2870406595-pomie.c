// ITEM Made by player(³Î°Ô:q2870406595) /data/item/q/q2870406595-pomie.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 27 12:52:55 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("ÆÆÃğ[2;37;0m", ({ "pomie" }));
	set_weight(1575);
	set("item_make", 1);
	set("unit", "Ì×");
	set("long", "ÕâÊÇÓÉ[37m¾«Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ì×Ö¸Ì×¡£
ÆÆËéĞé¿Õ£¬ÕâÌìµØÒ²Ì«ÏÁĞ¡£¬ºÎÒÔÔµÆğºÎÒÔÔµÃğ£¬ÍòÎï½ÔÔÚÎÒµÄÕÆÏÂ[2;37;0m
Ö¸Ì×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º³Î°Ô(q2870406595)
");
	set("value", 700000);
	set("point", 66);
	set("material", "iron");
	set("wear_msg", "$NÊÖÉÏ³öÒ»¸ö¼ÅÃğµÄÆøÏ¢£¬Ë«ÊÖÒ»»Î$n³öÏÖÔÚÁË[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁËÆÆÃğ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return query("long") + item_long(); }
