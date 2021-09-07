// ITEM Made by player(³Î³½:zjzs123) /data/item/z/zjzs123-fgjs.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Dec 18 22:04:35 2018
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31m·ğ¹âôÂôÄ[2;37;0m", ({ "fgjs" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
·ğ×æÉíÉÏÒÂ£¬ÓĞÔµÈËµÃÖ®[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º³Î³½(zjzs123)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "[1;31mÖÚÉú½ÔÆ½µÈ[2;37;0m\n");
	set("remove_msg", "[1;31m°¢ÃÖÍÓ·ğ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
