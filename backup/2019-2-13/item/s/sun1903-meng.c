// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-meng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Jan 27 21:34:30 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÃÎ÷Ê[2;37;0m", ({ "meng" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "[1;31mÔ¶¹ÅµÄÒ»¸öÀèÃ÷£¬ÌìÉ«ºÚ°×½»¼ÊµÄÒ»Ë²¼ä£¬Ò»Ë«ÊÖ»º»ºÑïÆğ¡£Ë«ÊÖºÏÎÕÖ®ÖĞÊÇÒ»½Ø½£±ú£¬Ö»ÓĞ½£±ú²»¼û³¤½£½£Éí[2;37;0m\n");
	set("unwield_msg", "[1;33m$NÖ±µ½ÔÙÕÒ²»µ½¶ÔÊÖ£¬²ÅÊÕ²ØÆğ×Ô¼ºµÄ½£·æ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
