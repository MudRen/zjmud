#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�����ϴ��");
	set("long", @LONG
�����Ǿ��ǵ������ϴ�֣���ʯ������·��ͨ�ϱ���������ש������ͬҲ
����������ϡ��ֵ��ϵ����������������Ϸ��Ӿ��ǵ���������֣���������
�ı���֡�
LONG );
       set("exits", ([
		"north" : __DIR__"shi_2",
		"south" : __DIR__"bei_3",
	]));
	set("objects", ([
		__DIR__"npc/liumang" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

