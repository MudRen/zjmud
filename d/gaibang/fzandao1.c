// Room: /d/gaibang/fzandao1.c
// Date: Haa 96/03/22

#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
����ؤ�Ｋ�����ܵĵ���ͨ��������ؤ�Ｘ����֮��Ѫ��ɡ� 
LONG );
	set("exits", ([
		"southeast" : __DIR__"fzandao2",
		"northwest" : __DIR__"undertre",
	]));
	set("no_clean_up", 0);
	setup();
}
