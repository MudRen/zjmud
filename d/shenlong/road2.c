
inherit ROOM;

void create()
{
	set("short", "ɽ��");
	set("long", @LONG
����һ����խ��ɽ�������ű���һ��ɽ����ȥ��ת���˼���ɽ�£�̧
ͷң���嶥���ż��������ݡ�
LONG );
	set("exits", ([
		"north" : __DIR__"damen",
		"south" : __DIR__"road",
	]));
	set("objects", ([
		__DIR__"npc/dizi": random(4),
		__DIR__"npc/old": random(3),
	]) );
	setup();
}


