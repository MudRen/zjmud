// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-axns.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Dec 30 21:27:57 2018
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("°£ĞÁÅµË¹Õ½ÈĞ[2;37;0m", ({ "axns" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
ÕâÔ­±¾ÊÇÒ»¸ö½Ğ°£ĞÁÅµË¹µÄ¶ñÄ§µÄÎäÆ÷£¬µ«Ëû±»É±ËÀºó£¬ÒÁÀûµ¤ÄÃ×ßÁËËûµÄÎäÆ÷¡£Õâ¶ÔÕ½ÈĞÉ¢·¢×ÅĞ°ÄÜµÄÆøÏ¢¡£[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "¶ñÄ§µ¹ÏÂÁË£¬ËûµÄÎäÆ÷±»$NµÃµ½ÁË[2;37;0m\n");
	set("unwield_msg", "$N½«Õ½ÈĞÊÕÁËÆğÀ´[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
