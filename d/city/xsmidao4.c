// Room: /city/xsmidao4.c
// YZC 1995/12/04 

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
		"southeast" : __DIR__"xsmidao3",
		"west" : __DIR__"xsmidao5",
	]));

	setup();
}
