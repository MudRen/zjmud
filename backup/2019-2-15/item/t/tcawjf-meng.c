// ITEM Made by player(ÃÎÃÎ:tcawjf) /data/item/t/tcawjf-meng.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan  1 12:49:09 2019
#include <ansi.h>
#include <armor.h>

inherit HANDS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;34mÒ»ÃÎÇ§Äê[2;37;0m", ({ "meng" }));
	set_weight(2700);
	set("item_make", 1);
	set("unit", "Ë«");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»Ë«ÌúÕÆ¡£
Ç§Äê¼äÒ»Ë²¶ø¹ı£¬ÃÎÖĞµ¯Ö¸Ò»»Ó¼ä[2;37;0m
ÌúÕÆÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎÃÎ(tcawjf)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wear_msg", "Ëé¾õÀ²[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;34mÒ»ÃÎÇ§Äê[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/unarmed_damage", apply_damage());
	set("armor_prop/armor", 10);
	set("armor_prop/hand", 10);
	set("armor_prop/strike", 10);

	setup();
}

string long() { return query("long") + item_long(); }
