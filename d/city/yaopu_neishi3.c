// Room: /city/yaopu.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "��ҩ��");
	set("long", @LONG
����ҩ�̵ı�ҩ�ң�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵļ��ٸ�С
������ɢ�������ġ�һ��С���վ�ڹ�̨���к��Ź˿͡�
LONG );
	
	set("objects", ([
		__DIR__"npc/sell_yao3" : 1,
	]));
	set("no_fight", 1);     
	set("no_sleep_room", 1);
	set("exits", ([
		"south" : __DIR__"yaopu_neishi",

	]));
	setup();
}
