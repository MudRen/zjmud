#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
�����Ǿ��ǵĻ���·�������ӷ����š�ֻҪ����������Ǯ����������ͻ�
�ܵ�������к����κ��㲻֪�����£����������һ�£�������֪�����˾Ų�
��ʮ�������ڽִ���һ�Ҳ���Ŀ�ջ���ϱ���һ���޴��լԺ������ĳ�����
���˾�ס�ĳ�����
LONG );
	set("exits", ([
		"south" : __DIR__"hai_men",
		"north" : __DIR__"fukedian",
		"east" : __DIR__"tianqiao",
		"west" : __DIR__"fu_1",
	]));
	set("objects", ([
		__DIR__"npc/haoke1" : 1,
		__DIR__"npc/girl2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

