#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ľ��");
	set("long", @LONG
������һ�俴�ƺ���ͨ����ӣ�����ȴҪ��ͨ������Ӵ���������������
����һ��������ͷ��������ϱ�����һ���š�
LONG );
       set("exits", ([
		"south" : __DIR__"qingmu_dating",
		"west" : __DIR__"qingmu_dayuan",
	]));
	set("objects", ([
		__DIR__"npc/xutianchuan" : 1
	]));
	set("outdoors", "beijing");
	setup();
}

