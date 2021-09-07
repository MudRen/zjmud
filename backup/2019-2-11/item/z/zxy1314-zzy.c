// ITEM Made by player(·ò²î¸ç¸ç:zxy1314) /data/item/z/zxy1314-zzy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan  2 10:22:15 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("ÖËÑ×ĞıÁ÷ÒÂ[2;37;0m", ({ "zzy" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
Á÷Ñ×±é²¼[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º·ò²î¸ç¸ç(zxy1314)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "Ëü½«ÅãÄãÕ÷Õ½ÎäÁÖ[2;37;0m\n");
	set("remove_msg", "¸ÃĞİÏ¢ÁË[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
