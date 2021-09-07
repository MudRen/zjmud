// ITEM Made by player(ºú·çÒİ:uiop) /data/item/u/uiop-hsp.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 20 10:47:04 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[31mºì½õ»ğÊ¥ÅÛ[2;37;0m", ({ "hsp" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
[31mÕâÊÇÒ»¼ş»ğºìÕ½ÅÛ£¬ÒşÒşÔ¼Ô¼¿ÉÒÔ¿´³öÕâÔøÎªÒ»¼ş¶Ç¶µ¡£[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ººú·çÒİ(uiop)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "[31m$NµÀ¡°ÏãÆø³Á³ÁÓ¦Ç¬À¤£¬È¼ÆğÇåÏãÍ¸ÌìÃÅ£¬ÉñÁú½ÅÆßĞÇ²½£¬Éí´©»¤Ìåºì¶Ç¶µ£¬ÊÖ³ÖÅùö¨ºìÓ§Ç¹£¬Í¨ÌìÕğµØ¹íÉñ¾ª£¬ÉÏÌìÏÂµØ¼ûÕæÉí£¬½÷Çëºìº¢¶ù½µÁÙ¡£¡±[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[31mºì½õ»ğÊ¥ÅÛ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
