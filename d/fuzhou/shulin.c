// Room: /d/fuzhou/shulin.c
inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ڸ��ݶ����������С�����ʱʱ���������������
��������ƺ���һС������һɽ��������ġ�����ƽ̹
ƽԭ�ϡ�
LONG );
	set("exits", ([
		"north"  : __DIR__"wuxiang",
		"eastup" : __DIR__"gushan",
		"west"   : __DIR__"dongmen",
	]));
	set("outdoors", "fuzhou");
	setup();
}

