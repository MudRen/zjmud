#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��̳����");
	set("long",  @LONG
��������̳�ı��ţ�վ�������Ѿ����������������̳�м�������ߵĽ�
�����������ഫÿ���ʵۼ���֮�����ǵ�����������������λߵͷ����
л�⡣����̳����������ͨ�������ķ����š�
LONG );
	set("exits", ([
		"south" : __DIR__"tiantan",
		"north" : __DIR__"tianqiao",
	]));
	set("objects", ([
		__DIR__"npc/girl2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

