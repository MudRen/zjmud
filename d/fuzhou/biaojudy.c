// Room: /city/biaojudy.c
inherit ROOM;

void create()
{
	set("short", "�ھִ�Ժ");
	set("long", @LONG
��Ժ���Ե���Щ���ң������ֺ���ʦ�ǽ����������ƺ�
����������æµ��ʲô��һ�úܴ����������Ժ�����룬��
�������ĸ��ݴ���һ����ˬ��
LONG );
	set("exits", ([
		"south"   : __DIR__"biaoju",
		"north" : __DIR__"biaojuzt",
	]));
	set("objects", ([
		__DIR__"npc/shi" : 1,
	]));
	set("outdoors", "fuzhou");
	setup();
}

