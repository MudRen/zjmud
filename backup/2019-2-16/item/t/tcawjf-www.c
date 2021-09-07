// ITEM Made by player(ÃÎÃÎ:tcawjf) /data/item/t/tcawjf-www.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan  5 19:59:19 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("[2;37;0m[36mÅåç÷[2;37;0m", ({ "www" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎÃÎ(tcawjf)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "Ğ¡ÖíÅåÆæÉíÉÏÎÆ£¬´Ó´Ë¾ÍÊÇÉç»áÈË[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[2;37;0m[36mÅåç÷[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
