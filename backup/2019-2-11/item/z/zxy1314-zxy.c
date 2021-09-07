// ITEM Made by player(·ò²î¸ç¸ç:zxy1314) /data/item/z/zxy1314-zxy.c
// Written by GAN JIANG(Doing Lu 1998/11/2)	Sat Dec 22 15:34:14 2018
#include <ansi.h>
#include <weapon.h>

inherit SWORD;
inherit F_ITEMMAKE;

void create()
{
	set_name("ÁúÔ¨[2;37;0m", ({ "zxy" }));
	set_weight(7500);
	set("item_make", 1);
	set("unit", "±ú");
	set("long", "ÕâÊÇÓÉ[37mÉÏ¹Åº®Ìú[2;37;0mÁ¶ÖÆ¶ø³ÉµÄÒ»±ú½£¡£
½£Èç°×ÉßÍÂĞÅ£¬Ë»Ë»ÆÆ·ç£¬ÓÖÈçÓÎÁú´©Ëó£¬ĞĞ×ßËÄÉí£¬Ê±¶øÇáÓ¯ÈçÑà£¬µã½£¶øÆğ£¬Ê±¶øÖèÈçÉÁµç£¬ÂäÒ¶·×±À¡£[2;37;0m
½£±úÉÏ¿Ì×ÅÒ»ĞĞĞ¡×Ö£º·ò²î¸ç¸ç(zxy1314)
");
	set("value", 1500000);
	set("point", 154);
	set("material", "steel");
	set("wield_msg", "ÎâÍõÉìÊÖÒ»¶¶£¬ÊÖÌáÈı³ßÁúÈª½£²»Õ¶¼éĞ°ÊÄ²»Ğİ[2;37;0m\n");
	set("unwield_msg", "½£Æø³åĞÇ¶·£¬ÎÄ¹âÉäÈÕºç¡£[2;37;0m\n");
	if (! check_clone()) return;
	restore();
	init_sword(apply_damage());

	setup();
}

string long() { return query("long") + item_long(); }
