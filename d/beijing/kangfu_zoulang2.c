#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
����һ��ľ�Ƶ����ȣ�������ǹ⻬����������һ����Ⱦ��������������
���ڴ��߶����ϱ��ǿ����Ĵ��������������������᷿�������ǿ��������鷿
���ڡ�����վ��һ��ͺͷ���У����ǿ���������ͷ�졣
LONG );
       set("exits", ([
		"north" : __DIR__"kangfu_shufang",
		"south" : __DIR__"kangfu_dating",
		"west" : __DIR__"kangfu_xifang",
		"east" : __DIR__"kangfu_dongfang",
	]));
	set("objects", ([
		__DIR__"npc/jiading_k" : 1,
		__DIR__"npc/yahuan_k" : 1,
		__DIR__"npc/shenzhao" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}