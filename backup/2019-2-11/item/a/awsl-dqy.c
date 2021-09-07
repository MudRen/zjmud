// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-dqy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 13 10:31:12 2019
#include <ansi.h>
#include <armor.h>

inherit WAIST;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[35mĞ¡ÇÉµÄ¶ÇÆêÑÛ[2;37;0m", ({ "dqy" }));
	set_weight(1440);
	set("item_make", 1);
	set("unit", "Ìõ");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÌõÑü´ø¡£
[35mĞ¡ÇÉµÄ¶ÇÆêÑÛ[2;37;0m
Ñü´øÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 61);
	set("material", "silk");
	set("wear_msg", "±¾À´¾ÍÓĞ[2;37;0m\n");
	set("remove_msg", "È¡²»ÏÂÀ´[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
