#include <room.h>
inherit ROOM;

void create()
{
	set("short", "Τ������");
	set("long", @LONG
����һ��ľ�Ƶ����ȣ�������ǹ⻬����������һ����Ⱦ������Τ������
���ڴ��߶��������Ǹ��޴�Ļ�԰��
LONG );
       set("exits", ([
		"north" : __DIR__"weifu_dayuan",
		"east" : __DIR__"weifu_men",
	]));
	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}