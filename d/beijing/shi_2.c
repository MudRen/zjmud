#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���ı����");
	set("long", @LONG
�����Ǿ��ǵ����ı���֣���ʯ������·��ͨ�ϱ����ֵ��ϵ�����������
��������һ�������Ĵ�ٵ������������ϣ������������ͨ�������ϴ�ֽ�
��������֡�
LONG );
       set("exits", ([
		"north" : __DIR__"shi_3",
		"south" : __DIR__"shi_1",
		"west" : __DIR__"guandao_1",
	]));
	set("objects", ([
		__DIR__"npc/boy1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

