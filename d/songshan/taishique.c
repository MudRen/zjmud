
// Room: /d/songshan/taishique.c
inherit ROOM;

void create()
{
	set("short", "̫����");
	set("long", @LONG
��ɽ�ųƷ��⣬�ֳƳ�ɽ��Ϊ�����е���������̫�����Ҷ�ɽ��
����ɡ������ʱ�� "�Ը�" ��ȡ��ʫ�� "����ά�ߣ���������" ��
������֮Ϊ����С���졣�׸����࣬����� "����̫������" ���֣�
׭�Ĺ��ӣ��Ծ���������������ȥ����ɽ�����µ�·������һ�����
���������ˣ�������һС�ݡ�
LONG );
	set("exits", ([
		"north" : __DIR__"tianzhongge",
		"east"  : "/d/shaolin/ruzhou",
		"west"  : "/d/shaolin/shijie1",
		"south" : "/d/shaolin/maowu",
	]));
	set("outdoors", "songshan");
	set("objects", ([
		__DIR__"npc/yao" : 1,
	]));
	setup();
}

