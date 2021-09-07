// ITEM Made by player(Ğş³½:zjzs123) /data/item/z/zjzs123-jtl.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Dec 27 20:27:21 2018
#include <ansi.h>
#include <weapon.h>

inherit WHIP;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m¾ªÌìÀ×[2;37;0m", ({ "jtl" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "¸ù");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¸ù±Ş¡£
±Ş±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞş³½(zjzs123)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wield_msg", "ÎŞÔµ[2;37;0m\n");
	set("unwield_msg", "µçÉÁÀ×Ãù[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_whip(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
