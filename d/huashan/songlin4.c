// Room: /d/huashan/songlin3.c

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
		"north" : __DIR__"songlin1",
		"east"  : __DIR__"songlin" + (random(4) + 1),
		"west"  : __DIR__"songlin" + (random(4) + 1),
	]));
	set("objects", ([
		__DIR__"npc/lin-pingzhi": 1,
	]));

	set("outdoors", "huashan");
	setup();
}

