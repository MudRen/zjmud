// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-yan.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:17:06 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;32mÃÎÑÔ[2;37;0m", ({ "yan" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÌõÑü´ø¡£
[1;32mÑüÊøÔÂ°×ÏéÔÆÎÆµÄ¿íÑü´ø£¬ÆäÉÏÖ»¹ÒÁËÒ»¿éÓñÖÊ¼«¼ÑµÄÄ«Óñ£¬ĞÎ×´¿´ËÆ´Ö²ÚÈ´¹ÅÆÓ³ÁÓô[2;37;0m
Ñü´øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[1;32mÃÎÑÔ[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;32mÃÎÑÔ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
