// ITEM Made by player(Ğş³½:zjzs123) /data/item/z/zjzs123-dyll.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 30 12:42:32 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("´óÒ¶ÁúÁé¼×[2;37;0m", ({ "dyll" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
ÆÕÍ¨µÄÒ»Åú[2;37;0m
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞş³½(zjzs123)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "silk");
	set("wear_msg", "µÂÂêÎ÷ÑÇ[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË´óÒ¶ÁúÁé¼×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
