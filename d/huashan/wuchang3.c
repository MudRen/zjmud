// wuchang3.c

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
�����ǻ�ɽ�ɵ����䳡���������⼸��ľ�ˣ��ش�ƫƧ����Щ������
LONG );
	set("exits", ([ /* sizeof() == 2 */
	    "west"     : __DIR__"wuchang1",
	]));
	set("objects", ([
	    "/clone/npc/mu-ren" : 3,
	]));
	set("outdoors", "huashan");

	set("for_family", "��ɽ��");

	setup();
}

