// Room: /city/yaopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "����ҩ����");
	set("long", @LONG
����ҩ�����ң�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵļ��ٸ�С
������ɢ�������ġ�һ��С���վ�ڹ�̨���к��Ź˿͡�
LONG );
	
	set("objects", ([
		__DIR__"npc/sell_yao" : 1,
	]));
	set("no_fight", 1);     
	set("no_sleep_room", 1);
	set("exits", ([
		 "south" : __DIR__"yaopu",
		 "east" : __DIR__"yaopu_neishi1",
		 "west" : __DIR__"yaopu_neishi2",
		 "north" : __DIR__"yaopu_neishi3",
	]));
	setup();
}
