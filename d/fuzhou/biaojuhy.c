// Room: /city/biaojuhy.c
inherit ROOM;

void create()
{
	set("short", "�ھֺ�Ժ");
	set("long", @LONG
�ھֺ�Ժ��ƽ����ʦ�Ǵ�ȭ����֮�������˼���ľ׮ʯ
���⣬�������
LONG );
	set("exits", ([
		"south" : __DIR__"biaojuzt",
	]));
	set("objects", ([
		__DIR__"npc/zheng" : 1,
	]));
	set("outdoors", "fuzhou");
	setup();
}

