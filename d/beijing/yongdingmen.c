#include <room.h>
#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
���������Ͻ��������ţ��ߴ�ĳ������Ϸ����š������š��������֣���
ʵ��̵Ĺų�ǽ�߸������š��������������վ�ż�����������ϸ�ļ�������
�ÿ�춼������˾���������뾩�ǡ����������ţ�һ����ֱ�Ĵ�ٵ�����
���������졣�ϱߵĹٵ����������������������������ͨ�����ǵ����ġ�
LONG );
	set("exits", ([
		"north" : __DIR__"yongdingdao",
		"south" : __DIR__"road5",
	]));
	set("objects", ([
		__DIR__"npc/ducha" : 1,
		__DIR__"npc/bing1" : 2,
	]));
	set("outdoors", "beijing");
	setup();
}
