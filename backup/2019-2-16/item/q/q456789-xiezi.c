// ITEM Made by player(ÌÆÈı:q456789) /data/item/q/q456789-xiezi.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 31 11:53:50 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36mĞÂ¶¡¿ìÑ¥[2;37;0m", ({ "xiezi" }));
	set_weight(420);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[1;37mÌì¾§[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«Ñ¥×Ó¡£
Ñ¥×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÌÆÈı(q456789)
");
	set("value", 6100000);
	set("point", 264);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[1;36mĞÂ¶¡¿ìÑ¥[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;36mĞÂ¶¡¿ìÑ¥[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
