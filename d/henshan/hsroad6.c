// Room: /d/henshan/hsroad6.c �ּ���
// Modified by Java on Feb.14.1998
inherit ROOM;

void create()
{
	set("short", "�ּ���");
	set("long", @LONG
������һ���ּ����������������ѡ������Ǻ��Ͼ��ڡ�������
������·���пɹ�·����Ϣ��С��ͤ��
LONG );
	set("outdoors", "hengyang");

	set("exits", ([
		"east"   : __DIR__"chating",
		"north"  : __DIR__"hsroad7",
		"south"  : __DIR__"hsroad5",
	]));

	setup();
}
