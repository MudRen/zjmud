#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��ٵ�");
	set("long", @LONG
������һ����������Ĵ�ٵ��ϡ���ʱ��������������߷ɳ۶�������
��һ·��������·��������������������֡�������Զ�����Ǿ�����������ʤ
ʮ�����ꡣ
LONG );
       set("exits", ([
		"north" : __DIR__"huangling",
		"south" : __DIR__"guandao_1",
	]));
	set("outdoors", "beijing");
	setup();
}

