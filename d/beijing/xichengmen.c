#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�����Ǿ��ǵ������ţ���ʵ��̵Ĺų�ǽ�߸������š��������������վ
�ż�����������ϸ�ļ��������ÿ�춼������˾���������뾩�ǡ�������
���ţ�һ����ֱ�Ĵ�ٵ������������졣���ߵĹٵ��������������������
��������ͨ�����ǵ���������֡�
LONG );
	set("exits", ([
		"east" : __DIR__"ximenkou",
		"west" : __DIR__"ximenwai",
	]));
	set("objects", ([
		__DIR__"npc/ducha" : 1,
		__DIR__"npc/bing1" : 2,
		__DIR__"npc/tangzi" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

