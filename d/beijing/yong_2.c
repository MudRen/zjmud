#include <room.h>
inherit ROOM;

void create()
{
	set("short", "���ڶ���");
	set("long", @LONG
���ڶ�����һ�������Ĵ�֣�Ҳ�Ǳ��������ҵĵضΡ�һ����������ʯ��
�����д�����������ͷ���졣�����Ǿ����������ķ����š��ӱ���Ʈ��һ��
�����˵Ļ��㣬��ʱ��ľ���Ϊ֮һ���ϱ���һ��������, ��ʱ����������
�˵��ô�����
LONG );
	set("exits", ([
		"south" : __DIR__"tiepu",
		"north" : __DIR__"huadian",
		"east" : __DIR__"yong_3",
		"west" : __DIR__"yong_1",
	]));

	set("outdoors", "beijing");
	setup();
}

