// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-xien.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan 11 11:37:47 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("Ğ°ÄÜ»ğÑæ[2;37;0m", ({ "xien" }));
	set_weight(700);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ìõ¿ã×Ó¡£
Ğ°ÄÜÊÇÒ»ÖÖ¿ÉÅÂµÄÁ¦Á¿£¬ËüĞÎ³ÉµÄ»ğÑæ¿ÉÒÔ×ÆÉÕÁé»ê¡£[2;37;0m
¿ã×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 2100000);
	set("point", 110);
	set("material", "silk");
	set("wear_msg", "±ÌÂ¶µÄ»ğÑæÈ¼ÉÕ£¬ÈËÃÇ¸Ğ¾õ×Ô¼ºµÄÁé»ê·Â·ğ¹éÓÚÅ¤ÇúĞé¿Õ¡£[2;37;0m\n");
	set("remove_msg", "Ğ°ÄÜ»ğÑæÏ¨ÃğÁË£¬¶ñÄ§ÁÔÊÖ¿´ÆğÀ´ÓĞĞ©ĞéÈõ¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
