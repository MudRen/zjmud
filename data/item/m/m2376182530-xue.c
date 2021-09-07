// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-xue.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 18 14:25:52 2019
#include <ansi.h>
#include <armor.h>

inherit BOOTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[31mÏÊÑªÖ®×ã[2;37;0m", ({ "xue" }));
	set_weight(18000);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[36mĞşÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«Ñ¥×Ó¡£
[1;36mËäÈ»ÊÇ±ù¹Ú±¤ÀİµÄÎüÑª¹íÃÇµÄ×°±¸£¬µ«ÓĞÊ±ºò¶ñÄ§ÁÔÊÖÒ²²»½éÒâ½èÀ´´©´©¡£[2;37;0m
Ñ¥×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸[2;37;0m[31mÏÊÑªÖ®×ã[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[31mÏÊÑªÖ®×ã[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/dodge", apply_armor() / 10 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
