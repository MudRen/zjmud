#include <room.h>
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
���ֵ�������������Ͻ��ǵĽ�ͨҪ������������ʯ���������ͷ���죬
�ֵ������˲��ϣ�������ʢ�������Զ��������������ԶԶ����������һ��
�¸ߴ��ʵ�Ĺų�ǽ�������������찲�Ź㳡�ˡ�������ת�����������ˣ���
Ҳ�Ǿ�����ķ����ضΡ��ϱ߲����ﲻʱ����һ�������ӵĳ�������
LONG );
       set("exits", ([
		"west" : __DIR__"caroad_w1",
		"east" : __DIR__"cagc_w",
		"north" : __DIR__"xi_2",
		"south" : __DIR__"gaosheng",
	]));
	set("objects", ([
		__DIR__"npc/boy2" : 1,
		__DIR__"npc/richman1" : 1,
		__DIR__"npc/shusheng1" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

