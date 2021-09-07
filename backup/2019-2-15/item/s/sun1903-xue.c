// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-xue.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 15 22:02:16 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;35mÃÎÑ©[2;37;0m", ({ "xue" }));
	set_weight(2500);
	set("item_make", 1);
	set("unit", "¶Ô");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶Ô»¤Íó¡£
[1;35m°ÑÔÂ¹âËºÁÑ¿ª£¬ÓÃÆäÖĞ¾«»ª´òÔì£¬À´±£»¤×Ô¼º[2;37;0m
»¤ÍóÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 1500000);
	set("point", 37);
	set("material", "steel");
	set("wear_msg", "[1;35mÔÂ»ª¾ÛÔÚÊÖÍóÉÏÄı³É[2;37;0m\n");
	set("remove_msg", "[1;35mÔÂ»ªÈ÷Âä[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/claw", apply_armor() / 6 + 1);
	set("armor_prop/armor", apply_armor());
	set("armor_prop/sword", apply_armor() / 6 + 1);
	set("armor_prop/blade", apply_armor() / 6 + 1);
	set("armor_prop/club", apply_armor() / 6 + 1);
	set("armor_prop/hand", apply_armor() / 6 + 1);
	set("armor_prop/strike", apply_armor() / 6 + 1);
	set("armor_prop/dagger", apply_armor() / 6 + 1);
	set("armor_prop/cuff", apply_armor() / 6 + 1);
	set("armor_prop/finger", apply_armor() / 6 + 1);
	set("armor_prop/staff", apply_armor() / 6 + 1);
	set("armor_prop/parry", apply_armor() / 6 + 1);
	set("armor_prop/stick", apply_armor() / 6 + 1);
	set("armor_prop/hammer", apply_armor() / 6 + 1);
	set("armor_prop/unarmed", apply_armor() / 6 + 1);
	set("armor_prop/whip", apply_armor() / 6 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
