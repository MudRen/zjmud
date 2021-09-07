// ITEM Made by player(ÎÊÌì:wentianaa) /data/item/w/wentianaa-wan.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Jan 22 22:13:15 2019
#include <ansi.h>
#include <armor.h>

inherit WRISTS;
inherit F_ITEMMAKE;

void create()
{
	set_name("»¤Íó[2;37;0m", ({ "wan" }));
	set_weight(2500);
	set("item_make", 1);
	set("unit", "¶Ô");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¶Ô»¤Íó¡£
»¤ÍóÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÎÊÌì(wentianaa)
");
	set("value", 1500000);
	set("point", 17);
	set("material", "steel");
	set("wear_msg", "[33m$N[33m×°±¸»¤Íó[2;37;0m[33m¡£[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË»¤Íó[2;37;0m[33m¡£[2;37;0m\n");
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
