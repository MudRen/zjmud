// ITEM Made by player(¶ÉÎò:liuyiping) /data/item/l/liuyiping-qhyz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan 28 21:11:02 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("ÆáºÚÑÛÕÖ[2;37;0m", ({ "qhyz" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "¶¥");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶¥Í·¿ø¡£
ÎÒ¿´²»µ½Õâ¸öÊÀ½çµÄÉÆ¶ñ£¬ºÚ°×£¬Ï²Å­£¬ÎÒÑÛÀïÖ»ÓĞ¿Õ¡£[2;37;0m
Í·¿øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶ÉÎò(liuyiping)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸ÆáºÚÑÛÕÖ[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁËÆáºÚÑÛÕÖ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
