// Room: /d/songshan/dadian.c
inherit ROOM;

void create()
{
	set("short", "�������");
	set("long", @LONG
��������ż䣬������䣬�����е�ʽ�ݶ����������߳߸ߵ�̨
���ϣ�������ΰ������й���������������
LONG );
	set("exits", ([
		"northup" : __DIR__"shandao1",
		"south"   : __DIR__"chongsheng",
	]));
	set("no_clean_up", 0);
	setup();
}

