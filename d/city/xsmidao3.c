// Room: /city/xsmidao3.c
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
		"southeast" : __DIR__"xsmidao2",
		"northwest" : __DIR__"xsmidao4",
	]));

	setup();
}
