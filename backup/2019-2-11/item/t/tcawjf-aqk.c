// ITEM Made by player(ÃÎÃÎ:tcawjf) /data/item/t/tcawjf-aqk.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 17:48:15 2019
#include <ansi.h>
#include <armor.h>

inherit PANTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[36m°²È«¿ã[2;37;0m", ({ "aqk" }));
	set_weight(1800);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ìõ¿ã×Ó¡£
¿ã×ÓÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎÃÎ(tcawjf)
");
	set("value", 1500000);
	set("point", 77);
	set("material", "silk");
	set("wear_msg", "[33m$N[33m×°±¸[2;37;0m[36m°²È«¿ã[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[36m°²È«¿ã[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
