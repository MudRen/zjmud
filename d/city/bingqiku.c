// Room: /city/bingqiku.c

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "±øÆ÷¿â");
	set("long", @LONG
ÕâÀïÊÇ±øÆ÷¿â£¬µ½´¦Òø¹âÉÁÉÁ£¬ÈÃÈËÑÛ»¨çÔÂÒ¡£±¦µ¶¡¢±¦½£¡¢½ð¹¿°ô£¬´ó
µ¶¡¢³¤½£¡¢ÉÚ°ô£¬¶Ìµ¶¡¢¶Ì½£¡¢¶Ì¹÷£¬¸÷É«¸÷ÑùµÄ±øÆ÷Ó¦ÓÐ¾¡ÓÐ£¬ÄãÒ»Ê±²»Öª
µÀÌôÊ²Ã´ºÃ¡£
LONG );
	set("exits", ([
		"north" : __DIR__"bingyin",
	]));
	set("no_clean_up", 0);
	create_door("north", "ÌúÃÅ", "south", DOOR_CLOSED);
	setup();
}