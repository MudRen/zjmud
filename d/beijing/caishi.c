#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���ֲ���");
	set("long", @LONG
�����Ǿ���������������ߵ�һ�����У���ʯ�������ŵ��档�ֵ����߰�
�����߲�̯��ˮ��̯, С���Ŵ���ߺ���ţ����ǵİ��ն��Ǵ������ÿ������
��ʳ�ﹺ��, ����һ�ٶٿɿڵļ��ȡ�
LONG );
       set("exits", ([
		"east" : __DIR__"bei_3",
	]));
	set("objects", ([
		__DIR__"npc/caifan" : 1,
		__DIR__"npc/jumin1" : 2,
	]));
	set("outdoors", "beijing");
	setup();
}

