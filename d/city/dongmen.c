// Room: /city/dongmen.c
inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���Ƕ����ţ��������Ϸ����š����š�����������֣���ǽ�����ż���
�ٸ���ʾ��һ����ֱ����ʯ���������������졣�����ǽ��⣬�����ǳ��������һƬïʢ�������֡�
LONG );
	set("outdoors", "city");
	set("item_desc", ([
		"����ʾ��" : (: look_gaoshi :),
	]));
	set("exits", ([
		"east" : "/d/taishan/yidao",
		"north" : __DIR__"ml1",
		"south" : __DIR__"jiaowai1",
		"west" : __DIR__"dongdajie2",
	]));
	set("objects", ([
		__DIR__"npc/wujiang" : 1,
		__DIR__"npc/bing" : 2,
	]));

	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��ҩ��\n";
}

