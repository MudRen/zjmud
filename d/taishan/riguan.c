// Room: /d/taishan/.c
inherit ROOM;

void create()
{
	set("short", "�չ۷�");
	set("long", @LONG
������λ�������������ɽ�룬��ʯ�ܴأ���ߵĵط�һʯ
׿������Ϊ���ӷ塣�����߱���̩ɽ�������š�
LONG );
	set("exits", ([
		"westup" : __DIR__"yuhuang",
		"eastup" : __DIR__"tanhai",
	]));
	set("objects", ([
		__DIR__"npc/tianmen" : 1,
	]));
	set("no_clean_up", 0);
	setup();
}

