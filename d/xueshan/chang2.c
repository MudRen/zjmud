// chang.c ���䳡
// Designed by secret (����)
// 97/04/09

inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
������ѩɽ�µĴ����䳡�����źö�ľ׮��ɳ����ɮ
�����ճ����ڴ˿̿�ϰ�䡣�������ǹ㳡������һֱ����
�����䳡�и�С�ⷿ��
LONG );
	set("outdoors", "xueshan");

	set("exits", ([
		"east" : __DIR__"guangchang",
		"west" : __DIR__"chang",
	]));

	set("objects", ([
		    __DIR__"npc/x_lama" : 1,
	    "/clone/npc/mu-ren" : 4,
	]));

	setup();
}

