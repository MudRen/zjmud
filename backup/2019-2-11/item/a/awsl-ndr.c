// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-ndr.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Wed Jan 30 11:07:02 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÄæµ¶ÈĞ[2;37;0m", ({ "ndr" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
[1;31m½£ÊÇĞ×Æ÷£¬½£¼¼ÊÇÉ±ÈËµÄ¼¿Á©£¬ÎŞÂÛÓÃÊ²Ã´´ÊÔåÈ¥ĞŞÊÎ£¬Õâ£¬Ê¼ÖÕÊÇÊÇÊÂÊµ[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "°Î³öÀ´£¬ÎÒĞÄÈçÌú[2;37;0m\n");
	set("unwield_msg", "·Å»ØÈ¥£¬½£´À´ÀÓû¶¯[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
