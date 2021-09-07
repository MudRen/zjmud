// ITEM Made by player(ĞÄÄ§:l3440039129) /data/item/l/l3440039129-lsz.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  1 00:14:02 2019
#include <ansi.h>
#include <weapon.h>

inherit STAFF;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mÁúÉßÊÖÕÈ[2;37;0m", ({ "lsz" }));
	set_weight(6750);
	set("item_make", 1);
	set("unit", "¸ù");
	set("long", "ÕâÊÇÓÉ[37m¾«Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¸ùÕÈ¡£
ÕÈ±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞÄÄ§(l3440039129)
");
	set("value", 700000);
	set("point", 66);
	set("material", "iron");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»¸ù[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_staff(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
