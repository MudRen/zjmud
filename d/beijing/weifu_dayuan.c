#include <room.h>
inherit ROOM;

void create()
{
	set("short", "Τ����Ժ");
	set("long", @LONG
����¹����������ǰ���һ�������Ĵ�Ժ����Ժ����ֲ�Ÿ��໨�ݣ���ɽ
ˮ�أ���¥��̨���ǳ�������Ժ�ڴ�ɨ�÷ǳ��ɾ���Τ��������˴������У�
������һ��ľ�����ȣ�ͨ�������Ĵ�����
LONG );
       set("exits", ([
		"south" : __DIR__"weifu_zoulang1",
		"north" : __DIR__"weifu_zoulang2",
	]));
	set("objects", ([
		__DIR__"npc/yuanding" : 1,
	]));
	set("outdoors", "beijing");
	setup();
}