// ITEM Made by player(ÎŞÄÎ:wsxc) /data/item/w/wsxc-sgsp.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Feb 14 22:38:30 2019
#include <ansi.h>
#include <weapon.h>

inherit HAMMER;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33mÊ¥¹âÉóÅĞ[2;37;0m", ({ "sgsp" }));
	set_weight(17500);
	set("item_make", 1);
	set("unit", "°Ñ");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»°Ñ´¸¡£
[1;33mÕâÊÇÊ¥ÆïÊ¿ÉóÅĞÒì¶ËµÄÎäÆ÷¡£[2;37;0m
´¸±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎŞÄÎ(wsxc)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "[1;33mÎªÁËÊ¥¹âÉóÅĞÄã¡£[2;37;0m\n");
	set("unwield_msg", "[1;33m$N²ÁÁË²ÁÕ½´¸ÉÏµÄÑª¼££¬¸ß¸ß¾ÙÆğÁËÕ½´¸£¬Ğû¸æËûµÄÈÙÒ«¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_hammer(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
