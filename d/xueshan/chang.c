// chang.c ���䳡
inherit ROOM;

void create()
{
	set("short", "�����䳡");
	set("long", @LONG
������ѩɽ�µĴ����䳡�����źö�ľ׮��ɳ����ɮ
�����ճ����ڴ˿̿�ϰ�䡣�����ߴ������������䳡����
�㳡�������и�С�ⷿ���ϱ�һ��Ƭ�����أ�����ѩɽ��
�����ڵļ�̳�ˡ�
LONG );
	set("outdoors", "xueshan");

	set("exits", ([
		"east" : __DIR__"chang2",
		"west" : __DIR__"kufang",
		"north" : __DIR__"chang3",
		"south" : __DIR__"jitan",
	]));

	set("objects", ([
		__DIR__"npc/x_lama" : 1,
	    	"/clone/npc/mu-ren" : 4,
	]));

	setup();

}
