#include <ansi.h>

inherit ROOM;

void create()
{
	set("short", "��Ӣ��¥��¥");
	set("long", @LONG
��¥�����νྻ�����п������κ��ݣ�ʮ���Ǹ��̴�֡�������Ը����
���Ͻ��ǵ�ȫ����
LONG );
	set("exits", ([
		"down" : __DIR__"huiying",
	]));
	set("objects", ([
		"/d/tulong/yitian/npc/zhaomin2" : 1,
		"/d/tulong/yitian/npc/zhao1" : 1,
		"/d/tulong/yitian/npc/qian2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}
