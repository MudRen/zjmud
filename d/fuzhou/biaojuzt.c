// Room: /d/fuzhou/biaojuzt.c
// Date: may.12 1998 Java

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����Ǹ����ھֵ���������ֻ̫ʦ��һ���ſ���������
��������ͷ���ֳ��̴������ڱ�Ŀ��˼��ǽ�Ϲ��ż����ֻ�
��һ�ѱ�����
LONG );
	set("exits", ([
		"north" : __DIR__"biaojuhy",
		"south" : __DIR__"biaojudy",
		"west"  : __DIR__"biaojunz",
	]));
	set("objects", ([
		__DIR__"hubiao/linzhennan" : 1,
	]));
	setup();
}

