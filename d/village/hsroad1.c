// hsroad1.c
inherit BUILD_ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������������ҴҶ�����
���������һЩС��̯���ƺ���һ�����С��ϱ�ͨ�����ݳǡ�
LONG );
	set("outdoors", "village");

	set("exits", ([
		"north" : __DIR__"hsroad2",
		"south" : "/d/changan/road2",
	]));
	set("max_room", 8);
	set("objects", ([
		__DIR__"npc/girl" : 4,
	]));

	setup();
	replace_program(BUILD_ROOM);
}

