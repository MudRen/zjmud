#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���᷿");
	set("long", @LONG
�����ǿ�����������ߵ�һ���᷿���ǹ������Ŀ��˾�ס�ġ�����վ��һ
������ݸߵ���ʦ�����ֱ��������ƺ���һ����书��
LONG );
	set("exits", ([
		"east" : __DIR__"kangfu_zoulang2",
	]));

	set("objects", ([
		__DIR__"npc/qiyuankai" : 1,
	]));

	set("sleep_room", "1");
	set("outdoors", "beijing");
	setup();
}
