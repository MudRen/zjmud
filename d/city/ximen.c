// Room: /city/ximen.c
inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���������ţ�����ǰ�����⵽���˵Ĺ�������Ե���Щ�ưܡ���������
������ǿǿ�����ϳ������š��������֣���ǽ�����ż���ͨ����ʾ��
һ����ֱ����ʯ���������������졣�����ǽ��⣬�����ǳ��
LONG );
	set("outdoors", "city");
	set("item_desc", ([
		"����ʾ��" : (: look_gaoshi :),
	]));

	set("exits", ([
		"east"  : __DIR__"xidajie2",
		"west"  : __DIR__"ximenroad",
	]));
	set("objects", ([
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
		"/d/mingjiao/npc/fenggongying" : 1,
	]));
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��ҩ��\n";
}

