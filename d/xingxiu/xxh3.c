// Room: /d/xingxiu/xxh3.c
// Jay 3/18/96

inherit ROOM;

void create()
{
	set("short", "���޺�");
	set("long", @LONG
���������޺��ߡ�˵�Ǻ�����ʵ��Ƭ���������󣬵���ʮ���ն�
����ͨ�����޺������
LONG );
	set("objects", ([
		"/kungfu/class/xingxiu/tianlang"  : 1,
	]) );
	set("exits", ([
	     "southwest" : __DIR__"xxh2",
	     "northwest" : __DIR__"xxh5",
	]));
	set("outdoors", "xingxiu");
	setup();
}


