// ITEM Made by player(ÒÁÀûµ¤:m2376182530) /data/item/m/m2376182530-emzy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Tue Dec 18 21:46:53 2018
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("¶ñÄ§Ö®Òí[2;37;0m", ({ "emzy" }));
	set_weight(1400);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[1;37m±ù²ÏË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
ÎüÊÕÁË¹Å¶ûµ¤Ö®Â­Ö®ºó£¬ÒÁÀûµ¤³¤³öÁË¶ñÄ§µÄË«Òí¡£[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÒÁÀûµ¤(m2376182530)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "silk");
	set("wear_msg", "ÆáºÚµÄÓğÒíÅÄ´ò×Å£¬Ê®·ÖµÄ²»°²·Ö¡£[2;37;0m\n");
	set("remove_msg", "$N½«ÓğÒíÊÕºÃ¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
