// Room: /city/xidajie2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "�����");
	set("long", @LONG
������������ϣ��е�����Ľ���Ҫ�ȱ𴦵ĸɾ������ࡣ�����Ϊ����
���š���Ӫ���ܱ�����Ե�ʣ������Ƕ�ϲ��ס������ϱ���һ����ݣ�������һ�������ûʵĴ�լ
Ժ��
LONG );
	set("outdoors", "city");
	set("no_clean_up", 0);
	set("exits", ([
		"east"  : __DIR__"xidajie1",
		"north" : "/d/city/wuguan/menlang",
		"west"  : __DIR__"ximen",
		"south" : __DIR__"caizhu",
	]));

	set("objects", ([
		"/d/quanzhen/npc/youfang": 1,
	]));

	setup();
}

