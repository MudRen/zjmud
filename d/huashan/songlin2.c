// Room: /d/huashan/songlin2.c

inherit ROOM;

void create()
{
	set("short", "������");
	set("long", @LONG
����һƬ�����֡����ɸߵ������������飬�ڵò������ա�����
�������룬�в�֪����Ұ��͵͵�ӹ�������һƬ�ž���
LONG );
	set("exits", ([
		"south" : __DIR__"songlin" + (random(4) + 1),
		"north" : __DIR__"songlin" + (random(4) + 1),
		"east"  : __DIR__"songlin" + (random(4) + 1),
		"west"  : __DIR__"songlin3",
	]));

	set("outdoors", "huashan");
	setup();
}


