#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���ڶ���");
	set("long", @LONG
���ڶ�����һ�������Ĵ�֣�Ҳ�Ǳ��������ҵĵضΡ�һ����������ʯ��
�����д�����������ͷ���졣�����Ǿ����������ķ����š�������һ�Һ���
�Ĵ�ĳ�����ʱ�������洫��һ���󲻿�������������ϱ��ǻ�Ӣ��¥���ھ�
���У�Ҳ����С�������ġ�
LONG );
	set("exits", ([
		"south" : __DIR__"huiying",
		"north" : __DIR__"duchang",
		"east" : __DIR__"yong_2",
		"west" : __DIR__"tianqiao",
	]));
	set("objects", ([
		__DIR__"npc/dipi" : 1,
		__DIR__"npc/boy1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

