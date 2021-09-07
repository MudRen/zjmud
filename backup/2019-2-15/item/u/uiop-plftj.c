// ITEM Made by player(ºú·çÒİ:uiop) /data/item/u/uiop-plftj.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Mon Jan 28 11:33:03 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;33mÅÌÁú·½Ìì½£[2;37;0m", ({ "plftj" }));
	set_weight(9000);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;35mÉñÌú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
[1;36mÈı¹ú½£ÉñÍõÔ½ËùÓÃµÄ¾øÊÀÉñ±ø£¬ÖØËÄÊ®½ï£¬³¤Èı³ß¡£Õû±ú½£ÎªÌìÎªÔÉÌúÖı¾Í£¬½£Éí²Ê»æÅÌÁú¡£ÓÖ³Æ·½Ìì±¦½££¬¶ÔÊ¹ÓÃÕßµÄÒªÇó¼«¸ß¡£[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ººú·çÒİ(uiop)
");
	set("value", 2100000);
	set("point", 220);
	set("material", "magic stone");
	set("wield_msg", "[31m$NµÀ£º¡°ÌìÇåÇå£¬µØÃ÷Ã÷£¬ÇëÉñ½µÌ³ÕÕÌìÇå£¬½£ÉñÍõÔ½ËÙÏÔÁé£¬Áôµ½Ì³Ç°Éí»¯Éñ£¬Éñ»¯Éí£¬»¯ÆğÈÕÔÂÕÕ·ÖÃ÷£¬ÍõÔ½½£Éñ³ÏĞÄÇë£¬´ÍÎÒ±¦½£É¨ÇåÆ½¡£¡±[2;37;0m\n");
	set("unwield_msg", "$NËæÊÖÒ»Ä¨£¬ÊÕÆğÁË$n¡£\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
