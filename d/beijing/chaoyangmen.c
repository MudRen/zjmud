#include <room.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
������Ǿ��ǵĳ������ˣ���ǽ�Ͽ��š������š��������֡���������ͨ
��������������������֡����������������ǽ������ǵ�Ҫ������������վ��
�˹ٱ����̲�ʮ�����ܡ�һ�������Ĵ�����Ŷ����������죬��������ǵ���
���ǵĶ�����
LONG );
       set("exits", ([
	      "east" : __DIR__"road1",
		"west" : __DIR__"chaoyang_dao2",
	]));

	set("objects", ([
		__DIR__"npc/ducha" : 1,
		__DIR__"npc/bing1" : 2,
	]));

	set("outdoors", "beijing");
	setup();
}
