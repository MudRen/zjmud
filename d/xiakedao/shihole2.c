// /d/xiakedao/shihole2.c ���͵� ʯ��2

inherit ROOM;

void create()
{
	set("short", "ʯ��");
	set("long", @LONG
�˶�ͨ��ڶ���ʯ�ҡ�����ˮ�����ȣ�����ǡ��һ��ɽȪ������
�м��ĸ������������ʯ�ڡ�Ʈ�����ơ������������ɫ�᣻��ơ�
�������µ���������
LONG );
	set("exits", ([
		"out"   : __DIR__"shihole1",
		"enter" : __DIR__"shihole3",
		"north" : __DIR__"shiroom05",
		"south" : __DIR__"shiroom06",
		"east"  : __DIR__"shiroom07",
		"west"  : __DIR__"shiroom08",
	]));
	set("objects", ([
		__DIR__"npc/maliu": 1,
	]));
	setup();
}