// Room: /city/xsmidao.c
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
		"up"   : __DIR__"dangpu",
		"west" : __DIR__"xsmidao1",
	]));

	setup();
}
