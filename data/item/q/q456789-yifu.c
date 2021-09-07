// ITEM Made by player(ÌÆÈı:q456789) /data/item/q/q456789-yifu.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 31 11:50:40 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36mĞÂ¶¡³¤ÉÀ[2;37;0m", ({ "yifu" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[1;37mÌì¾§[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÌÆÈı(q456789)
");
	set("value", 6100000);
	set("point", 660);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[1;36mĞÂ¶¡³¤ÉÀ[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;36mĞÂ¶¡³¤ÉÀ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
