// ITEM Made by player(ÎÊÌì:wentianaa) /data/item/w/wentianaa-zhang.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:25:39 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33mÈçÀ´ÉñÕÆ[2;37;0m", ({ "zhang" }));
	set_weight(2250);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«ÌúÕÆ¡£
[1;33mÒ»ÕÆ³ö£¬ÍòÎïÍË¡£[2;37;0m
ÌúÕÆÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎÊÌì(wentianaa)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wear_msg", "$n[1;33m´ÓÌì¶ø½µ[2;37;0m\n");
	set("remove_msg", "$n[1;33mÏûÊ§²»¼û[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }
