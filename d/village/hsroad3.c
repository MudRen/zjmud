// hsroad3.c
inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
һ���ӿ����ݵ���·������������ͨ��ɽ�
LONG );
	set("outdoors", "village");
	set("exits", ([
		"southeast" : __DIR__"hsroad2",
		"north"     : __DIR__"sexit",
	]));
	set("objects", ([
		"/d/taishan/npc/tangzi" : 4,
	]));

	setup();
}

