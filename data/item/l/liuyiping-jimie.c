// ITEM Made by player(ĞşÎò:liuyiping) /data/item/l/liuyiping-jimie.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Jan  5 14:35:02 2019
#include <ansi.h>
#include <armor.h>

inherit CLOTH;
inherit F_ITEMMAKE;

void create()
{
	set_name("¼ÅÃğ[2;37;0m", ({ "jimie" }));
	set_weight(3600);
	set("item_make", 1);
	set("unit", "¼ş");
	set("long", "ÕâÊÇÓÉ[33mÎÚ½ğË¿[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»¼şÕ½ÒÂ¡£
°×É«µÄ·çÒÂÉÏĞ´×ÅÒ»¸ö´ó´óµÄÃğ×Ö[2;37;0m
Õ½ÒÂÔµÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºĞşÎò(liuyiping)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "silk");
	set("wear_msg", "[1;37mÖÜÎ§µÄ³¾°£¶¼Æ½¾²ÏÂÀ´ÁË[2;37;0m\n");
	set("remove_msg", "[33m$N[33mÍÑÏÂÁË¼ÅÃğ[2;37;0m[33m¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	set("armor_prop/armor", apply_armor());

	setup();
}

string long() { return query("long") + item_long(); }
