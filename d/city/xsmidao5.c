// Room: /city/xsmidao5.c
inherit ROOM;

void create()
{
	set("short", "ѩɽ���ܵ�");
	set("long", @LONG
����ѩɽ�µ�ɮ��Ϊ�˷���������ԭ���ص����õ��ܵ����Ա���
��֪��������������
LONG
	);

	set("exits", ([
		"east" : __DIR__"xsmidao4",
		"up"   : "/d/xueshan/mishi",
	]));

	setup();
}
