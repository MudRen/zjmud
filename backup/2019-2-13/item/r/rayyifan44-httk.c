// ITEM Made by player(Ğşºú:rayyifan44) /data/item/r/rayyifan44-httk.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan  5 20:07:11 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("ºÚÌúÍ·¿ø[2;37;0m", ({ "httk" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "¶¥");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶¥Í·¿ø¡£
Í·¿øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞşºú(rayyifan44)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸ºÚÌúÍ·¿ø[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁËºÚÌúÍ·¿ø[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
