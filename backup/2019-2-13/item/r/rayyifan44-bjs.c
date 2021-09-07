// ITEM Made by player(³Îºú:rayyifan44) /data/item/r/rayyifan44-bjs.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Jan  4 22:12:32 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("°×ôÂôÄ[2;37;0m", ({ "bjs" }));
	set_weight(1050);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º³Îºú(rayyifan44)
");
	set("value", 2100000);
	set("point", 176);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸°×ôÂôÄ[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË°×ôÂôÄ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
