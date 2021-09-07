// ITEM Made by player(ÌÆÈı:q456789) /data/item/q/q456789-gui.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan 19 16:42:56 2019
#include <ansi.h>
#include <weapon.h>

inherit AXE;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;36mĞÂ¶¡½£[2;37;0m", ({ "gui" }));
	set_weight(9900);
	set("item_make", 1);
	set("unit", "°Ñ");
	set("long", "ÕâÊÇÓÉ[37m¾«Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»°Ñ¸«¡£
¸«±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÌÆÈı(q456789)
");
	set("value", 700000);
	set("point", 66);
	set("material", "iron");
	set("wield_msg", "[1;36m$N[1;36mÒ»ÉùÇåĞ¥£¬¶¶³öÒ»°Ñ[1;36m$n[1;36m¡£[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_axe(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
