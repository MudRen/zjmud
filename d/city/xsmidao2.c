// Room: /city/xsmidao2.c
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
		"east" : __DIR__"xsmidao1",
		"northwest" : __DIR__"xsmidao3",
	]));

	setup();
}
