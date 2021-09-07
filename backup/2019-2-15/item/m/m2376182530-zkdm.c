// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-zkdm.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 22:59:59 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[35mÔú¿¨¶ÅÄ·[2;37;0m", ({ "zkdm" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÌõÑü´ø¡£
[1;36mÔ­±¾ÊÇÒ»Ö»Ãû½Ğ[35mÔú¿¨¶ÅÄ·[1;36mµÄµØÓüÈ®£¬µ«±»ÒÁÀûµ¤´ò°Üºó£¬±»ÄÃÀ´´ò³ÉÁËÒ»¼ş×°±¸¡£[2;37;0m
Ñü´øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "µØÓüÈ®°§º¿×Åµ¹ÏÂÁË¡£[2;37;0m\n");
	set("remove_msg", "Ôú¿¨¶ÅÄ·ÒÑ²»ÔÙ»Ô»Í¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
