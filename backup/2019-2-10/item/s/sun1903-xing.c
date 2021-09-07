// ITEM Made by player(ÃÎĞÇ:sun1903) /data/item/s/sun1903-xing.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Fri Feb  8 23:14:49 2019
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("[1;31mÃÎ÷Ê[2;37;0m", ({ "xing" }));
	set_weight(1050);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[1;37mÌì¾§[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
[1;36mÈç¾µ°ãµÄ½£ÉíÀäÆøÉ­É­Æ®³öÃÉÃÉº®Òâ£¬½£ÈĞÖĞ¼äÄı½á×ÅÒ»µãº®¹â·Â·ğ²»Í£µÄÁ÷¶¯£¬[1;31mÒª³ÉÎªÌìÏÂÈËµÄØ¬ÃÎ[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£ºÃÎĞÇ(sun1903)
");
	set("value", 6100000);
	set("point", 660);
	set("material", "silk");
	set("wield_msg", "[1;37m$N»º»º°Ñ$n[1;37m°Î³öÀ´Ö®Ê±£¬ÔÚÕâÉ²ÄÇÖ®¼ä£¬ËÆºõÊÇÎŞÊıµÄÔÆÎíÕÚ±ÎÁËÌìµØ£¬Ò»ÇĞÔÚÕâÉ²ÄÇÖ®¼äËÆºõ¶¼±äµÃÄÇÃ´µÄëüëÊ[2;37;0m\n");
	set("unwield_msg", "[1;34mÏÊÑª£¬Ò»µÎÒ»µÎÑØ×Å½£ÈĞ»®Âä£¬È¾ºìÁËÍÁµØ£¬Ö±µ½Á÷¾¡£¬ÄÇµÀºÚÉ«µÄÉíÓ°²Å°Ñ$n[1;34mÕâ±úĞ×Æ÷²åÈë½£ÇÊ[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
