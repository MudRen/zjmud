// Room: /city/yaopu_neishi1.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "��ҩ��");
	set("long", @LONG
����ҩ�̵�ҩ�ң�һ��ŨŨ��ҩζ���㼸����Ϣ�����Ǵ�ҩ���ϵļ��ٸ�С
������ɢ�������ġ�һ��С���վ�ڹ�̨���к��Ź˿͡�
LONG );
	
	set("objects", ([
		__DIR__"npc/sell_yao1" : 1,
	]));
	set("no_fight", 1);     
	set("no_sleep_room", 1);
	set("exits", ([
		"west" : __DIR__"yaopu_neishi",
	]));
	setup();
}
