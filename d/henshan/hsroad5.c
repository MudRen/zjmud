// Room: /d/henshan/hsroad5.c �ּ���
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
	set("short", "�ּ���");
	set("long", @LONG
������һ���ּ����������Ǻ��Ͼ��ڡ��ϱ�ͨ�������һ��
ɽ�ڡ�·���������Կ���һ�ǳ�ǽ��������һ���Ͷ�ɽ�֡�
LONG );
	set("outdoors", "hengyang");

	set("exits", ([
		"west"     : "/d/motianya/mtroad1",
		"east"     : __DIR__"hsroad4",
		"north"    : __DIR__"hsroad6",
		"southup"  : __DIR__"hsroad9",
	]));

	setup();
}

