// Room: /city/yaopu_neishi2.c
// YZC 2010/02/16 

inherit ROOM;

void create()
{
	set("short", "��ҩ��");
	set("long", @LONG
����ҩ�̵���ҩ�ң�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵļ��ٸ�С
������ɢ�������ġ�һ��С���վ�ڹ�̨���к��Ź˿͡�

LONG );
	set("objects", ([
		__DIR__"npc/sell_yao2" : 1,
	]));
	set("no_fight", 1);     
	set("no_sleep_room", 1);
	set("exits", ([
		"east" : __DIR__"yaopu_neishi",

	]));
	setup();
}
