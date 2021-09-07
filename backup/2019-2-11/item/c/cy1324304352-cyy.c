// ITEM Made by player(Î÷Ê©ÃÃÃÃ:cy1324304352) /data/item/c/cy1324304352-cyy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Dec 28 08:11:34 2018
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("ºìÁ«ÌìÎè¼×[2;37;0m", ({ "cyy" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
ºìÒÂÎèÌìÏÂ[2;37;0m
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎ÷Ê©ÃÃÃÃ(cy1324304352)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "¾ÅÌìÎè£¬Îè¾ÅÌì£¬Ò»ÎèÌìµØÒ»õäõÑ[2;37;0m\n");
	set("remove_msg", "¾ÅÌìÒ»Îè[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
