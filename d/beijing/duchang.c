#include <room.h>
inherit ROOM;

void create()
{
	set("short", "�����ĳ�");
	set("long", @LONG
������Ǳ����������ĺ����ĳ������ܵĶķ��ﴫ����ߺ������ĶĲ�
��������ĳ���ģ���㲻�Ϻܴ�, ���ĵ�����ȴ����ȫ, ����Ҳ�ǳ��ܵ�����
���, ���ϵĸ��и�ɫ���˼�����һ��, ���������ĸ����ӵ�, Ҳ����ö�
�����������õ��佣�ĵĽ�������, Ҳ�е���ॵ�����å�������йٸ���
����, Ҳ�����ӵķ��ˡ�
LONG );
       set("exits", ([
		"south" : __DIR__"yong_1",
	]));
	set("objects", ([
		__DIR__"npc/duke" : 2,
		__DIR__"npc/liumang" : 1,
		__DIR__"npc/haoke1" : 1,
		__DIR__"npc/dipi" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

