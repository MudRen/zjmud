// ITEM Made by player(¶À¹ÂÂÜÀò:awsl) /data/item/a/awsl-bsw.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Thu Jan 10 11:43:25 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;37m°×Ë¿³¤ÊÖÌ×[2;37;0m", ({ "bsw" }));
	set_weight(2500);
	set("item_make", 1);
	set("unit", "¶Ô");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶Ô»¤Íó¡£
[1;37m±¡±¡µÄÊÖÌ×[2;37;0m
»¤ÍóÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º¶À¹ÂÂÜÀò(awsl)
");
	set("value", 1500000);
	set("point", 37);
	set("material", "steel");
	set("wear_msg", "´©ÉÏ[2;37;0m\n");
	set("remove_msg", "ÍÑÏÂ[2;37;0m\n");
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
