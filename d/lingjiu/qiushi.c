// ROOM qiushi.c

inherit ROOM;
void create()
{
	set("short", "����");
	set("long",@LONG
���ǡ����չ�����Ѻ���˵ĵط������й��߻谵����ζ���š�
LONG );
	set("exits", ([
		"east" : __DIR__"men1",
	]));

	setup();
}
