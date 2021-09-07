// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-zhua.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 09:22:55 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("Àû×¦[2;37;0m", ({ "zhua" }));
	set_weight(13500);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[36mĞşÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«ÌúÕÆ¡£
ÌúÕÆÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸Àû×¦[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁËÀû×¦[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }
