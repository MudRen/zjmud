// Room: /d/village/nwhouse.c

inherit ROOM;

void create()
{
	set("short", "��");
	set("long", @LONG
����һ��С���䣬������Ʈ��һ�ɴ�м���۵�ζ������ǽ�����Ŵ�
������ͷ�и�С��ױ̨��
LONG );
	set("exits", ([ /* sizeof() == 1 */
	    "northeast" : __DIR__"nwroad2",
	]));
	set("objects", ([
		__DIR__"npc/cuihua": 1
	]) );

	setup();
}
 
