// Room: /city/menpai-jieyin.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "���ɰ��´�");
	set("long", @LONG
����װ�޺��������ɰ��´���������������ŵ��ӻ����ɵ��ӿ�����������!!!
LONG );
	set("no_fight", 1);     
	set("no_sleep_room", 1);
	set("exits", ([		
		"west" : __DIR__"majiu",
	]));

	set("objects", ([
		__DIR__"npc/jieyin-shi" : 1,
	]));
	setup();
}

