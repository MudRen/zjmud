// ITEM Made by player(ÎèÇàÒÂ:sj2605673550) /data/item/s/sj2605673550-xtzj.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 25 23:19:47 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("ĞşÌúÖØ½£[2;37;0m", ({ "xtzj" }));
	set_weight(45000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[36mĞşÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎèÇàÒÂ(sj2605673550)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»±ú[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
