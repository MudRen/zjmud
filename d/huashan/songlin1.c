// Room: /d/huashan/songlin1.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����һƬ�����֡����ɸߵ������������飬�ڵò������ա�����
�������룬�в�֪����Ұ��͵͵�ӹ�������һƬ�ž���
LONG );
	set("exits", ([
		"south" : __DIR__"changlang",
		"north" : __DIR__"songlin" + (random(4) + 1),
		"east"  : __DIR__"songlin2",
		"west"  : __DIR__"songlin" + (random(4) + 1),
	]));

	set("outdoors", "huashan");
	setup();
}

