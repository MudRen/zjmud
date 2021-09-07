// ITEM Made by player(Ğş°Ô:q2870406595) /data/item/q/q2870406595-ylx.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sun Feb  3 10:57:50 2019
#include <ansi.h>
#include <armor.h>

inherit ARMOR;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÑ×Áúîø¼×[2;37;0m", ({ "ylx" }));
	set_weight(45000);
	set("item_make", 1);
	set("unit", "ÕÅ");
	set("long", "ÕâÊÇÓÉ[36mĞşÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»ÕÅ»¤¼×¡£
ÁÒ»ğÖËÈÈÉıÌÚÎŞÏŞÁ¦Á¿£¬ÕÙ»½Õß¿É½èÓÉÑ×ÁúÕÙ»½Æ÷£¬·¢Éä»ğ¾§Ê¯Ö®¹âÄÜÁ¿£¬²¢½ÓÊÜ»ğÖ®Ñ×Áúîø¼×Íê³ÉºÏÌå£¬³ÉÎªîø¼×ÓÂÊ¿¡°Ñ×ÁúÏÀ¡±¡£[2;37;0m
»¤¼×ÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞş°Ô(q2870406595)
");
	set("value", 1500000);
	set("point", 123);
	set("material", "steel");
	set("wear_msg", "$nºÏÌå£¬Ò»ÕóàèÅ¾àèÅ¾±¬Ïì£¬Ñ×ÁúÏÀ½µÁÙ[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË[1;31mÑ×Áúîø¼×[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());
	set("armor_prop/parry", apply_armor() / 15 + 1);

	setup();
}

string long() { return query("long") + item_long(); }
