#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����������������Ҳ�Ǿ�����ķ����ضΡ�����������ʮ�����֡�����
��Ȼ�࣬����ֻ�Ĵ����ƣ��Ŷ������������Ҳ��������ʲô�����ұ�Ʈ��
һ��ŨŨ��ҩ����ζ��������������ġ��ش��á�ҩ���ˡ��������˴ӱ�����
�����ƺ�����Ҳͦ���֡��ϱ����Ǿ��������������֡�
LONG );
       set("exits", ([
		"east" : __DIR__"huichuntang",
		"west" : __DIR__"xi_1",
		"north" : __DIR__"bei_2",
		"south" : __DIR__"caroad_w2",
	]));
	set("objects", ([
		__DIR__"npc/boy3" : 1,
		__DIR__"npc/xiaofan" : 1,
		__DIR__"npc/girl2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

