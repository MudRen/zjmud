// Room: /d/quanzhou/jxnanmen.c
inherit ROOM;

void create()
{
	set("short", "��������");
	set("long", @LONG
�����Ǽ��˵����š���Χ����ï�ܵ����֡������������
���Ͽ��븣�������Ͼ��Ǻų����õĺ��ݳ��ˡ�
LONG );
	set("exits", ([
		"north"    : __DIR__"jiaxing",
		"east"     : __DIR__"tieqiang",
		"south"    : __DIR__"qzroad4",
		"southwest": __DIR__"majiu2",
		"southeast": "/d/hangzhou/road1",
	]));
	set("outdoors", "jiaxing");
	setup();
}

