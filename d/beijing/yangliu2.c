#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������ͬ");
	set("long", @LONG
������������ͬ������ߵ��������Խ���İ�����������խ��ͨ����
�ڲ��ϵ����ϱ����졣
LONG );
       set("exits", ([
		"north" : __DIR__"yangliu1",
		"south" : __DIR__"yangliu3",
	]));

	set("outdoors", "beijing");
	setup();
}

