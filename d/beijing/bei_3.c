#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���������");
	set("long", @LONG
�����Ǳ����ǵ���������֣������Ĵ�����ϱ��������졣�ֵ��ϵ�����
����������о������������ٱ����������Լ�С��С����ߺ�������ϣ�������
�����У��������֡����������ֵı��ֲ��У��������������ϴ���ˡ�
LONG );
       set("exits", ([
		"east" : __DIR__"bei_4",
		"west" : __DIR__"caishi",
		"north" : __DIR__"shi_1",
		"south" : __DIR__"bei_1",
	]));
	set("objects", ([
		__DIR__"npc/girl3" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

