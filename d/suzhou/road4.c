// Room: /d/suzhou/road4.c
// Date: May 31, 98  Java

inherit BUILD_ROOM;

void create()
{
	set("short", "��ʯ�ٵ�");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ������
������ҴҶ��������������һЩС��̯���ƺ���һ�����С�
����������ݳ��ˡ�������ͨ��ɽ�¡�
LONG );
	set("outdoors", "suzhou");
	set("exits", ([
		"northwest" : __DIR__"hanshansi",
		"east"      : __DIR__"road3",
	]));

	set("max_room", 3);

	setup();
	replace_program(BUILD_ROOM);
}
