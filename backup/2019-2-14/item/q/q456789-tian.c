// ITEM Made by player(ÌÆÈı:q456789) /data/item/q/q456789-tian.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 19 16:48:26 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36mĞÂ¶¡½£[2;37;0m", ({ "tian" }));
	set_weight(245);
	set("item_make", 1);
	set("unit", "Ì×");
	set("long", "ÕâÊÇÓÉ[1;37mÌì¾§[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ì×Ö¸Ì×¡£
Ö¸Ì×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÌÆÈı(q456789)
");
	set("value", 6100000);
	set("point", 660);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[1;36mĞÂ¶¡½£[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;36mĞÂ¶¡½£[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/finger", 10);
	set("armor_prop/claw", 10);
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);

	setup();
}

string long() { return query("long") + item_long(); }
