// Room: /d/henshan/zhongting.c
#include <ansi.h>
inherit BUILD_ROOM;
void create()
{
	set("short", "��ͤ");
	set("long", @LONG
��ͤ��������һ�ڣ��ؾ�ǧ�ÿ��ɽ�鱩����������飬����ʾ
�������Ŷ�ʮ���⡣ 
LONG);
	set("max_room",2);
	set("exits", ([ /* sizeof() == 4 */
	   "west"   : __DIR__"kuixingge",
	]));
	set("no_clean_up", 0);
	setup();
	replace_program(BUILD_ROOM);
}

