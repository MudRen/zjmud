#include <room.h>
inherit ROOM;

void create()
{
	set("short", "Τ���鷿");
	set("long", @LONG
������Τ��ү���鷿�����������������������һ���ľ������������
һ�����߸ߵĻ�ͭ��¯�����ܵ�����϶ѷ����˸����鼮�����������׿�����
���ܾ�û�˶����ˡ�
LONG );

	set("exits", ([
		"south" : __DIR__"weifu_dating",
	]));
	set("objects", ([
		__DIR__"npc/shizhe" : 1,
	]));
	setup();
}
