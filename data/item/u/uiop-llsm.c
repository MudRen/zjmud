// ITEM Made by player(ºú·çÒİ:uiop) /data/item/u/uiop-llsm.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Feb 11 15:16:11 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33mÁáççÊ¨Âù¼×[2;37;0m", ({ "llsm" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
Õ½Éñ¼×ëĞÕ½ÉñÂÀ²¼Ëù´©µÄîø¼×£¬ÓÉÈı²¿·Ö×é³ÉÈıÎªÀÕ¼×ÁáççÊ¨Âù¼×£¬ÒòÆäÍÈ¼×²»ÏÔ£¬ÊÀÈËÎóÒÔÎªÖ»ÓĞÑü´ø£¬ËùÒÔ£¬ÓÖÃûÀÕ¼×ÁáççÊ¨Âù´ø¡£[2;37;0m
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ººú·çÒİ(uiop)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "$NµÀ¡°Ìì·êÃÅÏÂ£¬Õ½ÉñÂÀ²¼£¬´İÄ§·¥¶ñ£¬Ó¥È®µ±ÏÈ£¬¶ş½«ÎÅÕÙ£¬Á¢ÖÁÌ³Ç°£¬ÒÀÂÉ·îÁî£¬Éñ¹¦µÛĞû£¬Ä§ÑıÍò¹í£¬ÖïÕ½ÎŞ¸Ç£¬Ì«ÉÏÊ¥Á¦£¬ºÆµ´ÎŞ±ß£¬¼±¼±·î±±µÛÂÉÁî¡£¡±[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;33mÁáççÊ¨Âù¼×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
