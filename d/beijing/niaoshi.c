#include <room.h>
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
��һ�ߵ�����������������ɸ��ָ���������Ľ�����֯�ɵĶ�����
����������Կ����ܶྩ�������Ż����Ĺ��Ӹ�������ﾫ��ϸѡ��һ����
��ͷ���棬ƽʱ���¿������Ϳ���Щ�����Ż����ӡ�
LONG );
       set("exits", ([
		"east" : __DIR__"xi_1",
		"west" : __DIR__"majiu",
	]));
	set("objects", ([
		__DIR__"npc/richman1" : 1,
		__DIR__"npc/shusheng2" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

