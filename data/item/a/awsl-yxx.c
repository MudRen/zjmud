// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-yxx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 17:51:14 2019
#include <ansi.h>
#include <weapon.h>

inherit XSWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÓñóï[2;37;0m", ({ "yxx" }));
	set_weight(1500);
	set("item_make", 1);
	set("unit", "Ö§");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ö§óï¡£
[1;31m²»ÖªµÀ¶À¹ÂÂÜÀòÄÄÀï¼ñÀ´µÄ[2;37;0m
óï±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "ÄÃÉÏ[2;37;0m\n");
	set("unwield_msg", "·ÅÏÂ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_xsword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
