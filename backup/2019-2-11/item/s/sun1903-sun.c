// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-sun.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 02:00:26 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37mÃÎ»ê[2;37;0m", ({ "sun" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
[1;37mĞå×ÅÑÅÖÂÖñÒ¶»¨ÎÆµÄÑ©°×¹ö±ß£¬ÅÛ·şÑ©°×£¬Ò»³¾²»È¾£¬Á¬ÈÕ¹â¶¼²»ºÃÒâË¼ÁôÏÂ°ß²µµÄÊ÷Ó°[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "silk");
	set("wear_msg", "$NÄıÉñÒ»Ïë£¬Ò»Õó°×Ó°ÆÌÃæ¶øÀ´£¬$n»º»ºµÄ¸¡ÔÚÉíÉÏ[2;37;0m\n");
	set("remove_msg", "$NÉìÊÖÒ»»Ó£¬$nÏûÊ§²»¼û£¬²»½ûÁ¯Ï§ÆğÀ´[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
