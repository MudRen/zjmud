#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
�������Ͻ��Ǳ��߿������ŵ�һ�������Ĵ�����Ϸ���Զ���Ǿ��ǵ�����
���ˣ���ʵ��̵Ĺų�ǽ�߸������š�ÿ�춼������˾�������������뾩�ǡ�
�����򾭹���̳ͨ�����ǵ����ġ�
LONG );
	set("exits", ([
		"north" : __DIR__"tiantan",
		"south" : __DIR__"yongdingmen",
	]));
	set("objects", ([
		__DIR__"npc/tiaofu" : 1,
		__DIR__"npc/kid1" : 1,
		__DIR__"npc/tangzi" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}

