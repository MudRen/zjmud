#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
���ֵ�������������Ͻ��ǵĽ�ͨҪ������������ʯ���������ͷ���죬
�ֵ������˲��ϣ�������ʢ�������Զ��������������ԶԶ����������һ��
�¸ߴ��ʵ�Ĺų�ǽ�������������찲�Ź㳡�ˡ������Ƿ�������������߲�
Զ����һ�ҹ�ģ����Ŀ͵ꡣ����Ľֵ�����խ������������ͬ�ĺ�ͬ���ˡ�
LONG );
       set("exits", ([
		"east" : __DIR__"caroad_w2",
		"west" : __DIR__"kedian",
		"north" : __DIR__"xi_1",
		"south" : __DIR__"yangliu1",
	]));
	set("objects", ([
		__DIR__"npc/kid1" : 1,
		__DIR__"npc/haoke1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

