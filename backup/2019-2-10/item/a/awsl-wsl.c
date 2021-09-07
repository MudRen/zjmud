// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-wsl.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 11 11:00:37 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mÏ¸ÂíÎ²¶Ğ´ø[2;37;0m", ({ "wsl" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "¶¥");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶¥Í·¿ø¡£
[1;34mÄ³¸ö¶Ô¶À¹ÂÂÜÀòºÜÖØ£¬²»×îÖØÒªµÄÈËËÍ¸øËıµÄÀñÎï£¨Ã»´í¾ÍÊÇÎÒ£©[2;37;0m
Í·¿øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "Ï¸ÉÏ[2;37;0m\n");
	set("remove_msg", "È¡ÏÂ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
