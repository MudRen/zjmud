// wuchang2.c

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
�����ǻ�ɽ�ɵ����䳡���������⼸��ľ�ˣ���������һ�����䳡��
�����ǻ�ɽ�ĵ����������������ַǷ���
LONG );
	set("exits", ([ /* sizeof() == 2 */
	    "south"     : __DIR__"wuchang1",
	]));
	set("objects", ([
	    "/clone/npc/mu-ren" : 4,
	]));
	set("outdoors", "huashan" );
	set("for_family", "��ɽ��");

	setup();
}

