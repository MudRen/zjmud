// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-bian.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 18:36:41 2019
#include <ansi.h>
#include <weapon.h>

inherit WHIP;
inherit F_ITEMMAKE;

void create()
{
	set_name("ĞÂ¶¡±Ş[2;37;0m", ({ "bian" }));
	set_weight(6750);
	set("item_make", 1);
	set("unit", "¸ù");
	set("long", "ÕâÊÇÓÉ[37m¾«Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¸ù±Ş¡£
±Ş±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 700000);
	set("point", 30);
	set("material", "iron");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»¸ù[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_whip(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
