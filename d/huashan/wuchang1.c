// wuchang1.c

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
�����ǻ�ɽ�ɵ����䳡���������⼸��ľ�ˣ�����ͨ��㳡����������һ
�����䳡������Ҳ��һ�����䳡�����ǲ�֪��ô�ģ��ƺ��������˹�ȥ������
�����ǻ�ɽ�ĵ����������������ַǷ���
LONG );
	set("exits", ([ /* sizeof() == 2 */
	    "southwest" : __DIR__"square",
	    "north"     : __DIR__"wuchang2",
	    "east"      : __DIR__"wuchang3",
	]));
	set("objects", ([
	    "/clone/npc/mu-ren" : 4,
	]));
	set("outdoors", "huashan" );
	set("for_family", "��ɽ��");

	setup();
}

