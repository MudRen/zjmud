// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-loser.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 17:28:54 2019
#include <ansi.h>
#include <armor.h>

inherit HEAD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[31mÃÎĞÑ[2;37;0m", ({ "loser" }));
	set_weight(3750);
	set("item_make", 1);
	set("unit", "¶¥");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶¥Í·¿ø¡£
[1;36mÒ»¶¥ÂÌéÅ¶ìÃ«Ã±ÏÂ¿¡Ã¼ĞŞÑÛ£¬¹ËÅÎÉñ·É£¬ÔÆ÷Ù¶ë¶ë£¬¼ûÖ®ÍüË×[2;37;0m
Í·¿øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸[2;37;0m[31mÃÎĞÑ[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[31mÃÎĞÑ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
